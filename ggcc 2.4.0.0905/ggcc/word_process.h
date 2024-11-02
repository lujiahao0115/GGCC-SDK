// word_process.h
// ggcc文字处理库

#ifndef GGCC_WORD_PROCESS_H
#define GGCC_WORD_PROCESS_H

#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <vector>

namespace ggcc {
	namespace wp {

		class TextBuffer {
		private:
			std::string text;
			std::string basic;
			std::map <std::string, bool> used;
			std::map <std::string, bool> load;
			bool change = false;
			int basic_maximum = 1000;
			int maximum = 1000;
			int load_sum = 0;
		public:
			TextBuffer(std::string str = "") {
				used.clear();
				Check(str);
				basic = str;
			}
			std::string Text() {
				return text;
			}
			void SetMaximum(int maxn) {
				basic_maximum = maxn;
			}
			int GetMaximum() {
				return maximum;
			}
			void Clear() {
				text = "";
				change = true;
				used.clear();
			}
			void CheckChar(std::string str) {
				if (used[str] == false) {
					used[str] = true;
					text += str;
					change = true;
				}
				if (load[str] == false) {
					load[str] = true;
					load_sum += str.size();
				}
			}
			void Check(std::string str) {
				int count = 0, i = 0;
				while (i < str.size()) {
					if ((str[i] & 0xF8) == 0xF8)count = 5;
					else if ((str[i] & 0xF0) == 0xF0)count = 4;
					else if ((str[i] & 0xE0) == 0xE0)count = 3;
					else if ((str[i] & 0xC0) == 0xC0)count = 2;
					else count = 1;
					std::string t = str.substr(i, count);
					CheckChar(t);
					i += count;
				}
			}
			void Set(std::string str) {
				text = "";
				change = true;
				used.clear();
				Check(str);
			}
			bool Change() {
				if (change) {
					change = false;
					return true;
				}
				return false;
			}
			void Update() {
				if (text.size() > maximum) {
					if (load_sum > maximum) {
						maximum *= 1.5;
					} else Set(basic);
				}
				if (text.size() < maximum * 0.35) {
					maximum /= 2;
					if (maximum < basic_maximum)maximum = basic_maximum;
				}
				load.clear();
				load_sum = 0;
				Check(basic);
			}
		};

