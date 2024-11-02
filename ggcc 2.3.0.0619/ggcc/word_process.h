// to_utf8.h
// ggcc编码转换库

#ifndef GGCC_TO_UTF8_H
#define GGCC_TO_UTF8_H

#include <string>

namespace ggcc {
	namespace wp {
		std::string GetChar(int a) {
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

		class TextBuffer {
		private:
			std::string text;
			bool change = false;
		public:
			TextBuffer(std::string str = "") {
				text = str;
			}
			std::string Text() {
				return text;
			}
			void Add(std::string str) {
				if (str == "")return;
				text += str;
				change = true;
			}
			void Clear() {
				text = "";
				change = true;
			}
			void Set(std::string str) {
				text = str;
				change = true;
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
					if (text.find(t) == -1)Add(t);
					i += count;
				}
			}
			bool Change() {
				if (change) {
					change = false;
					return true;
				}
				return false;
			}
		};
		
		// 字符串格式化功能
		std::string CheckStringNest(std::string a) {
			std::string b;
			for(int i=0;i<a.size();i++) {
				if(a[i]=='\'')b+="\\",b+=a[i];
				else if(a[i]=='\"')b+="\\",b+=a[i];
				else if(a[i]=='\\')b+="\\",b+=a[i];
				else b+=a[i];
			}
			return b;
		}
	}
}

#endif
