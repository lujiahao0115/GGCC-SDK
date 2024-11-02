// word_process.h
// ggcc文字处理库

#ifndef GGCC_TO_UTF8_H
#define GGCC_TO_UTF8_H

#include <bits/stdc++.h>

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
		int GetStringLength(std::string str) {
			return str.size() - GetChineseCharacterCount(str);
		}
		int strLen(std::string str) {
			int count = 0, i = 0;
			while (i < str.size()) {
				if ((str[i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((str[i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((str[i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((str[i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
			}
			return count;
		}

		// 输入输出相关功能
		int Index2Cursor(std::vector<std::string>& input, int line, int index) {
			if (line >= input.size())return 0;
			return wp::strLen(input[line].substr(0, index));
		}
		int Cursor2Index(std::vector<std::string>& input, int line, int cursor) {
			if (line >= input.size())return 0;
			if (cursor == 0)return 0;
			int count = 0, i = 0;
			while (i < input[line].size()) {
				if ((input[line][i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((input[line][i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((input[line][i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((input[line][i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
				if (count >= cursor)return i;
			}
			return input[line].size();
		}
		int GetPreCharacter(std::vector<std::string>& input, int line, int index) {
			if (index == 0)return 0;
			int tindex = index;
			index--;
			while (index >= 0) {
				if (input[line][index] >= -128 && input[line][index] <= -65)index--;
				else break;
			}
			return tindex - index;
		}
		int GetNextCharacter(std::vector<std::string>& input, int line, int index) {
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
				if ((input[i] & 0xF8) == 0xF8)i += 5, count += 2;
				else if ((input[i] & 0xF0) == 0xF0)i += 4, count += 2;
				else if ((input[i] & 0xE0) == 0xE0)i += 3, count += 2;
				else if ((input[i] & 0xC0) == 0xC0)i += 2, count += 2;
				else i++, count++;
				if (count >= cursor)return i;
			}
			return input.size();
		}
		int GetPreCharacter(std::string& input, int index) {
			if (index == 0)return 0;
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
			} else {
				str += char(a / 4096 + 224);
				str += char(a % 4096 / 64 + 128);
				str += char(a % 64 + 128);
			}
			return str;
		}
		inline std::string GetChar(int a) {
			return Unicode_UTF8(a);
		}
	}
}

#endif
