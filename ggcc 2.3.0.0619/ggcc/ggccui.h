// ggccui.h
// ggcc用户界面库（调试器风格）（raylib）

#ifndef GGCCUI_H
#define GGCCUI_H

// 以下是当前版本号
#define UIVer "GGCC UI 2.3.0.0619"

#include <bits/stdc++.h>
#include <raylib.h>
#include <rlgl.h>
#include <ggcc/animation.h>
#include <ggcc/math/point.h>
#include <ggcc/math/geometry.h>
#include <ggcc/word_process.h>

namespace ggcc {

	namespace ui {

		// 重要定义
		enum Position {
			pos_full = 0,
			pos_mid,
			pos_left,
			pos_right
		};
		enum SiderPosition {
			spos_left = 0,
			spos_right = 1,
			spos_top = 2,
			spos_bottom = 3
		};
		enum SplitStyle {
			split_main = 1,
			split_row = 2,
			split_col = 5
		};
		enum WinState {
			state_static = 0,
			state_moving = 1,
			state_resizing = 2,
		};

		// 参数
		int TextHeight = 16;							// 字符高度
		int UnitHeight = 20;							// 单元格高度
		int SpaceSize = 5;								// 空白长度
		int SliderWidth = 15;							// 滚动条宽度
		int ScissorDeep = 0;							// 剪切深度
		realn Alpha = 1;								// 透明度
		int AlphaDeep = 0;								// 透明度栈深度
		std::stack<realn> AlphaStack;					// 透明度栈
		Vector2 ScissorPoint[64];						// 剪切起始位置
		Vector2 ScissorSize[64];						// 剪切大小
		Vector2 DPI = Vector2 {1, 1};					// dpi
		int tick = 0;									// 运行刻
		double Scale = 1.0;								// 放大率
		Font font;										// 字体
		Font IconFont;									// 图标字体
		std::string Icons;								// 图标集
		int winW;										// 窗口宽
		int winH;										// 窗口高
		Vector2 Mouse;									// 鼠标位置
		Vector2 MouseShadow;							// 鼠标残影位置
		Vector2 WindowPos;								// 窗口位置
		Vector2 WindowSize;								// 窗口大小
		Vector2 LastWindowPos;							// 上次窗口位置
		Vector2 LastWindowSize;							// 上次更新时窗口大小
		WinState WindowState;							// 窗口状态
		Color MainColor = Color {43, 74, 121, 255};		// 主题色
		Color UnitBgColor = Color {43, 74, 121, 150};	// 单元格背景色
		Color ChooseColor = Color {132, 132, 132, 50};	// 选择背景色
		Color BgColor = Color {32, 32, 32, 220};		// 背景色
		Color TextColor = WHITE;						// 字体色
		Color TextColor2 = LIGHTGRAY;					// 辅助字体色
		char GetChar = 0;								// 字符输入
		std::string GetCharString = "";					// 字符输入
		int MouseCursorStyle = MOUSE_CURSOR_ARROW;		// 鼠标样式
		bool AutoInterface = true;						// 是否开启自动添加至主界面
		bool DrawSpecialEffect = true;					// 是否开启特效
		bool DebugMode = false;							// 是否开启调试模式
		bool StartAni = true;							// 是否开启启动动画
		bool Running = true;							// 程序是否在运行
		bool UseSliderX = false;						// 是否有Slider正在使用
		bool UseSliderY = false;						// 是否有Slider正在使用
		bool PrintChecking = true;						// 打印检查
		bool FasterInput = false;						// 是否启用英文高速键入
		realn dpi;										// dpi
		Animation MouseXAni, MouseYAni;					// 鼠标阴影动画