		// 字符串相关功能
		std::string CheckStringNest(std::string a) {
			std::string b;
			for (int i = 0; i < a.size(); i++) {
				if (a[i] == '\'')b += "\\", b += a[i];
				else if (a[i] == '\"')b += "\\", b += a[i];
				else if (a[i] == '\\')b += "\\", b += a[i];
				else b += a[i];
			}
			return b;
		}
		int GetChineseCharacterCount(std::string str) {
			int len = str.size();
			int count = 0;
			int i = 0;
			while (i < len) {
				if ((str[i] & 0xE0) == 0xE0)count++, i += 3;
				else i++;
			}
			return count;
		}
		int strLen(std::string str) {
			if (str.size() == 0)return 0;
			int count = 0, i = 0;
			while (i < str.size()) {
				if (str[i] == '\t')i++, count = floor(count / 4.0) * 4 + 4;
				else if ((str[i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((str[i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((str[i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((str[i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
			}
			return count;
		}
		template <typename T>
		std::string tostr(T text) {
			std::stringstream ss;
			ss << text;
			return ss.str();
		}

		// 输入输出相关功能
		int Index2Cursor(std::vector<std::string>& input, int line, int index) {
			if (index <= 0)return 0;
			if (line >= input.size())return 0;
			return wp::strLen(input[line].substr(0, index));
		}
		int Cursor2Index(std::vector<std::string>& input, int line, int cursor) {
			if (line >= input.size())return 0;
			if (cursor <= 0)return 0;
			int count = 0, i = 0;
			while (i < input[line].size()) {
				if (input[line][i] == '\t')i++, count = floor(count / 4.0) * 4 + 4;
				else if ((input[line][i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((input[line][i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((input[line][i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((input[line][i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
				if (count >= cursor)return i;
			}
			return input[line].size();
		}
		int GetPreCharacter(std::vector<std::string>& input, int line, int index) {
			if (index <= 0)return 0;
			int tindex = index;
			index--;
			while (index >= 0) {
				if (input[line][index] >= -128 && input[line][index] <= -65)index--;
				else break;
			}
			return tindex - index;
		}
		int GetNextCharacter(std::vector<std::string>& input, int line, int index) {
			if (index < 0)return 0;
			if (index >= input[line].size())return 0;
			if ((input[line][index] & 0xF8) == 0xF8)return 5;
			else if ((input[line][index] & 0xF0) == 0xF0)return 4;
			else if ((input[line][index] & 0xE0) == 0xE0)return 3;
			else if ((input[line][index] & 0xC0) == 0xC0)return 2;
			else return 1;
		}
		int Index2Cursor(std::string& input, int index) {
			return wp::strLen(input.substr(0, index));
		}
		int Cursor2Index(std::string& input, int cursor) {
			if (cursor <= 0)return 0;
			int count = 0, i = 0;
			while (i < input.size()) {
				if (input[i] == '\t')i++, count = floor(count / 4.0) * 4 + 4;
				else if ((input[i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((input[i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((input[i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((input[i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
				if (count >= cursor)return i;
			}
			return input.size();
		}
		int GetPreCharacter(std::string& input, int index) {
			if (index <= 0)return 0;
			int tindex = index;
			index--;
			while (index >= 0) {
				if (input[index] >= -128 && input[index] <= -65)index--;
				else break;
			}
			return tindex - index;
		}
		int GetNextCharacter(std::string& input, int index) {
			if (index >= input.size())return 0;
			if ((input[index] & 0xF8) == 0xF8)return 5;
			else if ((input[index] & 0xF0) == 0xF0)return 4;
			else if ((input[index] & 0xE0) == 0xE0)return 3;
			else if ((input[index] & 0xC0) == 0xC0)return 2;
			else return 1;
		}

		// 文字处理功能
		int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount) {
			int codepointsNoDupsCount = codepointCount;
			int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
			memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));
			for (int i = 0; i < codepointsNoDupsCount; i++) {
				for (int j = i + 1; j < codepointsNoDupsCount; j++)	{
					if (codepointsNoDups[i] == codepointsNoDups[j])	{
						for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];
						codepointsNoDupsCount--;
						j--;
					}
				}
			}
			*codepointsResultCount = codepointsNoDupsCount;
			return codepointsNoDups;
		}

		// 编码转换功能
		std::string Unicode_UTF8(int a) {
			std::string str = "";
			if (a < 128)str += char(a);
			else if (a < 4096) {
				str += char(a / 64 + 192);
				str += char(a % 64 + 128);
			} else if (a < 65536) {
				str += char(a / 4096 + 224);
				str += char(a % 4096 / 64 + 128);
				str += char(a % 64 + 128);
			} else if (a < 4194304) {
				str += char(a / 65536 + 240);
				str += char(a % 65536 / 4096 + 128);
				str += char(a % 4096 / 64 + 128);
				str += char(a % 64 + 128);
			} else {
				str += char(a / 4194304 + 248);
				str += char(a % 4194304 / 65536 + 128);
				str += char(a % 65536 / 4096 + 128);
				str += char(a % 4096 / 64 + 128);
				str += char(a % 64 + 128);
			}
			return str;
		}
		std::string Unicode_to_UTF8(uint32_t a) {
			std::string str;

			// 处理 Unicode 范围内的码点
			if (a <= 0x7F) {
				// 单字节 UTF-8
				str += static_cast<char>(a);
			} else if (a <= 0x7FF) {
				// 双字节 UTF-8
				str += static_cast<char>((a >> 6) | 0xC0);
				str += static_cast<char>((a & 0x3F) | 0x80);
			} else if (a <= 0xFFFF) {
				// 三字节 UTF-8
				// 注意：这里排除了 U+D800 到 U+DFFF 的代理对区域
				if (a >= 0xD800 && a <= 0xDFFF) return ""; // 或者抛出异常
				str += static_cast<char>((a >> 12) | 0xE0);
				str += static_cast<char>(((a >> 6) & 0x3F) | 0x80);
				str += static_cast<char>((a & 0x3F) | 0x80);
			} else if (a <= 0x10FFFF) {
				// 四字节 UTF-8
				str += static_cast<char>((a >> 18) | 0xF0);
				str += static_cast<char>(((a >> 12) & 0x3F) | 0x80);
				str += static_cast<char>(((a >> 6) & 0x3F) | 0x80);
				str += static_cast<char>((a & 0x3F) | 0x80);
			} else {
				// 超出 Unicode 范围，返回空字符串或抛出异常
				return ""; // 或者 throw std::out_of_range("Unicode code point out of range");
			}

			return str;
		}
		int UTF8_Unicode(std::string a) {
			if (a.size() == 0)return 0;
			if (a.size() == 1 && (unsigned char)a[0] <128 )return (unsigned char)a[0];
			if ((a[0] & 0xF8) == 0xF8) {
				int a0 = ((unsigned char)a[0] ^ 0xF8);
				int a1 = ((unsigned char)a[1] ^ 0x80);
				int a2 = ((unsigned char)a[2] ^ 0x80);
				int a3 = ((unsigned char)a[3] ^ 0x80);
				int a4 = ((unsigned char)a[4] ^ 0x80);
				return (a0 << 24) | (a1 << 18) | (a2 << 12) | (a3 << 6) | a4;
			}
			if ((a[0] & 0xF0) == 0xF0) {
				int a0 = ((unsigned char)a[0] ^ 0xF0);
				int a1 = ((unsigned char)a[1] ^ 0x80);
				int a2 = ((unsigned char)a[2] ^ 0x80);
				int a3 = ((unsigned char)a[3] ^ 0x80);
				return (a0 << 18) | (a1 << 12) | (a2 << 6) | a3;
			}
			if ((a[0] & 0xE0) == 0xE0) {
				int a0 = ((unsigned char)a[0] ^ 0xE0);
				int a1 = ((unsigned char)a[1] ^ 0x80);
				int a2 = ((unsigned char)a[2] ^ 0x80);
				return (a0 << 12) | (a1 << 6) | a2;
			}
			if ((a[0] & 0xC0) == 0xC0) {
				int a0 = ((unsigned char)a[0] ^ 0xC0);
				int a1 = ((unsigned char)a[1] ^ 0x80);
				return (a0 << 6) | a1;
			}
			return 0;
		}
		uint32_t UTF8_to_Unicode(const std::string& a) {
			if (a.empty()) return 0;

			// 处理 ASCII 字符
			if (a.size() == 1 && static_cast<unsigned char>(a[0]) < 0x80) {
				return static_cast<unsigned char>(a[0]);
			}

			// 验证 UTF-8 字节序列的起始字节
			unsigned char firstByte = static_cast<unsigned char>(a[0]);
			if ((firstByte & 0xF8) == 0xF0) { // 4 字节 UTF-8
				if (a.size() < 4) return 0; // 长度不足
				return ((firstByte & 0x07) << 18) |
				((static_cast<unsigned char>(a[1]) & 0x3F) << 12) |
				((static_cast<unsigned char>(a[2]) & 0x3F) << 6) |
				(static_cast<unsigned char>(a[3]) & 0x3F);
			} else if ((firstByte & 0xF0) == 0xE0) { // 3 字节 UTF-8
				if (a.size() < 3) return 0; // 长度不足
				return ((firstByte & 0x0F) << 12) |
				((static_cast<unsigned char>(a[1]) & 0x3F) << 6) |
				(static_cast<unsigned char>(a[2]) & 0x3F);
			} else if ((firstByte & 0xE0) == 0xC0) { // 2 字节 UTF-8
				if (a.size() < 2) return 0; // 长度不足
				return ((firstByte & 0x1F) << 6) |
				(static_cast<unsigned char>(a[1]) & 0x3F);
			}

			// 如果不匹配任何 UTF-8 编码模式，则返回 0 或抛出异常
			return 0;
		}
		inline std::string GetChar(int a) {
			return Unicode_to_UTF8(a);
		}

		// 字体相关功能
		bool IsIcon(int a) {
			if (a >= 58911 && a <= 63692)return true;
			else return false;
		}
		bool IsIcon(std::string a) {
			return IsIcon(UTF8_to_Unicode(a));
		}
		bool IsEmoji(int a) {
			if(IsIcon(a))return false;
			if (a >= 0x1F300 && a <= 0x1F6FF)return true;
			if (a >= 0x1F900 && a <= 0x1FAFF)return true;
			else return false;
		}
		bool IsEmoji(std::string a) {
			return IsEmoji(UTF8_to_Unicode(a));
		}

		// 进制相关功能
		std::string tobin(int a) {
			std::string ans = "";
			int t = 0;
			while (a) {
				int x = a % 2;
				a /= 2, t++;
				if (x == 0)ans = "0" + ans;
				else ans = "1" + ans;
				if (t % 8 == 0 && a)ans = "," + ans;
			}
			return ans;
		}
		std::string tobin(std::string a) {
			std::string ans;
			for(int i=0;i<a.size();i++) {
				ans += tobin((unsigned char)a[i]) + "|";
			}
			return ans;
		}

	}
}

#endif