		// 字体相关定义
		std::string FontName = "微软雅黑";				// 字体
		wp::TextBuffer UseCharacter{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;\':\",./<>?"};
		int fileSize;
		unsigned char *fontFileData;
		int codepointsCount;
		int *codepoints;

		// 声明(不全)
		int Init(int, int, double);						// 初始化
		void Update();									// 更新
		void BeginScissor(float, float, float, float);	// 开始剪切
		void EndScissor();								// 结束剪切
		void Print(int, int, std::string, Color c);		// 打印文本
		bool MouseInRect(realn, realn, realn, realn); 	// 鼠标是否在矩形内
		class Element;									// 元素（基类）
		class Title;									// 标题
		class Text;										// 字幕
		class Line;										// 分割线
		class Textbox;									// 文本框
		class Button;									// 按钮
		class Button2;									// 按钮（两个）
		class Button3;									// 按钮（三个）
		class Slider;									// 拉动条
		class Slider_Int;								// 拉动条(整型)
		class Switch;									// 开关
		class Choose;									// 选择框
		class Dropdown;									// 下拉内容
		class Interface;								// 界面
		class Popup;									// 弹窗
		class InputBox;									// 输入框
		class CheckBox;									// 复选框
		class System;									// 系统
		class Window;									// 窗口
		Element* ChooseInputBox = NULL;					// 选择的输入框
		Slider* ChooseSlider = nullptr;					// 选择的拉动条

		void BeginScissor(float x, float y, float w, float h);
		void GetScissor(float* x, float* y, float* w, float* h);
		bool InScissor(float x, float y, float w, float h);
		bool InScissor(float x, float y);
		void EndScissor();
		void BeginAlphaMode(realn alpha);
		void EndAlphaMode();
		realn GetAlpha();

		namespace color_theme {
			Color Color_Default 		= Color{255, 255, 255, 255};	//编辑器默认
			Color Color_Gutter 			= Color{255, 255, 255, 255};	//行号
			Color Color_Gutter_AL		= Color{255, 255, 255, 255};	//当前行号
			Color Color_Comment 		= Color{114, 112, 91, 255};		//注释
			Color Color_Symbol 			= Color{255, 255, 255, 255};	//符号
			Color Color_Bracket_L1		= Color{101, 188, 148, 255};	//1级括号
			Color Color_Bracket_L2		= Color{ 99, 148, 160, 255};	//2级括号
			Color Color_Bracket_L3 		= Color{211, 127, 81, 255};		//3级括号

			Color Color_Bracket_L4 		= Color{121, 106, 167, 255};	//4级括号
			Color Color_Number 			= Color{216, 128, 245, 255};	//数字
			Color Color_Preprocessor 	= Color{255, 36, 72, 255};		//预处理指令
			Color Color_Character 	 	= Color{216, 219, 112, 255};	//字符
			Color Color_String 		 	= Color{216, 219, 112, 255};	//字符串
			Color Color_EscapeSequences	= Color{216, 128, 245, 255};	//转义序列0x06
			Color Color_ReservedWord 	= Color{ 58, 215, 255, 255};	//关键字
			Color Color_Function 		= Color{104, 226, 53, 255};		//函数
			Color Color_Variable 		= Color{247, 248, 239, 255};	//变量
		}

		// 附属功能
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
		int GetChineseCharacterCount(const char* str) {
			int len = strlen(str);
			int count = 0;
			int i = 0;
			while (i < len) {
				if ((str[i] & 0xE0) == 0xE0) {
					count++;
					i += 3;
				} else {
					i++;
				}
			}
			return count;
		}
		int GetStringLength(std::string str) {
			return str.size() - GetChineseCharacterCount(str.c_str());
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
		// 时间相关功能
		std::string Realn2HourTime(realn time) {
			std::stringstream ss;
			std::string k = "", k2 = "";
			if (int(time) % 60 < 10)k = "0";
			if (int(time / 60) % 60 < 10)k2 = "0";
			ss << int(time / 3600) << ':' << k2 << int(time / 60) % 60 << ":" << k << int(time);
			return ss.str();
		}
		std::string Realn2MinuteTime(realn time) {
			std::stringstream ss;
			std::string k = "";
			if (int(time) % 60 < 10)k = "0";
			ss << int(time / 60) << ":" << k << int(time) % 60;
			return ss.str();
		}
		int GetTick() {
			return tick;
		}
		// 键盘输入功能
		std::map <int, short> key_state;
		std::map <int, int> key_down_time;
		std::map <int, int> key_down_tick;
		bool IsKeyInput(int key) {
			bool input = false;
			if (tick != 0 && tick == key_down_tick[key])return true;
			if (IsKeyDown(key)) {
				if (key_state[key] == 0) {
					key_state[key] = 1, input = true;
					key_down_time[key] = clock();
					key_down_tick[key] = tick;
				} else if (key_state[key] == 1) {
					if (clock() - key_down_time[key] > 500) {
						key_state[key] = 2, input = true;
						key_down_time[key] = clock();
						key_down_tick[key] = tick;
					}
				} else {
					if (clock() - key_down_time[key] > 30) {
						key_state[key] = 2, input = true;
						key_down_time[key] = clock();
						key_down_tick[key] = tick;
					}
				}
			} else key_state[key] = 0;
			return input;
		}
		// 鼠标输入功能
		std::map <int, short> mouse_state;
		std::map <int, int> mouse_down_time;
		bool IsMouseInput(int mouse) {
			bool input = false;
			if (IsMouseButtonDown(mouse)) {
				if (mouse_state[mouse] == 0) {
					mouse_state[mouse] = 1, input = true;
					mouse_down_time[mouse] = clock();
				} else if (mouse_state[mouse] == 1) {
					if (clock() - mouse_down_time[mouse] > 500) {
						mouse_state[mouse] = 2, input = true;
						mouse_down_time[mouse] = clock();
					}
				} else {
					if (clock() - mouse_down_time[mouse] > 30) {
						mouse_state[mouse] = 2, input = true;
						mouse_down_time[mouse] = clock();
					}
				}
			} else mouse_state[mouse] = 0;
			return input;
		}
		// 嵌套裁剪区功能
		void BeginScissor(float x, float y, float w, float h) {
			if (w < 0)w = 0;
			if (h < 0)h = 0;
			float x2 = x + w;
			float y2 = y + h;
			float X, Y, W, H;
			if (ScissorDeep >= 1) {
				X = ScissorPoint[ScissorDeep].x;
				Y = ScissorPoint[ScissorDeep].y;
				W = ScissorSize[ScissorDeep].x;
				H = ScissorSize[ScissorDeep].y;
			} else X = 0, Y = 0, W = winW, H = winH;
			float X2 = X + W;
			float Y2 = Y + H;
			float ax, ay, ax2, ay2, aw, ah;
			ax = std::max(0.0f, std::max(x, X));
			ay = std::max(0.0f, std::max(y, Y));
			ax2 = std::min((float)winW, std::min(x2, X2));
			ay2 = std::min((float)winH, std::min(y2, Y2));
			aw = ax2 - ax, ah = ay2 - ay;
			if (aw < 0)aw = 0;
			if (ah < 0)ah = 0;
			ScissorDeep++;
			ScissorPoint[ScissorDeep] = {(float)ax, (float)ay};
			ScissorSize[ScissorDeep] = {(float)aw, (float)ah};
			EndScissorMode();
			BeginScissorMode(ax, ay, aw, ah);
			if (DebugMode) {
				DrawRectangle(ax, ay, aw, ah, Fade(RED, 0.02));
				Print(ax, ay, to_string(vector2d{ScissorDeep, 0}), BLUE);
			}
		}
		void GetScissor(float* x, float* y, float* w, float* h) {
			if (ScissorDeep >= 1) {
				*x = ScissorPoint[ScissorDeep].x;
				*y = ScissorPoint[ScissorDeep].y;
				*w = ScissorSize[ScissorDeep].x;
				*h = ScissorSize[ScissorDeep].y;
			} else *x = 0, *y = 0, *w = winW, *h = winH;
		}
		bool InScissor(float x, float y, float w, float h) {
			float X, Y, W, H;
			GetScissor(&X, &Y, &W, &H);
			if (x + w >= X && y + h >= Y && x < X + W && y < Y + H)return true;
			return false;
		}
		bool InScissor(float x, float y) {
			float X, Y, W, H;
			GetScissor(&X, &Y, &W, &H);
			if (x >= X && y >= Y && x < X + W && y < Y + H)return true;
			return false;
		}
		void EndScissor() {
			if (ScissorDeep == 0)return;
			ScissorDeep--;
			EndScissorMode();
			if (ScissorDeep > 0) {
				float x = ScissorPoint[ScissorDeep].x;
				float y = ScissorPoint[ScissorDeep].y;
				float w = ScissorSize[ScissorDeep].x;
				float h = ScissorSize[ScissorDeep].y;
				BeginScissorMode(x, y, w, h);
			}
		}
		// 嵌套透明模式功能
		void BeginAlphaMode(realn alpha) {
			if (AlphaDeep == 0)AlphaStack.push(alpha);
			else AlphaStack.push(alpha*AlphaStack.top());
			Alpha = AlphaStack.top();
			AlphaDeep++;
			if (Alpha > 1)Alpha = 1;
			if (Alpha < 0)Alpha = 0;
		}
		void EndAlphaMode() {
			if (AlphaDeep > 0)AlphaDeep--;
			if (AlphaDeep == 0)Alpha = 1;
			else {
				AlphaStack.pop();
				Alpha = AlphaStack.top();
			}
			if (Alpha > 1)Alpha = 1;
			if (Alpha < 0)Alpha = 0;
		}
		realn GetAlpha() {
			if (Alpha > 1)Alpha = 1;
			if (Alpha < 0)Alpha = 0;
			return Alpha;
		}
		// 颜色辅助功能
		bool operator ==(const Color& a, const Color& b) {
			return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
		}
		Color ColorF(int r, int g, int b, int a) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(a*GetAlpha())};
		}
		Color ColorF(float r, float g, float b, float a) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(a*GetAlpha())};
		}
		Color ColorF(double r, double g, double b, double a) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(a*GetAlpha())};
		}
		Color ColorF(long double r, long double g, long double b, long double a) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(a*GetAlpha())};
		}
		Color ColorF(Color color) {
			return Color{(unsigned char)(color.r), (unsigned char)(color.g), (unsigned char)(color.b), (unsigned char)(color.a*GetAlpha())};
		}
		Color MixColor(Color c1, Color c2, realn k) {
			return Color{c1.r*k + c2.r*(1.0 - k), c1.g*k + c2.g*(1.0 - k), c1.b*k + c2.b*(1.0 - k), 255};
		}
		// 其他功能
		bool operator ==(const Vector2& a, const Vector2& b) {
			return a.x == b.x&&a.y == b.y;
		}
		bool operator ==(const Vector3& a, const Vector3& b) {
			return a.x == b.x&&a.y == b.y&&a.z == b.z;
		}
		bool operator !=(const Vector2& a, const Vector2& b) {
			return a.x != b.x || a.y != b.y;
		}
		bool operator !=(const Vector3& a, const Vector3& b) {
			return a.x != b.x || a.y != b.y || a.z != b.z;
		}
		bool CompareTime(int y1, int mt1, int d1, int h1, int m1, int s1,
		                 int y2, int mt2, int d2, int h2, int m2, int s2) {
			if (y1 > y2)return true;
			else if (y1 == y2) {
				if (mt1 > mt2)return true;
				else if (mt1 == mt2) {
					if (d1 > d2)return true;
					else if (d1 == d2) {
						if (h1 > h2)return true;
						else if (h1 == h2) {
							if (m1 > m2)return true;
							else if (m1 == m2) {
								if (s1 > s2)return true;
								return false;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		// 消息
		namespace message {
			class Message {
			public:
				std::string text = "[Message]";
				bool pop = false;
				int width;
				Animation xAni, yAni;
				int textsize = 0;
				Color color = {255, 207, 73, 255};
				int duration = 5000;
				int pop_time = 0;
				Message() {
					xAni.sms(anif::bounce3);
					xAni.ssp(0);
					xAni.sd(400);
					yAni.sd(300);
					yAni.ssp(winH);
				}
				void Pop() {
					if (textsize == 0)textsize = GetStringLength(text.c_str());
					xAni.stp(textsize * TextHeight / 2 + UnitHeight * 2);
					pop = true;
					pop_time = clock();
				}
				void Close() {
					xAni.stp(0);
					pop = false;
				}
				int Draw(int y) {
					if (textsize == 0)textsize = text.size();
					width = textsize * TextHeight / 2 + UnitHeight * 2;
					xAni.Update();
					yAni.Update();
					int h = (UnitHeight - TextHeight) / 2;
					if (!pop && !xAni.IsRunning())yAni.stp(winH - UnitHeight * 4);
					yAni.stp(y);
					DrawRectangleRounded({-UnitHeight, yAni.gnp(), xAni.gnp() + UnitHeight, UnitHeight}, 0.5, 0, ColorF(color));
					Print(SpaceSize - width + xAni.gnp(), yAni.gnp() + h, text.c_str(), DARKGRAY);
					Print(-UnitHeight + xAni.gnp() + TextHeight * 0.15, yAni.gnp() + h, "×", DARKGRAY);
					if (clock() - pop_time >= duration)Close();
					if (!pop)return 0;
					if (MouseInRect(-UnitHeight + xAni.gnp(), yAni.gnp(), UnitHeight, UnitHeight)) {
						DrawRectangleRounded({-UnitHeight + xAni.gnp(), yAni.gnp(), UnitHeight, UnitHeight}, 0.5, 0, ColorF(ChooseColor));
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))Close();
					}
					return UnitHeight;
				}
			};
			std::deque<Message> Message_queue;
			void Send(std::string a, int duration = 5000, Color _color = {255, 207, 73, 255}) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.color = _color;
				m.Pop();
				Message_queue.push_front(m);
			}
			void Draw() {
				int y = winH - UnitHeight * 4;
				for (int i = 0; i < Message_queue.size(); i++) {
					Message m = Message_queue.front();
					Message_queue.pop_front();
					int k = m.Draw(y);
					if (k != 0)y -= UnitHeight + SpaceSize;
					Message_queue.push_back(m);
				}
				for (int i = 0; i < Message_queue.size(); i++) {
					Message m = Message_queue.back();
					if (m.pop == false && !m.xAni.IsRunning())Message_queue.pop_back();
					else break;
				}
			}
		};
		namespace special_effect {
			class ClickCircle {
			public:
				Animation rAni;
				Animation aAni;
				int x, y;
				bool start = false;
				ClickCircle() {
					rAni.sms(anif::linear);
					rAni.sd(300);
					aAni.sms(anif::linear);
					aAni.sd(300);
				}
				void Click(int x2, int y2, int r) {
					x = x2, y = y2;
					start = true;
					rAni.ssp(0);
					rAni.stp(r);
					aAni.ssp(100);
					aAni.stp(0);
				}
				void Draw() {
					if (!start)return;
					if (!rAni.IsRunning())return;
					rAni.Update();
					aAni.Update();
					int r = rAni.gnp(), a = aAni.gnp();
					DrawCircle(x, y, r, Color{200, 200, 200, a});
				}
			};
			class LoadingCircle {
			public:
				Animation angle[5];
				int duration = 2000;
				int update_time = 0;
				int update_pos = -1;
				int last_time = -2000;
				static realn lani(realn x) {
					return sin(x) / cos(x);
				}
				LoadingCircle() {
					for (int i = 0; i < 5; i++) {
						angle[i].sd(duration);
						angle[i].sms(lani, -1.35, 1.35);
						angle[i].ssp(0 - (i - 2) * 0.2);
						angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, (i - 2)*duration / 10);
						update_time = clock();
					}
				}
				void Draw(int x, int y, int r) {
					if (clock() - last_time > 500) {
						for (int i = 0; i < 5; i++) {
							angle[i].sd(duration);
							angle[i].sms(lani, -1.35, 1.35);
							angle[i].ssp(0 - (i - 2) * 0.2);
							angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, (i - 2)*duration / 10);
						}
						update_time = clock();
						update_pos = -1;
					}
					for (int i = 0; i < 5; i++) {
						angle[i].Update();
						if (clock() - update_time - (i - 2) * duration / 10 >= duration && update_pos < i) {
							update_pos = i;
							angle[i].ssp(0 - (i - 2) * 0.2);
							angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, clock() - update_time - duration - (i - 2)*duration / 10);
							if (i == 4)update_time += duration, update_pos = -1;
						}
						vector2d v = {0, -r};
						v = v.Rotate(-angle[i].gnp());
						if (angle[i].is_run())DrawCircle(x + v.x, y - v.y, ceil(r / 7.0), WHITE);
					}
					last_time = clock();
				}
			};
			class LoadingLine {
			public:
				Animation angle[5];
				int duration = 2000;
				static realn lani(realn x) {
					return sin(x) / cos(x);
				}
				LoadingLine() {
					for (int i = 0; i < 5; i++) {
						angle[i].sd(duration);
						angle[i].sms(lani, -1.35, 1.35);
						angle[i].ssp(0 - i * 0.01);
						angle[i].stp(1 - i * 0.01, i * duration / 10);
					}
				}
				void Draw(int x, int y, int w, realn r = 2.5 * DPI.x) {
					BeginScissor(x, y - r, w, r * 2);
					for (int i = 0; i < 5; i++) {
						angle[i].Update();
						if (angle[4].gnp() == angle[4].gtp())
							for (int i = 0; i < 5; i++) {
								angle[i].sd(duration);
								angle[i].sms(lani, -1.35, 1.35);
								angle[i].ssp(0 - i * 0.01);
								angle[i].stp(1 - i * 0.01, i * duration / 10);
							}
						if (angle[i].IsRunning())DrawCircle(x + angle[i].gnp() * w, y, r, WHITE);
					}
					EndScissor();
				}
			};
			class LoadingLineSolid {
			public:
				Animation a1, a2;
				int duration = 1500;
				LoadingLineSolid() {
					a1.sd(duration), a1.sms((realn(*)(realn))atan, -5, 5), a1.ssp(-0.2), a1.stp(1.2), a1.Repeat(true);
					a2.sd(duration), a2.sms((realn(*)(realn))atan, -5, 5), a2.ssp(-0.2), a2.stp(1.2, duration / 7.0), a2.Repeat(true);
				}
				void Draw(int x, int y, int w, double r = 1.5 * DPI.x) {
					a1.update();
					a2.update();
					double x1 = std::max((realn)0.0, a2.gnp()), x2 = std::min((realn)1.0, a1.gnp());
					BeginScissor(x, y - r, w, r * 2);
					DrawRectangleRounded(Rectangle{x1 * w + x, y - r, x2 * w - x1 * w, r * 2}, 1, 0, WHITE);
					EndScissor();
				}
			};
			ClickCircle clickcircle;
			LoadingCircle loading_circle;
			LoadingLine loading_line;
			LoadingLineSolid loading_line_solid;
			void Draw() {
//				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))clickcircle.Click(Mouse.x, Mouse.y, 100);
//				clickcircle.Draw();
//				for (int i = 0; i < 5; i++) {
//					loading_circle.angle[i].Update();
//					if (clock() - loading_circle.update_time - (i - 2)*loading_circle.duration / 10 >= loading_circle.duration && loading_circle.update_pos < i) {
//						loading_circle.update_pos = i;
//						loading_circle.angle[i].ssp(0 - (i - 2) * 0.2);
//						loading_circle.angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, clock() - loading_circle.update_time - loading_circle.duration - (i - 2)*loading_circle.duration / 10);
//						if (i == 4)loading_circle.update_time += loading_circle.duration, loading_circle.update_pos = -1;
//					}
//				}
			}
			void DrawMouseRectangle(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
					a = {MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
				}
				for (int i = y + s; i < y + h - s; i += s) {
					int s1 = s, s2 = s;
					if (i + s > y + h - s)s2 = y + h - s - i;
					vector2d a = {MouseShadow.x - x, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x, i, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
					a = {MouseShadow.x - x - w, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x + w - s, i, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
				}
				if (MouseInRect(x, y, w, h)) {
					DrawRectangleLinesEx({x, y, w, h}, s, Color{255, 255, 255, 40});
				}
			}
			void DrawMouseRectangle_onlyLight(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
					a = {MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
				}
				for (int i = y + s; i < y + h - s; i += s) {
					int s1 = s, s2 = s;
					if (i + s > y + h - s)s2 = y + h - s - i;
					vector2d a = {MouseShadow.x - x, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x, i, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
					a = {MouseShadow.x - x - w, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x + w - s, i, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
				}
			}
			void DrawMouseRectangle_onlyLevel(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
					a = {MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, Color{255, 255, 255, 255 * (1.0 * (r - Mod(a)) / r * 0.4)});
				}
			}
			void DrawMouseCircle(int x, int y, int rad, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				vector2d v = {0, rad};
				vector2d mouse = {MouseShadow.x, MouseShadow.y};
				double d = 2 * 3.1415926 / 10.0;
				for (double i = d; i < 2 * 3.1415926; i += d) {
					vector2d v2 = v.Rotate(-i) + vector2d{x, y};
					vector2d temp = mouse - v2;
					double dist = Mod(temp);
					if (dist <= r)DrawRing({x, y}, rad - s, rad, R2A * i, R2A * (i + d), 3, Color{255, 255, 255, 255 * (1.0 * (r - dist) / r * 0.4)});
				}
				if (Mod2(mouse - vector2d{x, y}) <= rad * rad)DrawCircleLines(x, y, rad, Color{255, 255, 255, 40});
			}
			void DrawMouseBox(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				DrawRectangleLinesEx({x - s, y - s, w + s * 2, h + s * 2}, s, Color{255, 255, 255, 30});
				DrawMouseRectangle_onlyLight(x - s, y - s, w + s * 2, h + s * 2, r, s);
			}
			void DrawFrame(int x, int y, int w, int h) {
				DrawRectangleLinesEx({x, y, w, h}, dpi, Color{30, 30, 30, 255});
			}
			void DrawLoadingCircle(int x, int y, int r, std::string text = "", int size = 0) {
				loading_circle.Draw(x, y, r);
				if (size == 0)size = text.size();
				Print(x - size * TextHeight / 4, y + r * 2.1, text, WHITE);
			}
			void DrawLoadingLine(int x, int y, int w, std::string text = "", int size = 0) {
				loading_line.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, WHITE);
			}
			void DrawLoadingLineSolid(int x, int y, int w, std::string text = "", int size = 0) {
				loading_line_solid.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, WHITE);
			}
			void DrawShadowLine(int x1, int y1, int x2, int y2, int r, double dark = 0.5) {
				if (!DrawSpecialEffect)return;
				vector2d v = {x2 - x1, y2 - y1};
				v = v.Rotate(3.1415927 / 2.0);
				v = VecUnit(v);
				v *= r / 5.0;
				x1 += (v / 2).x, x2 += (v / 2).x, y1 += (v / 2).y, y2 += (v / 2).y;
				for (int i = 0; i < 5; i++)DrawLineEx({x1 + v.x * i, y1 + v.y * i}, {x2 + v.x * i, y2 + v.y * i}, r / 5.0, Color{0, 0, 0, 100 * dark - i * 20 * dark});
			}
			void DrawShadowRectangle(int x, int y, int w, int h, int r = 15 * dpi) {
				if (!DrawSpecialEffect)return;
				double r1 = r;
				for (int i = 0; i < 5; i++) {
					DrawRectangleRoundedLines({x, y, w, h}, 1.0 * r1 / std::min(w, h), 30, ui::dpi, Color{0, 0, 0, (unsigned char)(50 - i * 10)});
					x -= r / 5.0, y -= r / 5.0, w += r / 2.5, h += r / 2.50;
					r1 += r / 5.0 * 2;
				}
			}
		};

		// 实现

		class System {
		public:
			std::vector<Window*> win;
			static bool CMP_Window(Window* w1, Window* w2);
			void Update();
			void Add(Window* w) {
				win.push_back(w);
			}
			void Erase(Window* w) {
				for (auto i : win)if (i == w)win.erase((std::vector<Window * >::iterator)(&i));
			}
		} MainSystem;

		void Print(int x, int y, std::string text, Color color = TextColor2) {
			if (PrintChecking)UseCharacter.Check(text);
			DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, ColorF(color));
		}
		int PrintRect(int x, int y, int w, std::string text, Color color = TextColor2) {
			if (w < ui::TextHeight)return ui::UnitHeight;
			int len = 0, last = 0, line = 0;
			int h = (UnitHeight - TextHeight) / 2;
			for (int i = 0; i < text.size(); i++) {
				int j = i, temp = 0;
				if ((text[i] & 0xE0) == 0xE0)temp = 2, len += 2, i += 2;
				else if (text[i] == '\n' && len * ui::TextHeight / 2 <= w) {
					Print(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight;
					len = 0;
					line++;
					last = i + 1;
				} else temp = 1, len++;
				if (len * ui::TextHeight / 2 > w) {
					Print(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight;
					len = temp;
					if (temp == 1)last = i;
					if (temp == 2)last = i - 2;
					line++;
				}
			}
			if (last != text.size()) {
				Print(x, y + h, text.substr(last), ColorF(color));
				line++;
			}
			return line;
		}
		int GetPrintRectLine(int x, int y, int w, std::string text) {
			if (w < ui::TextHeight)return ui::UnitHeight;
			int len = 0, last = 0, line = 0;
			int h = (UnitHeight - TextHeight) / 2;
			for (int i = 0; i < text.size(); i++) {
				int j = i, temp = 0;
				if ((text[i] & 0xE0) == 0xE0)temp = 2, len += 2, i += 2;
				else if (text[i] == '\n' && len * ui::TextHeight / 2 <= w) {
					y += ui::UnitHeight;
					len = 0;
					line++;
					last = i + 1;
				} else temp = 1, len++;
				if (len * ui::TextHeight / 2 > w) {
					y += ui::UnitHeight;
					len = temp;
					if (temp == 1)last = i;
					if (temp == 2)last = i - 2;
					line++;
				}
			}
			if (last != text.size()) {
				line++;
			}
			return line;
		}
		void UseIcon(std::string str, Font* font = &IconFont, int size = ui::TextHeight) {
			if (font == &IconFont)Icons += str, str = Icons;
			int fileSize;
			unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\segmdl2.ttf", &fileSize);
			int codepointsCount;
			int *codepoints = LoadCodepoints((str + "啊看见对方").c_str(), &codepointsCount);
			(*font) = LoadFontFromMemory(".ttf", fontFileData, fileSize, size, codepoints, codepointsCount);
			UnloadCodepoints(codepoints);
			UnloadFileData(fontFileData);
		}
		void PrintIcon(int x, int y, std::string text, Color color = ui::TextColor, Font* font = &IconFont, int size = ui::TextHeight) {
			DrawTextEx((*font), text.c_str(), Vector2 {(float)x, (float)y}, size, 0, ColorF(color));
		}
		bool MouseInRect(realn x1, realn y1, realn w, realn h) {
			realn x2 = x1 + w, y2 = y1 + h;
			if (Mouse.x >= x1 && Mouse.x < x2 && Mouse.y >= y1 && Mouse.y < y2)return true;
			return false;
		}

		// 基类
		class Element {
		public:
			int height = UnitHeight;				// 控件高度
			realn X, Y, W, H;						// 位置
			bool CHECK = true;						// 是否检查鼠标键盘事件
			bool extra = false;						// 是否扩展
			bool init_height = false;				// 是否已经初始化高度
			std::vector<Element*> key;				// 嵌套控件
			Element() {}
			virtual int Draw(int x, int y, int w, bool check = true) {
				return 0;
			}
			virtual int Draw(int x, int y, int w, int h, bool check = true) {
				return 0;
			}
			int Draw_Auto(int x, int y, int w, bool check = true) {
				int h = 0;
				if (!init_height) {
					BeginScissor(0, 0, 0, 0);
					CHECK = check;
					height = Draw(x, y, w, check);
					EndScissor();
					init_height = true;
				}
				if (w <= 0)return height;				// 无法绘制，舍弃
				X = x, Y = y, W = w;
				// 在裁剪区外，舍弃
				if (InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, height + height * 0.4))height = Draw(x, y, w, check);
				H = height;
				if (height < 1)height = 1;
				return height;
			}
			int Draw_Auto_Extra(int x, int y, int w, int h, bool check = true) {
				if (w <= 0 || h <= 0)return 0;			// 无法绘制，舍弃
				CHECK = check;
				X = x, Y = y, W = w, H = h;
				// 在裁剪区外，舍弃
				if (InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, h + height * 0.4))height = Draw(x, y, w, h, check);
				if (height < 1)height = 1;
				return height;
			}
			int Size() {
				return key.size();
			}
			virtual void Add(Element* a) {
				key.push_back(a);
			}
			virtual void Insert(int position, Element* a) {
				key.insert(key.begin() + position, a);
			}
			virtual void Erase(int position) {
				key.erase(key.begin() + position);
			}
			virtual void Erase(Element* e) {
				for (int i = 0; i < Size(); i++) {
					if (key[i] == e)key.erase(key.begin() + i);
				}
			}
			virtual void Swap(int p1, int p2) {
				std::swap(key[p1], key[p2]);
			}
			virtual void ClearKey() {
				while (Size()) {
					Erase(0);
				}
			}
		};
		double TopPriority = 0;
		double WindowTopPriority = 0;
		class Priority : public Element {
		public:
			double priority;
			std::string prio_flag = "Window";
		};

		// 一下为继承的控件
		class SliderBar : public Element {
		private:
			bool choose = false;			// 是否选择
			bool realn_mouse_input = true;	// 真正的鼠标输入
			bool fixed = false;				// 是否固定
			int chooseh = 0;				// 选择的高度
			int lx = 0;						// 控制的矩形x
			int ly = 0;						// 控制的矩形y
			int lw = ui::winW;				// 控制的矩形w
			int lh = ui::winH;				// 控制的矩形h
			double blank = 0.3;				// 空白大小
			double sum = 0;					// 总高度
			double now = 0;					// 当前位置
			Animation move;					// 滚动动画
			int cursor_pos = 0;				// 光标位置
			bool draw_cursor = false;		// 是否显示光标位置
		public:
			static realn ani_fun(realn x) {
				return exp(-x);
			}
			SliderBar() {
				move.sd(750);
				move.sms(ani_fun, 0, 20);
				extra = true;
			}
			void Set(int x) {
				move.update();
				move.stp(x);
			}
			void Shift(int x) {
				move.update();
				move.ssp(x);
				move.stp(x);
			}
			void GotoTop() {
				move.stp(0);
			}
			void GotoBottom() {
				move.stp(sum + blank*H - H);
			}
			int Now() {
				return now;
			}
			int Sum() {
				return sum;
			}
			void SetControl(int x, int y, int w, int h) {
				lx = x, ly = y, lw = w, lh = h;
			}
			void SetBlank(realn blank_) {
				blank = blank_;
			}
			void SetSum(realn sum_) {
				sum = sum_;
			}
			void SetCursorPos(realn pos) {
				cursor_pos = pos;
			}
			void SetDrawCursor(bool on) {
				draw_cursor = on;
			}
			void SetFixed(bool on) {
				fixed = on;
			}
			bool Update() {
				// 通过鼠标滚轮更新
				int sum2 = sum;
				if (H >= W) {
					sum2 += H * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderY)move.stp(move.gtp() - GetMouseWheelMoveV().y * 150);
					if (move.gtp() > sum2 - H)move.stp(sum2 - H);
					if (move.gtp() < 0)move.stp(0);
					sum2 -= H * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderY && GetMouseWheelMoveV().y != 0)UseSliderY = true;
				} else {
					sum2 += W * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderX)move.stp(move.gtp() - GetMouseWheelMoveV().x * 150);
					if (move.gtp() > sum2 - W)move.stp(sum2 - W);
					if (move.gtp() < 0)move.stp(0);
					sum2 -= W * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderX && GetMouseWheelMoveV().y != 0)UseSliderX = true;
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				X = x, Y = y, W = w, H = h, CHECK = check;
				move.update();
				now = move.gnp();
				int sum2 = sum;
				if (h >= w) {
					// 总高度小于实际高度，舍弃
					sum2 += h * blank;
					if (h >= sum2) {
						if (fixed) {
							// 绘制整体
							DrawRectangle(x, y, w, h, ColorF(27, 27, 27, 255));
							// 绘制箭头
							DrawLine(x + w / 2, y + w * 3 / 8, x + w / 4, y + w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + w * 3 / 8, x + w * 3  / 4, y + w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + h - w * 3 / 8, x + w / 4, y + h - w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + h - w * 3 / 8, x + w * 3 / 4, y + h - w * 5 / 8, ColorF(WHITE));
							return SliderWidth;
						} else return SliderWidth;
					}
					// 绘制整体
					DrawRectangle(x, y, w, h, ColorF(27, 27, 27, 255));
					// 绘制箭头
					DrawLine(x + w / 2, y + w * 3 / 8, x + w / 4, y + w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + w * 3 / 8, x + w * 3  / 4, y + w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w / 4, y + h - w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w * 3 / 4, y + h - w * 5 / 8, ColorF(WHITE));
					// 绘制拖动条
					double k = 1.0 * now / sum2;
					double k2 = 1.0 * h / sum2;
					double h2 = 0;
					if (k2 * (h - 2 * w) < w)h2 = (w - k2 * (h - 2 * w)), k2 = 1.0 * w / (h - 2 * w - h2);
					if (choose)DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), ColorF(158, 158, 157, 255));
					else if (MouseInRect(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2)))
						DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), ColorF(118, 118, 117, 255));
					else DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), ColorF(72, 72, 73, 255));
					// 检查鼠标点击上下滚动按钮事件
					if (MouseInRect(x, y, w, w)) {						// 向上滚
						DrawRectangle(x, y, w, w, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT) && realn_mouse_input)move.stp(move.gnp() - 50 * dpi);
					} else if (MouseInRect(x, y + h - w, w, w)) {		// 向下滚
						DrawRectangle(x, y + h - w, w, w, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT) && realn_mouse_input)move.stp(move.gnp() + 50 * dpi);
					} else {
						if (check && IsMouseButtonDown(MOUSE_BUTTON_LEFT))realn_mouse_input = false;
						else realn_mouse_input = true;
					}
					// 检查鼠标拖动事件
					if (MouseInRect(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2)) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = y + w + (Mouse.y - (y + k * (h - w * 2 - h2) + w));
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))choose = false;
					// 检查鼠标点击跳转事件
					if (MouseInRect(x, y + w, w, h - w * 2) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						double k3 = Mouse.y - (y + w);
						k3 /= h - 2 * w;
						move.stp(k3 * sum2 - h / 2);
					}
					// 执行拖动
					if (choose) {
						double k3 = Mouse.y - chooseh;
						k3 /= h - 2 * w - h2;
						move.stp(k3 * sum2);
					}
					// 绘制光标
					if (draw_cursor)DrawRectangle(x, y + cursor_pos / sum2 * (h - w * 2 - h2) + w - dpi, w, dpi * 2, ColorF(LIGHTGRAY));
				} else {
					sum2 += w * blank;
					if (w >= sum2) {
						if (fixed) {
							DrawRectangle(x, y, w, h, ColorF(27, 27, 27, 255));
							DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h / 4, ColorF(WHITE));
							DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
							DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h / 4, ColorF(WHITE));
							DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
							return SliderWidth;
						} else return SliderWidth;
					}
					DrawRectangle(x, y, w, h, ColorF(27, 27, 27, 255));
					DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h / 4, ColorF(WHITE));
					DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
					DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h / 4, ColorF(WHITE));
					DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
					double k = 1.0 * now / sum2;
					double k2 = 1.0 * w / sum2;
					double w2 = 0;
					if (k2 * (w - 2 * h) < h)w2 = (h - k2 * (w - 2 * h)), k2 = 1.0 * h / (w - 2 * h - w2);
					if (choose)DrawRectangle(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h, ColorF(158, 158, 157, 255));
					else if (MouseInRect(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h))
						DrawRectangle(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h, ColorF(118, 118, 117, 255));
					else DrawRectangle(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h, ColorF(72, 72, 73, 255));
					if (MouseInRect(x, y, h, h)) {
						DrawRectangle(x, y, h, h, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT) && realn_mouse_input)move.stp(move.gnp() - 50 * dpi);
					} else if (MouseInRect(x + w - h, y, h, h)) {
						DrawRectangle(x + w - h, y, h, h, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT) && realn_mouse_input)move.stp(move.gnp() + 50 * dpi);
					} else {
						if (check && IsMouseButtonDown(MOUSE_BUTTON_LEFT))realn_mouse_input = false;
						else realn_mouse_input = true;
					}
					if (MouseInRect(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = x + h + (Mouse.x - (x + k * (w - h * 2 - w2) + h));
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))choose = false;
					if (MouseInRect(x + h, y, w - h * 2, h) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						double k3 = Mouse.x - (x + h);
						k3 /= w - 2 * h;
						move.stp(k3 * sum2 - w / 2);
					}
					if (choose) {
						double k3 = Mouse.x - chooseh;
						k3 /= w - 2 * h - w2;
						move.stp(k3 * sum2);
					}
				}
				return ui::SpaceSize * 4;
			}
		};
		class Title : public Element {
		public:
			std::string text = "Title";
			int Draw(int x, int y, int w = 600, bool check = true) {
				Print(x, y, text);
				return UnitHeight;
			}
		};
		class Head : public Element {
		private:
			Font ofont;
			std::string last_text = "";
		public:
			std::string text = "你好";
			Color color = TextColor;
			void LoadNewFont() {
				int fileSize;
				unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\simhei.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints((text + "啊看见对方").c_str(), &codepointsCount);
				ofont = LoadFontFromMemory(".ttf", fontFileData, fileSize, ui::TextHeight * 2, codepoints, codepointsCount);
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				if (text != last_text) {
					LoadNewFont();
					last_text = text;
				}
				DrawTextEx(ofont, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight * 2, 0, ColorF(color));
				return UnitHeight * 3;
			}
		};
		class Text : public Element {
		public:
			std::string text = "Text";
			int Draw(int x, int y, int w = 600, bool check = true) {
				height = PrintRect(x, y, w, text) * ui::UnitHeight;
				return height;
			}
		};
		class Line : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				DrawLine(x, y + UnitHeight / 4, x + w, y + UnitHeight / 4, TextColor2);
				return UnitHeight / 2;
			}
		};
		Line line;
		class Space : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				return UnitHeight / 2;
			}
		};
		Space space;
		class Shadow_down : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				special_effect::DrawShadowLine(x, y, x + w, y, UnitHeight / 2);
				return UnitHeight / 2;
			}
		};
		class Shadow_up : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				special_effect::DrawShadowLine(x + w, y + UnitHeight / 2, x, y + UnitHeight / 2, UnitHeight / 2);
				return UnitHeight / 2;
			}
		};
		class Logo : public Element {
		public:
			Color ftcolor = DARKGRAY;
			Color bgcolor = Color{25, 25, 25, 255};
			Logo() {
				extra = true;
			}
			int Draw(int x, int y, int w, bool check = true) {
				DrawPoly(Vector2{x + w / 2, y + w / 2}, 6, w / 2, 30, ftcolor);
				DrawPolyLinesEx(Vector2{x + w / 2, y + w / 2}, 6, w / 5, 30, w / 20.0 * 1.15, bgcolor);
				DrawPoly(Vector2{x + w / 2 + w / 20 * sqrt(3), y + w / 2 - w / 20}, 6, w / 5 - w / 20.0, 30, ftcolor);
				vector2d v = {0, w / 2 - w / 5};
				realn pi = 3.14159265359;
				vector2d v2 = v.Rotate(pi / 3);
				Vector2 A = {x + w / 2, y + w / 2 - w / 5}, B = {x + w / 2 - v2.x, y + w / 2 - w / 5 - v2.y};
				Vector2 C = {x + w / 2, y + w / 2 - w / 5 + w / 20}, D = {x + w / 2 - v2.x + w / 40 * sqrt(3), y + w / 2 - w / 5 - v2.y + w / 40};
				DrawTriangle(A, D, B, bgcolor);
				DrawTriangle(A, C, D, bgcolor);
				//DrawPoly(Vector2{x+w/2,y+w/2},6,w/5,0,w/20,bgcolor);
				return w;
			}
		};
		class Textbox : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				return UnitHeight;
			}
		};
		class Button : public Element {
		public:
			std::string text = "Button";
			bool click = false;
			int Draw(int x, int y, int w = 600, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				DrawRectangle(x, y + h / 2, w, UnitHeight - h, MainColor);
				special_effect::DrawMouseRectangle(x, y + h / 2, w, UnitHeight - h);
				Print(x + (w - GetStringLength(text.c_str())*TextHeight / 2) / 2, y + h, text, TextColor);
				if (MouseInRect(x, y + h / 2, w, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))click = true;
					else click = false;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, UnitHeight - h, Color {32, 32, 32, 50});
					DrawRectangle(x, y + h / 2, w, UnitHeight - h, ChooseColor);
				} else click = false;
				return UnitHeight;
			}
		};
		class Button2 : public Element {
		private:
			bool DrawOne(int x, int y, std::string text, int w = 600, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				bool flag = false;
				DrawRectangle(x, y, w, UnitHeight - h, MainColor);
				special_effect::DrawMouseRectangle(x, y, w, UnitHeight - h);
				Print(x + (w - GetStringLength(text.c_str())*TextHeight / 2) / 2, y + h / 2, text, TextColor);
				if (MouseInRect(x, y, w, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))flag = true;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, UnitHeight - h, Color {32, 32, 32, 50});
					DrawRectangle(x, y, w, UnitHeight - h, ChooseColor);
				}
				return flag;
			}
		public:
			std::string text1 = "Button1";
			std::string text2 = "Button2";
			bool click1 = false;
			bool click2 = false;
			int Draw(int x, int y, int w = 600, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				click1 = DrawOne(x, y + h / 2.0, text1, (w - h) / 2.0, check);
				click2 = DrawOne(x + (w - h) / 2.0 + h, y + h / 2.0, text2, (w - h) / 2.0, check);
				return UnitHeight;
			}
		};
		class Button3 : public Element {
		private:
			bool DrawOne(int x, int y, std::string text, int w = 600, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				bool flag = false;
				DrawRectangle(x, y, w, UnitHeight - h, MainColor);
				special_effect::DrawMouseRectangle(x, y, w, UnitHeight - h);
				Print(x + (w - GetStringLength(text.c_str())*TextHeight / 2) / 2, y + h / 2, text, TextColor);
				if (MouseInRect(x, y, w, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))flag = true;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, UnitHeight - h, Color {32, 32, 32, 50});
					DrawRectangle(x, y, w, UnitHeight - h, ChooseColor);
				}
				return flag;
			}
		public:
			std::string text1 = "Button1";
			std::string text2 = "Button2";
			std::string text3 = "Button3";
			bool click1 = false;
			bool click2 = false;
			bool click3 = false;
			int Draw(int x, int y, int w = 600, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				click1 = DrawOne(x, y + h / 2, text1, (w - 2 * h) / 3, check);
				click2 = DrawOne(x + (w - 2 * h) / 3.0 + h, y + h / 2, text2, (w - 2 * h) / 3.0, check);
				click3 = DrawOne(x + (w - 2 * h) / 3.0 * 2 + h * 2, y + h / 2, text3, (w - 2 * h) / 3.0, check);
				return UnitHeight;
			}
		};
		class IconButton : public ui::Element {
		private:
			Font iconf;
			int isize = ui::TextHeight * 1;
			std::string last_icon = "";
		public:
			bool click = false;
			bool draw_background = true;
			Color color = Color{47, 47, 47, 255};
			std::string icon = "";
			std::string text = "";
			int GetWidth() {
				int t = (ui::UnitHeight * 1.5 - ui::TextHeight) / 2;
				int w = t;
				if (icon != "")w += strLen(icon) * ui::TextHeight / 2 + t;
				if (text != "")w += strLen(text) * ui::TextHeight / 2 + t;
				return w;
			}
			int Draw(int x, int y, int w, bool check = true) {
				click = false;
				int h = ui::UnitHeight * 1.5;
				int t = (ui::UnitHeight * 1.5 - ui::TextHeight) / 2;
				if (draw_background) {
					w = t;
					y += ui::SpaceSize / 2;
					if (icon != "")w += strLen(icon) * ui::TextHeight / 2 + t;
					if (text != "")w += strLen(text) * ui::TextHeight / 2 + t;
					DrawRectangle(x, y, w, h, color);
				}
				w = t;
				PrintIcon(x + w, y + t, icon);
				if (icon != "")w += strLen(icon) * ui::TextHeight / 2 + t;
				Print(x + w, y + t, text);
				if (text != "")w += strLen(text) * ui::TextHeight / 2 + t;
				special_effect::DrawMouseRectangle(x, y, w, h);
				if (ui::MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ui::ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check)click = true;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, h, ui::ChooseColor);
				}
				if (draw_background)h += ui::SpaceSize;
				return h;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				click = false;
				int t = (ui::UnitHeight * 1.5 - ui::TextHeight) / 2;
				int w2 = t, w3;
				if (icon != "")w2 += strLen(icon) * ui::TextHeight / 2 + t;
				if (text != "")w2 += strLen(text) * ui::TextHeight / 2 + t;
				if (draw_background)DrawRectangle(x, y, w, h, color);
				w3 = t;
				PrintIcon(x + w / 2 - w2 / 2 + w3, y + h / 2 - ui::TextHeight / 2, icon);
				if (icon != "")w3 += strLen(icon) * ui::TextHeight / 2 + t;
				Print(x + w / 2 - w2 / 2 + w3, y + h / 2 - ui::TextHeight / 2, text);
				if (text != "")w3 += strLen(text) * ui::TextHeight / 2 + t;
				special_effect::DrawMouseRectangle(x, y, w, h);
				if (ui::MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ui::ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check)click = true;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, h, ui::ChooseColor);
				}
				return h;
			}
		};
		class Warning : public ui::Element {
		public:
			std::string text = "[注意]";
			int Draw(int x, int y, int w, bool check = true) {
				int h = (ui::UnitHeight - ui::TextHeight) / 2;
				height = ui::GetPrintRectLine(x + ui::SpaceSize + ui::UnitHeight, y + ui::SpaceSize * 3 / 2, w - ui::SpaceSize * 2 - ui::UnitHeight, text) * ui::UnitHeight;
				DrawRectangle(x, y + ui::SpaceSize / 2, w, height + ui::SpaceSize * 2, Color{255, 153, 0, 100});
				ui::PrintIcon(x + ui::SpaceSize, y + ui::SpaceSize * 3 / 2 + height / 2 - ui::TextHeight / 2, "");
				ui::PrintRect(x + ui::SpaceSize + ui::UnitHeight, y + ui::SpaceSize * 3 / 2, w - ui::SpaceSize * 2 - ui::UnitHeight, text);
				height += ui::SpaceSize * 3;
				return height + ui::SpaceSize;
			}
		};
		class Error : public ui::Element {
		public:
			std::string text = "[警告]";
			int Draw(int x, int y, int w, bool check = true) {
				int h = (ui::UnitHeight - ui::TextHeight) / 2;
				height = ui::GetPrintRectLine(x + ui::SpaceSize + ui::UnitHeight, y + ui::SpaceSize * 3 / 2, w - ui::SpaceSize * 2 - ui::UnitHeight, text) * ui::UnitHeight;
				DrawRectangle(x, y + ui::SpaceSize / 2, w, height + ui::SpaceSize * 2, Color{192, 44, 56, 100});
				ui::PrintIcon(x + ui::SpaceSize, y + ui::SpaceSize * 3 / 2 + height / 2 - ui::TextHeight / 2, "");
				ui::PrintRect(x + ui::SpaceSize + ui::UnitHeight, y + ui::SpaceSize * 3 / 2, w - ui::SpaceSize * 2 - ui::UnitHeight, text);
				height += ui::SpaceSize * 3;
				return height + ui::SpaceSize;
			}
		};
		class LoadingBar : public Element {
		private:
			Animation move, color;
			Font icon_font;
			std::string last_icon = "";
		public:
			realn now = 0;
			std::string text = "进度";
			std::string icon = "";
			bool draw_loading_circle = true;
			LoadingBar() {
				move.sd(300);
			}
			int Draw(int x, int y, int w, bool check = true) {
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				int tempH2 = (ui::UnitHeight * 1.5 - ui::TextHeight * 1.5) / 2;
				if (now > 1)now = 1;
				if (now < 0)now = 0;
				move.update();
				move.stp(now);
				y += ui::SpaceSize / 2;
				// 图标
				if (icon != "") {
					if (last_icon != icon) {
						ui::UseIcon(icon, &icon_font, ui::TextHeight * 1.5);
						last_icon = icon;
					}
					ui::PrintIcon(x, y + tempH2, icon, BLUE, &icon_font, ui::TextHeight * 1.5);
					x += ui::UnitHeight * 1.5 + ui::SpaceSize * 2, w -= ui::UnitHeight * 1.5 + ui::SpaceSize * 2;
				}
				// 字幕
				ui::Print(x, y + tempH, text, ui::TextColor);
				std::stringstream ss;
				ss << "已完成 " << int(now * 100) << "." << int(now * 1000) % 10 << "%";
				std::string text2 = ss.str();
				ui::Print(x + w - ui::strLen(text2)*ui::TextHeight / 2, y + tempH, text2, ui::MixColor({100, 100, 100, 255}, ui::TextColor2, color.gnp()));
				if (abs(now - 1) > 0.0001)ui::special_effect::DrawLoadingCircle(x + ui::strLen(text) * ui::TextHeight / 2 + ui::UnitHeight, y + ui::UnitHeight / 2, ui::UnitHeight * 0.4);
				// 进度条
				y += ui::UnitHeight + tempH;
				DrawRectangle(x, y, w, ui::UnitHeight / 4, Color{75, 75, 75, 255});
				color.update();
				if (abs(now - 1) <= 0.0001 && draw_loading_circle)color.stp(1);
				else color.stp(0);
				DrawRectangle(x, y, move.gnp()*w, ui::UnitHeight / 4, BLUE);
				return ui::UnitHeight * 1.25 + tempH * 2 + ui::SpaceSize;
			}
		};
		class Slider : public Element {
		public:
			Animation move;
			realn num = 0;
			realn minn = 0;
			realn maxn = 10;
			bool text_visible = true;
			std::string text = "Slider";
			void Set(realn x) {
				num = x;
			}
			virtual int Draw(int x, int y, int w = 400, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				int nw = UnitHeight * 1.7;
				realn h2 = UnitHeight / 6;
				if (text_visible)cw = w * 0.6;
				else cw = w;
				move.sd(200);
				move.Update();
				move.stp((cw - UnitHeight / 5) * (num - minn) / (maxn - minn));
				realn k = move.gnp();
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, GRAY);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, MainColor);
				DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, MainColor);
				if (text_visible) {
					Print(x + cw + SpaceSize, y + h, text, TextColor);
					DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, TextColor2);
					std::ostringstream out;
					out << num;
					std::string t = out.str();
					if (t.size() > 4)t.resize(4);
					Print(x + w - nw + h, y + h, t, MainColor);
				}
				if (MouseInRect(x, y + h / 2, cw, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseSlider = this;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (ChooseSlider == this && check) {
					realn kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5) + minn;
					if (kx < minn)kx = minn;
					if (kx > maxn)kx = maxn;
					num = kx;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))ChooseSlider = NULL;
				return UnitHeight;
			}
		};
		class Slider_Int : public Slider {
		public:
			int num = 0;
			int minn = 0;
			int maxn = 10;
			std::string text = "Slider";
			void Set(int x) {
				num = x;
			}
			int Draw(int x, int y, int w = 400, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				int nw = UnitHeight * 1.7;
				realn h2 = UnitHeight / 6;
				move.sd(200);
				move.Update();
				move.stp((cw - UnitHeight / 5)*num / (maxn - minn));
				realn k = move.gnp();
				Print(x + cw + SpaceSize, y + h, text, TextColor);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, GRAY);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, MainColor);
				DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, MainColor);
				DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, TextColor2);
				std::ostringstream out;
				out << num;
				std::string t = out.str();
				t = t.substr(0, 5);
				Print(x + w - nw + h, y + h, t, MainColor);
				if (MouseInRect(x, y + h / 2, cw, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseSlider = this;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (ChooseSlider == this) {
					realn kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5);
					if (kx < minn)kx = minn;
					if (kx > maxn)kx = maxn;
					num = kx;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))ChooseSlider = NULL;
				return UnitHeight;
			}
		};
		class Switch : public Element {
		private:
			Animation move;
		public:
			std::string text = "Switch";
			bool on = false;
			int Draw(int x, int y, int w = 600, bool check = true) {
				move.sd(300);
				move.sms(anif::bounce4);
				int h = (UnitHeight - TextHeight) / 2;
				int nw = UnitHeight * 1.7;
				realn h2 = UnitHeight / 4;
				move.Update();
				Print(x, y + h, text);
				DrawRectangle(x + w - nw, y + UnitHeight / 2 - h2 / 2, nw, h2, GRAY);
				DrawRectangle(x + w - nw, y + UnitHeight / 2 - h2 / 2, round(move.gnp()), h2, MainColor);
				DrawRectangle(x + w - nw + round(move.gnp()), y + h / 2, round(UnitHeight / 3.5), UnitHeight - h, MainColor);
				if (MouseInRect(x + w - nw, y + h / 2, nw, UnitHeight - h) && check) {
					DrawRectangle(x + w - nw + round(move.gnp()), y + h / 2, round(UnitHeight / 3.5), UnitHeight - h, WHITE);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))on = !on;
				}
				if (on)move.stp(nw - UnitHeight / 3.5);
				else move.stp(0.0);
				return UnitHeight;
			}
		};
		class Choose : public Element {
		private:
			Animation angle;
			Animation move;
			bool open = false;
		public:
			std::string text = "Choose";
			std::vector<std::string> key;
			int choose = -1;
			void Open() {
				open = true;
				angle.stp(acos(-1) / 2);
				move.stp(key.size()*UnitHeight);
			}
			void Close() {
				open = false;
				angle.stp(0);
				move.stp(0);
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				angle.sd(300);
				move.sd(300);
				angle.Update();
				move.Update();
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				Print(x + SpaceSize + cw, y + h, text, TextColor);
				DrawRectangle(x, y + h / 2, cw, UnitHeight - h, UnitBgColor);
				special_effect::DrawMouseRectangle(x, y + h / 2, cw, UnitHeight - h);
				if (choose != -1)Print(x + SpaceSize, y + h, key[choose], TextColor);
				vector2d k1 = vector2d {-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8};
				vector2d k2 = vector2d {TextHeight / 4 * 0.8, 0};
				vector2d k3 = vector2d {-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8};
				vector2d p1 = k1.Rotate(angle.gnp());
				vector2d p2 = k2.Rotate(angle.gnp());
				vector2d p3 = k3.Rotate(angle.gnp());
				realn TempX = x + cw - UnitHeight / 2.0;
				realn TempY = y + UnitHeight / 2.0;
				DrawLine(p1.x + TempX, p1.y + TempY, p2.x + TempX, p2.y + TempY, LIGHTGRAY);
				DrawLine(p2.x + TempX, p2.y + TempY, p3.x + TempX, p3.y + TempY, LIGHTGRAY);
				if (MouseInRect(x, y + h / 2.0, cw, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))Open();
					DrawRectangle(x, y + h / 2.0, cw, UnitHeight - h, UnitBgColor);
					DrawRectangle(x + cw - UnitHeight, y + h / 2, UnitHeight, UnitHeight - h, UnitBgColor);
					DrawLine(p1.x + TempX, p1.y + TempY, p2.x + TempX, p2.y + TempY, LIGHTGRAY);
					DrawLine(p2.x + TempX, p2.y + TempY, p3.x + TempX, p3.y + TempY, LIGHTGRAY);
				}
				if (move.gnp() > 0) {
					DrawRectangle(x, y + h / 2.0 + UnitHeight, cw, move.gnp(), UnitBgColor);
				}
				return UnitHeight;
			}
		};
		int TempHeight = 0;
		class Dropdown : public Element {
		private:
			Animation move;
			Animation angle;
			int Height = 0;
			bool swapping = false;
		public:
			std::string text = "Dropdown";
			bool open = false;
			bool deep = 0;
			bool draw_background = true;
			bool draw_menu_background = false;
			bool insert_ani = false;
			Dropdown() {
				angle.sd(300);
				move.sd(300 * log(5 * UnitHeight) / 4);
				angle.sms(anif::bounce5);
				move.sms(MoveAni, -10.68721, 0);
			}
			void Open() {
				open = true;
				angle.stp(acos(-1) / 2);
				move.stp(Height);
			}
			void Close() {
				open = false;
				angle.stp(0);
				move.stp(0);
			}
			static realn MoveAni(realn x) {
				realn h = TempHeight - UnitHeight * 5;
				if (h > 0) {
					if (x > -7.68721)return anif::bounceFun(x);
					realn c = TempHeight / UnitHeight / 5.0 * anif::bounceFun(-7.68721);
					realn c1 = h / UnitHeight / 5.0 * anif::bounceFun(-7.68721);
					return c + (x + 7.68721) * (h / 3.0);
				} else {
					return anif::bounceFun(x * 7.68721 / 8.9726);
				}
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				Height = 0;
				X = x, Y = y, W = w;
				swapping = false;
				for (int i = 0; i < key.size(); i++)
					Height += key[i]->height;
				TempHeight = Height;
				angle.Update();
				move.Update();
				int h = (UnitHeight - TextHeight) / 2;
				if (draw_menu_background)DrawRectangle(x, y + UnitHeight - h, w, move.gnp(), Color{20, 20, 20, 150});
				if (deep == 0 && draw_background)DrawRectangle(x, y + h / 2, w, UnitHeight - h, MainColor);
				if (MouseInRect(x, y + h / 2, w, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						if (!open)Open();
						else Close();
					}
					DrawRectangle(x, y + h / 2, w, UnitHeight - h, ChooseColor);
				}
				special_effect::DrawMouseRectangle(x, y + h / 2, w, UnitHeight - h);
				Print(x + 2 * h + UnitHeight, y + h, text, WHITE);
				vector2d k1 = vector2d {-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8};
				vector2d k2 = vector2d {TextHeight / 4 * 0.8, 0};
				vector2d k3 = vector2d {-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8};
				vector2d p1 = k1.Rotate(angle.gnp());
				vector2d p2 = k2.Rotate(angle.gnp());
				vector2d p3 = k3.Rotate(angle.gnp());
				int TempX = x + h + UnitHeight / 2;
				int TempY = y + UnitHeight / 2;
				DrawLine(p1.x + TempX, p1.y + TempY, p2.x + TempX, p2.y + TempY, LIGHTGRAY);
				DrawLine(p2.x + TempX, p2.y + TempY, p3.x + TempX, p3.y + TempY, LIGHTGRAY);
				if (move.gnp() != Height && open && move.gnp() == move.gtp()) {
					move.ssp(Height);
					move.stp(Height);
				}
				if (open)Open();
				BeginScissor(x, y + UnitHeight, w, move.gnp());
				check &= open;
				if (move.gnp() != 0) {
					realn nowh = move.gnp() - Height;
					realn nowh2 = 0;
					for (int i = 0; i < key.size(); i++)nowh2 += key[i]->Draw_Auto(x + UnitHeight * 0.7, y + UnitHeight + nowh, w - UnitHeight * 1.4, check && !swapping);
				}
				EndScissor();
				height = move.gnp() + UnitHeight;
				return height;
			}
		};
		class Box : public Element {
		private:
			int Height = 0;
			bool swapping = false;
		public:
			bool insert_ani = false;
			int Draw(int x, int y, int w, bool check = true) {
				Height = 0;
				X = x, Y = y, W = w, CHECK = check;
				swapping = false;
				for (int i = 0; i < key.size(); i++)Height += key[i]->height;
				DrawRectangle(x, y, w, Height, Color{43, 43, 43, 255});
				ui::special_effect::DrawFrame(x, y, w, Height);
				realn nowh = 0;
				for (int i = 0; i < key.size(); i++)nowh += key[i]->Draw_Auto(x + UnitHeight, y, w - UnitHeight * 2, check && !swapping);
				height = Height;
				return height;
			}
		};

		vector2d _v(Vector2 v) {
			return vector2d {v.x, v.y};
		}
		Vector2 _V(vector2d v) {
			return Vector2 {v.x, v.y};
		}
		vector3d _v(Vector3 v) {
			return vector3d {v.x, v.y, v.z};
		}
		Vector3 _V(vector3d v) {
			return Vector3 {v.x, v.y, v.z};
		}
		vector2d _polar(vector2d v) {
			return vector2d{v.x * cos(v.y), v.x * sin(v.y)};
		}
		vector2d get_rel(vector2d p, vector2d rfrc, realn rotate) {
			return p.Rotate(rotate) + rfrc;
		}
		vector2d get_rel(vector2d p, vector2d rfrc, vector2d dir) {
			return p.Rotate(atan2(dir.y, dir.x)) + rfrc;
		}
		class GraphDebugger : public Element {
		public:
			vector2d camera = {0, 0};
			bool choose = false;
			bool mouse_move = false;
			bool movable = true;
			realn zoom = 100;
			realn startx, starty, endx, endy;
			realn mesh_startx, mesh_starty, mesh_endx, mesh_endy;
			realn click_time = 0;
			vector2d choose_pos;
			Animation zoom_ani;
			Animation ilenAni, idegAni;
			Animation jlenAni, jdegAni;
			Slider zoom_slider;
			std::map <vector2d*, std::pair<Animation, Animation> > v2ani;
			std::map <vector2d*, bool> v2state;
			void (*draw_fun)(GraphDebugger*) = nullptr;

			bool mesh_visible = true;
			bool axis_visible = true;
			bool zoom_visible = true;
			bool polar_visible = false;
			bool number_visible = true;
			bool mesh_limit = false;
			realn move_threshold_dist = 5 * ui::dpi;
			realn move_threshold_time = 0.3;

			GraphDebugger(void (*DrawFun)(GraphDebugger*) = nullptr) {
				zoom_ani.sd(300);
				zoom_ani.ssp(2);
				ilenAni.sd(1000), ilenAni.ssp(1);
				idegAni.sd(1000), idegAni.ssp(0);
				jlenAni.sd(1000), jlenAni.ssp(1);
				jdegAni.sd(1000), jdegAni.ssp(3.1415926535897932 / 2);
				ilenAni.sms(anif::tanh);
				jlenAni.sms(anif::tanh);
				idegAni.sms(anif::tanh);
				jdegAni.sms(anif::tanh);
				extra = true;
				zoom_slider.text_visible = false;
				zoom_slider.minn = -3;
				zoom_slider.maxn = 7;
				draw_fun = DrawFun;
			}
			void set_zoom(realn z = 2) {
				zoom_ani.SetTargetPos(z);
			}
			realn get_zoom() {
				return zoom_ani.gnp();
			}
			void set_position(vector2d pos) {
				camera = pos;
			}
			void set_position(realn x, realn y) {
				camera = vector2d{x, y};
			}
			std::string ts(realn a) {
				std::ostringstream out;
				out << a;
				return out.str();
			}
			vector2d W2S(vector2d w) {
				w.x = (w.x - camera.x) * zoom + W / 2;
				w.y = -(w.y - camera.y) * zoom + H / 2;
				return w;
			}
			vector2d W2S(realn wx, realn wy) {
				wx = (wx - camera.x) * zoom + W / 2;
				wy = -(wy - camera.y) * zoom + H / 2;
				return vector2d{wx, wy};
			}
			realn W2S(realn w) {
				return w*zoom;
			}
			vector2d S2W(vector2d s) {
				s.x -= W / 2;
				s.y -= H / 2;
				s.y = -s.y;
				s /= zoom;
				s += camera;
				return s;
			}
			vector2d S2W(realn sx, realn sy) {
				sx -= W / 2;
				sy -= H / 2;
				sy = -sy;
				sx /= zoom;
				sy /= zoom;
				sx += camera.x;
				sy += camera.y;
				return vector2d{sx, sy};
			}
			realn S2W(realn s) {
				return s / zoom;
			}
			vector2d GetMouse() {
				if (!CHECK)return {0, 0};
				return S2W(vector2d{Mouse.x - X, Mouse.y - Y});
			}
			bool MousePressed(MouseButton mb) {
				return IsMouseButtonReleased(mb) && !mouse_move && CHECK && MouseInRect(X, Y, W, H);
			}

			void DrawMesh_(realn sspace, Color color, bool num = false) {
				vector2d O = W2S({0, 0});
				realn x = X, y = Y, w = W, h = H;
				zoom = pow(10, zoom_ani.gnp());
				realn startx = -ceil(1.0 * (O.x) / sspace) * sspace + O.x + x;
				realn starty = -ceil(1.0 * (O.y) / sspace) * sspace + O.y + y;
				if (mesh_limit) {
					vector2d ms = W2S(mesh_startx, mesh_endy) + vector2d{X, Y};
					vector2d me = W2S(mesh_endx, mesh_starty) + vector2d{X, Y};
					for (realn i = startx; i <= x + w; i += sspace)if (i >= ms.x && i <= me.x)DrawLine(i, std::max(y, ms.y), i, std::min(y + h, me.y), color);
					for (realn i = starty; i <= y + h; i += sspace)if (i >= ms.y && i <= me.y)DrawLine(std::max(x, ms.x), i, std::min(x + w, me.x), i, color);
					DrawRectangleLines(round(ms.x), round(ms.y), round(me.x) - round(ms.x), round(me.y) - round(ms.y), LIGHTGRAY);
				} else {
					for (realn i = startx; i <= x + w; i += sspace)DrawLine(i, y, i, y + h, color);
					for (realn i = starty; i <= y + h; i += sspace)DrawLine(x, i, x + w, i, color);
				}
				if (num) {
					if (sspace <= 70 * dpi)sspace = sspace * 5;
					for (realn i = std::max((realn)O.x, O.x + int((x - O.x) / sspace) * sspace); i <= w; i += sspace) {
						realn k = S2W({i, 0}).x;
						std::string s = ts(k);
						if (i == O.x)s = "[0]";
						Print(i + x, y, s.c_str());
					}
					for (realn i = std::min((realn)(O.x - sspace), O.x + int((x + W - O.x) / sspace) * sspace); i >= 0; i -= sspace) {
						realn k = S2W({i, 0}).x;
						std::string s = ts(k);
						Print(i + x, y, s.c_str());
					}
					for (realn i = std::max((realn)O.y, O.y + int((y - O.y) / sspace) * sspace); i <= H; i += sspace) {
						realn k = S2W({0, i}).y;
						std::string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str());
					}
					for (realn i = std::min((realn)(O.y - sspace), O.y + int((y + W - O.y) / sspace) * sspace); i >= 0; i -= sspace) {
						realn k = S2W({0, i}).y;
						std::string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str());
					}
				}
			}
			bool in_sight(realn x, realn y) {
				vector2d a = W2S({x, y});
				if (a.x >= 0 && a.x <= W && a.y >= 0 && a.y <= H)return true;
				return false;
			}
			bool in_sight(vector2d v) {
				vector2d a = W2S(v);
				if (a.x >= 0 && a.x <= W && a.y >= 0 && a.y <= H)return true;
				return false;
			}
			bool in_sight(realn x1, realn y1, realn x2, realn y2) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 > y2)std::swap(y1, y2);
				if (x2 < startx || x1 > endx || y2 < starty || y1 > endy)return false;
				else return true;
			}
			void draw_text(realn x, realn y, std::string text, Color color = GREEN) {
				if (!in_sight(x, y))return;
				vector2d a = W2S({x, y});
				Print(a.x + X - strLen(text)*ui::TextHeight / 4, a.y + Y - ui::TextHeight / 2, text, color);
			}
			void draw_text(vector2d pos, std::string text, Color color = GREEN) {
				draw_text(pos.x, pos.y, text, color);
			}
			void draw_point(realn x, realn y, Color color = GREEN) {
				if (!in_sight(x, y))return;
				vector2d a = W2S({x, y});
				DrawCircle(a.x + X, a.y + Y, 2.5 * dpi, color);
			}
			void draw_point(vector2d v, Color color = GREEN) {
				draw_point(v.x, v.y, color);
			}
			bool choose_point = false;
			bool float_point = false;
			void draw_point_controlled_rel(vector2d* v, vector2d rfrc = {0, 0}, realn rotate = 0, Color color = GREEN) {
				vector2d abs_v = v->Rotate(rotate) + rfrc;
				if (!in_sight(abs_v) && !v2state[v])return;
				else {
					vector2d m = _v(Mouse) - vector2d{X, Y};
					vector2d a = W2S(abs_v);
					DrawCircle(a.x + X, a.y + Y, 8 * dpi, Color{100 + color.r / 2, 100 + color.g / 2, 100 + color.b / 2, 50});
					draw_point(abs_v, color);
					if (Mod2(m - a) < 64 * dpi * dpi || v2state[v]) {
						if (CHECK) {
							if (!float_point)DrawCircleLines(a.x + X, a.y + Y, 8 * dpi, color);
							MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
							if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !choose_point && ChooseSlider == NULL) {
								if (!float_point)v2state[v] = true;
								choose_point = true;
							}
							float_point = true;
						}
					}
					if (v2state[v] && ChooseSlider == NULL) {
						(*v) = (S2W(m) - rfrc).Rotate(-rotate);
						choose = false;
					}
					if (v2state[v] && ChooseSlider == NULL) {
						(*v) = (S2W(m) - rfrc).Rotate(-rotate);
						MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
						choose = false;
					}
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
						for (auto i = v2state.begin(); i != v2state.end(); i++)i->second = false;
						choose_point = false;
					}
				}
			}
			void draw_point_controlled_rel(vector2d* v, vector2d rfrc = {0, 0}, vector2d dir = {1, 0}, Color color = GREEN) {
				draw_point_controlled_rel(v, rfrc, atan2(dir.y, dir.x), color);
			}
			void draw_point_controlled(vector2d* v, Color color = GREEN) {
				draw_point_controlled_rel(v, vector2d{0, 0}, 0, color);
			}
			void draw_line(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
			}
			void draw_line(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_line(v1.x, v1.y, v2.x, v2.y, color);
			}
			void draw_line_controlled(vector2d *v1, vector2d *v2, Color color = GREEN) {
				draw_line(*v1, *v2, color);
				draw_point_controlled(v1, color);
				draw_point_controlled(v2, color);
			}
			void draw_ray(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				vector2d a = W2S({x1, y1}), b = W2S(vector2d{x1 + x2 * 10000, y1 + y2 * 10000});
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
			}
			void draw_ray(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_ray(v1.x, v1.y, v2.x, v2.y, color);
			}
			void draw_ray_controlled(vector2d *v1, vector2d *v2, Color color = GREEN) {
				draw_ray(*v1, *v2, color);
				draw_point_controlled(v1, color);
				draw_point_controlled(v2, color);
			}
			void draw_rectangle_lines(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangleLines(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color);
			}
			void draw_rectangle(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				a = W2S({x1, y1}), b = W2S({x2, y2});
				if (b.x - a.x >= 4 * ui::dpi && b.y - a.y >= 4 * ui::dpi) {
					color2 = color;
					color2.a *= 0.2;
					DrawRectangle(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color2);
					DrawRectangleLines(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), color);
				} else {
					if (round(b.x) - round(a.x) < 1 || round(b.y) - round(a.y) < 1)return;
					color2 = color;
					color2.a *= 0.6;
					DrawRectangle(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), color2);
				}
			}
			void draw_rectangle_solid(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangle(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), color);
			}
			void draw_rectangle(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_rectangle(v1, v2, color);
			}
			void draw_rectangle_controlled(vector2d *v1, vector2d *v2, Color color = GREEN) {
				draw_rectangle(*v1, *v2, color);
				draw_point_controlled(v1, color);
				draw_point_controlled(v2, color);
			}
			void draw_rectangle(vector2d pos, realn w, realn h, realn rotate, Color color = GREEN) {
				vector2d p[5];
				p[0] = rel2abs(vector2d{w / 2, h / 2}, pos, rotate);
				p[1] = rel2abs(vector2d{-w / 2, h / 2}, pos, rotate);
				p[2] = rel2abs(vector2d{-w / 2, -h / 2}, pos, rotate);
				p[3] = rel2abs(vector2d{w / 2, -h / 2}, pos, rotate);
				Vector2 p2[5];
				p2[0] = _V(W2S(p[0]) + vector2d(X, Y));
				p2[1] = _V(W2S(p[1]) + vector2d(X, Y));
				p2[2] = _V(W2S(p[2]) + vector2d(X, Y));
				p2[3] = _V(W2S(p[3]) + vector2d(X, Y));
				color2 = color;
				color2.a *= 0.2;
				DrawTriangleFan(p2, 4, color2);
				draw_line(p[0], p[1], color);
				draw_line(p[1], p[2], color);
				draw_line(p[2], p[3], color);
				draw_line(p[3], p[0], color);
			}
			void draw_rectangle_solid(vector2d pos, realn w, realn h, realn rotate, Color color = GREEN) {
				vector2d p[5];
				p[0] = rel2abs(vector2d{w / 2, h / 2}, pos, rotate);
				p[1] = rel2abs(vector2d{-w / 2, h / 2}, pos, rotate);
				p[2] = rel2abs(vector2d{-w / 2, -h / 2}, pos, rotate);
				p[3] = rel2abs(vector2d{w / 2, -h / 2}, pos, rotate);
				Vector2 p2[5];
				p2[0] = _V(W2S(p[0]) + vector2d(X, Y));
				p2[1] = _V(W2S(p[1]) + vector2d(X, Y));
				p2[2] = _V(W2S(p[2]) + vector2d(X, Y));
				p2[3] = _V(W2S(p[3]) + vector2d(X, Y));
				DrawTriangleFan(p2, 4, color);
			}
			void draw_triangle(vector2d p1, vector2d p2, vector2d p3, Color color = GREEN) {
				vector2d t1 = W2S(p1) + vector2d{X, Y};
				vector2d t2 = W2S(p2) + vector2d{X, Y};
				vector2d t3 = W2S(p3) + vector2d{X, Y};
				color2 = color;
				color2.a *= 0.2;
				DrawTriangle(_V(t1), _V(t2), _V(t3), color2);
				DrawTriangle(_V(t1), _V(t3), _V(t2), color2);
				DrawTriangleLines(_V(t1), _V(t2), _V(t3), color);
			}
			void draw_triangle_solid(vector2d p1, vector2d p2, vector2d p3, Color color = GREEN) {
				vector2d t1 = W2S(p1) + vector2d{X, Y};
				vector2d t2 = W2S(p2) + vector2d{X, Y};
				vector2d t3 = W2S(p3) + vector2d{X, Y};
				DrawTriangle(_V(t1), _V(t2), _V(t3), color);
				DrawTriangle(_V(t1), _V(t3), _V(t2), color);
			}
			void draw_triangle(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = GREEN) {
				draw_triangle(vector2d{x1, y1}, vector2d{x2, y2}, vector2d{x3, y3}, color);
			}
			void draw_triangle_solid(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = GREEN) {
				draw_triangle_solid(vector2d{x1, y1}, vector2d{x2, y2}, vector2d{x3, y3}, color);
			}
			void draw_triangle_controlled(vector2d *p1, vector2d *p2, vector2d *p3, Color color = GREEN) {
				draw_triangle(*p1, *p2, *p3, color);
				draw_point_controlled(p1, color);
				draw_point_controlled(p2, color);
				draw_point_controlled(p3, color);
			}
			void draw_arc(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = GREEN) {
				realn a = x1 - x2;
				realn b = y1 - y2;
				realn c = x1 - x3;
				realn d = y1 - y3;
				realn e = ((x1 * x1 - x2 * x2) - (y2 * y2 - y1 * y1)) / 2;
				realn f = ((x1 * x1 - x3 * x3) - (y3 * y3 - y1 * y1)) / 2;
				realn x = (e * d - b * f) / (a * d - b * c);
				realn y = (a * f - e * c) / (a * d - b * c);
				realn r = Mod(vector2d{x1, y1} -vector2d{x, y});
				realn a1 = atan2(y1 - y, x1 - x);
				realn a2 = atan2(y2 - y, x2 - x);
				realn a3 = atan2(y3 - y, x3 - x);
				if (a1 < 0)a1 = 2 * PI + a1;
				if (a2 < 0)a2 = 2 * PI + a2;
				if (a3 < 0)a3 = 2 * PI + a3;
				if (a2 < a1)a2 += PI * 2;
				if (a3 < a1)a3 += PI * 2;
				a1 = a1 * 180 / PI + 90;
				a2 = a2 * 180 / PI + 90;
				a3 = a3 * 180 / PI + 90;
				vector2d v = vector2d{x, y};
				v = W2S(v) + vector2d{X, Y};
				if (a2 - a1 < a3 - a1)DrawRingLines(_V(v), r * zoom, r * zoom, a1, a3, 0, color);
				if (a2 - a1 > a3 - a1) {
					if (a1 < a3)a1 += 360;
					DrawRingLines(_V(v), r * zoom, r * zoom, a3, a1, 0, color);
				}
//				if(Cross(vector2d{x1-x,y1-y},vector2d{x2-x,y2-y}))DrawRingLines(_V(v),r*zoom,r*zoom,a1*180/PI+90,a2*180/PI+90,0,color);
//				else DrawRingLines(_V(v),r*zoom,r*zoom,a2*180/PI+90,a1*180/PI+90,0,color);
//				if(Cross(vector2d{x2-x,y2-y},vector2d{x3-x,y3-y}))DrawRingLines(_V(v),r*zoom,r*zoom,a2*180/PI+90,a3*180/PI+90,0,color);
//				else DrawRingLines(_V(v),r*zoom,r*zoom,a3*180/PI+90,a2*180/PI+90,0,color);
			}
			void draw_arc(vector2d p1, vector2d p2, vector2d p3, Color color = GREEN) {
				draw_arc(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
			}
			void draw_arc_controlled(vector2d *p1, vector2d *p2, vector2d *p3, Color color = GREEN) {
				draw_arc(*p1, *p2, *p3, color);
				draw_point_controlled(p1, color);
				draw_point_controlled(p2, color);
				draw_point_controlled(p3, color);
			}
			void draw_circle(realn x1, realn y1, realn r, Color color = GREEN) {
				a = W2S({x1, y1});
				color2 = color;
				color2.a *= 0.2;
				DrawCircleSector({a.x + X, a.y + Y}, r * zoom, 0, 360, 0, color2);
				DrawRingLines({a.x + X, a.y + Y}, r * zoom, r * zoom, 0, 360, 0, color);
			}
			void draw_circle_solid(realn x1, realn y1, realn r, Color color = GREEN) {
				a = W2S({x1, y1});
				DrawCircleSector({a.x + X, a.y + Y}, r * zoom, 0, 360, 0, color);
			}
			void draw_circle(vector2d pos, realn r, Color color = GREEN) {
				draw_circle(pos.x, pos.y, r, color);
			}
			void draw_circle_solid(vector2d pos, realn r, Color color = GREEN) {
				draw_circle_solid(pos.x, pos.y, r, color);
			}
			void draw_ellipse(vector2d pos, realn a, realn b, realn rotate = 0, Color color = GREEN) {
				Vector2 p2[30];
				for (int i = 0; i < 30; i++) {
					realn th = PI * i / 15.0, th2 = PI * (i + 1) / 15.0;
					vector2d t = rel2abs({cos(th)*a, sin(th)*b}, pos, rotate);
					vector2d t2 = rel2abs({cos(th2)*a, sin(th2)*b}, pos, rotate);
					draw_line(t, t2);
					p2[i] = _V(W2S(t) + vector2d(X, Y));
				}
				color2 = color;
				color2.a *= 0.2;
				DrawTriangleFan(p2, 30, color2);
			}
			void draw_vector(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				x2 += x1, y2 += y1;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.5);
				vector2d v2 = (b - a).Rotate(-2.5);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
				if (Mod(a - b) > 30 * ui::dpi) {
					v1 = VecUnit(v1) * 10 * ui::dpi;
					v2 = VecUnit(v2) * 10 * ui::dpi;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, color);
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, color);
				} else {
					v1 = VecUnit(v1) * Mod(a - b) / 3.0;
					v2 = VecUnit(v2) * Mod(a - b) / 3.0;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, color);
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, color);
				}
			}
			void draw_vector_head(realn x1, realn y1, realn x2, realn y2, Color color = GREEN) {
				x2 += x1, y2 += y1;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.75);
				vector2d v2 = (b - a).Rotate(-2.75);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
				vector2d t = vector2d{X, Y};
				if (Mod(a - b) > 37.5 * ui::dpi) {
					v1 = VecUnit(v1) * 12.5 * ui::dpi;
					v2 = VecUnit(v2) * 12.5 * ui::dpi;
					DrawTriangle(_V(b + t), _V(b + v2 + t), _V(b + v1 + t), color);
				} else {
					v1 = VecUnit(v1) * Mod(a - b) / 3.0;
					v2 = VecUnit(v2) * Mod(a - b) / 3.0;
					DrawTriangle(_V(b + t), _V(b + v2 + t), _V(b + v1 + t), color);
				}
			}
			void draw_vector(realn x, realn y, Color color = GREEN) {
				draw_vector(0, 0, x, y, color);
			}
			void draw_vector(vector2d v, Color color = GREEN) {
				draw_vector(0, 0, v.x, v.y, color);
			}
			void draw_vector(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_vector(v1.x, v1.y, v2.x, v2.y, color);
			}
			void draw_vector_controlled(vector2d* pos, vector2d* dir, Color color = GREEN) {
				draw_vector(*pos, *dir);
				draw_point_controlled_rel(dir, *pos, 0, color);
				draw_point_controlled(pos, color);
			}
			void draw_vector_controlled(vector2d* dir, Color color = GREEN) {
				draw_vector(*dir, color);
				draw_point_controlled_rel(dir, {0, 0}, 0, color);
			}
			void draw_vector_head(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_vector_head(v1.x, v1.y, v2.x, v2.y, color);
			}
			void draw_vector_head_controlled(vector2d* pos, vector2d* dir, Color color = GREEN) {
				draw_vector_head(*pos, *dir);
				draw_point_controlled_rel(dir, *pos, 0, color);
				draw_point_controlled(pos, color);
			}
			void draw_arrow(vector2d pos, vector2d dir, Color color = GREEN) {
				dir.y = -dir.y;
				dir = VecUnit(dir);
				a = W2S(pos);
				a += dir * 7 * ui::dpi;
				vector2d v1 = dir.Rotate(2.75);
				vector2d v2 = dir.Rotate(-2.75);
				vector2d t = vector2d{X, Y};
				v1 = VecUnit(v1) * 12.5 * ui::dpi;
				v2 = VecUnit(v2) * 12.5 * ui::dpi;
				DrawTriangle(_V(a + t), _V(a + v2 + t), _V(a + v1 + t), color);
			}
			void draw_arrow(realn x, realn y, realn dx, realn dy, Color color = GREEN) {
				draw_arrow(vector2d{x, y}, vector2d{dx, dy}, color);
			}
			void draw_vector_withAni(vector2d v1, vector2d* v2, Color color = GREEN) {
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.stp(v2->x);
				v2ani[v2].second.stp(v2->y);
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.sms(anif::tanh);
				v2ani[v2].second.sms(anif::tanh);
				draw_vector(0, 0, v2ani[v2].first.gnp(), v2ani[v2].second.gnp(), color);
			}
			void draw_vector_withAni(vector2d* v2, Color color = GREEN) {
				draw_vector_withAni({0, 0}, v2, color);
			}
			void draw_bezier2(vector2d v1, vector2d v2, vector2d v3, Color color = GREEN) {
				vector2d l = v1;
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector2d p1 = (v2 - v1) * t + v1;
					vector2d p2 = (v3 - v2) * t + v2;
					vector2d p3 = (p2 - p1) * t + p1;
					draw_line(l, p3, color);
					l = p3;
				}
			}
			void draw_bezier3(vector2d v1, vector2d v2, vector2d v3, vector2d v4, Color color = GREEN) {
				vector2d l = v1;
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector2d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					draw_line(l, p, color);
					l = p;
				}
			}
			void draw_bezier3_mesh(vector2d v1, vector2d v2, vector2d v3, vector2d v4, realn radius = 1, Color color = GREEN) {
				vector2d l = v1, l1 = v1, l2 = v1;
				Color c1, c2;
				c1 = c2 = color;
				c1.a *= 0.3;
				c2.a *= 0.6;
				for (realn t = 0, i = 0; t <= 1.01; t += 0.02, i++) {
					vector2d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					vector2d dp = v1 * (-3 * t * t + 6 * t - 3) + v2 * (9 * t * t - 12 * t + 3) + v3 * (-9 * t * t + 6 * t) + v4 * (3 * t * t);
					vector2d temp = dp.Rotate(G_PI / 2);
					temp = VecUnit(temp);
					draw_line(l, p, color);
					draw_line(l1, p + temp * radius, c2);
					draw_line(l2, p - temp * radius, c2);
					if (int(i) % 5 == 0) {
						draw_line(p, p + temp * radius, c1);
						draw_line(p, p - temp * radius, c1);
					}
					l = p;
					l1 = p + temp * radius;
					l2 = p - temp * radius;
				}
			}
			void draw_function(realn (*fun)(realn), Color color = GREEN) {
				for (realn i = startx; i <= endx; i += 1.0 / zoom)draw_line(i, fun(i), i + 1.0 / zoom, fun(i + 1.0 / zoom), color);
			}
			void draw_function_polar(realn (*fun)(realn), realn start = 0, realn end = PI * 2, int prec = 100, Color color = GREEN) {
				for (int i = 0; i < prec; i++) {
					realn t1 = start + 1.0 * i * (end - start) / prec;
					realn t2 = start + 1.0 * (i + 1) * (end - start) / prec;
					vector2d k1 = _polar({fun(t1), t1});
					vector2d k2 = _polar({fun(t2), t2});
					draw_line(k1.x, k1.y, k2.x, k2.y, color);
				}
			}
			void draw_function(vector2d (*fun)(realn), realn start = 0, realn end = 10, int prec = 5, Color color = GREEN) {
				for (realn i = start; i < end; i += 1.0 / prec)draw_line(fun(i).x, fun(i).y, fun(i + 1.0 / prec).x, fun(i + 1.0 / prec).y, color);
			}
			void draw_mesh(vector2d (*mesh)(realn, realn), realn sx, realn ex, realn sy, realn ey, realn space = 1.0, int prec = 5, Color color = GREEN) {
				for (realn i = sx; i <= ex; i += space) {
					for (realn j = sy; j < ey; j += space / prec) {
						draw_line(mesh(i, j), mesh(i, j + space / prec), color);
					}
				}
				for (realn j = sy; j <= ey; j += space) {
					for (realn i = sx; i < ex; i += space / prec) {
						draw_line(mesh(i, j), mesh(i + space / prec, j), color);
					}
				}
			}
			void draw_liner_transformation(realn m11, realn m12, realn m21, realn m22, realn r = 10, realn space = 1.0, Color color = GREEN) {
				realn r2 = ceil(r / space) * space;
				for (realn i = -r2; i <= r2; i += space) {
					draw_line(m11 * i + m12 * (-r), m21 * i + m22 * (-r), m11 * i + m12 * r, m21 * i + m22 * r, color);
					draw_line(m11 * (-r) + m12 * i, m21 * (-r) + m22 * i, m11 * r + m12 * i, m21 * r + m22 * i, color);
				}
			}
			void draw_liner_transformation_withAni(realn m11, realn m12, realn m21, realn m22, realn r = 10, realn space = 1.0, Color color = GREEN) {
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				ilenAni.stp(sqrt(m11 * m11 + m21 * m21));
				jlenAni.stp(sqrt(m12 * m12 + m22 * m22));
				if (abs(atan2(m21, m11) - idegAni.gnp()) > abs(atan2(m21, m11) - idegAni.gnp() + 3.1415926535897932 * 2))idegAni.stp(atan2(m21, m11) + 3.1415926535897932 * 2);
				else if (abs(atan2(m21, m11) - idegAni.gnp()) > abs(atan2(m21, m11) - idegAni.gnp() - 3.1415926535897932 * 2))idegAni.stp(atan2(m21, m11) - 3.1415926535897932 * 2);
				else idegAni.stp(atan2(m21, m11));
				if (abs(atan2(m22, m12) - jdegAni.gnp()) > abs(atan2(m22, m12) - jdegAni.gnp() + 3.1415926535897932 * 2))jdegAni.stp(atan2(m22, m12) + 3.1415926535897932 * 2);
				else if (abs(atan2(m22, m12) - jdegAni.gnp()) > abs(atan2(m22, m12) - jdegAni.gnp() - 3.1415926535897932 * 2))jdegAni.stp(atan2(m22, m12) - 3.1415926535897932 * 2);
				else jdegAni.stp(atan2(m22, m12));
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				realn il = ilenAni.gnp(), jl = jlenAni.gnp();
				realn id = idegAni.gnp(), jd = jdegAni.gnp();
				realn ix = il * cos(id), iy = il * sin(id);
				realn jx = jl * cos(jd), jy = jl * sin(jd);
				draw_liner_transformation(ix, jx, iy, jy, r, space, color);
				draw_vector(ix, iy, RED);
				draw_vector(jx, jy, BLUE);
			}
			// std::vector<std::vector<realn> > LastMeshPosX,LastMeshPosY;
			// void draw_mesh_withAni(vector2d (*mesh)(realn,realn),realn sx,realn ex,realn sy,realn ey,realn space=1.0,int prec=5,Color color=GREEN) {
			// 	if((ex-sx)*prec/space+10>1000||(ex-sx)*prec/space+10>1000) {
			// 		draw_mesh(vector2d (*mesh)(realn,realn),realn sx,realn ex,realn sy,realn ey,realn space=1.0,int prec=5,Color color=GREEN);
			// 		return;
			// 	}
			// 	if(LastMeshPosX.size()!=(ex-sx)*prec/space+10)LastMeshPosX.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosY.size()!=(ey-sy)*prec/space+10)LastMeshPosY.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosY.size()!=(ex-sx)/space+10)for(int i=0;i<LastMeshPosY.size();i++)LastMeshPosY.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosX.size()!=(ey-sy)/space+10)for(int i=0;i<LastMeshPosX.size();i++)LastMeshPosX.resize((ex-sx)*prec/space+10);
			// 	for(realn i=sx;i<=ex;i+=space) {
			// 		for(realn j=sy;j<ey;j+=space/prec) {
			// 			draw_line(mesh(i,j),mesh(i,j+space/prec),color);
			// 		}
			// 	}
			// 	for(realn j=sy;j<=ey;j+=space) {
			// 		for(realn i=sx;i<ex;i+=space/prec) {
			// 			draw_line(mesh(i,j),mesh(i+space/prec,j),color);
			// 		}
			// 	}
			// }
			void draw_shape(pg::shape* shape, Color color) {
				shape->Draw(this, color.r, color.g, color.b, color.a);
				draw_point(shape->pos, color);
				draw_line(shape->pos, shape->pos + vector2d{0, 0.3}.Rotate(shape->rotate));
			}
			void draw_shape_controlled(pg::shape* shape, Color color) {
				shape->Draw(this, color.r, color.g, color.b, color.a);
				draw_line(shape->pos, shape->pos + vector2d{0, 0.3}.Rotate(shape->rotate));
				draw_point_controlled(&shape->pos, color);
			}

			vector2d last_mouse_pos{0, 0};
			int Draw(int x, int y, int w, int h, bool check = true) {
				X = x, Y = y, W = w, H = h, CHECK = check;
				BeginScissor(x, y, w, h);
				zoom_ani.Update();
				zoom = pow(10, zoom_ani.gnp());
				startx = S2W({0, 0}).x, endx = S2W({w, 0}).x;
				starty = S2W({0, h}).y, endy = S2W({0, 0}).y;
				realn wspace = pow(10, ceil(log10(30 * dpi / zoom)));
				realn sspace = wspace * zoom;
				float_point = false;
				vector2d O = W2S({0, 0});

				if (movable) {
					if (MouseInRect(x, y, w, h))UseSliderX = UseSliderY = true;
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						click_time = GetTime();
						if (MouseInRect(x, y, w, h) && check && !ChooseSlider != NULL) {
							choose = true;
							choose_pos = S2W(_v(Mouse) - vector2d{x, y});
						}
					}
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && check)choose = false;
					vector2d move = S2W(_v(Mouse) - vector2d{x, y}) - choose_pos;
					if (choose && !ChooseSlider != NULL && check) {
						if (Mod(_v(Mouse) - last_mouse_pos) > move_threshold_dist)camera -= move;
						startx = S2W({0, 0}).x, endx = S2W({w, 0}).x;
						starty = S2W({0, h}).y, endy = S2W({0, 0}).y;
						O = W2S({0, 0});
					}
					if (Mod(_v(Mouse) - last_mouse_pos) >= move_threshold_dist)mouse_move = true;
					else mouse_move = false;
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))last_mouse_pos = _v(Mouse);
				} else mouse_move = false;

				if (mesh_visible) {
					if (sspace / 10.0 > 10 * dpi) {
						realn a = (sspace / 10 - 10 * dpi) / (20.0 * dpi);
						DrawMesh_(sspace / 10, Color{60, 60, 60, a * 255});
						DrawMesh_(sspace, Color{60 + 60 * a, 60 + 60 * a, 60 + 60 * a, 255}, true);
						DrawMesh_(sspace * 10, Color{120 + 60 * a, 120 + 60 * a, 120 + 60 * a, 255});
					} else {
						DrawMesh_(sspace, Color{60, 60, 60, 255}, true);
						DrawMesh_(sspace * 10, Color{120, 120, 120, 255});
					}
				}
				if (polar_visible) {
				}
				if (axis_visible) {
					DrawRectangle(x + O.x - 3 * dpi, y + O.y - 3 * dpi, 6 * dpi, 6 * dpi, LIGHTGRAY);
					DrawLine(x, y + O.y, x + w, y + O.y, LIGHTGRAY);
					DrawLine(x + O.x, y, x + O.x, y + h, LIGHTGRAY);
				}
				zoom_ani.update();
				if (ChooseSlider == NULL)zoom_slider.num = zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (draw_fun != nullptr) {
					BeginScissor(X, Y, W, H);
					draw_fun(this);
					EndScissor();
				}
				if (zoom_visible) {
					int tw = std::min(int(300 * dpi), w - ui::SpaceSize * 4);
					DrawRectangleRounded({x + w / 2 - tw / 2, y + h - UnitHeight - SpaceSize * 1.5, tw, UnitHeight + SpaceSize}, 1, 10, Color{50, 50, 70, 150});
					zoom_slider.Draw(x + w / 2 - (tw - 80) / 2, y + h - UnitHeight - SpaceSize, (tw - 80));
				}
				zoom_ani.update();
				if (ChooseSlider == NULL)zoom_slider.num = zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (MouseInRect(x, y, w, h) && check) {
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && choose && !ChooseSlider != NULL) {
						DrawCircle(Mouse.x, Mouse.y, 7 * dpi, Color{255, 255, 255, 100});
					}
					zoom_ani.stp(zoom_ani.gtp() + GetMouseWheelMove() / 10.0);
					if (zoom_ani.gtp() < -3)zoom_ani.stp(-3);
					if (zoom_ani.gtp() > 7)zoom_ani.stp(7);
					zoom_ani.update();
				}
				EndScissor();
				return h;
			}
			int Draw(int x, int y, int w, bool check = true) {
				x += dpi, y += dpi, w -= dpi * 2;
				Draw(x, y, w, w * 0.8, check);
				special_effect::DrawMouseBox(x, y, w, w * 0.8);
				return w * 0.8 + dpi * 2;
			}
		private:
			Color color2;
			vector2d a, b;
		};
		class GraphDebugger3D : public Element {
		private:
			realn f(realn a) {
				return a - floor(a);
			}
			realn window_scale = 1;

		public:
			Camera3D camera = { 0 };
			void (*draw_fun)(GraphDebugger3D*) = nullptr;

			bool axis_visible = true;
			bool zoom_visible = true;
			bool mesh_visible = true;
			bool movable = true;

			GraphDebugger3D() {
				extra = true;
				// 初始化摄像机
				camera.position = (Vector3) {
					2.0f, 2.0f, 2.0f
				}; //相机所在位置{x,y,z}
				camera.target = (Vector3) {
					0.0f, 0.0f, 0.0f
				}; //相机朝向位置{x,y,z}
				camera.up = (Vector3) {
					0.0f, 1.0f, 0.0f
				}; //相机正上方朝向矢量
				camera.fovy = 70;
				camera.projection = CAMERA_PERSPECTIVE;
			}
			void draw_point(vector3d pos, Color color = GREEN) {
				realn dist = Mod(_v(camera.position) - pos);
				DrawSphere(_V(pos), 0.007 * dist * 1000.0 / (window_scale * winH), color);
			}
			void draw_vector_rotate(vector3d start, vector3d v, Color color = GREEN) {
				DrawLine3D(_V(start), _V(v + start), color);
				vector3d v2 = Cross(v, {0, 0, 1});
				if (v2 == vector3d{0, 0, 0})v2 = Cross(v, {0, 1, 0});
				vector3d v31 = VecUnit(v.Rotate(v2, PI / 8) * (-1));
				vector3d v32 = VecUnit(v.Rotate(v2, -PI / 8) * (-1));
				v31 = v31.Rotate(v, clock() / 200.0);
				v32 = v32.Rotate(v, clock() / 200.0);
				vector3d v41 = v + v31 * Mod(v) / 10;
				vector3d v42 = v + v32 * Mod(v) / 10;
				DrawLine3D(_V(v + start), _V(v41 + start), color);
				DrawLine3D(_V(v + start), _V(v42 + start), color);
			}
			void draw_line(vector3d v1, vector3d v2, Color color = GREEN) {
				DrawLine3D(_V(v1), _V(v2), color);
			}
			void draw_cube(vector3d pos, realn w = 1, realn h = 1, realn l = 1, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.2 + BgColor.r * 0.8;
				color2.g = color.g * 0.2 + BgColor.g * 0.8;
				color2.b = color.b * 0.2 + BgColor.b * 0.8;
				DrawCube(_V(pos), w, h, l, color2);
				DrawCubeWires(_V(pos), w, h, l, color);
			}
			void draw_sphere(vector3d pos, realn r = 0.5, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.2 + BgColor.r * 0.8;
				color2.g = color.g * 0.2 + BgColor.g * 0.8;
				color2.b = color.b * 0.2 + BgColor.b * 0.8;
				DrawSphere(_V(pos), r, color2);
				DrawCircle3D(_V(pos), r * 1.002, {0, 0, 1}, 0, color);
				DrawCircle3D(_V(pos), r * 1.002, {0, 1, 0}, 90, color);
				DrawCircle3D(_V(pos), r * 1.002, {1, 0, 0}, 90, color);
			}
			void draw_cylinder(vector3d v1, realn r = 0.5, realn r2 = 0.5, realn h = 1, int slices = 3, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.2 + BgColor.r * 0.8;
				color2.g = color.g * 0.2 + BgColor.g * 0.8;
				color2.b = color.b * 0.2 + BgColor.b * 0.8;
				DrawCylinder(_V(v1), r, r2, h, slices, color2);
				DrawCylinderWires(_V(v1), r, r2, h, slices, color);
			}
			void draw_cylinder(vector3d v1, vector3d v2, realn r = 0.5, realn r2 = 0.5, int slices = 3, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.2 + BgColor.r * 0.8;
				color2.g = color.g * 0.2 + BgColor.g * 0.8;
				color2.b = color.b * 0.2 + BgColor.b * 0.8;
				DrawCylinderEx(_V(v1), _V(v2), r, r2, slices, color2);
				DrawCylinderWiresEx(_V(v1), _V(v2), r, r2, slices, color);
			}
			void draw_vector(vector3d start, vector3d v, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.5 + BgColor.r * 0.5;
				color2.g = color.g * 0.5 + BgColor.g * 0.5;
				color2.b = color.b * 0.5 + BgColor.b * 0.5;
				DrawLine3D(_V(start), _V(v + start), color);
				DrawCylinderEx(_V(start + v * 0.9), _V(start + v), Mod(v * 0.02), 0, 10, color2);
			}
			void draw_vector(vector3d v, Color color = GREEN) {
				draw_vector({0, 0, 0}, v, color);
			}
			void draw_vector(realn x, realn y, realn z, Color color = GREEN) {
				draw_vector({0, 0, 0}, {x, y, z}, color);
			}
			void draw_capsule(vector3d v1, vector3d v2, realn r, Color color = GREEN) {
				Color color2 = color;
				color2.r = color.r * 0.5 + BgColor.r * 0.5;
				color2.g = color.g * 0.5 + BgColor.g * 0.5;
				color2.b = color.b * 0.5 + BgColor.b * 0.5;
				DrawCapsule(_V(v1), _V(v2), r, 15, 10, color2);
				DrawCapsuleWires(_V(v1), _V(v2), r, 3, 10, color);
			}
			void draw_bezier2(vector3d v1, vector3d v2, vector3d v3, Color color = GREEN) {
				vector3d l = v1;
				draw_line(v1, v2, GRAY);
				draw_line(v2, v3, GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector3d p1 = (v2 - v1) * t + v1;
					vector3d p2 = (v3 - v2) * t + v2;
					vector3d p3 = (p2 - p1) * t + p1;
					draw_line(l, p3, color);
					l = p3;
				}
			}
			void draw_bezier3(vector3d v1, vector3d v2, vector3d v3, vector3d v4, Color color = GREEN) {
				vector3d l = v1;
				draw_line(v1, v2, GRAY);
				draw_line(v3, v4, GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				draw_point(v4);
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector3d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					draw_line(l, p, color);
					l = p;
				}
			}
			void draw_bezier3_mesh(vector3d v1, vector3d v2, vector3d v3, vector3d v4, vector3d dir1 = {0, 0, 1}, realn angle = 0, realn radius = 1, Color color = GREEN) {
				vector3d l = v1, l1 = v1, l2 = v1;
				Color c1, c2;
				c1 = c2 = color;
				c1.a *= 0.3;
				c2.a *= 0.6;
				draw_line(v1, v2, GRAY);
				draw_line(v3, v4, GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				draw_point(v4);
				vector3d dp = v1 * (-3) + v2 * (3);
				dir1 = VecUnit(dir1 - (dir1 >> dp));
//				dir2=VecUnit(dir2-(dir2>>dp));
//				realn angle=VecAngle(dir1,dir2);
				draw_vector(v1, dir1 * radius);
				for (realn t = 0, i = 0; t <= 1.01; t += 0.02, i++) {
					vector3d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					vector3d dp = v1 * (-3 * t * t + 6 * t - 3) + v2 * (9 * t * t - 12 * t + 3) + v3 * (-9 * t * t + 6 * t) + v4 * (3 * t * t);
					dir1 = VecUnit(dir1 - (dir1 >> dp));
//					dir2=VecUnit(dir2-(dir2>>dp));
					vector3d temp = dp ^ (dir1.Rotate(dp, t * angle));
					temp = VecUnit(temp);

					draw_line(l, p, c2);
					draw_line(l1, p + temp * radius, color);
					draw_line(l2, p - temp * radius, color);
					if (int(i) % 5 == 0) {
						draw_line(p, p + temp * radius, c1);
						draw_line(p, p - temp * radius, c1);
					}
					l = p;
					l1 = p + temp * radius;
					l2 = p - temp * radius;
				}
//				draw_vector(v4,dir2*radius);
			}

			int Draw(int x, int y, int w, int h, bool check = true) {
				BeginMode3D(camera);
				UpdateCamera(&camera, CAMERA_ORBITAL);
				double k = pow(10, round(log10(abs(camera.position.y)))), k01 = k / 10.0;
				if (k < 1)k = 1, k01 = k / 10;

				realn temp = 1.0 * winH / winW;
				float x2, y2, w2, h2;
				GetScissor(&x2, &y2, &w2, &h2);
				if (x != x2 || y != y2 || w != w2 || h != h2)BeginScissor(x, y, w, h);
				if (1.0 * h / w >= temp) {
					rlViewport(x - (h / temp - w) / 2, winH - y - h, h / temp, h);
					window_scale = 1.0 * h / winH;
				} else {
					rlViewport(x, winH - (y - (w * temp - h) / 2) - w * temp, w, w * temp);
					window_scale = 1.0 * w / winW;
				}

				if (movable) {
					if (MouseInRect(x, y, w, h))UseSliderX = UseSliderY = true;
				}
				if (mesh_visible) {
					for (int i = -60; i <= 60; i ++) {
						for (int j = -60; j <= 60; j ++) {
							// 计算线段的距离
							int x2 = ceil(i + camera.position.x / k01);
							int z2 = ceil(j + camera.position.z / k01);
							realn x = x2 * k01, z = z2 * k01;
							realn distance = sqrtf((x - camera.position.x) * (x - camera.position.x) + (z - camera.position.z) * (z - camera.position.z));

							// 根据距离设置线段的颜色
							if (1.0f - distance * 0.03f / abs(camera.position.y) * 10 < 0)continue;
							Color lineColor = (Color) {
								150, 150, 150, 255 * ((1 - f(log10(abs(camera.position.y)) - 0.5)))*(1.0f - distance * 0.03f / abs(camera.position.y) * 10)
							};

							// 绘制线段
							if (x2 % 10 != 0)DrawLine3D((Vector3) {
								x, 0.0f, z
							}, (Vector3) {
								x, 0.0f, z + k01
							}, lineColor);
							if (z2 % 10 != 0)DrawLine3D((Vector3) {
								x, 0.0f, z
							}, (Vector3) {
								x + k01, 0.0f, z
							}, lineColor);
						}
					}
					for (int i = -60; i <= 60; i ++) {
						for (int j = -60; j <= 60; j ++) {
							// 计算线段的距离
							int x2 = ceil(i + camera.position.x / k);
							int z2 = ceil(j + camera.position.z / k);
							realn x = x2 * k, z = z2 * k;
							float distance = sqrtf((x - camera.position.x) * (x - camera.position.x) + (z - camera.position.z) * (z - camera.position.z));

							// 根据距离设置线段的颜色
							if (1.0f - distance * 0.03f / abs(camera.position.y) * 9 < 0)continue;
							Color lineColor = (Color) {
								150, 150, 150, 255 * (1.0f - distance * 0.03f / abs(camera.position.y) * 9)
							};

							// 绘制线段
							if (x2 != 0)DrawLine3D((Vector3) {
								x, 0.0f, z
							}, (Vector3) {
								x, 0.0f, z + k
							}, lineColor);
							if (z2 != 0)DrawLine3D((Vector3) {
								x, 0.0f, z
							}, (Vector3) {
								x + k, 0.0f, z
							}, lineColor);
						}
					}
				}
				if (axis_visible) {
					/*x*/DrawLine3D((Vector3) {
						10000, 0, 0
					}, (Vector3) {
						-10000, 0, 0
					}, Color{231, 162, 154, 255});
					/*y*/DrawLine3D((Vector3) {
						0, 10000, 0
					}, (Vector3) {
						0, -10000, 0
					}, Color{140, 128, 191, 255});
					/*z*/DrawLine3D((Vector3) {
						0, 0, 10000
					}, (Vector3) {
						0, 0, -10000
					}, Color{255, 128, 192, 255});
				}
				if (draw_fun != nullptr)draw_fun(this);

				EndMode3D();
				rlViewport(0, 0, winW, winH);
				if (x != x2 || y != y2 || w != w2 || h != h2)EndScissor();
				return h;
			}
			int Draw(int x, int y, int w, bool check = true) {
				x += dpi, y += dpi, w -= dpi * 2;
				Draw(x, y, w, w * 0.8, check);
				special_effect::DrawMouseBox(x, y, w, w * 0.8);
				return w * 0.8 + dpi * 2;
			}

		};
		class Sider {
		public:
			Element* ele = nullptr;
			SiderPosition spos = spos_top;
			int occupy = 50;
		};
		class InputBox : public  Element {
		public:
			std::string text = "Input box";
			std::string input = "";
			int input_pos = 0;
			int fix_time = 0;
			int start_pos = 0;
			bool choose = false;
			int choose_start = 0;
			int choose_end = 0;
			bool chosen = false;
			Animation ipa;
			Animation spa;
			Animation move;
			InputBox() {
				ipa.sd(200);
				spa.sd(400);
			}
			int Draw(int x, int y, int w, bool check = true) {
				ipa.update();
				spa.update();
				move.update();
				int h = ( UnitHeight -  TextHeight) / 2;
				char c =  GetChar;
				BeginScissor(x, y + h / 2, w,  UnitHeight - h);
				DrawRectangle(x, y + h / 2, w,  UnitHeight - h, Color{30, 30, 30, 255});
				ipa.stp(input_pos);
				spa.stp(start_pos);
				Print(x +  SpaceSize - spa.gnp()* TextHeight / 2, y + h, input);
				int a = (clock() - fix_time) % 1000;
				if (a < 300)a = 200;
				else if (a < 500)a = 500 - a;
				else if (a < 800)a = 0;
				else a = a - 800;
				if (true) {
					if ( MouseInRect(x, y, w,  UnitHeight)) {
						MouseCursorStyle = MOUSE_CURSOR_IBEAM;
						//DrawRectangle(x,y+h/2,w, UnitHeight-h, ChooseColor);
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseInputBox = this;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ChooseInputBox == this)ChooseInputBox = NULL;
					if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
					if (choose && ChooseInputBox != this)choose = false, move.stp(0);
					if (choose) {
						if ( MouseInRect(x +  SpaceSize, y + h / 2, w -  SpaceSize,  UnitHeight - h)) {
							if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
								int k =  Mouse.x - x -  SpaceSize;
								int k2 = round(1.0 * k * 2 /  TextHeight) + start_pos;
								k2 = std::min(k2, int(input.size()));
								input_pos = k2;
							}
						}
						if (IsKeyInput(KEY_BACKSPACE) && input_pos)input.erase(input_pos - 1, 1), input_pos--;
						else if (IsKeyInput(KEY_DELETE) && input_pos < input.size())input.erase(input_pos, 1);
						else if (IsKeyInput(KEY_LEFT) && input_pos)input_pos--;
						else if (IsKeyInput(KEY_RIGHT) && input_pos < input.size())input_pos++;
						else if (IsKeyInput(KEY_END))input_pos = input.size();
						else if (IsKeyInput(KEY_HOME))input_pos = 0;
						else if (IsKeyInput(KEY_TAB))input.insert(input_pos, "    "), input_pos += 4;
						else if (IsKeyDown(KEY_LEFT_CONTROL)) {
							if (c == KEY_C) {}
							if (IsKeyPressed(KEY_V)) {
								std::string str = GetClipboardText();
								for (int i = 0; i < str.size(); i++)if (str[i] == '\n')str.erase(i, 1);
								input.insert(input_pos, str), input_pos += str.size();
							}
						} else {
							std::string str = " ";
							str[0] = c;
							if (c)input.insert(input_pos, str), input_pos++;
						}
						if ((input_pos - start_pos) * TextHeight / 2 > w -  SpaceSize * 2)start_pos += w /  TextHeight;
						if ((input_pos - start_pos) * TextHeight / 2 < 0)start_pos -= w /  TextHeight;
						if (start_pos < 0)start_pos = 0;
						for (int i = 1; i <= 350; i++)if (IsKeyDown(i))a = 200, fix_time = clock();
					} else start_pos = 0;
				}
				if (!check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))start_pos = 0; //, ChooseInputBox = NULL;
				if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
				if (choose && ChooseInputBox != this)choose = false, move.stp(0);
				if (choose) {
					a = a * 255 / 200;
					DrawRectangle(x +  SpaceSize +  TextHeight / 2 * (ipa.gnp() - spa.gnp()) -  dpi, y + h / 2, 2 *  dpi,  TextHeight + h, Color{232, 192, 114, a});
				}
				DrawRectangle(x + w / 2 - w * move.gnp() / 2, y +  UnitHeight - h, w * move.gnp(), h,  MainColor);
				EndScissor();
				return  UnitHeight;
			}
		};
		struct InputHistory {
			std::string op = "insert";
			vector2d pos1;
			vector2d pos2;
			std::string str;
			realn time;
		};
		class MultiInputBox : public  ui::Element {
		private:
			int choose_start = 0;
			int choose_end = 0;
			bool choose_word = false;
			bool choose_word_on = false;
			bool choose_minimap = false;
			int choose_minimap_delta = 0;
			vector2d choose_pos = {0, 0};
			vector2d choose_pos2 = {0, 0};
			Animation ipx, ipy;
			Animation move;

		public:
			std::string text = "Input box";
			std::vector<std::string> input;
			vector2d input_pos = {0, 0};
			vector2d size = {0, 0};
			int fix_time = 0;
			bool choose = false;
			int multi_height = 5;
			bool chosen = false;
			Color background_color = BgColor;
			std::vector<std::vector<Color> > color;
			ui::SliderBar sx, sy;

			bool label_visible = false;
			bool auto_complete = true;
			bool minimap_visible = false;
			bool highlight_visible = true;
			bool color_scheme_enable = false;
			bool input_enable = true;
			int minimap_width = 100 * dpi;

			std::stack<InputHistory> history;
			std::stack<InputHistory> history2;
			int last_history_len = -1;

			MultiInputBox() {
				ipx.sd(200), ipy.sd(200);
				extra = true;
				sx.SetBlank(0), sy.SetBlank(0);
				input.push_back("");
			}
			int Index2Cursor(int line, int index) {
				if (line >= input.size())return 0;
				return strLen(input[line].substr(0, index));
			}
			int Cursor2Index(int line, int cursor) {
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
			int GetPreCharacter(int line, int index) {
				if (index == 0)return 0;
				int tindex = index;
				index--;
				while (index >= 0) {
					if (input[line][index] >= -128 && input[line][index] <= -65)index--;
					else break;
				}
				return tindex - index;
			}
			int GetNextCharacter(int line, int index) {
				if (index >= input[line].size())return 0;
				if ((input[line][index] & 0xF8) == 0xF8)return 5;
				else if ((input[line][index] & 0xF0) == 0xF0)return 4;
				else if ((input[line][index] & 0xE0) == 0xE0)return 3;
				else if ((input[line][index] & 0xC0) == 0xC0)return 2;
				else return 1;
			}
			vector2d GetPos(vector2d v) {
				int tempW = 0;
				if (label_visible)tempW = ui::TextHeight * 4;
				int tempx = X - sx.Now() + ui::SpaceSize + tempW;
				int tempy = Y - sy.Now() + ui::SpaceSize;
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				return vector2d {
					tempx + ui::TextHeight / 2 * v.x,
					tempy + ui::UnitHeight * v.y
				};
			}
			std::string Copy(vector2d pos1, vector2d pos2) {
				vector2d v1, v2;
				if (pos1.y < pos2.y)v1 = pos1, v2 = pos2;
				else if (pos1.y > pos2.y)v1 = pos2, v2 = pos1;
				else  {
					if (pos1.x < pos2.x)v1 = pos1, v2 = pos2;
					else v2 = pos1, v1 = pos2;
				}
				std::string temp_str = "";
				if (v1.y != v2.y) {
					temp_str += input[v1.y].substr(v1.x, input[v1.y].size()) + "\n";
					for (int i = v1.y + 1; i <= v2.y - 1; i++)temp_str += input[i] + "\n";
					temp_str += input[v2.y].substr(0, v2.x);
				} else {
					temp_str = input[v1.y].substr(v1.x, v2.x - v1.x);
				}
				return temp_str;
			}
			std::string CopyAll() {
				return Copy({0, 0}, {input[input.size() - 1].size(), input.size() - 1});
			}
			vector2d Insert(vector2d pos, std::string str) {
				if (pos.y > input.size() - 1)pos.y = input.size() - 1;
				if (pos.x > input[pos.y].size())pos.x = input[pos.y].size();
				if (pos.y < 0)pos.y = 0;
				if (pos.x < 0)pos.x = 0;
				std::string temp_str = input[pos.y].substr(pos.x);
				std::string backup = str;
				vector2d backup_pos = pos;
				input[pos.y].erase(pos.x);
				int n_pos = -1, l_pos = 0;
				std::string str2 = "";
				for (int i = 0; i < str.size(); i++) {
					if (str[i] == '\r' && str[i + 1] == '\n') {
						input[pos.y].insert(pos.x, str2);
						pos.y++;
						input.insert(input.begin() + (int)pos.y, "");
						pos.x = 0;
						str2 = "";
						i++;
					} else if (str[i] == '\n') {
						input[pos.y].insert(pos.x, str2);
						pos.y++;
						input.insert(input.begin() + (int)pos.y, "");
						pos.x = 0;
						str2 = "";
					} else if (str[i] == '\t')str2 += "    ";
					else str2 += str[i];
				}
				input[pos.y].insert(pos.x, str2), pos.x += str2.size();
				input[pos.y] += temp_str;

				InputHistory temp_history;
				temp_history.op = "insert";
				temp_history.pos1 = backup_pos;
				temp_history.pos2 = pos;
				temp_history.str = backup;
				history.push(temp_history);

				return pos;
			}
			vector2d InsertBack(std::string str) {
				return Insert({input[input.size() - 1].size(), input.size() - 1}, str);
			}
			vector2d InsertLine(int pos, std::string str) {
				return Insert({input[pos - 1].size(), pos - 1}, "\n" + str);
			}
			vector2d Delete(vector2d pos1, vector2d pos2) {
				vector2d v1, v2;
				if (pos1.y < pos2.y)v1 = pos1, v2 = pos2;
				else if (pos1.y > pos2.y)v1 = pos2, v2 = pos1;
				else {
					if (pos1.x < pos2.x)v1 = pos1, v2 = pos2;
					else v2 = pos1, v1 = pos2;
				}
				std::string backup = Copy(v1, v2);
				if (v1.y < v2.y) {
					input[v1.y].erase(v1.x);
					input[v1.y] += input[v2.y].substr(v2.x);
					for (int i = v1.y + 1; i <= v2.y; i++)input.erase(input.begin() + int(v1.y + 1));
				} else {
					input[v1.y].erase(v1.x, v2.x - v1.x);
				}

				InputHistory temp_history;
				temp_history.op = "delete";
				temp_history.pos1 = v1;
				temp_history.pos2 = v2;
				temp_history.str = backup;
				history.push(temp_history);

				return v1;
			}
			vector2d Delete(vector2d pos, int n) {
				return pos;
			}
			vector2d DeleteLine(int pos) {
				if (pos == 0)return Delete({0, 0}, {input[0].size(), 0});
				else return Delete({input[pos - 1].size(), pos - 1}, {input[pos].size(), pos});
			}
			vector2d SwapLine(int l1, int l2) {
				std::swap(input[l1], input[l2]);
				InputHistory temp_history;
				temp_history.op = "std::swap";
				temp_history.pos1.y = l1;
				temp_history.pos2.y = l2;
				history.push(temp_history);
				return {input_pos.x, l2};
			}
			vector2d GetEnd() {
				return {input[input.size() - 1].size(), input.size() - 1};
			}
			vector2d Clear() {
				return Delete({0, 0}, GetEnd());
			}
			vector2d Undo() {
				if (last_history_len != history.size()) {
					std::stack<InputHistory>().swap(history2);
					last_history_len = history.size();
				}
				if (history.empty())return input_pos;
				InputHistory temp = history.top();
				vector2d v;
				history.pop();
				if (temp.op == "insert") {
					v = Delete(temp.pos1, temp.pos2);
					history.pop();
				} else if (temp.op == "delete") {
					v = Insert(temp.pos1, temp.str);
					history.pop();
				} else if (temp.op == "std::swap") {
					v = SwapLine(temp.pos2.y, temp.pos1.y);
					history.pop();
				}
				history2.push(temp);
				last_history_len = history.size();
				return v;
			}
			vector2d Redo() {
				if (last_history_len != history.size()) {
					std::stack<InputHistory>().swap(history2);
					last_history_len = history.size();
				}
				if (history2.empty())return input_pos;
				InputHistory temp = history2.top();
				vector2d v;
				history2.pop();
				if (temp.op == "insert") {
					v = Insert(temp.pos1, temp.str);
					history.pop();
				} else if (temp.op == "delete") {
					v = Delete(temp.pos1, temp.pos2);
					history.pop();
				} else if (temp.op == "std::swap") {
					v = SwapLine(temp.pos1.y, temp.pos2.y);
					history.pop();
				}
				history.push(temp);
				last_history_len = history.size();
				return v;
			}
			void DrawColorInRange(int r1, int c1, int r2, int c2, Color cl) {
				int r, c;
				for (r = r1; r <= r2; r++) {
					if (r == r1) c = c1;
					else c = 0;
					while (c < input[r].size()) {
						color[r][c] = cl;
						if (r == r2 && c == c2) break;
						c++;
					}
				}
			}
			int FindMatch(int r, int c1, char ch) {
				int c;
				for (c = c1 + 1; c < input[r].size(); c++) {
					if (input[r][c] == ch && color[r][c] == color_theme::Color_Default) {
						if (ch == '\'' && input[r][c - 1] == '\\'
						    && c - 2 >= 0 && input[r][c - 2] != '\\') {
							continue;
						}
						if (ch == '"' && input[r][c - 1] == '\\'
						    && c - 2 >= 0 && input[r][c - 2] != '\\') {
							continue;
						}
						return c;
					}
				}
				return -1;
			}
			int FindReservedWord(int r1, int c1) {
				static char* word[48] = {
					// C语言33关键字
					"auto", "break", "case", "char", "const",
					"continue", "default", "do", "double", "else",
					"enum", "extern", "float", "for", "goto",
					"if", "inline", "int", "long", "register",
					"return", "short", "signed", "sizeof", "static",
					"struct", "switch", "typedef", "union", "unsigned",
					"void", "volatile", "while",
					// 常见C++关键字增补11
					"bool", "class", "delete", "false", "namespace",
					"new", "private", "public", "this", "true",
					"using",
					// 常见Python关键字增补4
					"def", "from", "import", "in"
				};
				int i, j;
				for (i = 0; i < 48; i++) {
					for (j = 0; word[i][j] != 0; j++) {
						if (c1 + j < input[r1].size() && input[r1][c1 + j] == word[i][j]);
						else break;
					}
					if (word[i][j] == 0)	{
						if (c1 + j < input[r1].size() && ((input[r1][c1 + j] >= '0' && input[r1][c1 + j] <= '9')
						                                  || (input[r1][c1 + j] >= 'A' && input[r1][c1 + j] <= 'Z')
						                                  || (input[r1][c1 + j] >= 'a' && input[r1][c1 + j] <= 'z')
						                                  || input[r1][c1 + j] == '_')) {
							continue;
						}
						return j;
					}
				}
				return 0;//返回匹配关键字字符数
			}
			void AnalysisColor() {
				int r, c, end, commentStart;
				int bLevel = 0;
				//符号着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
//						std::cout<<r<<' '<<c<<std::endl;
						/*----------------
						ASCII:
						0-8:    控制码
						9:      制表符\t
						10-13:  空白符\n \v \f \r
						14-31:  控制码
						32:     空格
						33-47:  !"#$%&'()*+,-./
						48-57:  0123456789
						58-64:  :;<=>?@
						65-70:  ABCDEF
						71-90:  GHIJKLMNOPQRSTUVWXYZ
						91-96:  [\]^_`
						97-102: abcdef
						103-122:ghijklmnopqrstuvwxyz
						123-126:{|}~
						127:    退格符
						----------------*/
						color[r][c] = color_theme::Color_Default;
						if (input[r][c] == '!'
						    || input[r][c] == '%'
						    || input[r][c] == '&'
						    || input[r][c] == '*'
						    || input[r][c] == '+'
						    || input[r][c] == ','
						    || input[r][c] == '-'
						    || input[r][c] == '.'
						    || input[r][c] == '/'
						    || input[r][c] == ':'
						    || input[r][c] == ';'
						    || input[r][c] == '<'
						    || input[r][c] == '='
						    || input[r][c] == '>'
						    || input[r][c] == '?'
						    || input[r][c] == '^'
						    || input[r][c] == '|'
						    || input[r][c] == '~') {
							color[r][c] = color_theme::Color_Symbol;
						} else if (input[r][c] == '(' || input[r][c] == ')'
						           || input[r][c] == '[' || input[r][c] == ']'
						           || input[r][c] == '{' || input[r][c] == '}') {
							color[r][c] = color_theme::Color_Symbol;
						}
					}
				}
				//数字着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
						if (input[r][c] >= '0' && input[r][c] <= '9') {
							if (c > 0 && ((input[r][c - 1] >= 'A' && input[r][c - 1] <= 'Z')
							              || (input[r][c - 1] >= 'a' && input[r][c - 1] <= 'z')
							              || input[r][c - 1] == '_'));
							else {
								color[r][c] = color_theme::Color_Number;
							}
						}
						if (input[r][c] == '.' && c > 0 && c + 1 < input[r].size()) {
							if (input[r][c - 1] >= '0' && input[r][c - 1] <= '9'
							    && input[r][c + 1] >= '0' && input[r][c + 1] <= '9') {
								color[r][c] = color_theme::Color_Number;
							}
						}
						if (input[r][c] == '0' && c + 1 < input[r].size() && input[r][c + 1] == 'x')	{
							if (c + 2 < input[r].size()) {
								if ((input[r][c + 2] >= '0' && input[r][c + 2] <= '9')
								    || (input[r][c + 2] >= 'A' && input[r][c + 2] <= 'F')
								    || (input[r][c + 2] >= 'a' && input[r][c + 2] <= 'f')) {
									color[r][c + 1] = color_theme::Color_Number;
									for (c += 2; c < input[r].size(); c++) {
										if ((input[r][c] >= '0' && input[r][c] <= '9')
										    || (input[r][c] >= 'A' && input[r][c] <= 'F')
										    || (input[r][c] >= 'a' && input[r][c] <= 'f')) {
											color[r][c] = color_theme::Color_Number;
										} else {
											break;
										}
									}
								}
							}
						}
					}
				}
				//预处理指令着色
				for (r = 0; r < input.size(); r++) {
					if (input[r].size() > 0 && input[r][0] == '#') {
						for (c = 0; c < input[r].size(); c++) {
							if (input[r][c] == '<') break;
							color[r][c] = color_theme::Color_Preprocessor;
						}
					}//行首为#且在<前的内容
				}
				//注释着色
				commentStart = 0;
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < (int)input[r].size() - 1; c++) {
						if (input[r][c] == '/' && input[r][c + 1] == '*') {
							commentStart = 1;
						}
						if (commentStart == 1) {
							color[r][c] = color_theme::Color_Comment;
						}
						if (input[r][c] == '*' && input[r][c + 1] == '/') {
							commentStart = 0;
							color[r][c + 1] = color_theme::Color_Comment;
						}
					}
					for (c = 0; c < (int)input[r].size() - 1; c++) {
						if (input[r][c] == '/' && input[r][c + 1] == '/') {
							for (; c < input[r].size(); c++) {
								color[r][c] = color_theme::Color_Comment;
							}
						}
					}
				}
				//字符和字符串着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
						if (input[r][c] == '\'')	{
							end = FindMatch(r, c, '\'');
							if (end != -1) {
								DrawColorInRange(r, c, r, end, color_theme::Color_Character);
								c = end;
							}
						}
					}
					for (c = 0; c < input[r].size(); c++) {
						if (input[r][c] == '"') {
							end = FindMatch(r, c, '"');
							if (end != -1) {
								DrawColorInRange(r, c, r, end, color_theme::Color_String);
								//转义序列着色
								for (c++; c < end; c++) {
									if (input[r][c] == '\\')	{
										if (input[r][c + 1] == '\''
										    || input[r][c + 1] == '"'
										    || input[r][c + 1] == '?'
										    || input[r][c + 1] == '\\'
										    || input[r][c + 1] == 'a'
										    || input[r][c + 1] == 'b'
										    || input[r][c + 1] == 'f'
										    || input[r][c + 1] == 'n'
										    || input[r][c + 1] == 'r'
										    || input[r][c + 1] == 't'
										    || input[r][c + 1] == 'v') {
											color[r][c] = color_theme::Color_EscapeSequences;
											color[r][c + 1] = color_theme::Color_EscapeSequences;
											c++;
										} else if (input[r][c + 1] >= '0' && input[r][c + 1] <= 7 && c + 3 < end
										           && input[r][c + 2] >= '0' && input[r][c + 2] <= 7
										           && input[r][c + 3] >= '0' && input[r][c + 3] <= 7) {
											color[r][c] = color_theme::Color_EscapeSequences;
											color[r][c + 1] = color_theme::Color_EscapeSequences;
											color[r][c + 2] = color_theme::Color_EscapeSequences;
											color[r][c + 3] = color_theme::Color_EscapeSequences;
											c += 3;
										}
									}
								}
								//c = end;
							}
						}
					}
				}
				//彩虹括号着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
						if (color[r][c] == color_theme::Color_Symbol) {
							if (input[r][c] == '(' || input[r][c] == ')'
							    || input[r][c] == '[' || input[r][c] == ']'
							    || input[r][c] == '{' || input[r][c] == '}') {
								if (input[r][c] == '(' || input[r][c] == '[' || input[r][c] == '{') {
									bLevel++;
								}
								if (bLevel % 4 == 0) color[r][c] = color_theme::Color_Bracket_L1;
								else if (bLevel % 4 == 1) color[r][c] = color_theme::Color_Bracket_L2; //保持底层为L2
								else if (bLevel % 4 == 2) color[r][c] = color_theme::Color_Bracket_L3;
								else if (bLevel % 4 == 3) color[r][c] = color_theme::Color_Bracket_L4;
								if (input[r][c] == ')' || input[r][c] == ']' || input[r][c] == '}') {
									bLevel--;
								}
							}
						}
					}
				}
				//关键字着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
						if (c == 0 && color[r][c] == color_theme::Color_Default) {
							end = FindReservedWord(r, c);
							if (end > 0)	{
								DrawColorInRange(r, c, r, c + end - 1, color_theme::Color_ReservedWord);
							}
						}
						if (c > 0) {
							if (((input[r][c - 1] >= '0' && input[r][c - 1] <= '9')
							     || (input[r][c - 1] >= 'A' && input[r][c - 1] <= 'Z')
							     || (input[r][c - 1] >= 'a' && input[r][c - 1] <= 'z')
							     || input[r][c - 1] == '_'));
							else if (color[r][c] == color_theme::Color_Default) {
								end = FindReservedWord(r, c);
								if (end > 0)	{
									DrawColorInRange(r, c, r, c + end - 1, color_theme::Color_ReservedWord);
								}
							}
						}
					}
				}
				//函数着色
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < (int)input[r].size() - 1; c++) 	{
						if (color[r][c] == color_theme::Color_Default && input[r][c + 1] == '(') {
							for (end = c; c >= 0; c--) {
								if ((input[r][c] >= '0' && input[r][c] <= '9')
								    || (input[r][c] >= 'A' && input[r][c] <= 'Z')
								    || (input[r][c] >= 'a' && input[r][c] <= 'z')
								    || input[r][c] == '_') {
									color[r][c] = color_theme::Color_Function;
								} else {
									break;
								}
							}
							c = end;//防止死循环
						}
					}
				}
				//剩余内容均视为变量
				for (r = 0; r < input.size(); r++) {
					for (c = 0; c < input[r].size(); c++) {
						if (color[r][c] == color_theme::Color_Default) {
							color[r][c] = color_theme::Color_Variable;
						}
					}
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {

				BeginScissor(x, y, w, h);

				// 更新动画
				ipx.stp(Index2Cursor(input_pos.y, input_pos.x)), ipy.stp(input_pos.y);
				ipx.update(), ipy.update();
				sx.SetControl(x, y, w, h);
				sy.SetControl(x, y, w, h);
				X = x, Y = y, W = w, H = w;
				vector2d input_pos1 = vector2d(Index2Cursor(input_pos.y, input_pos.x), input_pos.y);
				move.update();
				// 计算文本区起止位置
				int start_x = 2 * (sx.Now() - ui::SpaceSize) / ui::TextHeight;
				int start_y = (sy.Now() - ui::SpaceSize) / ui::UnitHeight;
				int end_x = 2 * (sx.Now() - ui::SpaceSize + w) / ui::TextHeight + 1;
				int end_y = (sy.Now() - ui::SpaceSize + h) / ui::UnitHeight + 1;
				// 绘制背景色
				if (background_color.r != BgColor.r ||
				    background_color.g != BgColor.g ||
				    background_color.b != BgColor.b)DrawRectangle(x, y, w, h, ColorF(background_color));
				int tempW = 0;
				// 绘制行号
				if (label_visible) {
					tempW = ui::TextHeight * 4;
					DrawRectangle(x, y, tempW, h, ColorF(25, 25, 25, 255));
					int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
					int tempx = x - sx.Now() + ui::SpaceSize;
					int tempy = y - sy.Now() + ui::SpaceSize;
					for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
						size.x = std::max(size.x, (realn)input[i].size());
						std::string temp_str = "";
						for (int j = 1; j <= 4 - int(log10(i + 1)); j++)temp_str += ' ';
						std::stringstream a;
						a << (i + 1);
						temp_str += a.str();
						ui::Print(x + ui::TextHeight * 0.5, tempy + tempH + i * ui::UnitHeight, temp_str, WHITE);
					}
					// 绘制高亮行
					if (highlight_visible) {
						if (minimap_visible)DrawRectangle(x + ui::SpaceSize, tempy + ui::UnitHeight * ipy.gnp(), w - ui::SpaceSize - minimap_width, ui::UnitHeight, ColorF(100, 100, 100, 100));
						else DrawRectangle(x + ui::SpaceSize, tempy + ui::UnitHeight * ipy.gnp(), w - ui::SpaceSize, ui::UnitHeight, ColorF(100, 100, 100, 100));
					}
					x += tempW;
					w -= tempW;
				} else {
					int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
					int tempx = x - sx.Now() + ui::SpaceSize;
					int tempy = y - sy.Now() + ui::SpaceSize;
					// 绘制高亮行
					if (highlight_visible) {
						if (minimap_visible)DrawRectangle(x, tempy + ui::UnitHeight * ipy.gnp(), w - minimap_width, ui::UnitHeight, ColorF(100, 100, 100, 100));
						else DrawRectangle(x, tempy + ui::UnitHeight * ipy.gnp(), w, ui::UnitHeight, ColorF(100, 100, 100, 100));
					}
				}
				// 计算文本裁剪区
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				int tempx = x - sx.Now() + ui::SpaceSize;
				int tempy = y - sy.Now() + ui::SpaceSize;
				char c = ui::GetChar;
				if (minimap_visible)ui::BeginScissor(x, y, w - minimap_width, h);
				else ui::BeginScissor(x, y, w, h);
				size.x = 0;
				// 计算文本长度
				for (int i = start_y; i <= end_y; i++)size.x = std::max(size.x, (realn)Index2Cursor(i, input[i].size()));
				size.y = input.size();
				// 计算光标透明度
				int a = (clock() - fix_time) % 1000;
				if (a < 300)a = 200;
				else if (a < 500)a = 500 - a;
				else if (a < 800)a = 0;
				else a = a - 800;
				// 处理按键事件
				if (true) {
					// 判断焦点
					if (ui::MouseInRect(x - tempW, y, w + tempW - ui::SpaceSize * 3, h - ui::SpaceSize * 3) && InScissor(Mouse.x, Mouse.y) && check) {
						ui::MouseCursorStyle = MOUSE_CURSOR_IBEAM;
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseInputBox = this;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ChooseInputBox == this)ChooseInputBox = NULL;
					if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
					if (choose && ChooseInputBox != this)choose = false, move.stp(0);
					// 处于焦点状态
					if (choose) {
						// 判断是否选择文本
						if (!choose_word && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))choose_word_on = false;
						// 移动光标
						if (ui::MouseInRect(x, y, w - ui::SpaceSize * 3, h - ui::SpaceSize * 3) || choose_word) {
							if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0 * ky / ui::UnitHeight);
								if (kx2 < 0)kx2 = 0;
								if (ky2 < 0)ky2 = 0;
								ky2 = std::min(ky2, int(input.size() - 1));
								kx2 = Cursor2Index(ky2, kx2);
								kx2 = std::min(kx2, int(input[ky2].size()));
								input_pos = {kx2, ky2};
								ipx.stp(Index2Cursor(input_pos.y, input_pos.x)), ipy.stp(input_pos.y);
								ipx.update(), ipy.update();
							}
							if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0 * ky / ui::UnitHeight);
								if (kx2 < 0)kx2 = 0;
								if (ky2 < 0)ky2 = 0;
								ky2 = std::min(ky2, int(input.size() - 1));
								kx2 = Cursor2Index(ky2, kx2);
								kx2 = std::min(kx2, int(input[ky2].size()));
								input_pos = {kx2, ky2};
								choose_word = true;
								choose_pos = {kx2, ky2};
							}
						}
						// 是否取消选择文本
						if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))choose_word = false;
						// 如果选择文本，计算选择起止点
						if (choose_word) {
							int kx = ui::Mouse.x - tempx;
							int ky = ui::Mouse.y - tempy;
							int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
							int ky2 = floor(1.0 * ky / ui::UnitHeight);
							if (kx2 < 0)kx2 = 0;
							if (ky2 < 0)ky2 = 0;
							ky2 = std::min(ky2, int(input.size() - 1));
							kx2 = Cursor2Index(ky2, kx2);
							kx2 = std::min(kx2, int(input[ky2].size()));
							if (kx2 != choose_pos.x || ky2 != choose_pos.y) {
								choose_word_on = true;
								choose_pos2 = vector2d{kx2, ky2};
							}
						}
						bool delete_choose = false;
						// 防止动画过长而做的优化
						if (abs(input_pos.y - ipy.gnp()) > 20)ipy.ssp(input_pos.y);
						// 选择文本后的事件
						input_pos1 = vector2d(Index2Cursor(input_pos.y, input_pos.x), input_pos.y);
						if (choose_word_on) {
							// 绘制起止光标间的阴影
							vector2d v1, v2;
							choose_pos2 = vector2d(ipx.gnp(), ipy.gnp());
							vector2d choose_pos1 = vector2d(Index2Cursor(choose_pos.y, choose_pos.x), choose_pos.y);
							if (abs(input_pos1.y - ipy.gnp()) == 0 && abs(input_pos1.x - ipx.gnp()) > 10)choose_pos2.x = input_pos1.x;
							if (abs(input_pos1.y - ipy.gnp()) > 5)choose_pos2.y = input_pos1.y, choose_pos2.x = input_pos1.x;
							if (choose_pos1.y < choose_pos2.y)v1 = choose_pos1, v2 = choose_pos2;
							else if (choose_pos1.y > choose_pos2.y)v1 = choose_pos2, v2 = choose_pos1;
							else  {
								if (choose_pos1.x < choose_pos2.x)v1 = choose_pos1, v2 = choose_pos2;
								else v2 = choose_pos1, v1 = choose_pos2;
							}
							vector2d v3 = GetPos(v1), v4 = GetPos(v2);
							Color color = ui::MainColor;
							color.a = 100;
							if (v2.y - v1.y > 1 && v3.y < y + h && v4.y > y)DrawRectangle(x, std::max(int(v3.y + ui::UnitHeight), y), w, ceil(std::min(v4.y, realn(y + h)) - std::max(int(v3.y + ui::UnitHeight), y)), ColorF(color));
							if (v2.y - v1.y < 0.9)DrawRectangle(v3.x, v3.y, v4.x - v3.x, ui::UnitHeight, ColorF(color));
							else {
								DrawRectangle(v3.x, v3.y, x + w - v3.x, ui::UnitHeight, ColorF(color));
								DrawRectangle(x, v4.y, v4.x - x, ui::UnitHeight, ColorF(color));
							}
							// 绘制起止光标
							DrawRectangle(
							    tempx + ui::TextHeight / 2 * choose_pos1.x - ui::dpi,
							    tempy + ui::UnitHeight * choose_pos1.y - tempH,
							    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(BLUE)
							);
							DrawRectangle(
							    tempx + ui::TextHeight / 2 * choose_pos2.x - ui::dpi,
							    tempy + ui::UnitHeight * choose_pos2.y - tempH,
							    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(BLUE)
							);
							// 判断是否通过一些按键取消选择
							if (IsKeyDown(KEY_HOME) || IsKeyDown(KEY_END) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
								choose_word_on = false;
							}
							if (input_enable) {
								bool flag = false;
								for (int i = 32; i <= 127; i++)if (c == i) {
										flag = true;
										break;
									}
								if (IsKeyDown(KEY_BACKSPACE) || IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_TAB) || IsKeyDown(KEY_DELETE))flag = true;
								if (flag) {
									input_pos = Delete(choose_pos, input_pos);
									choose_word_on = false;
									delete_choose = true;
								}
							}
						}
						// 检测按键
						if (input_enable) {
							if (ui::IsKeyInput(KEY_BACKSPACE) && !delete_choose) {
								if (input_pos.x > 0)input_pos = Delete(input_pos - vector2d{GetPreCharacter(input_pos.y, input_pos.x), 0}, input_pos);
								else if (input_pos.y > 0)input_pos = Delete({input[input_pos.y - 1].size(), input_pos.y - 1}, input_pos);
							} else if (ui::IsKeyInput(KEY_DELETE) && !delete_choose) {
								if (input_pos.x < input[input_pos.y].size())input_pos = Delete(input_pos + vector2d{GetNextCharacter(input_pos.y, input_pos.x), 0}, input_pos);
								else if (input_pos.y < input.size() - 1)input_pos = Delete({0, input_pos.y + 1}, input_pos);
							} else if (ui::IsKeyInput(KEY_LEFT)) {
								if (input_pos.x > 0)input_pos.x -= GetPreCharacter(input_pos.y, input_pos.x);
								else if (input_pos.y > 0)input_pos.y--, input_pos.x = input[input_pos.y].size();
							} else if (ui::IsKeyInput(KEY_RIGHT)) {
								if (input_pos.x < input[input_pos.y].size())input_pos.x += GetNextCharacter(input_pos.y, input_pos.x);
								else if (input_pos.y < input.size() - 1)input_pos.y++, input_pos.x = 0;
							} else if (ui::IsKeyInput(KEY_UP) && input_pos.y > 0) {
								if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT)) {
									if (input_pos.y > 0)SwapLine(input_pos.y, input_pos.y - 1);
								}
								input_pos.y--;
							} else if (ui::IsKeyInput(KEY_DOWN) && input_pos.y < input.size() - 1) {
								if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT)) {
									if (input_pos.y < input.size() - 1)SwapLine(input_pos.y, input_pos.y + 1);
								}
								input_pos.y++;
							} else if (ui::IsKeyInput(KEY_END))input_pos.x = input[input_pos.y].size();
							else if (ui::IsKeyInput(KEY_HOME))input_pos.x = 0;
							else if (ui::IsKeyInput(KEY_TAB))input[input_pos.y].insert(input_pos.x, "    "), input_pos.x += 4;
							else if (ui::IsKeyInput(KEY_ENTER)) {
								bool flag = true;
								if (input_pos.x <= 0 || input_pos.x >= input[input_pos.y].size())flag = false;
								if (flag && input[input_pos.y][input_pos.x - 1] == '{' && input[input_pos.y][input_pos.x] == '}') {
									Insert(input_pos, "\n\n");
									input_pos.y++;
									input_pos.x = 0;
									int space_size = 0;
									std::string temp = "";
									for (int i = 0; i < input[input_pos.y - 1].size(); i++) {
										if (input[input_pos.y - 1][i] == ' ')space_size++, temp += ' ';
										else {
											break;
										}
									}
									if (space_size % 4 == 0) {
										Insert(input_pos + vector2d{0, 1}, temp);
										input_pos = Insert(input_pos, temp + "    ");
									}
								} else {
									input_pos = Insert(input_pos, "\n");
									int space_size = 0;
									std::string temp = "";
									for (int i = 0; i < input[input_pos.y - 1].size(); i++) {
										if (input[input_pos.y - 1][i] == ' ')space_size++, temp += ' ';
										else {
											break;
										}
									}
									if (space_size % 4 == 0)input_pos = Insert(input_pos, temp);
								}
							}
							if (IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT)) {
								if (choose_word_on) {
									if (IsKeyPressed(KEY_C)) {
										choose_pos2 = vector2d{input_pos.x, input_pos.y};
										SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
										ui::message::Send("已复制到剪切板");
									} else if (IsKeyPressed(KEY_X)) {
										ui::message::Send("已复制到剪切板");
										choose_pos2 = vector2d{input_pos.x, input_pos.y};
										SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
										input_pos = Delete(choose_pos, choose_pos2);
										choose_word_on = false;
									}
								}
								if (IsKeyPressed(KEY_A)) {
									choose_word_on = true;
									choose_pos = {0, 0};
									choose_pos2 = {input[input.size() - 1].size(), input.size() - 1};
									input_pos = choose_pos2;
								}
								if (ui::IsKeyInput(KEY_V)) {
									if (choose_word_on) {
										input_pos = Delete(choose_pos, input_pos);
										choose_word_on = false;
									}
									std::string str = GetClipboardText();
									input_pos = Insert(input_pos, str);
								}
								if (ui::IsKeyInput(KEY_E)) {
									choose_word_on = false;
									std::string temp_str = input[input_pos.y];
									InsertLine(input_pos.y + 1, temp_str);
								}
								if (ui::IsKeyInput(KEY_D)) {
									choose_word_on = false;
									DeleteLine(input_pos.y);
								}
								if (ui::IsKeyInput(KEY_Z)) {
									choose_word_on = false;
									input_pos = Undo();
								}
								if (ui::IsKeyInput(KEY_Y)) {
									choose_word_on = false;
									input_pos = Redo();
								}
							}
							// 检测到正常字符输入，插入字符，并自动补全
							else {
								std::string str = GetCharString;
								if (c) {
									input_pos = Insert(input_pos, str);
									if (auto_complete) {
										if (str == "<" && input[input_pos.y][0] == '#')Insert(input_pos, ">");
										if (str == "(")Insert(input_pos, ")");
										if (str == "[")Insert(input_pos, "]");
										if (str == "{")Insert(input_pos, "}");
										if (str == "\'")Insert(input_pos, "\'");
										if (str == "\"")Insert(input_pos, "\"");
									}
								}
							}
						}
						// 判断光标是否越界
						if (input_pos.y > input.size() - 1)input_pos.y = input.size() - 1;
						if (input_pos.x > input[input_pos.y].size())input_pos.x = input[input_pos.y].size();
						// 判断是否有按键事件或鼠标点击，如果有，则通过光标移动视野
						bool flag = false;
						for (int i = 1; i <= 350; i++)if (IsKeyDown(i)) {
								flag = true;
								break;
							}
						if (flag || ipx.IsRunning() || ipy.IsRunning() || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							a = 200, fix_time = clock();
							if (input_pos1.x * ui::TextHeight / 2 < sx.Now())sx.Set(input_pos1.x * ui::TextHeight / 2);
							if (input_pos1.y * ui::UnitHeight < sy.Now())sy.Set(input_pos1.y * ui::UnitHeight);
							if (input_pos1.x * ui::TextHeight / 2 + ui::SpaceSize * 2 > sx.Now() + w - ui::SpaceSize * 3)sx.Set(input_pos1.x * ui::TextHeight / 2 + ui::SpaceSize * 2 - (w - ui::SpaceSize * 3));
							if ((input_pos1.y + 1) * ui::UnitHeight + ui::SpaceSize * 2 > sy.Now() + h - ui::SpaceSize * 3)sy.Set((input_pos1.y + 1) * ui::UnitHeight + ui::SpaceSize * 2 - (h - ui::SpaceSize * 3));
						}
					}
				} else ChooseInputBox = NULL;
				// 如果光标在运动，则通过光标移动视野
				if (ipx.IsRunning() || ipy.IsRunning()) {
					a = 200, fix_time = clock();
					if (input_pos1.x * ui::TextHeight / 2 < sx.Now())sx.Set(input_pos1.x * ui::TextHeight / 2);
					if (input_pos1.y * ui::UnitHeight < sy.Now())sy.Set(input_pos1.y * ui::UnitHeight);
					if (input_pos1.x * ui::TextHeight / 2 + ui::SpaceSize * 2 > sx.Now() + w - ui::SpaceSize * 3 - minimap_width * minimap_visible)sx.Set(input_pos1.x * ui::TextHeight / 2 + ui::SpaceSize * 2 - (w - ui::SpaceSize * 3 - minimap_width * minimap_visible));
					if ((input_pos1.y + 1) * ui::UnitHeight + ui::SpaceSize * 2 > sy.Now() + h - ui::SpaceSize * 3)sy.Set((input_pos1.y + 1) * ui::UnitHeight + ui::SpaceSize * 2 - (h - ui::SpaceSize * 3));
				}
				if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
				if (choose && ChooseInputBox != this)choose = false, move.stp(0);
				// 绘制文本
				if (!color_scheme_enable) {
					for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
						ui::Print(tempx, tempy + tempH + i * ui::UnitHeight, input[i]);
					}
				} else {
					color.resize(input.size());
					for (int i = 0; i < color.size(); i++)color[i].resize(input[i].size());
					std::string char2str;
					AnalysisColor();
					for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
						int count = 0;
						for (int j = 0; j < input[i].size();) {
							char2str = "";
							char2str += input[i][j];
							int count2 = count, j2 = j;
							if ((input[i][j] & 0xF8) == 0xF8)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], char2str += input[i][j + 4], j += 5, count += 2;
							else if ((input[i][j] & 0xF0) == 0xF0)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], j += 4, count += 2;
							else if ((input[i][j] & 0xE0) == 0xE0)char2str += input[i][j + 1], char2str += input[i][j + 2], j += 3, count += 2;
							else if ((input[i][j] & 0xC0) == 0xC0)char2str += input[i][j + 1], j += 2, count += 2;
							else j++, count++;
							ui::Print(tempx + count2 * ui::TextHeight / 2, tempy + tempH + i * ui::UnitHeight, char2str, color[i][j2]);
						}
					}
				}
				// 绘制光标
				if (choose) {
					// 焦点状态，黄色
					a = a * 255 / 200;
					if (!choose_word_on)DrawRectangle(
						    tempx + ui::TextHeight / 2 * ipx.gnp() - ui::dpi,
						    tempy + ui::UnitHeight * ipy.gnp() - tempH,
						    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(232, 192, 114, a)
						);
				} else {
					// 非焦点，灰色
					DrawRectangle(
					    tempx + ui::TextHeight / 2 * ipx.gnp() - ui::dpi,
					    tempy + ui::UnitHeight * ipy.gnp() - tempH,
					    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(70, 70, 70, 255)
					);
				}
				// 绘制行号栏的阴影
				if (label_visible) {
					if (sx.Now() > ui::SpaceSize - 1) {
						int delta = sx.Now() - ui::SpaceSize + 1;
						if (delta > ui::UnitHeight * 2)delta = ui::UnitHeight * 2;
						ui::special_effect::DrawShadowLine(x, y + h, x, y, 10 * ui::dpi, 1.0 * delta / ui::UnitHeight / 2);
					}
				}

				ui::EndScissor();

				// 绘制小地图
				if (minimap_visible) {
					realn temp = 1.0 * sy.Now() / sy.Sum() * (1 - h * 3 * dpi / UnitHeight / h);
					realn start = 1.0 * sy.Now() / ui::UnitHeight - temp * h / dpi / 3;
					int delta_y = start * dpi * 3;
					if (start < 0)start = 0;
					for (int i = start; i < std::min((int)input.size(), int(start + h / 3 / dpi)); i++) {
						int p1 = 0;
						for (int j = 0; j < input[i].size(); j++) {
							if (input[i][j] != ' ') {
								if (color_scheme_enable) {
									DrawRectangle(x + w - minimap_width + j * dpi, y + i * dpi * 3 - delta_y, dpi, dpi * 2, ColorF(MixColor(color[i][j], ui::BgColor, 0.5)));
								} else {
									DrawRectangle(x + w - minimap_width + j * dpi, y + i * dpi * 3 - delta_y, dpi, dpi * 2, ColorF(GRAY));
								}
							}
						}
					}
					DrawRectangle(x + w - minimap_width, y + sy.Now() * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight, ColorF(ChooseColor));
					if (size.x * ui::TextHeight / 2 - sx.Now() > w - minimap_width) {
						int delta = size.x * ui::TextHeight / 2 - sx.Now() - w + minimap_width;
						if (delta > ui::UnitHeight * 2)delta = ui::UnitHeight * 2;
						ui::special_effect::DrawShadowLine(x + w - minimap_width, y, x + w - minimap_width, y + h, 10 * ui::dpi, 1.0 * delta / ui::UnitHeight / 2);
					}
					if (check && MouseInRect(x + w - minimap_width, y, minimap_width - ui::SpaceSize * 3, h - ui::SpaceSize * 3)) {
						if (MouseInRect(x + w - minimap_width, y + sy.Now() * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight)) {
							DrawRectangle(x + w - minimap_width, y + sy.Now() * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight, ColorF(ChooseColor));
						}
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							if (MouseInRect(x + w - minimap_width, y + sy.Now() * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3.0 * dpi / UnitHeight)) {
								realn k = ((Mouse.y - (y + sy.Now() * dpi * 3.0 / UnitHeight - delta_y + h * 3.0 * dpi / UnitHeight / 2))) / h;
								choose_minimap = true;
								choose_minimap_delta = k * (sy.Now() * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight)));
							} else {
								realn k = (Mouse.y - h * 3.0 * dpi / UnitHeight / 2 - y) / h;
								sy.Set(k * (sy.Now() * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight))));
								choose_minimap = true;
								choose_minimap_delta = 0;
							}
						}
					}
					if (choose_minimap) {
						DrawRectangle(x + w - minimap_width, y + sy.Now() * dpi * 3.0 / UnitHeight - delta_y, minimap_width, h * 3.0 * dpi / UnitHeight, ColorF(ChooseColor));
						realn k = (Mouse.y - h * 3.0 * dpi / UnitHeight / 2 - y) / h;
						sy.Set(k * (sy.Sum() * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight))) - choose_minimap_delta);
					}
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))choose_minimap = false;
				}

				// 绘制滚动条
				sx.SetFixed(true);
				sy.SetFixed(true);
				sx.SetSum(size.x * ui::TextHeight / 2 + SliderWidth + tempW + minimap_width * minimap_visible);
				sy.SetSum(size.y * ui::UnitHeight + h - ui::UnitHeight - SliderWidth);
				sy.SetDrawCursor(true);
				sy.SetCursorPos(ipy.gnp() * UnitHeight);
				sx.Draw(x - tempW, y + h - SliderWidth, w - SliderWidth + tempW, SliderWidth);
				sy.Draw(x + w - SliderWidth, y, SliderWidth, h - SliderWidth);
				sx.Update();
				sy.Update();
				DrawRectangle(x + w - SliderWidth, y + h - SliderWidth, SliderWidth, SliderWidth, ColorF(DARKGRAY));

				// 结束
				EndScissor();
				return ui::UnitHeight;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = multi_height * ui::UnitHeight + 2 * ui::SpaceSize;
				x += dpi, y += dpi, w -= dpi * 2, h;
				Draw(x, y, w, h, check);
				special_effect::DrawMouseBox(x, y, w, h);
				return h + dpi;
			}
		};
		class CheckBox : public Element {
		public:
			bool choose = false;
			std::string text = "Check Box";
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				if (!choose)DrawRectangle(x, y + h, TextHeight, TextHeight, Color{20, 20, 20, 100});
				else DrawRectangle(x, y + h, TextHeight, TextHeight, MainColor);
				Print(x + TextHeight + SpaceSize, y + h, text);
				special_effect::DrawMouseRectangle(x, y + h, TextHeight, TextHeight);
				if (check && MouseInRect(x, y, w, UnitHeight)) {
					DrawRectangle(x, y + h, TextHeight, TextHeight, ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						choose = !choose;
					}
				}
				return UnitHeight;
			}
		};
		class Hyperlink : public Element {
		public:
			std::string text = "Hyperlink";
			std::string link = "https://www.luogu.com.cn/";
			Animation move;
			Hyperlink() {
				move.sd(300);
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				move.update();
				PrintIcon(x + SpaceSize, y + h, "", Color{177, 164, 246, 255});
				Print(x + UnitHeight + SpaceSize, y + h, text, Color{177, 164, 246, 255});
				int wi = text.size() * TextHeight / 2;
				DrawLineEx({x + SpaceSize + UnitHeight + wi / 2 - move.gnp()*wi / 2, y + h + TextHeight}, {x + SpaceSize + UnitHeight + wi / 2 + move.gnp()*wi / 2, y + h + TextHeight}, dpi, Color{177, 164, 246, 255});
				if (MouseInRect(x + UnitHeight + SpaceSize, y, text.size() * TextHeight / 2, UnitHeight)) {
					move.stp(1);
					MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						OpenURL(link.c_str());
					}
				} else move.stp(0);
				return UnitHeight;
			}
		};
		class RadioBox : public Element {
		private:
			Animation choose_ani[32];
			int DrawOne(int id, int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				DrawCircle(x + TextHeight / 2, y + h + TextHeight / 2, TextHeight / 2, Color{20, 20, 20, 255});
				DrawRing({x + TextHeight / 2, y + h + TextHeight / 2}, std::min(TextHeight / 2 - int(choose_ani[id].gnp()*TextHeight / 3.0), TextHeight / 2), TextHeight / 2, 0, 360, 30, MainColor);
				Print(x + TextHeight + SpaceSize, y + h, text[id]);
				special_effect::DrawMouseCircle(x + TextHeight / 2, y + h + TextHeight / 2, TextHeight / 2);
				if (check && MouseInRect(x, y, w, UnitHeight)) {
					DrawCircle(x + TextHeight / 2, y + h + TextHeight / 2, TextHeight / 2, ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						choose_ani[id].stp(1);
						choose = id;
					}
				}
				return UnitHeight;
			}
		public:
			int n = 3;
			int choose = -1;
			std::string text[32];
			RadioBox() {
				text[0] = "Radio Box # 1";
				text[1] = "Radio Box # 2";
				text[2] = "Radio Box # 3";
				for (int i = 0; i < 32; i++) {
					choose_ani[i].sd(400);
					choose_ani[i].sms(anif::bounce5);
				}
			}
			int Draw(int x, int y, int w, bool check = true) {
				for (int i = 0; i < n; i++) {
					choose_ani[i].update();
					DrawOne(i, x, y + ui::UnitHeight * i, w, check);
					if (choose != i)choose_ani[i].stp(0);
				}
				return UnitHeight * n;
			}
		};
		class TopMenuButton : public Element {
		public:
			int n = 3;
			std::string text[32];
			std::string icon[32];
			int click = -1;
			TopMenuButton() {
				text[0] = "Button1";
				text[1] = "Button1";
				text[2] = "Button3";
				icon[0] = "";
				icon[1] = "";
				icon[2] = "";
			}
			int DrawOne(int id, int x, int y, int w, int h, bool check = true) {
				int t = (UnitHeight * 2 - TextHeight) / 2;
				special_effect::DrawMouseRectangle(x, y + SpaceSize / 2, w, h - SpaceSize);
				PrintIcon(x + SpaceSize, y + t, icon[id], WHITE);
				Print(x + SpaceSize * 2 + TextHeight, y + t, text[id], WHITE);
				if (MouseInRect(x, y + SpaceSize / 2, w, h - SpaceSize)) {
					DrawRectangle(x, y + SpaceSize / 2, w, h - SpaceSize, ColorF(ChooseColor));
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && check)DrawRectangle(x, y + SpaceSize / 2, w, h - SpaceSize, ColorF(ChooseColor));
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check)click = id;
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				DrawRectangle(x, y, w, h, ColorF(50, 50, 50, 255));
				int w2 = dpi;
				click = -1;
				for (int i = 0; i < n; i++) {
					int s = GetStringLength(text[i]);
					DrawOne(i, x + w2, y, s * TextHeight / 2 + SpaceSize * 3 + TextHeight, h, check);
					w2 += s * TextHeight / 2 + SpaceSize * 3 + TextHeight + dpi;
				}
				return UnitHeight * 2;
			}
		};
		class BottomMenu : public Element {
		private:
			IconButton button[10];
		public:
			int n = 0;
			std::string text[10];
			std::string icon[10];
			Color color[10];
			int click = -1;
			BottomMenu() {
				for (int i = 0; i < 10; i++)color[i] = Color{47, 47, 47, 255};
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				click = -1;
				DrawRectangle(x, y, w, h, Color{35, 35, 35, 255});
				DrawLineEx({x, y + dpi / 2}, {x + w, y + dpi / 2}, dpi, Color{255, 255, 255, 30});
				int t = UnitHeight * 0.6;
				int width = t;
				for (int i = 0; i < n; i++) {
					button[i].text = text[i];
					button[i].icon = icon[i];
					button[i].color = color[i];
					int k = std::max(button[i].GetWidth(), UnitHeight * 4);
					button[i].Draw_Auto_Extra(x + w - width - k, y + t, k, UnitHeight * 1.3);
					if (button[i].click)click = i;
					width += k + SpaceSize;
				}
				return UnitHeight * 2.5;
			}
		};
		class Tip : public Priority {
		public:
			std::string text = "This is a tip.";
			bool pop = false;
			int pop_time = -1000;
			bool float_ = false;
			int float_time = 0;
			int delay = 1500;
			short flag = 0;
			int cx, cy, cw, ch;
			Element* ele;
			Tip() {
				extra = true;
				prio_flag = "Other";
			}
			int Set(int x, int y, int w, int h) {
				flag = 0;
				cx = x, cy = y, cw = w, ch = h;
			}
			int Set(Element* Ele) {
				flag = 1;
				ele = Ele;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (flag == 0)x = cx, y = cy, w = cw, h = ch;
				else x = ele->X, y = ele->Y, w = ele->W, h = ele->height;
				if (MouseInRect(x, y, w, h)) {
					if (!float_) {
						float_ = true;
						float_time = clock();
					}
				} else if (float_) {
					float_ = false;
				}
				if (float_ && clock() - float_time > delay && !pop) {
					pop = true;
					pop_time = clock();
					priority = ++TopPriority;
				}
				if (!float_ && pop) {
					pop = false;
					pop_time = clock();
				}
				if (pop || clock() - pop_time <= 200) {
					int tx, ty, tw, th;
					th = UnitHeight;
					tw = text.size() * TextHeight / 2 + SpaceSize * 2;
					tx = x + w / 2 - tw / 2;
					ty = y - th - SpaceSize;
					int h = (UnitHeight - TextHeight) / 2;
					double a;
					if (pop)a = (clock() - pop_time) / 200.0;
					else a = 1 - (clock() - pop_time) / 200.0;
					if (a > 1)a = 1;

					special_effect::DrawShadowRectangle(tx, ty, tw, th, a * 15 * dpi);
					DrawRectangleRounded(Rectangle{(float)tx, (float)ty, (float)tw, (float)th}, 0.4, 10, Fade(BgColor, a * 0.7));
					DrawRectangleRoundedLines(Rectangle{(float)tx, (float)ty, (float)tw, (float)th}, 0.4, 10, dpi, Fade(MainColor, a * 0.7));
					Print(tx + SpaceSize, ty + h, text, Fade(TextColor, a * 0.7));
				} else priority = -1;
				return 0;
			}
		};
		class Free : public Element {
		public:
			void (*draw_fun)(Free*) = nullptr;
			Camera2D camera = { 0 };
			Free() {
				extra = true;
				camera.target = (Vector2) {
					winW / 2, winH / 2
				};
				camera.offset = (Vector2) {
					winW / 2.0f, winH / 2.0f
				};
				camera.rotation = 0.0f;
				camera.zoom = 1.0f;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {

				camera.target = {0, 0};
				camera.offset = {x, y};
				BeginMode2D(camera);

				draw_fun(this);

				EndMode2D();

				return h;
			}
		};
		class Interface : public Element {
		private:
			int Height = 0;						// 控件高度
			bool swapping = false;				// 是否正在执行交换动画
			Animation appearAni;				// 淡入动画
			int update_tick = GetTick() - 100;	// 上次更新时间刻
		public:
			bool visible = true;				// 是否可见
			bool insert_ani = false;			// 是否启用插入动画
			bool appear_ani = true;				// 是否启用淡入动画
			bool sbar_visible = true;			// 是否启用滚动条
			int interval = ui::SpaceSize * 4;	// 控件与界面左右间隔
			int max_width = 500;				// 最大宽度
			realn blank = 0.3;					// 滚动条空白
			SliderBar sbar;						// 滚动条
			std::vector<Sider> sider;			// 侧边栏
			Position pos = pos_full;			// 控件位置
			void AddSider(Element* ele, SiderPosition spos, int occupy = -1) {
				Sider temp;
				temp.ele = ele;
				temp.spos = spos;
				temp.occupy = occupy;
				sider.push_back(temp);
			}
			Interface() {
				extra = true;
			}
			realn GetAniBias(int id) {
				return (1 - appearAni.GetPos(clock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id > 0)return appearAni.GetPos(clock() - id * 50);
				else return appearAni.GetPos((clock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}
			int Draw(int x, int y, int w = 600, int h = 600, bool check = true) {
				// 界面不可见，直接退出
				if (!visible)return 0;
				// 界面可见，检查是否启动淡入动画
				if (GetTick() - update_tick > 10) {
					appearAni.ssp(0);
					appearAni.stp(1);
				}
				update_tick = GetTick();
				// 初始化
				swapping = false;
				X = x, Y = y, W = w, H = h;
				BeginScissor(x, y, w, h);
				// 计算控件总高度
				Height = 0;
				for (int i = 0; i < key.size(); i++)if (!key[i]->extra)Height += key[i]->height;
				BeginAlphaMode(GetAniAlpha(-2));
				// 绘制侧边栏
				int dx = 0, dy = 0, dw = 0, dh = 0;
				for (int i = 0; i < sider.size(); i++) {
					if (sider[i].spos == spos_left) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, sider[i].occupy, h + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, sider[i].occupy, h + dh, check);
						dx += sider[i].occupy, dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_top) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, w + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, w + dw, sider[i].occupy, check);
						dy += sider[i].occupy, dh -= sider[i].occupy;
					}
					if (sider[i].spos == spos_right) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx + w + dw - sider[i].occupy, y + dy, sider[i].occupy, h + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx + w + dw - sider[i].occupy, y + dy, sider[i].occupy, h + dh, check);
						dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_bottom) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy + h + dh - sider[i].occupy, w + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy + h + dh - sider[i].occupy, w + dw, sider[i].occupy, check);
						dh -= sider[i].occupy;
					}
				}
				// 绘制控件
				for (int i = 0; i < key.size(); i++)if (key[i]->extra)key[i]->Draw_Auto_Extra(x + dx, y + dy, w + dw, h + dh, check);
				EndAlphaMode();
				BeginScissor(x + dx, y + dy, w + dw, h + dh);
				realn nowh = -sbar.Now();
				for (int i = 0; i < key.size(); i++) {
					if (!key[i]->extra) {
						bool next_check = (check && !swapping && MouseInRect(x + dx, y + dy, w + dw - ui::SpaceSize * 3, h + dh));
						int w2 = std::min(max_width, w + dw - interval);
						BeginAlphaMode(GetAniAlpha(i));
						if (pos == pos_full)		nowh += key[i]->Draw_Auto(x + dx + interval, y + dy + interval + nowh + GetAniBias(i), w + dw - interval * 2, next_check);
						else if (pos == pos_left)	nowh += key[i]->Draw_Auto(x + dx + interval, y + dy + interval + nowh + GetAniBias(i), w2, next_check);
						else if (pos == pos_right)	nowh += key[i]->Draw_Auto(x + dx + w + dw - interval - w2, y + dy + interval + nowh + GetAniBias(i), w2, next_check);
						else if (pos == pos_mid)	nowh += key[i]->Draw_Auto(x + dx + (w + dw) / 2 - w2 / 2, y + dy + interval + nowh + GetAniBias(i), w2, next_check);
						EndAlphaMode();
					}
				}
				EndScissor();
				// 绘制滚动条
				BeginAlphaMode(GetAniAlpha(-2));
				sbar.SetControl(x + dx, y + dy, w + dw, h + dh);
				sbar.SetSum(Height);
				sbar.SetBlank(blank);
				sbar.Draw(x + dx + w + dw - ui::SpaceSize * 3, y + dy, ui::SpaceSize * 3, h + dh, check);
				sbar.Update();
				EndAlphaMode();
				// 结束
				EndScissor();
				return H;
			}
		} mainintf;
		using interface = Interface;
		class Layout {
		public:
			ui::interface* intf = nullptr;
			Layout* lo1 = nullptr;
			Layout* lo2 = nullptr;
			double split = 0.5;
			bool movable = true;
			bool moving = false;
			SplitStyle split_style = split_main;

			~Layout() {
				delete lo1;
				delete lo2;
			}

			bool IsMoving() {
				return moving;
			}
			void Split(SplitStyle style, ui::interface* i1 = nullptr, ui::interface* i2 = nullptr) {
				if (style == split_main) {
					intf = i1;
				} else {
					split_style = style;
					if (lo1 != nullptr) {
						delete lo1;
					}
					if (lo2 != nullptr) {
						delete lo2;
					}
					lo1 = new Layout;
					lo2 = new Layout;
					lo1->intf = i1;
					lo2->intf = i2;
				}
			}
		};
		class Window : public Priority {
		public:
			std::string title = "Window";
			bool moving = false;
			bool rx = false, ry = false, rw = false, rh = false;
			bool pop = true;
			bool draw_title = true;
			bool draw_body = true;
			bool draw_dark = false;
			bool is_mainwin = false;
			int title_height = 25 * dpi;
			int ani_state = AniEnabled;
			int valid_x, valid_y, valid_w, valid_h;
			Vector2 move_start, pos_start;
			Animation xani, yani, wani, hani, darkani;
			Layout layout;

			std::vector<Sider> sider;
			SliderBar sbar;
			void AddSider(Element* ele, SiderPosition spos, int occupy = -1) {
				Sider temp;
				temp.ele = ele;
				temp.spos = spos;
				temp.occupy = occupy;
				sider.push_back(temp);
			}
			Window() {
				priority = ++TopPriority;
				prio_flag = "Window";
				MainSystem.Add(this);
				X = Y = 50;
				W = 860, H = 640;
				darkani.ssp(0.7);
				extra = true;
			}
			void Pop(int tx = 0, int ty = 0, int tw = winW, int th = winH, int fx = INT_MAX, int fy = INT_MAX, int fw = INT_MAX, int fh = INT_MAX) {
				X = tx, Y = ty, W = tw, H = th;
				if (fx == INT_MAX)fx = tx + tw / 4;
				if (fy == INT_MAX)fy = winH * 1.2;
				if (fw == INT_MAX)fw = tw / 2;
				if (fh == INT_MAX)fh = th;
				xani.ssp(fx + WindowPos.x), xani.stp(tx + WindowPos.x), xani.sd(500);
				yani.ssp(fy + WindowPos.y), yani.stp(ty + WindowPos.y), yani.sd(500);
				wani.ssp(fw + WindowPos.x), wani.stp(tw + WindowPos.y), wani.sd(500);
				hani.ssp(fh + WindowPos.x), hani.stp(th + WindowPos.y), hani.sd(500);
				priority = ++TopPriority;
				pop = true;
				darkani.stp(0.7);
			}
			void Close() {
				xani.stp(X + W / 4 + WindowPos.x);
				yani.stp(winH * 1.2 + WindowPos.y);
				wani.stp(W / 2);
				hani.stp(H);
				pop = false;
				darkani.stp(0);
			}
			void Hide() {
				xani.ssp(X + W / 4 + WindowPos.x);
				yani.ssp(winH * 1.2 + WindowPos.y);
				wani.ssp(W / 2);
				hani.ssp(H);
				pop = false;
				darkani.ssp(0);
				darkani.stp(0);
			}
			void SetPos(int x, int y, int w, int h) {
				X = x, W = w, Y = y, H = h;
				if (W < 100 * dpi)W = 100 * dpi;
				if (H < title_height)H = title_height;
				if (W > winW)W = winW;
				if (H > winH)H = winH;
				if (Y < 0)Y = 0;
				if (X < 0)X = 0;
				if (X + W > winW)X = winW - W;
				if (Y + H > winH)Y = winH - H;
			}
			void DrawLayout(Layout* lo, int x, int y, int w, int h, bool check = true) {
				int k = SpaceSize;
				if (lo->split_style == split_main && lo->intf != nullptr) {
					lo->intf->Draw_Auto_Extra(x, y, w, h, check);
				} else if (lo->split_style == split_row) {
					if (lo->movable) {
						if (lo->moving) {
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
							lo->split = 1.0 * (GetMouseX() - x - 4 * dpi) / (w - 8 * dpi);
							if (lo->split < 0)lo->split = 0;
							if (lo->split > 1)lo->split = 1;
							DrawLayout(lo->lo1, x, y, (w - 8 * dpi) * lo->split, h, check && !lo->moving);
							DrawLayout(lo->lo2, x + (w - 8 * dpi) * lo->split + 8 * dpi, y, (w - 8 * dpi) * (1 - lo->split), h, check && !lo->moving);
							DrawRectangle(x + (w - 8 * dpi) * lo->split, y, 8 * dpi, h, LIGHTGRAY);
							DrawLine(x + (w - 8 * dpi) * lo->split + 2 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * lo->split + 2 * dpi, y + h / 2 + 10 * dpi, BLACK);
							DrawLine(x + (w - 8 * dpi) * lo->split + 6 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * lo->split + 6 * dpi, y + h / 2 + 10 * dpi, BLACK);
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
							if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))lo->moving = false;
						} else {
							DrawLayout(lo->lo1, x, y, (w - 8 * dpi) * lo->split, h, check && !lo->moving);
							DrawLayout(lo->lo2, x + (w - 8 * dpi) * lo->split + 8 * dpi, y, (w - 8 * dpi) * (1 - lo->split), h, check && !lo->moving);
							special_effect::DrawMouseRectangle_onlyLight(x + (w - 8 * dpi) * lo->split, y, 8 * dpi, h);
							DrawLine(x + (w - 8 * dpi) * lo->split + 2 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * lo->split + 2 * dpi, y + h / 2 + 10 * dpi, DARKGRAY);
							DrawLine(x + (w - 8 * dpi) * lo->split + 6 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * lo->split + 6 * dpi, y + h / 2 + 10 * dpi, DARKGRAY);
							if (MouseInRect(x + (w - 8 * dpi) * lo->split, y, 8 * dpi, h) && check) {
								DrawRectangle(x + (w - 8 * dpi) * lo->split + dpi, y, 6 * dpi, h, Fade(LIGHTGRAY, 0.25));
								MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))lo->moving = true;
							}
						}
					} else {
						DrawLayout(lo->lo1, x, y, w * lo->split, h, check);
						DrawLayout(lo->lo2, x + w * lo->split, y, w * (1 - lo->split), h, check);
					}
				} else if (lo->split_style == split_col) {
					if (lo->movable) {
						if (lo->moving) {
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
							lo->split = 1.0 * (GetMouseY() - y - 4 * dpi) / (h - 8 * dpi);
							if (lo->split < 0)lo->split = 0;
							if (lo->split > 1)lo->split = 1;
							DrawLayout(lo->lo1, x, y, w, (h - 8 * dpi) * lo->split, check && !lo->moving);
							DrawLayout(lo->lo2, x, y + (h - 8 * dpi) * lo->split + 8 * dpi, w, (h - 8 * dpi) * (1 - lo->split), check && !lo->moving);
							DrawRectangle(x, y + (h - 8 * dpi) * lo->split, w, 8 * dpi, LIGHTGRAY);
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * lo->split + 2 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * lo->split + 2 * dpi, BLACK);
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * lo->split + 6 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * lo->split + 6 * dpi, BLACK);
							if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))lo->moving = false;
						} else {
							DrawLayout(lo->lo1, x, y, w, (h - 8 * dpi) * lo->split, check && !lo->moving);
							DrawLayout(lo->lo2, x, y + (h - 8 * dpi) * lo->split + 8 * dpi, w, (h - 8 * dpi) * (1 - lo->split), check && !lo->moving);
							special_effect::DrawMouseRectangle_onlyLight(x, y + (h - 8 * dpi) * lo->split, w, 8 * dpi);
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * lo->split + 2 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * lo->split + 2 * dpi, DARKGRAY);
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * lo->split + 6 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * lo->split + 6 * dpi, DARKGRAY);
							if (MouseInRect(x, y + (h - 8 * dpi) * lo->split, w, 8 * dpi) && check) {
								DrawRectangle(x, y + (h - 8 * dpi) * lo->split + dpi, w, 6 * dpi, Fade(LIGHTGRAY, 0.25));
								MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
								if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))lo->moving = true;
							}
						}
					} else {
						DrawLayout(lo->lo1, x, y, w, h * lo->split, check);
						DrawLayout(lo->lo2, x, y + h * lo->split, w, h * (1 - lo->split), check);
					}
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (pop) {
					xani.stp(X + WindowPos.x);
					yani.stp(Y + WindowPos.y);
					wani.stp(W);
					hani.stp(H);
					if (WindowState == state_moving) {
						xani.gt(X + WindowPos.x);
						yani.gt(Y + WindowPos.y);
						wani.gt(W);
						hani.gt(H);
					} else {
						if (moving || rx || ry || rw || rh) {
							xani.sms(anif::classics);
							yani.sms(anif::classics);
							wani.sms(anif::classics);
							hani.sms(anif::classics);
							xani.sd(300);
							yani.sd(300);
							wani.sd(300);
							hani.sd(300);
						} else {
							xani.sms(anif::bounce1);
							yani.sms(anif::bounce1);
							wani.sms(anif::bounce2);
							hani.sms(anif::bounce2);
							xani.sd(500);
							yani.sd(500);
							wani.sd(500);
							hani.sd(500);
						}
					}
				}
				xani.update();
				yani.update();
				wani.update();
				hani.update();
				darkani.update();
				x = xani.gnp() - WindowPos.x;
				y = yani.gnp() - WindowPos.y;
				w = wani.gnp();
				h = hani.gnp();

				if (!pop && !xani.IsRunning())return 0;
				if (draw_dark && !is_mainwin) {
					DrawRectangle(0, 0, winW, winH, Fade(BLACK, darkani.gnp()));
				}
				if (draw_body) {
					special_effect::DrawShadowRectangle(x, y, w, h, 15 * dpi);
					DrawRectangle(x, y, w, h, BgColor);
					DrawRectangleLines(x - 1, y - 1, w + 2, h + 2, Color{255, 255, 255, 30});
					DrawRectangleLines(x - 2, y - 2, w + 4, h + 4, Color{255, 255, 255, 30});
					if (draw_title) {
						if (priority == WindowTopPriority) {
							DrawRectangle(x, y, w, title_height, MainColor);
						} else {
							Color c = MainColor;
							c.r * 0.7, c.g *= 0.7, c.b *= 0.7;
							DrawRectangle(x, y, w, title_height, c);
						}
						int t = (title_height - TextHeight) / 2;
						int tw = TextHeight + SpaceSize * 2 + GetStringLength(title) * TextHeight / 2;
						PrintIcon(x + (w - tw) / 2, y + t, "", TextColor2);
						Print(x + (w - tw) / 2 + TextHeight + SpaceSize * 2, y + t, title, TextColor2);
					}
					if (priority == WindowTopPriority) {
						if (draw_title) {
							if ( MouseInRect(x, y, w, title_height) && !rx && !ry && !rw && !rh) {
								if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ani_state = AniEnabled, moving = true, move_start = Mouse, pos_start = {X, Y};
							}
						}
						if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))moving = false;
						if (moving && pop) {
							X = Mouse.x - move_start.x + pos_start.x;
							Y = Mouse.y - move_start.y + pos_start.y;
							xani.stp(X);
							yani.stp(Y);
						}
					}
					if (draw_title) {
						y += title_height;
						h -= title_height;
					}
				}

				BeginScissor(x, y, w, h);
				int dx = 0, dy = 0, dw = 0, dh = 0;

				for (int i = 0; i < sider.size(); i++) {
					if (sider[i].spos == spos_left) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, sider[i].occupy, h + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, sider[i].occupy, h + dh, check);
						dx += sider[i].occupy, dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_top) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, w + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy, w + dw, sider[i].occupy, check);
						dy += sider[i].occupy, dh -= sider[i].occupy;
					}
					if (sider[i].spos == spos_right) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx + w + dw - sider[i].occupy, y + dy, sider[i].occupy, h + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx + w + dw - sider[i].occupy, y + dy, sider[i].occupy, h + dh, check);
						dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_bottom) {
						if (sider[i].occupy <= 0)sider[i].occupy = 25 * dpi, sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy + h + dh - sider[i].occupy, w + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(x + dx, y + dy + h + dh - sider[i].occupy, w + dw, sider[i].occupy, check);
						dh -= sider[i].occupy;
					}
				}

				int tx = x, ty = y, tw = w, th = h;
				x += dx, y += dy, w += dw, h += dh;

				xani.update();
				yani.update();
				wani.update();
				hani.update();
				BeginScissor(x, y, w, h);
				valid_x = x, valid_y = y, valid_w = w, valid_h = h;
				DrawLayout(&layout, x, y, w, h, check && (!(rx || ry || rw || rh) | !IsMouseButtonDown(MOUSE_BUTTON_LEFT)));
				EndScissor();
				EndScissor();
				xani.update();
				yani.update();
				wani.update();
				hani.update();

				if (draw_title) {
					if (priority == WindowTopPriority || check) {
						if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							if (!is_mainwin) {
								bool cx = false, cy = false, cw = false, ch = false;
								int k = 5 * dpi;
								if ( Mouse.y >= Y - k && Mouse.y <= Y + H + k) {
									if ( Mouse.x >= X - k && Mouse.x < X)cx = true;
									if ( Mouse.x > X + W && Mouse.x <= X + W + k)cw = true;
								}
								if ( Mouse.x >= X - k && Mouse.x <= X + W + k) {
									if ( Mouse.y >= Y - k && Mouse.y < Y)cy = true;
									if ( Mouse.y > Y + H && Mouse.y <= Y + H + k)ch = true;
								}
								if ((cx && cy) || (cw && ch)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NWSE;
								else if ((cx && ch) || (cy && cw)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NESW;
								else if (cx || cw) MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								else if (cy || ch) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
								rx = cx, ry = cy, rw = cw, rh = ch;
							}
						}
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
							if (!is_mainwin) {
								int tx = Mouse.x, ty = Mouse.y;
								if (tx < 0)tx = 0;
								if (ty < 0)ty = 0;
								if (tx > winW)tx = winW;
								if (ty > winH)ty = winH;
								if (rx)W = X + W - tx, X = tx;
								if (ry)H = Y + H - ty, Y = ty;
								if (rw)W = tx - X;
								if (rh)H = ty - Y;
								if ((rx && ry) || (rw && rh)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NWSE;
								else if ((rx && rh) || (ry && rw)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NESW;
								else if (rx || rw) MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								else if (ry || rh) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
							}
						}
					}
				}

				if (W < 100 * dpi)W = 100 * dpi;
				if (H < title_height)H = title_height;
				if (W > winW)W = winW;
				if (H > winH)H = winH;
				if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
					if (Y < 0)Y = 0;
					if (X < 0)X = 0;
					if (X + W > winW)X = winW - W;
					if (Y + H > winH)Y = winH - H;
				}

				if (pop) {
					xani.stp(X + WindowPos.x);
					yani.stp(Y + WindowPos.y);
					wani.stp(W);
					hani.stp(H);
				}

				return 0;
			}
		} mainwin;

		bool System::CMP_Window(Window* w1, Window* w2) {
			return w1->priority > w2->priority;
		}
		void System::Update() {
			sort(win.begin(), win.end(), CMP_Window);
			TopPriority = win[0]->priority;
			bool c[1005], flag = false;
			int k = 5 * dpi;
			for (int i = 0; i < win.size(); i++) {
				if ( MouseInRect(win[i]->X - k, win[i]->Y - k, win[i]->W + k * 2, win[i]->H + k * 2)) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && win[i]->pop && (!win[i]->is_mainwin || !flag)) {
						if (win[i]->priority != TopPriority)win[i]->priority = ++TopPriority;
						break;
					}
				}
				if (win[i]->pop)flag = true;
			}
			sort(win.begin(), win.end(), CMP_Window);
			for (int i = 0; i < win.size(); i++) {
				if (win[i]->prio_flag == "Window" && win[i]->pop) {
					WindowTopPriority = win[i]->priority;
					break;
				}
			}
			memset(c, 0, sizeof(c));
			for (int i = 0; i < win.size(); i++) {
				c[i] = false;
				if (!win[i]->pop)continue;
				if ( (MouseInRect(win[i]->X - k, win[i]->Y - k, win[i]->W + k * 2, win[i]->H + k * 2) || win[i]->is_mainwin )
				     && (win[i]->priority == WindowTopPriority || !win[i]->is_mainwin)) {
					c[i] = true;
					break;
				}
			}
			for (int i = win.size() - 1; i >= 0; i--) {
				win[i]->Draw(0, 0, 0, 0, c[i]);
			}
		}

		class LeftMenu : public Element {
		public:
			int n = 5;
			std::string text[32];
			std::string icon[32];
			int last_choose = -1;
			int choose = 0;
			bool draw_full = false;
			bool full_alltime = false;
			interface* intf[32];
			Window* target = nullptr;
			Animation move;
			bool move_inited = false;
			int choise = -1;
			int choose_time = 0;
			int menu_width = 250;
			LeftMenu() {
				text[0] = "Interface #1";
				text[1] = "Interface #2";
				text[2] = "Interface #3";
				text[3] = "Interface #4";
				text[4] = "Interface #5";
				icon[0] = "";
				icon[1] = "";
				icon[2] = "";
				icon[3] = "";
				icon[4] = "";
				move.sd(300);
			}
			int DrawOne(int id, int x, int y, int w, bool check = true) {
				int t = (2 * UnitHeight - TextHeight) / 2;
				special_effect::DrawMouseRectangle_onlyLight(x, y, w, UnitHeight * 2);
				if (id == -1) {
					PrintIcon(x + SpaceSize * 3, y + t, "", WHITE);
					return 0;
				}
				if (id == choose)PrintIcon(x + SpaceSize * 3, y + t, icon[id].c_str(), BLUE);
				else PrintIcon(x + SpaceSize * 3, y + t, icon[id].c_str(), WHITE);
				if (draw_full || full_alltime)Print(x + SpaceSize * 6 + TextHeight, y + t, text[id], WHITE);
				if (MouseInRect(x, y, w, UnitHeight * 2)) {
					DrawRectangle(x, y, w, UnitHeight * 2, ChooseColor);
					if (check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						choise = id;
						choose_time = clock();
					}
				}
				if (choise == id) {
					DrawRectangle(x, y, w, UnitHeight * 2, ChooseColor);
				}
				if (choise != -1 && clock() - choose_time > 200) {
					choose = choise;
					choise = -1;
				}
				return 0;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (full_alltime)draw_full = true;
				if (!move_inited) {
					if (!draw_full)move.ssp(SpaceSize * 6 + TextHeight);
					else move.ssp(menu_width * dpi);
					move_inited = true;
				} else {
					if (!draw_full)move.stp(SpaceSize * 6 + TextHeight);
					else move.stp(menu_width * dpi);
				}
				move.update();
				DrawRectangle(x, y, move.gnp(), h, BLACK);
				for (int i = 0; i <= n; i++) {
					if (draw_full)DrawOne(i - 1, x, y + i * UnitHeight * 2, move.gnp(), check);
					else DrawOne(i - 1, x, y + i * UnitHeight * 2, move.gnp(), check);
				}
				if (target != nullptr) {
					if (choose != last_choose) {
						target->layout.intf = intf[choose];
						intf[choose]->sbar.Set(0);
						last_choose = choose;
					}
				}
				if (target->W > 700 * dpi)draw_full = true;
				else draw_full = false;
				return move.gnp();
			}
		};

		int Init(int winw = 1080, int winh = 720, double zoom = 1) {
			// 窗口
			if (!IsWindowReady()) {
				SetConfigFlags(FLAG_MSAA_4X_HINT);
				SetConfigFlags(FLAG_WINDOW_RESIZABLE);
				SetTraceLogLevel(LOG_WARNING);
				InitWindow(winw, winh, "GGCC UI - Debugger");
				winW = winw, winH = winh;
			}
			winW = GetScreenWidth();
			winH = GetScreenHeight();
			DPI = GetWindowScaleDPI();
			TextHeight = 16;
			UnitHeight = 20;
			SpaceSize = 5;
			DPI.x *= zoom * Scale;
			TextHeight *= DPI.x;
			UnitHeight *= DPI.x;
			SpaceSize *= DPI.x;
			SliderWidth *= DPI.x;
			dpi = DPI.x;
			// 虚拟窗口
			mainwin.draw_body = false;
			mainwin.is_mainwin = true;
			mainwin.layout.intf = &mainintf;
			// 字体
			if (FontName == "仿宋")fontFileData = LoadFileData("C:/windows/fonts/simfang.ttf", &fileSize);
			if (FontName == "宋体")fontFileData = LoadFileData("C:/windows/fonts/SIMSUN.ttf", &fileSize);
			if (FontName == "微软雅黑")fontFileData = LoadFileData("C:/windows/fonts/simhei.ttf", &fileSize);
			if (FontName == "隶书")fontFileData = LoadFileData("C:/windows/fonts/simli.ttf", &fileSize);
			if (FontName == "楷体")fontFileData = LoadFileData("C:/windows/fonts/simkai.ttf", &fileSize);
			SetTraceLogLevel(LOG_WARNING);
			int codepointsCount;
			int *codepoints = LoadCodepoints(UseCharacter.Text().c_str(), &codepointsCount);
			font = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
			UnloadFileData(fontFileData);
			UnloadCodepoints(codepoints);
			ui::UseIcon(" ");
			// 字幕
			std::cout << "__________________________________" << std::endl << std::endl;
			std::cout << "[#] UI started successfully!" << std::endl;
			std::cout << "[#] UI Sysem : " << UIVer << std::endl;
			std::cout << "[#] GGCC Version : 6.0.0" << std::endl;
			std::cout << "[#] GGCC-SDK : 1.0.0" << std::endl;
			std::cout << "__________________________________" << std::endl;
			// 鼠标动画
			MouseXAni.sd(300);
			MouseYAni.sd(300);
			// 启动动画
			if (StartAni) {
				int _time = clock() + 3100;
				Animation logo_ani, cir_ani, a_ani;
				logo_ani.ssp(0);
				logo_ani.sd(600);
				logo_ani.sms(anif::sine);
				logo_ani.stp(1, 3100);
				cir_ani.ssp(0);
				cir_ani.sd(600);
				cir_ani.sms(anif::sine);
				cir_ani.stp(1, 3000);
				a_ani.ssp(255);
				a_ani.stp(0, 300);
				a_ani.sms(anif::linear);
				a_ani.sd(500);
				Logo logo;
				while (clock() - _time < 300 && !WindowShouldClose()) {
					logo_ani.update();
					a_ani.update();
					cir_ani.update();
					winW = GetScreenWidth();
					winH = GetScreenHeight();
					int k = std::min(int(winW * 0.1), int(80 * dpi));
					if (clock() - _time < 0) {
						BeginDrawing();
						ClearBackground(BgColor);
						logo.ftcolor = LIGHTGRAY;
						logo.bgcolor = BgColor;
						logo.Draw(winW / 2 - k, winH / 2 - k, k * 2, k * 2);
					} else {
						realn a = (300 - (clock() - _time)) / 300.0;
						BeginDrawing();
						ClearBackground(BgColor);
						logo.ftcolor.r = 200 * a + BgColor.r * (1 - a);
						logo.ftcolor.g = 200 * a + BgColor.g * (1 - a);
						logo.ftcolor.b = 200 * a + BgColor.b * (1 - a);
						logo.bgcolor = BgColor;
						logo.Draw(winW / 2 - k, winH / 2 - k + logo_ani.gnp() * (winH * 0.5 + winW * 0.1), k * 2, k * 2);
					}
					Color c = BgColor;
					c.a = a_ani.gnp();
					special_effect::DrawLoadingCircle(winW / 2, winH * 4 / 5 + cir_ani.gnp() * (winH * 0.5 + winW * 0.1), k / 5);
					DrawRectangle(0, 0, winW, winH, c);
					EndDrawing();
					if (WindowShouldClose()) {
						CloseWindow();
						exit(0);
					}
				}
				BeginDrawing();
				ClearBackground(BgColor);
				EndDrawing();
			}
			SetTargetFPS(70);

			return 0;
		}
		void Update() {
			// 更新内容
			special_effect::Draw();
			LastWindowSize = Vector2{winW, winH};
			LastWindowPos = WindowPos;
			winW = GetScreenWidth();
			winH = GetScreenHeight();
			Mouse = GetMousePosition();
			WindowPos = GetWindowPosition();
			WindowSize = Vector2{winW, winH};
			MouseXAni.update();
			MouseYAni.update();
			MouseXAni.stp(Mouse.x);
			MouseYAni.stp(Mouse.y);
			MouseShadow.x = MouseXAni.gnp();
			MouseShadow.y = MouseYAni.gnp();
			if (LastWindowSize != WindowSize)WindowState = state_resizing;
			else if (LastWindowPos != WindowPos)WindowState = state_moving;
			else WindowState = state_static;
			tick++;
			// 输入检查
			if (FasterInput) {
				GetChar = 0;
				GetCharString = "";
				for (int i = 32; i <= 96; i++)if (IsKeyInput(i)) {
						GetChar = i;
						break;
					}
				if (GetChar && IsKeyDown(KEY_LEFT_SHIFT)) {
					if (GetChar == '1')GetCharString = "!";
					else if (GetChar == '2')GetCharString = "@";
					else if (GetChar == '3')GetCharString = "#";
					else if (GetChar == '4')GetCharString = "$";
					else if (GetChar == '5')GetCharString = "%";
					else if (GetChar == '6')GetCharString = "^";
					else if (GetChar == '7')GetCharString = "&";
					else if (GetChar == '8')GetCharString = "*";
					else if (GetChar == '9')GetCharString = "(";
					else if (GetChar == '0')GetCharString = ")";
					else if (GetChar == '-')GetCharString = "_";
					else if (GetChar == '=')GetCharString = "+";
					else if (GetChar == '[')GetCharString = "{";
					else if (GetChar == ']')GetCharString = "}";
					else if (GetChar == '\\')GetCharString = "|";
					else if (GetChar == ';')GetCharString = ":";
					else if (GetChar == '\'')GetCharString = "\"";
					else if (GetChar == ',')GetCharString = "<";
					else if (GetChar == '.')GetCharString = ">";
					else if (GetChar == '/')GetCharString = "?";
					else if (GetChar == '`')GetCharString = "~";
					else GetCharString = GetChar;
				} else if (GetChar)GetCharString = tolower(GetChar);
				else if (!GetChar)GetCharString = "";
			} else {
				int key = GetCharPressed();
				GetChar = key;
				GetCharString = "";
				while (key > 0) {
					std::string temp = wp::GetChar(key);
					GetCharString += temp;
					key = GetCharPressed();
				}
			}
			// 字体加载
			if (UseCharacter.Change()) {
				UnloadFont(font);
				if (FontName == "仿宋")fontFileData = LoadFileData("C:/windows/fonts/simfang.ttf", &fileSize);
				if (FontName == "宋体")fontFileData = LoadFileData("C:/windows/fonts/SIMSUN.ttf", &fileSize);
				if (FontName == "微软雅黑")fontFileData = LoadFileData("C:/windows/fonts/simhei.ttf", &fileSize);
				if (FontName == "隶书")fontFileData = LoadFileData("C:/windows/fonts/simli.ttf", &fileSize);
				if (FontName == "楷体")fontFileData = LoadFileData("C:/windows/fonts/simkai.ttf", &fileSize);
				SetTraceLogLevel(LOG_WARNING);
				int codepointsCount;
				int *codepoints = LoadCodepoints(UseCharacter.Text().c_str(), &codepointsCount);
				font = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
				UnloadFileData(fontFileData);
				UnloadCodepoints(codepoints);
			}
			if (UseCharacter.Text().size() > 500) {
				UseCharacter.Set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;\':\",./<>?");
			}
			// 绘制
			UseSliderX = false;
			UseSliderY = false;
			MainSystem.Update();
			message::Draw();
			mainwin.SetPos(0, 0, winW, winH);
			mainwin.priority = 0;
			if (MouseCursorStyle >= 0) {
				ShowCursor();
				SetMouseCursor(MouseCursorStyle);
			} else HideCursor();
			MouseCursorStyle = MOUSE_CURSOR_ARROW;
		}
		void Run(void (*script)() = nullptr) {
			while (!WindowShouldClose()) {
				BeginDrawing();
				//rlViewport(0,0,ui::winW,ui::winH);
				ClearBackground(ui::BgColor);
				ui::Update();
				if (script != nullptr)script();
				EndDrawing();
			}
			Running = true;
		}

	}

	// 平面几何绘制函数
	namespace pg {
		void circle::Draw(ui::GraphDebugger* G, realn r2, realn g, realn b, realn a) {
			G->draw_circle(pos, r, Color{r2, g, b, a});
		}
		void ellipse::Draw(ui::GraphDebugger* G, realn r2, realn g, realn b2, realn a2) {
			G->draw_ellipse(pos, a, b, rotate, Color{r2, g, b2, a2});
		}
		void polygon::Draw(ui::GraphDebugger* G, realn r2, realn g, realn b, realn a) {
			int n = p.size();
			if (n <= 2)return;
			Vector2 p2[n], p3[n];
			for (int i = 0; i < n; i++)p2[i] = ggcc::ui::_V(G->W2S(Abs(p[i])) + vector2d{G->X, G->Y});
			for (int i = 0; i < n; i++)p3[n - i - 1] = ggcc::ui::_V(G->W2S(Abs(p[i])) + vector2d{G->X, G->Y});
			DrawTriangleFan(p2, n, Color{r2, g, b, a * 0.2});
			DrawTriangleFan(p3, n, Color{r2, g, b, a * 0.2});
			for (int i = 0; i < n - 1; i++)G->draw_line(Abs(p[i]), Abs(p[i + 1]), Color{r2, g, b, a});
			G->draw_line(Abs(p[n - 1]), Abs(p[0]), Color{r2, g, b, a});
		}
		void shape::Draw(ui::GraphDebugger* G, realn r2, realn g, realn b, realn a) {
			return;
		}
	}

}

#endif
