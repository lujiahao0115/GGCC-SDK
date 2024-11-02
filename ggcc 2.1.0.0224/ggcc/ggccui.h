// ggccui.h
// ggcc用户界面库（调试器风格）（raylib）

#ifndef GGCCUI_H
#define GGCCUI_H

// 以下是当前版本号
#define UIVer "GGCC UI 2.1.0.0224"

#include <bits/stdc++.h>
#include <raylib.h>
#include <rlgl.h>
#include <ggcc/animation.h>
#include <ggcc/math/point.h>

#ifdef USE_CHINESE_INPUT
#include <ggcc/to_utf8.h>
#endif

using namespace std;

#define real long double

namespace ggcc {
	
	namespace ui {
		
		// 参数
		int TextHeight = 16;				// 字符高度
		int UnitHeight = 20;				// 单元格高度
		int SpaceSize = 5;					// 空白长度
		int ScissorDeep = 0;				// 剪切深度
		Vector2 ScissorPoint[64];			// 剪切起始位置
		Vector2 ScissorSize[64];			// 剪切大小
		Vector2 DPI = Vector2 {1, 1};		// dpi
		double Scale=1.0;					// 放大率
		Font font;							// 字体
		Font IconFont;						// 图标字体
		string Icons;						// 图标集
		int winW;							// 窗口宽
		int winH;							// 窗口高
		Vector2 Mouse;						// 鼠标位置
		Vector2 MouseShadow;				// 鼠标残影位置
		Color MainColor = Color {43, 74, 121, 255};	// 主题色
		Color UnitBgColor = Color {43, 74, 121, 150};	// 单元格背景色
		Color ChooseColor = Color {132, 132, 132, 50};	// 选择背景色
		Color BgColor = Color {32, 32, 32, 220};			// 背景色
		Color TextColor = WHITE;						// 字体色
		Color TextColor2 = LIGHTGRAY;					// 辅助字体色
		char GetChar = 0;								// 字符输入
		string GetCharString = "";						// 字符输入
		int MouseCursorStyle = MOUSE_CURSOR_ARROW;		// 鼠标样式
		bool DrawSpecialEffect = true;				// 是否开启特效
		bool DebugMode=false;						// 是否开启调试模式
		bool StartAni = true;						// 是否开启启动动画
		bool Running = true;						// 程序是否在运行
		bool UseSliderX = false;					// 是否有Slider正在使用
		bool UseSliderY= false;					// 是否有Slider正在使用
		int tick=0;									// 运行刻
		string FontName="微软雅黑";
		unsigned int fileSize;
		unsigned char *fontFileData;
		int codepointsCount;
		int *codepoints;
		real dpi;
		Animation MouseXAni,MouseYAni;
		
		// 声明(不全)
		int Init(int, int, double);			// 初始化
		void Update();						// 更新
		void BeginScissor(float, float, float, float);	// 开始剪切
		void EndScissor();					// 结束剪切
		void Print(int, int, string, Color c);	// 打印文本
		bool MouseInRect(real, real, real, real); // 鼠标是否在矩形内
		class Element;						// 元素（基类）
		class Title;						// 标题
		class Text;							// 字幕
		class Line;							// 分割线
		class Textbox;						// 文本框
		class Button;						// 按钮
		class Button2;						// 按钮（两个）
		class Button3;						// 按钮（三个）
		class Slider;						// 拉动条
		class Slider_Int;					// 拉动条(整型)
		class Switch;						// 开关
		class Choose;						// 选择框
		class Dropdown;						// 下拉内容
		class Interface;					// 界面
		class Popup;						// 弹窗
		class InputBox;						// 输入框
		class CheckBox;						// 复选框
		class System;						// 系统
		class Window;						// 窗口
		Element* ChooseInputBox = NULL;		// 选择的输入框
		Slider* ChooseSlider = nullptr;		// 选择的拉动条
		
		void BeginScissor(float x, float y, float w, float h);
		void GetScissor(float* x, float* y, float* w, float* h);
		bool InScissor(float x, float y, float w, float h);
		bool InScissor(float x, float y);
		void EndScissor();
		
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
		
		// 附属功能
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
		int GetStringLength(string str) {
			return str.size() - GetChineseCharacterCount(str.c_str());
		}
		int strLen(string str) {
			return str.size() - GetChineseCharacterCount(str.c_str());
		}
		map <int, short> key_state;
		map <int, int> key_down_time;
		map <int, int> key_down_tick;
		bool IsKeyInput(int key) {
			bool input = false;
			if(tick!=0&&tick==key_down_tick[key])return true;
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
		namespace message {
			class Message {
			public:
				string text = "[Message]";
				bool pop = false;
				int width;
				Animation xAni, yAni;
				int textsize = 0;
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
					DrawRectangleRounded({-UnitHeight, yAni.gnp(), xAni.gnp() + UnitHeight, UnitHeight}, 0.5, 0, {255, 207, 73, 255});
					Print(SpaceSize - width + xAni.gnp(), yAni.gnp() + h, text.c_str(), DARKGRAY);
					Print(-UnitHeight + xAni.gnp() + TextHeight * 0.15, yAni.gnp() + h, "×", DARKGRAY);
					if (clock() - pop_time >= duration)Close();
					if (!pop)return 0;
					if (MouseInRect(-UnitHeight + xAni.gnp(), yAni.gnp(), UnitHeight, UnitHeight)) {
						DrawRectangleRounded({-UnitHeight + xAni.gnp(), yAni.gnp(), UnitHeight, UnitHeight}, 0.5, 0, ChooseColor);
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))Close();
					}
					return UnitHeight;
				}
			};
			deque<Message> Message_queue;
			void Send(string a, int duration = 5000, int size = 0) {
				Message m;
				m.text = a;
				m.textsize = size;
				m.duration = duration;
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
				int last_time=-2000;
				static real lani(real x) {
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
					if(clock()-last_time>500) {
						for (int i = 0; i < 5; i++) {
							angle[i].sd(duration);
							angle[i].sms(lani, -1.35, 1.35);
							angle[i].ssp(0 - (i - 2) * 0.2);
							angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, (i - 2)*duration / 10);
						}
						update_time = clock();
						update_pos=-1;
					}
					for (int i = 0; i < 5; i++) {
						angle[i].Update();
						if (clock() - update_time - (i - 2)*duration / 10 >= duration && update_pos < i) {
							update_pos = i;
							angle[i].ssp(0 - (i - 2) * 0.2);
							angle[i].stp(3.14159265359 * 2 - (i - 2) * 0.2, clock() - update_time - duration - (i - 2)*duration / 10);
							if (i == 4)update_time += duration, update_pos = -1;
						}
						vector2d v = {0, -r};
						v = v.Rotate(-angle[i].gnp());
						if(angle[i].is_run())DrawCircle(x + v.x, y - v.y, ceil(r / 7.0), WHITE);
					}
					last_time=clock();
				}
			};
			class LoadingLine {
			public:
				Animation angle[5];
				int duration = 2000;
				static real lani(real x) {
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
				void Draw(int x, int y, int w, real r = 2.5 * DPI.x) {
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
						if (angle[i].IsRunning())DrawCircle(x + angle[i].gnp()*w, y, r, WHITE);
					}
					EndScissor();
				}
			};
			class LoadingLineSolid {
			public:
				Animation a1, a2;
				int duration = 1500;
				LoadingLineSolid() {
					a1.sd(duration), a1.sms(atan, -5, 5), a1.ssp(-0.2), a1.stp(1.2), a1.Repeat(true);
					a2.sd(duration), a2.sms(atan, -5, 5), a2.ssp(-0.2), a2.stp(1.2, duration / 7.0), a2.Repeat(true);
				}
				void Draw(int x, int y, int w, double r = 1.5 * DPI.x) {
					a1.update();
					a2.update();
					double x1 = max((real)0.0, a2.gnp()), x2 = min((real)1.0, a1.gnp());
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
				DrawRectangleLinesEx({x-s,y-s,w+s*2,h+s*2},s,Color{255,255,255,30});
				DrawMouseRectangle_onlyLight(x-s,y-s,w+s*2,h+s*2,r,s);
			}
			void DrawLoadingCircle(int x, int y, int r, string text = "", int size = 0) {
				loading_circle.Draw(x, y, r);
				if (size == 0)size = text.size();
				Print(x - size * TextHeight / 4, y + r * 2.1, text, WHITE);
			}
			void DrawLoadingLine(int x, int y, int w, string text = "", int size = 0) {
				loading_line.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, WHITE);
			}
			void DrawLoadingLineSolid(int x, int y, int w, string text = "", int size = 0) {
				loading_line_solid.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, WHITE);
			}
			void DrawShadowLine(int x1, int y1, int x2, int y2, int r,double dark=0.5) {
				if (!DrawSpecialEffect)return;
				vector2d v = {x2 - x1, y2 - y1};
				v = v.Rotate(3.1415927 / 2.0);
				v = VecUnit(v);
				v *= r / 5.0;
				x1 += (v / 2).x, x2 += (v / 2).x, y1 += (v / 2).y, y2 += (v / 2).y;
				for (int i = 0; i < 5; i++)DrawLineEx({x1 + v.x * i, y1 + v.y * i}, {x2 + v.x * i, y2 + v.y * i}, r / 5.0, Color{0, 0, 0, 100*dark - i * 20*dark});
			}
			void DrawShadowRectangle(int x, int y, int w, int h, int r = 15 * dpi) {
				if (!DrawSpecialEffect)return;
				double r1 = r;
				for (int i = 0; i < 5; i++) {
					DrawRectangleRoundedLines({x, y, w, h}, 1.0 * r1 / min(w, h), 30, r / 5.0, Color{0, 0, 0, 50 - i * 10});
					x -= r / 5.0, y -= r / 5.0, w += r / 2.5, h += r / 2.50;
					r1 += r / 5.0 * 2;
				}
			}
		};
		
		// 实现
		
		class System {
		public:
			vector<Window*> win;
			static bool CMP_Window(Window* w1, Window* w2);
			void Update();
			void Add(Window* w) {
				win.push_back(w);
			}
			void Erase(Window* w) {
				for (auto i : win)if (i == w)win.erase((vector<Window*>::iterator)(&i));
			}
		} MainSystem;
		
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
			ax = max(0.0f, max(x, X));
			ay = max(0.0f, max(y, Y));
			ax2 = min((float)winW, min(x2, X2));
			ay2 = min((float)winH, min(y2, Y2));
			aw = ax2 - ax, ah = ay2 - ay;
			if (aw < 0)aw = 0;
			if (ah < 0)ah = 0;
			ScissorDeep++;
			ScissorPoint[ScissorDeep] = {(float)ax, (float)ay};
			ScissorSize[ScissorDeep] = {(float)aw, (float)ah};
			EndScissorMode();
			BeginScissorMode(ax, ay, aw, ah);
			if(DebugMode) {
				DrawRectangle(ax,ay,aw,ah,Fade(RED,0.02));
				Print(ax,ay,to_string(vector2d{ScissorDeep,0}),BLUE);
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
		void Print(int x, int y, string text, Color color = TextColor2) {
			DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, color);
		}
		int PrintRect(int x, int y, int w, string text, Color color = TextColor2) {
			if(w<ui::TextHeight)return ui::UnitHeight;
			int len=0,last=0,line=0;
			int h = (UnitHeight - TextHeight) / 2;
			for(int i=0;i<text.size();i++) {
				int j=i,temp=0;
				if ((text[i] & 0xE0) == 0xE0)temp=2,len+=2,i += 2;
				else if(text[i]=='\n'&&len*ui::TextHeight/2<=w) {
					Print(x,y+h,text.substr(last,j-last),color);
					y+=ui::UnitHeight;
					len=0;
					line++;
					last=i+1;
				}
				else temp=1,len++;
				if(len*ui::TextHeight/2>w) {
					Print(x,y+h,text.substr(last,j-last),color);
					y+=ui::UnitHeight;
					len=temp;
					if(temp==1)last=i;
					if(temp==2)last=i-2;
					line++;
				}
			}
			if(last!=text.size()) {
				Print(x,y+h,text.substr(last),color);
				line++;
			}
			return line;
		}
		int GetPrintRectLine(int x, int y, int w, string text) {
			if(w<ui::TextHeight)return ui::UnitHeight;
			int len=0,last=0,line=0;
			int h = (UnitHeight - TextHeight) / 2;
			for(int i=0;i<text.size();i++) {
				int j=i,temp=0;
				if ((text[i] & 0xE0) == 0xE0)temp=2,len+=2,i += 2;
				else if(text[i]=='\n'&&len*ui::TextHeight/2<=w) {
					y+=ui::UnitHeight;
					len=0;
					line++;
					last=i+1;
				}
				else temp=1,len++;
				if(len*ui::TextHeight/2>w) {
					y+=ui::UnitHeight;
					len=temp;
					if(temp==1)last=i;
					if(temp==2)last=i-2;
					line++;
				}
			}
			if(last!=text.size()) {
				line++;
			}
			return line;
		}
		void UseIcon(string str, Font* font = &IconFont, int size = ui::TextHeight) {
			if (font == &IconFont)Icons += str, str = Icons;
			unsigned int fileSize;
			unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\segmdl2.ttf", &fileSize);
			int codepointsCount;
			int *codepoints = LoadCodepoints(str.c_str(), &codepointsCount);
			(*font) = LoadFontFromMemory(".ttf", fontFileData, fileSize, size, codepoints, codepointsCount);
			UnloadCodepoints(codepoints);
		}
		void PrintIcon(int x, int y, string text, Color color = ui::TextColor, Font* font = &IconFont, int size = ui::TextHeight) {
			DrawTextEx((*font), text.c_str(), Vector2 {(float)x, (float)y}, size, 0, color);
		}
		bool MouseInRect(real x1, real y1, real w, real h) {
			real x2 = x1 + w, y2 = y1 + h;
			if (Mouse.x >= x1 && Mouse.x < x2 && Mouse.y >= y1 && Mouse.y < y2)return true;
			return false;
		}
		
		// 基类
		class Element {
		public:
			int height = UnitHeight;
			vector<Element*> key;
			Animation prelAniX;
			Animation prelAniY;
			real X, Y, W, H;
			real alpha = 1.0;
			bool extra = false;
			bool init_height = false;
			bool last_draw = false;
			bool CHECK = true;
			Element() {
				prelAniX.sd(600);
				prelAniY.sd(600);
				prelAniX.ssp(-winW);
				prelAniY.ssp(winH);
				prelAniX.sms(anif::bounce);
				prelAniY.sms(anif::bounce);
			}
			virtual int Draw(int x, int y, int w, bool check = true) {
				return 0;
			}
			virtual int Draw(int x, int y, int w, int h, bool check = true) {
				return 0;
			}
			int Draw_Auto(int x, int y, int w, bool check = true) {
				if (!init_height) {
					BeginScissor(0, 0, 0, 0);
					CHECK=check;
					height = Draw(x, y, w, check);
					EndScissor();
					init_height = true;
				}
				if (w < 0)return 1;
				X = x, Y = y, W = w;
				prelAniX.Update();
				prelAniY.Update();
				if (!InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, height + height * 0.4)) {
					if (height < 1)height = 1;
					return height;
				}
				height = Draw(x, y, w, check);
				if (height < 1)height = 1;
				return height;
			}
			int Draw_Auto_Extra(int x, int y, int w, int h, bool check = true) {
				if (w <= 0 || h <= 0)return 0;
				CHECK=check;
				X = x, Y = y, W = w, H = h;
				prelAniX.Update();
				prelAniY.Update();
				if (!InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, h + height * 0.4))return height;
				height = Draw(x, y, w, h, check);
				if (height < 1)height = 1;
				return height;
			}
			void PRelMoveTo(int x, int y) {
				prelAniX.stp(x);
				prelAniY.stp(y);
			}
			Vector2 GetPRel() {
				return Vector2{prelAniX.gnp(), prelAniY.gnp()};
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
				for(int i=0;i<Size();i++) {
					if(key[i]==e)key.erase(key.begin() + i);
				}
			}
			virtual void Swap(int p1, int p2) {
				swap(key[p1], key[p2]);
			}
			virtual void ClearKey() {
				while(Size()) {
					Erase(0);
				}
			}
		};
		double TopPriority = 0;
		double WindowTopPriority = 0;
		class Priority : public Element {
		public:
			double priority;
			string prio_flag = "Window";
		};
		
		// 一下为继承的控件
		class SliderBar : public Element {
		public:
			double sum = 0;
			double now = 0;
			double blank = 0.3;
			int lx=0, ly=0, lw=ui::winW, lh=ui::winH;
			Animation move;
			bool choose = false;
			bool real_mouse_input=true;
			int chooseh = 0;
			map <int, short> mouse_state;
			map <int, int> mouse_down_time;
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
			SliderBar() {
				move.sd(200);
				extra = true;
			}
			int Set(int x) {
				move.stp(x);
			}
			bool Update() {
				if(H>=W) {
					if (CHECK && MouseInRect(lx, ly, lw, lh)&&!UseSliderY)move.stp(move.gtp() - GetMouseWheelMoveV().y * 100);
					if (move.gtp() > sum - H)move.stp(sum - H);
					if (move.gtp() < 0)move.stp(0);
					sum -= H * blank;
					if(CHECK && MouseInRect(lx, ly, lw, lh)&&!UseSliderY&&GetMouseWheelMoveV().y!=0)UseSliderY=true;
				} else {
					if (CHECK && MouseInRect(lx, ly, lw, lh)&&!UseSliderX)move.stp(move.gtp() - GetMouseWheelMoveV().x * 100);
					if (move.gtp() > sum - W)move.stp(sum - W);
					if (move.gtp() < 0)move.stp(0);
					sum -= W * blank;
					if(CHECK && MouseInRect(lx, ly, lw, lh)&&!UseSliderX&&GetMouseWheelMoveV().y!=0)UseSliderX=true;
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if(h>=w)x += SpaceSize, w -= SpaceSize;
				else y += SpaceSize, h -= SpaceSize;
				X = x, Y = y, W = w, H = h,CHECK=check;
				move.update();
				now = move.gnp();
				sum += h * blank;
				if (h >= w) {
					if (h >= sum)return ui::SpaceSize * 4;
					DrawRectangle(x, y, w, h, Color{27, 27, 27, 255});
					DrawLine(x + w / 2, y + w * 3 / 8, x + w / 4, y + w * 5 / 8, WHITE);
					DrawLine(x + w / 2, y + w * 3 / 8, x + w * 3  / 4, y + w * 5 / 8, WHITE);
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w / 4, y + h - w * 5 / 8, WHITE);
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w * 3 / 4, y + h - w * 5 / 8, WHITE);
					double k = 1.0 * now / sum;
					double k2 = 1.0 * h / sum;
					double h2 = 0;
					if (k2 * (h - 2 * w) < w)h2 = (w - k2 * (h - 2 * w)), k2 = 1.0 * w / (h - 2 * w - h2);
					if (choose)DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), Color {158, 158, 157, 255});
					else if (MouseInRect(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2)))
						DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), Color {118, 118, 117, 255});
					else DrawRectangle(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2), Color {72, 72, 73, 255});
					if (MouseInRect(x, y, w, w)) {
						DrawRectangle(x, y, w, w, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT)&&real_mouse_input)move.stp(move.gnp() - 50 * dpi);
					} else if (MouseInRect(x, y + h - w, w, w)) {
						DrawRectangle(x, y + h - w, w, w, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT)&&real_mouse_input)move.stp(move.gnp() + 50 * dpi);
					} else {
						if (check && IsMouseButtonDown(MOUSE_BUTTON_LEFT))real_mouse_input=false;
						else real_mouse_input=true;
					}
					if (MouseInRect(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2)) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = y + w + (Mouse.y - (y + k * (h - w * 2 - h2) + w));
					if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))choose = false;
					if (MouseInRect(x, y + w, w, h - w * 2) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						double k3 = Mouse.y - (y + w);
						k3 /= h - 2 * w;
						move.stp(k3 * sum - h / 2);
					}
					if (choose) {
						double k3 = Mouse.y - chooseh;
						k3 /= h - 2 * w - h2;
						move.stp(k3 * sum);
					}
				} else {
					if (w >= sum)return ui::SpaceSize * 4;
					DrawRectangle(x, y, w, h, Color{27, 27, 27, 255});
					DrawLine(x + h*3 / 8, y + h / 2, x +h*5/8, y + h / 4, WHITE);
					DrawLine(x + h*3 / 8, y + h / 2, x +h*5/8, y + h*3 / 4, WHITE);
					DrawLine(x +w- h*3 / 8, y + h / 2, x +w-h*5/8, y + h / 4, WHITE);
					DrawLine(x +w- h*3 / 8, y + h / 2, x +w-h*5/8, y + h*3 / 4, WHITE);
					double k = 1.0 * now / sum;
					double k2 = 1.0 * w / sum;
					double w2 = 0;
					if (k2 * (w - 2 * h) < h)w2 = (h - k2 * (w - 2 * h)), k2 = 1.0 * h / (w - 2 * h - w2);
					if (choose)DrawRectangle(x + k * (w - h * 2 - w2) + h,y,k2 * (w - 2 * h - w2),h , Color {158, 158, 157, 255});
					else if (MouseInRect(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2),h))
						DrawRectangle(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2),h, Color {118, 118, 117, 255});
					else DrawRectangle(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2),h, Color {72, 72, 73, 255});
					if (MouseInRect(x, y, h, h)) {
						DrawRectangle(x, y, h, h, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT)&&real_mouse_input)move.stp(move.gnp() - 50 * dpi);
					} else if (MouseInRect(x + w - h, y, h, h)) {
						DrawRectangle(x + w - h, y, h, h, ChooseColor);
						if (check && IsMouseInput(MOUSE_BUTTON_LEFT)&&real_mouse_input)move.stp(move.gnp() + 50 * dpi);
					} else {
						if (check && IsMouseButtonDown(MOUSE_BUTTON_LEFT))real_mouse_input=false;
						else real_mouse_input=true;
					}
					if (MouseInRect(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2),h) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = x + h + (Mouse.x - (x + k * (w - h * 2 - w2) + h));
					if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))choose = false;
					if (MouseInRect(x+h, y, w-h*2, h) && check && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						double k3 = Mouse.x - (x + h);
						k3 /= w - 2 * h;
						move.stp(k3 * sum - w / 2);
					}
					if (choose) {
						double k3 = Mouse.x - chooseh;
						k3 /= w - 2 * h - w2;
						move.stp(k3 * sum);
					}
				}
				return ui::SpaceSize * 4;
			}
		};
		class Title : public Element {
		public:
			string text = "Title";
			int Draw(int x, int y, int w = 600, bool check = true) {
				Print(x, y, text);
				return UnitHeight;
			}
		};
		class Head : public Element {
		private:
			Font ofont;
			string last_text = "";
		public:
			string text = "Head";
			void LoadNewFont() {
				unsigned int fileSize;
				unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\simhei.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints(text.c_str(), &codepointsCount);
				ofont = LoadFontFromMemory(".ttf", fontFileData, fileSize, ui::TextHeight * 2, codepoints, codepointsCount);
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				if (text != last_text) {
					LoadNewFont();
					last_text = text;
				}
				DrawTextEx(ofont, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight * 2, 0, TextColor);
				return UnitHeight * 3;
			}
		};
		class Text : public Element {
		public:
			string text = "Text";
			int Draw(int x, int y, int w = 600, bool check = true) {
				height=PrintRect(x, y, w, text)*ui::UnitHeight;
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
			int Draw(int x, int y, int w, bool check = true) {
				DrawPoly(Vector2{x + w / 2, y + w / 2}, 6, w / 2, 0, ftcolor);
				DrawPolyLinesEx(Vector2{x + w / 2, y + w / 2}, 6, w / 5, 0, w / 20.0 * 1.15, bgcolor);
				DrawPoly(Vector2{x + w / 2 + w / 20 * sqrt(3), y + w / 2 - w / 20}, 6, w / 5 - w / 20.0, 0, ftcolor);
				vector2d v = {0, w / 2 - w / 5};
				real pi = 3.14159265359;
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
			string text = "Button";
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
			bool DrawOne(int x, int y, string text, int w = 600, bool check = true) {
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
			string text1 = "Button1";
			string text2 = "Button2";
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
			bool DrawOne(int x, int y, string text, int w = 600, bool check = true) {
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
			string text1 = "Button1";
			string text2 = "Button2";
			string text3 = "Button3";
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
			string last_icon = "";
		public:
			bool click = false;
			bool draw_background=true;
			Color color=Color{47,47,47,255};
			string icon = "";
			string text = "";
			int GetWidth() {
				int t=(ui::UnitHeight*1.5-ui::TextHeight)/2;
				int w=t;
				if(icon!="")w+=strLen(icon)*ui::TextHeight/2+t;
				if(text!="")w+=strLen(text)*ui::TextHeight/2+t;
				return w;
			}
			int Draw(int x, int y, int w, bool check = true) {
				click=false;
				int h=ui::UnitHeight*1.5;
				int t=(ui::UnitHeight*1.5-ui::TextHeight)/2;
				if(draw_background) {
					w=t;
					y+=ui::SpaceSize/2;
					if(icon!="")w+=strLen(icon)*ui::TextHeight/2+t;
					if(text!="")w+=strLen(text)*ui::TextHeight/2+t;
					DrawRectangle(x,y,w,h,color);
				}
				w=t;
				PrintIcon(x+w,y+t,icon);
				if(icon!="")w+=strLen(icon)*ui::TextHeight/2+t;
				Print(x+w,y+t,text);
				if(text!="")w+=strLen(text)*ui::TextHeight/2+t;
				special_effect::DrawMouseRectangle(x, y, w, h);
				if (ui::MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ui::ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check)click = true;
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, h, ui::ChooseColor);
				}
				if(draw_background)h+=ui::SpaceSize;
				return h;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				click=false;
				int t=(ui::UnitHeight*1.5-ui::TextHeight)/2;
				int w2=t,w3;
				if(icon!="")w2+=strLen(icon)*ui::TextHeight/2+t;
				if(text!="")w2+=strLen(text)*ui::TextHeight/2+t;
				if(draw_background)DrawRectangle(x,y,w,h,color);
				w3=t;
				PrintIcon(x+w/2-w2/2+w3,y+h/2-ui::TextHeight/2,icon);
				if(icon!="")w3+=strLen(icon)*ui::TextHeight/2+t;
				Print(x+w/2-w2/2+w3,y+h/2-ui::TextHeight/2,text);
				if(text!="")w3+=strLen(text)*ui::TextHeight/2+t;
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
			string text="[注意]";
			int Draw(int x,int y,int w,bool check=true) {
				int h = (ui::UnitHeight - ui::TextHeight) / 2;
				height=ui::GetPrintRectLine(x+ui::SpaceSize+ui::UnitHeight,y+ui::SpaceSize*3/2,w-ui::SpaceSize*2-ui::UnitHeight,text)*ui::UnitHeight;
				DrawRectangle(x,y+ui::SpaceSize/2,w,height+ui::SpaceSize*2,Color{255,153,0,100});
				ui::PrintIcon(x+ui::SpaceSize,y+ui::SpaceSize*3/2+height/2-ui::TextHeight/2,"");
				ui::PrintRect(x+ui::SpaceSize+ui::UnitHeight,y+ui::SpaceSize*3/2,w-ui::SpaceSize*2-ui::UnitHeight,text);
				height+=ui::SpaceSize*3;
				return height+ui::SpaceSize;
			}
		};
		class Error : public ui::Element {
		public:
			string text="[警告]";
			int Draw(int x,int y,int w,bool check=true) {
				int h = (ui::UnitHeight - ui::TextHeight) / 2;
				height=ui::GetPrintRectLine(x+ui::SpaceSize+ui::UnitHeight,y+ui::SpaceSize*3/2,w-ui::SpaceSize*2-ui::UnitHeight,text)*ui::UnitHeight;
				DrawRectangle(x,y+ui::SpaceSize/2,w,height+ui::SpaceSize*2,Color{192,44,56,100});
				ui::PrintIcon(x+ui::SpaceSize,y+ui::SpaceSize*3/2+height/2-ui::TextHeight/2,"");
				ui::PrintRect(x+ui::SpaceSize+ui::UnitHeight,y+ui::SpaceSize*3/2,w-ui::SpaceSize*2-ui::UnitHeight,text);
				height+=ui::SpaceSize*3;
				return height+ui::SpaceSize;
			}
		};
		class Slider : public Element {
		public:
			Animation move;
			real num = 0;
			real minn = 0;
			real maxn = 10;
			bool text_visible = true;
			string text = "Slider";
			void Set(real x) {
				num = x;
			}
			virtual int Draw(int x, int y, int w = 400, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				int nw = UnitHeight * 1.7;
				real h2 = UnitHeight / 6;
				if(text_visible)cw=w*0.6;
				else cw=w;
				move.sd(200);
				move.Update();
				move.stp((cw - UnitHeight / 5)*(num-minn) / (maxn - minn));
				real k = move.gnp();
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, GRAY);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, MainColor);
				DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, MainColor);
				if(text_visible) {
					Print(x + cw + SpaceSize, y + h, text, TextColor);
					DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, TextColor2);
					std::ostringstream out;
					out << num;
					string t = out.str();
					if (t.size() > 4)t.resize(4);
					Print(x + w - nw + h, y + h, t, MainColor);
				}
				if (MouseInRect(x, y + h / 2, cw, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseSlider = this;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (ChooseSlider == this&&check) {
					real kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5)+minn;
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
			string text = "Slider";
			void Set(int x) {
				num = x;
			}
			int Draw(int x, int y, int w = 400, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				int nw = UnitHeight * 1.7;
				real h2 = UnitHeight / 6;
				move.sd(200);
				move.Update();
				move.stp((cw - UnitHeight / 5)*num / (maxn - minn));
				real k = move.gnp();
				Print(x + cw + SpaceSize, y + h, text, TextColor);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, GRAY);
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, MainColor);
				DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, MainColor);
				DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, TextColor2);
				std::ostringstream out;
				out << num;
				string t = out.str();
				t = t.substr(0, 5);
				Print(x + w - nw + h, y + h, t, MainColor);
				if (MouseInRect(x, y + h / 2, cw, UnitHeight - h) && check) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseSlider = this;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, WHITE);
				}
				if (ChooseSlider == this) {
					real kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5);
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
			string text = "Switch";
			bool on = false;
			int Draw(int x, int y, int w = 600, bool check = true) {
				move.sd(300);
				move.sms(anif::bounce4);
				int h = (UnitHeight - TextHeight) / 2;
				int nw = UnitHeight * 1.7;
				real h2 = UnitHeight / 4;
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
			string text = "Choose";
			vector<string> key;
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
				if(choose!=-1)Print(x + SpaceSize, y + h, key[choose], TextColor);
				vector2d k1 = vector2d {-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8};
				vector2d k2 = vector2d {TextHeight / 4 * 0.8, 0};
				vector2d k3 = vector2d {-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8};
				vector2d p1 = k1.Rotate(angle.gnp());
				vector2d p2 = k2.Rotate(angle.gnp());
				vector2d p3 = k3.Rotate(angle.gnp());
				real TempX = x + cw - UnitHeight / 2.0;
				real TempY = y + UnitHeight / 2.0;
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
			bool swapping=false;
		public:
			string text = "Dropdown";
			bool open = false;
			bool deep = 0;
			bool draw_background = true;
			bool draw_menu_background = false;
			bool insert_ani=false;
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
			static real MoveAni(real x) {
				real h = TempHeight - UnitHeight * 5;
				if (h > 0) {
					if (x > -7.68721)return anif::bounceFun(x);
					real c = TempHeight / UnitHeight / 5.0 * anif::bounceFun(-7.68721);
					real c1 = h / UnitHeight / 5.0 * anif::bounceFun(-7.68721);
					return c + (x + 7.68721) * (h / 3.0);
				} else {
					return anif::bounceFun(x * 7.68721 / 8.9726);
				}
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				Height = 0;
				X=x,Y=y,W=w;
				swapping=false;
				for (int i = 0; i < key.size(); i++)
					Height += key[i]->height;
				TempHeight = Height;
				angle.Update();
				move.Update();
				int h = (UnitHeight - TextHeight) / 2;
				if(draw_menu_background)DrawRectangle(x,y+UnitHeight-h,w,move.gnp(),Color{20,20,20,150});
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
					real nowh = move.gnp() - Height;
					real nowh2 = 0;
//					for (int i = 0; i < key.size(); i++)
//						nowh += key[i]->Draw_Auto(x + UnitHeight, y + UnitHeight + nowh, w - UnitHeight - h * 3, check);
					for (int i = 0; i < key.size(); i++) {
						Vector2 ve = key[i]->GetPRel();
						if (insert_ani) {
							key[i]->prelAniX.stp(0, 300);
							key[i]->prelAniY.stp(nowh2, 0);
						} else {
							key[i]->prelAniX.ssp(0);
							key[i]->prelAniY.ssp(nowh2);
						}
						nowh2 += key[i]->Draw_Auto(x + ve.x+UnitHeight, y + ve.y+UnitHeight+nowh, w - UnitHeight - h * 3, check && !swapping);
					}
				}
				EndScissor();
				height = move.gnp() + UnitHeight;
				return height;
			}
			void Add(Element* a) {
				key.push_back(a);
				a->prelAniX.ssp(0);
				a->prelAniY.ssp(Height);
			}
			void Insert(int position, Element* a) {
				key.insert(key.begin() + position, a);
				a->prelAniX.ssp(-W);
				if (position != 0)a->prelAniY.ssp(key[position - 1]->GetPRel().y + key[position - 1]->height);
				else a->prelAniY.ssp(0);
			}
			void Swap(int a, int b) {
				swap(key[a], key[b]);
				swapping = true;
			}
		};
		
		vector2d _v(Vector2 v) {
			return vector2d {v.x, v.y};
		}
		Vector2 _V(vector2d v) {
			return Vector2 {v.x, v.y};
		}
		vector3d _v(Vector3 v) {
			return vector3d {v.x, v.y,v.z};
		}
		Vector3 _V(vector3d v) {
			return Vector3 {v.x, v.y,v.z};
		}
		vector2d _polar(vector2d v) {
			return vector2d{v.x*cos(v.y),v.x*sin(v.y)};
		}
		class GraphDebugger : public Element {
		public:
			vector2d camera = {0, 0};
			bool choose = false;
			bool mouse_move = false;
			bool movable=true;
			real leftx, rightx, zoom = 100;
			vector2d choose_pos;
			Animation zoom_ani;
			Animation ilenAni,idegAni;
			Animation jlenAni,jdegAni;
			Slider zoom_slider;
			map <vector2d*,pair<Animation,Animation> > v2ani;
			map <vector2d*,bool> v2state;
			void (*draw_fun)(GraphDebugger*) = nullptr;
			
			bool mesh_visible = true;
			bool axis_visible = true;
			bool zoom_visible = true;
			bool polar_visible = false;
			
			GraphDebugger() {
				zoom_ani.sd(300);
				zoom_ani.ssp(2);
				ilenAni.sd(1000),ilenAni.ssp(1);
				idegAni.sd(1000),idegAni.ssp(0);
				jlenAni.sd(1000),jlenAni.ssp(1);
				jdegAni.sd(1000),jdegAni.ssp(3.1415926535897932/2);
				ilenAni.sms(anif::tanh);
				jlenAni.sms(anif::tanh);
				idegAni.sms(anif::tanh);
				jdegAni.sms(anif::tanh);
				extra = true;
				zoom_slider.text_visible = false;
				zoom_slider.minn=-3;
				zoom_slider.maxn=7;
			}
			string ts(real a) {
				std::ostringstream out;
				out << a;
				return out.str();
			}
			vector2d W2S(vector2d w) {
				w -= camera;
				w *= zoom;
				w.x += W / 2;
				w.y = -w.y;
				w.y += H / 2;
				return w;
			}
			vector2d S2W(vector2d s) {
				s.x -= W / 2;
				s.y -= H / 2;
				s.y = -s.y;
				s /= zoom;
				s += camera;
				return s;
			}
			vector2d GetMouse() {
				if(!CHECK)return {0,0};
				return S2W(vector2d{Mouse.x-X,Mouse.y-Y});
			}
			bool MousePressed(MouseButton mb) {
				return IsMouseButtonPressed(mb)&&!mouse_move&&CHECK&&MouseInRect(X,Y,W,H);
			}
			
			void DrawMesh_(real sspace, Color color, bool num = false) {
				vector2d O = W2S({0, 0});
				real x = X, y = Y, w = W, h = H;
				zoom = pow(10,zoom_ani.gnp());
				real startx = -ceil(1.0 * (O.x) / sspace) * sspace + O.x + x;
				real starty = -ceil(1.0 * (O.y) / sspace) * sspace + O.y + y;
				for (real i = startx; i <= x + w; i += sspace)DrawLine(i, y, i, y + h, color);
				for (real i = starty; i <= y + h; i += sspace)DrawLine(x, i, x + w, i, color);
				if (num) {
					if (sspace <= 70 * dpi)sspace = sspace * 5;
					for (real i = max((real)O.x, O.x + int((x - O.x) / sspace) * sspace); i <= w; i += sspace) {
						real k = S2W({i, 0}).x;
						string s = ts(k);
						if (i == O.x)s = "[0]";
						Print(i + x, y, s.c_str());
					}
					for (real i = min((real)(O.x - sspace), O.x + int((x + W - O.x) / sspace) * sspace); i >= 0; i -= sspace) {
						real k = S2W({i, 0}).x;
						string s = ts(k);
						Print(i + x, y, s.c_str());
					}
					for (real i = max((real)O.y, O.y + int((y - O.y) / sspace) * sspace); i <= H; i += sspace) {
						real k = S2W({0, i}).y;
						string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str());
					}
					for (real i = min((real)(O.y - sspace), O.y + int((y + W - O.y) / sspace) * sspace); i >= 0; i -= sspace) {
						real k = S2W({0, i}).y;
						string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str());
					}
				}
			}
			bool in_sight(real x,real y) {
				vector2d a = W2S({x, y});
				if(a.x>=0&&a.x<=W&&a.y>=0&&a.y<=H)return true;
				return false;
			}
			bool in_sight(vector2d v) {
				vector2d a = W2S(v);
				if(a.x>=0&&a.x<=W&&a.y>=0&&a.y<=H)return true;
				return false;
			}
			void draw_text(real x, real y, string text, Color color = GREEN) {
				if(!in_sight(x,y))return;
				vector2d a = W2S({x, y});
				Print(a.x+X-strLen(text)*ui::TextHeight/4,a.y+Y-ui::TextHeight/2,text,color);
			}
			void draw_text(vector2d pos, string text, Color color = GREEN) {
				draw_text(pos.x,pos.y,text,color);
			}
			void draw_point(real x, real y, Color color = GREEN) {
				if(!in_sight(x,y))return;
				vector2d a = W2S({x, y});
				DrawCircle(a.x+X,a.y+Y,2.5*dpi,color);
			}
			void draw_point(vector2d v, Color color = GREEN) {
				draw_point(v.x,v.y,color);
			}
			bool choose_point=false;
			bool float_point=false;
			void draw_point_controlled(vector2d* v, Color color = GREEN) {
				if(!in_sight(*v)&&!v2state[v])return;
				else {
					vector2d m = _v(Mouse)-vector2d{X,Y};
					vector2d a = W2S({v->x, v->y});
					DrawCircle(a.x+X,a.y+Y,8*dpi,Color{100+color.r/2,100+color.g/2,100+color.b/2,50});
					draw_point(v->x,v->y,color);
					if(Mod2(m-a)<64*dpi*dpi||v2state[v]) {
						if(CHECK) {
							if(!float_point)DrawCircleLines(a.x+X,a.y+Y,8*dpi,color);
							MouseCursorStyle=MOUSE_CURSOR_POINTING_HAND;
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!choose_point&&ChooseSlider==NULL) {
								if(!float_point)v2state[v]=true;
								choose_point=true;
							}
							float_point=true;
						}
					}
					if(v2state[v]&&ChooseSlider==NULL) {
						(*v)=S2W(m);
						choose=false;
					}
					if(v2state[v]&&ChooseSlider==NULL) {
						(*v)=S2W(m);
						MouseCursorStyle=MOUSE_CURSOR_POINTING_HAND;
						choose=false;
					}
					if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
						for(auto i=v2state.begin();i!=v2state.end();i++)i->second=false;
						choose_point=false;
					}
				}
			}
			void draw_line(real x1, real y1, real x2, real y2, Color color = GREEN) {
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
			}
			void draw_line(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_line(v1.x,v1.y,v2.x,v2.y,color);
			}
			void draw_rectangle_lines(real x1, real y1, real x2, real y2, Color color = GREEN) {
				if (x1 > x2)swap(x1, x2);
				if (y1 < y2)swap(y1, y2);
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangleLines(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color);
			}
			void draw_rectangle(real x1, real y1, real x2, real y2, Color color = GREEN) {
				if (x1 > x2)swap(x1, x2);
				if (y1 < y2)swap(y1, y2);
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				Color color2 = color;
				color2.a *= 0.2;
				DrawRectangle(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color2);
				DrawRectangleLines(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color);
			}
			void draw_rectangle_solid(real x1, real y1, real x2, real y2, Color color = GREEN) {
				if (x1 > x2)swap(x1, x2);
				if (y1 < y2)swap(y1, y2);
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangle(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, color);
			}
			void draw_circle(real x1, real y1, real r, Color color = GREEN) {
				vector2d a = W2S({x1, y1});
				Color color2 = color;
				color2.a *= 0.2;
//					DrawCircle(a.x + X, a.y + Y, r * zoom, color2);
//					DrawCircleLines(a.x + X, a.y + Y, r * zoom, color);
//					DrawCircleSectorLines({a.x + X, a.y + Y}, r*zoom, 0, 360, 0, color);
				DrawCircleSector({a.x + X, a.y + Y}, r*zoom, 0, 360, 0, color2);
				DrawRingLines({a.x + X, a.y + Y}, r*zoom, r*zoom, 0, 360, 0, color);
			}
			void draw_circle(vector2d v, real r, Color color = GREEN) {
				draw_circle(v.x,v.y,r,color);
			}
			void draw_vector(real x1, real y1, real x2, real y2, Color color = GREEN) {
				x2 += x1, y2 += y1;
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.5);
				vector2d v2 = (b - a).Rotate(-2.5);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
				if(Mod(a-b)>30*ui::dpi) {
					v1 = VecUnit(v1) * 10 * ui::dpi;
					v2 = VecUnit(v2) * 10 * ui::dpi;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, color);
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, color);
				}
				else {
					v1 = VecUnit(v1) * Mod(a-b)/3.0;
					v2 = VecUnit(v2) * Mod(a-b)/3.0;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, color);
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, color);
				}
			}
			void draw_vector_head(real x1, real y1, real x2, real y2, Color color = GREEN) {
				x2 += x1, y2 += y1;
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.75);
				vector2d v2 = (b - a).Rotate(-2.75);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, color);
				vector2d t=vector2d{X,Y};
				if(Mod(a-b)>37.5*ui::dpi) {
					v1 = VecUnit(v1) * 12.5 * ui::dpi;
					v2 = VecUnit(v2) * 12.5 * ui::dpi;
					DrawTriangle(_V(b+t),_V(b+v2+t),_V(b+v1+t),color);
				}
				else {
					v1 = VecUnit(v1) * Mod(a-b)/3.0;
					v2 = VecUnit(v2) * Mod(a-b)/3.0;
					DrawTriangle(_V(b+t),_V(b+v2+t),_V(b+v1+t),color);
				}
			}
			void draw_vector(real x, real y,Color color = GREEN) {
				draw_vector(0,0,x,y,color);
			}
			void draw_vector(vector2d v,Color color = GREEN) {
				draw_vector(0,0,v.x,v.y,color);
			}
			void draw_vector(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_vector(v1.x,v1.y,v2.x,v2.y,color);
			}
			void draw_vector_head(vector2d v1, vector2d v2, Color color = GREEN) {
				draw_vector_head(v1.x,v1.y,v2.x,v2.y,color);
			}
			void draw_vector_withAni(vector2d v1,vector2d* v2,Color color = GREEN) {
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.stp(v2->x);
				v2ani[v2].second.stp(v2->y);
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.sms(anif::tanh);
				v2ani[v2].second.sms(anif::tanh);
				draw_vector(0,0,v2ani[v2].first.gnp(),v2ani[v2].second.gnp(),color);
			}
			void draw_vector_withAni(vector2d* v2,Color color = GREEN) {
				draw_vector_withAni({0,0},v2,color);
			}
			void draw_bezier2(vector2d v1,vector2d v2,vector2d v3,Color color=GREEN) {
				vector2d l=v1;
				for(real t=0.02;t<=1.01;t+=0.02) {
					vector2d p1=(v2-v1)*t+v1;
					vector2d p2=(v3-v2)*t+v2;
					vector2d p3=(p2-p1)*t+p1;
					draw_line(l,p3,color);
					l=p3;
				}
			}
			void draw_bezier3(vector2d v1,vector2d v2,vector2d v3,vector2d v4,Color color=GREEN) {
				vector2d l=v1;
				for(real t=0.02;t<=1.01;t+=0.02) {
					vector2d p=v1*(-t*t*t+3*t*t-3*t+1)+v2*(3*t*t*t-6*t*t+3*t)+v3*(-3*t*t*t+3*t*t)+v4*(t*t*t);
					draw_line(l,p,color);
					l=p;
				}
			}
			void draw_bezier3_mesh(vector2d v1,vector2d v2,vector2d v3,vector2d v4,real radius=1,Color color=GREEN) {
				vector2d l=v1,l1=v1,l2=v1;
				Color c1,c2;
				c1=c2=color;
				c1.a*=0.3;
				c2.a*=0.6;
				for(real t=0,i=0;t<=1.01;t+=0.02,i++) {
					vector2d p=v1*(-t*t*t+3*t*t-3*t+1)+v2*(3*t*t*t-6*t*t+3*t)+v3*(-3*t*t*t+3*t*t)+v4*(t*t*t);
					vector2d dp=v1*(-3*t*t+6*t-3)+v2*(9*t*t-12*t+3)+v3*(-9*t*t+6*t)+v4*(3*t*t);
					vector2d temp=dp.Rotate(G_PI/2);
					temp=VecUnit(temp);
					draw_line(l,p,color);
					draw_line(l1,p+temp*radius,c2);
					draw_line(l2,p-temp*radius,c2);
					if(int(i)%5==0) {
						draw_line(p,p+temp*radius,c1);
						draw_line(p,p-temp*radius,c1);
					}
					l=p;
					l1=p+temp*radius;
					l2=p-temp*radius;
				}
			}
			void draw_function(real (*fun)(real),Color color=GREEN) {
				for(real i=leftx;i<=rightx;i+=1.0/zoom)draw_line(i,fun(i),i+1.0/zoom,fun(i+1.0/zoom),color);
			}
			void draw_function_polar(real (*fun)(real),real start=0,real end=PI*2,int prec=100,Color color=GREEN) {
				for(int i=0;i<prec;i++) {
					real t1=start+1.0*i*(end-start)/prec;
					real t2=start+1.0*(i+1)*(end-start)/prec;
					vector2d k1=_polar({fun(t1),t1});
					vector2d k2=_polar({fun(t2),t2});
					draw_line(k1.x,k1.y,k2.x,k2.y,color);
				}
			}
			void draw_function(vector2d (*fun)(real),real start=0,real end=10,int prec=5,Color color=GREEN) {
				for(real i=start;i<end;i+=1.0/prec)draw_line(fun(i).x,fun(i).y,fun(i+1.0/prec).x,fun(i+1.0/prec).y,color);
			}
			void draw_mesh(vector2d (*mesh)(real,real),real sx,real ex,real sy,real ey,real space=1.0,int prec=5,Color color=GREEN) {
				for(real i=sx;i<=ex;i+=space) {
					for(real j=sy;j<ey;j+=space/prec) {
						draw_line(mesh(i,j),mesh(i,j+space/prec),color);
					}
				}
				for(real j=sy;j<=ey;j+=space) {
					for(real i=sx;i<ex;i+=space/prec) {
						draw_line(mesh(i,j),mesh(i+space/prec,j),color);
					}
				}
			}
			void draw_liner_transformation(real m11,real m12,real m21,real m22,real r=10,real space=1.0,Color color=GREEN) {
				real r2=ceil(r/space)*space;
				for(real i=-r2;i<=r2;i+=space) {
					draw_line(m11*i+m12*(-r),m21*i+m22*(-r),m11*i+m12*r,m21*i+m22*r,color);
					draw_line(m11*(-r)+m12*i,m21*(-r)+m22*i,m11*r+m12*i,m21*r+m22*i,color);
				}
			}
			void draw_liner_transformation_withAni(real m11,real m12,real m21,real m22,real r=10,real space=1.0,Color color=GREEN) {
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				ilenAni.stp(sqrt(m11*m11+m21*m21));
				jlenAni.stp(sqrt(m12*m12+m22*m22));
				if(abs(atan2(m21,m11)-idegAni.gnp())>abs(atan2(m21,m11)-idegAni.gnp()+3.1415926535897932*2))idegAni.stp(atan2(m21,m11)+3.1415926535897932*2);
				else if(abs(atan2(m21,m11)-idegAni.gnp())>abs(atan2(m21,m11)-idegAni.gnp()-3.1415926535897932*2))idegAni.stp(atan2(m21,m11)-3.1415926535897932*2);
				else idegAni.stp(atan2(m21,m11));
				if(abs(atan2(m22,m12)-jdegAni.gnp())>abs(atan2(m22,m12)-jdegAni.gnp()+3.1415926535897932*2))jdegAni.stp(atan2(m22,m12)+3.1415926535897932*2);
				else if(abs(atan2(m22,m12)-jdegAni.gnp())>abs(atan2(m22,m12)-jdegAni.gnp()-3.1415926535897932*2))jdegAni.stp(atan2(m22,m12)-3.1415926535897932*2);
				else jdegAni.stp(atan2(m22,m12));
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				real il=ilenAni.gnp(),jl=jlenAni.gnp();
				real id=idegAni.gnp(),jd=jdegAni.gnp();
				real ix=il*cos(id),iy=il*sin(id);
				real jx=jl*cos(jd),jy=jl*sin(jd);
				draw_liner_transformation(ix,jx,iy,jy,r,space,color);
				draw_vector(ix,iy,RED);
				draw_vector(jx,jy,BLUE);
			}
			// vector<vector<real> > LastMeshPosX,LastMeshPosY;
			// void draw_mesh_withAni(vector2d (*mesh)(real,real),real sx,real ex,real sy,real ey,real space=1.0,int prec=5,Color color=GREEN) {
			// 	if((ex-sx)*prec/space+10>1000||(ex-sx)*prec/space+10>1000) {
			// 		draw_mesh(vector2d (*mesh)(real,real),real sx,real ex,real sy,real ey,real space=1.0,int prec=5,Color color=GREEN);
			// 		return;
			// 	}
			// 	if(LastMeshPosX.size()!=(ex-sx)*prec/space+10)LastMeshPosX.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosY.size()!=(ey-sy)*prec/space+10)LastMeshPosY.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosY.size()!=(ex-sx)/space+10)for(int i=0;i<LastMeshPosY.size();i++)LastMeshPosY.resize((ex-sx)*prec/space+10);
			// 	if(LastMeshPosX.size()!=(ey-sy)/space+10)for(int i=0;i<LastMeshPosX.size();i++)LastMeshPosX.resize((ex-sx)*prec/space+10);
			// 	for(real i=sx;i<=ex;i+=space) {
			// 		for(real j=sy;j<ey;j+=space/prec) {
			// 			draw_line(mesh(i,j),mesh(i,j+space/prec),color);
			// 		}
			// 	}
			// 	for(real j=sy;j<=ey;j+=space) {
			// 		for(real i=sx;i<ex;i+=space/prec) {
			// 			draw_line(mesh(i,j),mesh(i+space/prec,j),color);
			// 		}
			// 	}
			// }
			int Draw(int x, int y, int w, int h, bool check = true) {
				X = x, Y = y, W = w, H = h, CHECK = check;
				BeginScissor(x, y, w, h);
				zoom_ani.Update();
				zoom = pow(10,zoom_ani.gnp());
				leftx = S2W({0, 0}).x, rightx = S2W({w, 0}).x;
				DrawRectangle(x, y, w, h, Color{32, 32, 32, 255});
				real wspace = pow(10, ceil(log10(30 * dpi / zoom)));
				real sspace = wspace * zoom;
				float_point=false;
				
				if(movable) {
					if(MouseInRect(x,y,w,h))UseSliderX=UseSliderY=true;
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check && !ChooseSlider!=NULL)if (MouseInRect(x, y, w, h))
						choose = true, mouse_move=false, choose_pos = S2W(_v(Mouse) - vector2d{x, y});
					if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && check)choose = false;
					if (choose && !ChooseSlider!=NULL && check) {
						vector2d move = S2W(_v(Mouse) - vector2d{x, y}) - choose_pos;
						if(move!=0)mouse_move=true;
						camera -= move;
					}
				}
//				if (IsKeyInput(KEY_UP))zoom_ani.stp(zoom_ani.gnp()*1.1111111111);
//				if (IsKeyInput(KEY_DOWN))zoom_ani.stp(zoom_ani.gnp()*0.9);
				
				vector2d O = W2S({0, 0});
				
				if(mesh_visible) {
					if (sspace / 10.0 > 10 * dpi) {
						real a = (sspace / 10 - 10 * dpi) / (20.0 * dpi);
						DrawMesh_(sspace / 10, Color{60, 60, 60, a * 255});
						DrawMesh_(sspace, Color{60 + 60 * a, 60 + 60 * a, 60 + 60 * a, 255}, true);
						DrawMesh_(sspace * 10, Color{120 + 60 * a, 120 + 60 * a, 120 + 60 * a, 255});
					} else {
						DrawMesh_(sspace, Color{60, 60, 60, 255}, true);
						DrawMesh_(sspace * 10, Color{120, 120, 120, 255});
					}
				}
				if(polar_visible) {
				}
				if(axis_visible) {
					DrawRectangle(x + O.x - 3 * dpi, y + O.y - 3 * dpi, 6 * dpi, 6 * dpi, LIGHTGRAY);
					DrawLine(x, y + O.y, x + w, y + O.y, LIGHTGRAY);
					DrawLine(x + O.x, y, x + O.x, y + h, LIGHTGRAY);
				}
				zoom_ani.update();
				if(ChooseSlider==NULL)zoom_slider.num=zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (draw_fun != nullptr) {
					BeginScissor(X,Y,W,H);
					draw_fun(this);
					EndScissor();
				}
				if(zoom_visible) {
					int tw=min(int(300*dpi),w-ui::SpaceSize*4);
					DrawRectangleRounded({x+w/2-tw/2,y+h-UnitHeight-SpaceSize*1.5,tw,UnitHeight+SpaceSize},1,10,Color{50,50,70,150});
					zoom_slider.Draw(x+w/2-(tw-80)/2,y+h-UnitHeight-SpaceSize,(tw-80));
				}
				zoom_ani.update();
				if(ChooseSlider==NULL)zoom_slider.num=zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (MouseInRect(x, y, w, h) && check) {
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)&&choose && !ChooseSlider!=NULL) {
						MouseCursorStyle = -1;
						DrawCircle(Mouse.x,Mouse.y,7*dpi,Color{255,255,255,100});
					}
					zoom_ani.stp(zoom_ani.gtp() + GetMouseWheelMove() / 10.0);
					if (zoom_ani.gtp() < -3)zoom_ani.stp(-3);
					if (zoom_ani.gtp() > 7)zoom_ani.stp(7);
					zoom_ani.update();
				}
				EndScissor();
				return h;
			}
			int Draw(int x,int y,int w,bool check=true) {
				x+=dpi,y+=dpi,w-=dpi*2;
				Draw(x,y,w,w*0.8,check);
				special_effect::DrawMouseBox(x,y,w,w*0.8);
				return w*0.8+dpi*2;
			}
		};
		class GraphDebugger3D : public Element {
		private:
			real f(real a) {return a-floor(a);}
			real window_scale=1;
			
		public:
			Camera3D camera = { 0 };
			void (*draw_fun)(GraphDebugger3D*) = nullptr;
			
			bool axis_visible = true;
			bool zoom_visible = true;
			bool mesh_visible = true;
			bool movable = true;
			
			GraphDebugger3D() {
				extra=true;
				// 初始化摄像机
				camera.position = (Vector3){ 2.0f, 2.0f, 2.0f }; //相机所在位置{x,y,z}
				camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; //相机朝向位置{x,y,z}
				camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; //相机正上方朝向矢量
				camera.fovy = 70;
				camera.projection = CAMERA_PERSPECTIVE;
			}
			void draw_point(vector3d pos,Color color=GREEN) {
				real dist=Mod(_v(camera.position)-pos);
				DrawSphere(_V(pos),0.007*dist*1000.0/(window_scale*winH),color);
			} 
			void draw_vector_rotate(vector3d start, vector3d v,Color color=GREEN) {
				DrawLine3D(_V(start),_V(v+start),color);
				vector3d v2=Cross(v,{0,0,1});
				if(v2==vector3d{0,0,0})v2=Cross(v,{0,1,0});
				vector3d v31=VecUnit(v.Rotate(v2,PI/8)*(-1));
				vector3d v32=VecUnit(v.Rotate(v2,-PI/8)*(-1));
				v31=v31.Rotate(v,clock()/200.0);
				v32=v32.Rotate(v,clock()/200.0);
				vector3d v41=v+v31*Mod(v)/10;
				vector3d v42=v+v32*Mod(v)/10;
				DrawLine3D(_V(v+start),_V(v41+start),color);
				DrawLine3D(_V(v+start),_V(v42+start),color);
			}
			void draw_line(vector3d v1,vector3d v2,Color color=GREEN) {
				DrawLine3D(_V(v1),_V(v2),color);
			}
			void draw_cube(vector3d pos,real w=1,real h=1,real l=1,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.2+BgColor.r*0.8;
				color2.g=color.g*0.2+BgColor.g*0.8;
				color2.b=color.b*0.2+BgColor.b*0.8;
				DrawCube(_V(pos),w,h,l,color2);
				DrawCubeWires(_V(pos),w,h,l,color);
			}
			void draw_sphere(vector3d pos,real r=0.5,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.2+BgColor.r*0.8;
				color2.g=color.g*0.2+BgColor.g*0.8;
				color2.b=color.b*0.2+BgColor.b*0.8;
				DrawSphere(_V(pos),r,color2);
				DrawCircle3D(_V(pos),r*1.002,{0,0,1},0,color);
				DrawCircle3D(_V(pos),r*1.002,{0,1,0},90,color);
				DrawCircle3D(_V(pos),r*1.002,{1,0,0},90,color);
			}
			void draw_cylinder(vector3d v1,real r=0.5,real r2=0.5,real h=1,int slices=3,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.2+BgColor.r*0.8;
				color2.g=color.g*0.2+BgColor.g*0.8;
				color2.b=color.b*0.2+BgColor.b*0.8;
				DrawCylinder(_V(v1),r,r2,h,slices,color2);
				DrawCylinderWires(_V(v1),r,r2,h,slices,color);
			}
			void draw_cylinder(vector3d v1,vector3d v2,real r=0.5,real r2=0.5,int slices=3,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.2+BgColor.r*0.8;
				color2.g=color.g*0.2+BgColor.g*0.8;
				color2.b=color.b*0.2+BgColor.b*0.8;
				DrawCylinderEx(_V(v1),_V(v2),r,r2,slices,color2);
				DrawCylinderWiresEx(_V(v1),_V(v2),r,r2,slices,color);
			}
			void draw_vector(vector3d start, vector3d v,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.5+BgColor.r*0.5;
				color2.g=color.g*0.5+BgColor.g*0.5;
				color2.b=color.b*0.5+BgColor.b*0.5;
				DrawLine3D(_V(start),_V(v+start),color);
				DrawCylinderEx(_V(start+v*0.9),_V(start+v),Mod(v*0.02),0,10,color2);
			}
			void draw_vector(vector3d v,Color color=GREEN) {
				draw_vector({0,0,0},v,color);
			}
			void draw_vector(real x,real y,real z,Color color=GREEN) {
				draw_vector({0,0,0},{x,y,z},color);
			}
			void draw_capsule(vector3d v1,vector3d v2,real r,Color color=GREEN) {
				Color color2 = color;
				color2.r=color.r*0.5+BgColor.r*0.5;
				color2.g=color.g*0.5+BgColor.g*0.5;
				color2.b=color.b*0.5+BgColor.b*0.5;
				DrawCapsule(_V(v1),_V(v2),r,15,10,color2);
				DrawCapsuleWires(_V(v1),_V(v2),r,3,10,color);
			}
			void draw_bezier2(vector3d v1,vector3d v2,vector3d v3,Color color=GREEN) {
				vector3d l=v1;
				draw_line(v1,v2,GRAY);
				draw_line(v2,v3,GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				for(real t=0.02;t<=1.01;t+=0.02) {
					vector3d p1=(v2-v1)*t+v1;
					vector3d p2=(v3-v2)*t+v2;
					vector3d p3=(p2-p1)*t+p1;
					draw_line(l,p3,color);
					l=p3;
				}
			}
			void draw_bezier3(vector3d v1,vector3d v2,vector3d v3,vector3d v4,Color color=GREEN) {
				vector3d l=v1;
				draw_line(v1,v2,GRAY);
				draw_line(v3,v4,GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				draw_point(v4);
				for(real t=0.02;t<=1.01;t+=0.02) {
					vector3d p=v1*(-t*t*t+3*t*t-3*t+1)+v2*(3*t*t*t-6*t*t+3*t)+v3*(-3*t*t*t+3*t*t)+v4*(t*t*t);
					draw_line(l,p,color);
					l=p;
				}
			}
			void draw_bezier3_mesh(vector3d v1,vector3d v2,vector3d v3,vector3d v4,vector3d dir1={0,0,1},real angle=0,real radius=1,Color color=GREEN) {
				vector3d l=v1,l1=v1,l2=v1;
				Color c1,c2;
				c1=c2=color;
				c1.a*=0.3;
				c2.a*=0.6;
				draw_line(v1,v2,GRAY);
				draw_line(v3,v4,GRAY);
				draw_point(v1);
				draw_point(v2);
				draw_point(v3);
				draw_point(v4);
				vector3d dp=v1*(-3)+v2*(3);				
				dir1=VecUnit(dir1-(dir1>>dp));
//				dir2=VecUnit(dir2-(dir2>>dp));
//				real angle=VecAngle(dir1,dir2);
				draw_vector(v1,dir1*radius);
				for(real t=0,i=0;t<=1.01;t+=0.02,i++) {
					vector3d p=v1*(-t*t*t+3*t*t-3*t+1)+v2*(3*t*t*t-6*t*t+3*t)+v3*(-3*t*t*t+3*t*t)+v4*(t*t*t);
					vector3d dp=v1*(-3*t*t+6*t-3)+v2*(9*t*t-12*t+3)+v3*(-9*t*t+6*t)+v4*(3*t*t);				
					dir1=VecUnit(dir1-(dir1>>dp));
//					dir2=VecUnit(dir2-(dir2>>dp));
					vector3d temp=dp^(dir1.Rotate(dp,t*angle));
					temp=VecUnit(temp);
					
					draw_line(l,p,c2);
					draw_line(l1,p+temp*radius,color);
					draw_line(l2,p-temp*radius,color);
					if(int(i)%5==0) {
						draw_line(p,p+temp*radius,c1);
						draw_line(p,p-temp*radius,c1);
					}
					l=p;
					l1=p+temp*radius;
					l2=p-temp*radius;
				}
//				draw_vector(v4,dir2*radius);
			}
			
			int Draw(int x,int y,int w,int h,bool check=true) {
				BeginMode3D(camera);
				UpdateCamera(&camera,CAMERA_ORBITAL);
				double k=pow(10,round(log10(abs(camera.position.y)))),k01=k/10.0;
				if(k<1)k=1,k01=k/10;
				
				real temp=1.0*winH/winW;
				float x2,y2,w2,h2;
				GetScissor(&x2,&y2,&w2,&h2);
				if(x!=x2||y!=y2||w!=w2||h!=h2)BeginScissor(x,y,w,h);
				if(1.0*h/w>=temp) {
					rlViewport(x-(h/temp-w)/2,winH-y-h,h/temp,h);
					window_scale=1.0*h/winH;
				}
				else {
					rlViewport(x,winH-(y-(w*temp-h)/2)-w*temp,w,w*temp);
					window_scale=1.0*w/winW;
				}
				
				if(movable) {
					if(MouseInRect(x,y,w,h))UseSliderX=UseSliderY=true;
				}
				if(mesh_visible) {
					for (int i = -60; i <= 60; i ++)
					{
						for (int j = -60; j <= 60; j ++)
						{
							// 计算线段的距离
							int x2=ceil(i+camera.position.x/k01);
							int z2=ceil(j+camera.position.z/k01);
							real x=x2*k01,z=z2*k01;
							real distance = sqrtf((x-camera.position.x)*(x-camera.position.x) + (z-camera.position.z) * (z-camera.position.z));
							
							// 根据距离设置线段的颜色
							if(1.0f - distance * 0.03f/abs(camera.position.y)*10<0)continue;
							Color lineColor = (Color){150,150,150,255*((1-f(log10(abs(camera.position.y))-0.5)))*(1.0f - distance * 0.03f/abs(camera.position.y)*10)};
							
							// 绘制线段
							if(x2%10!=0)DrawLine3D((Vector3){x, 0.0f, z}, (Vector3){x, 0.0f, z + k01}, lineColor);
							if(z2%10!=0)DrawLine3D((Vector3){x, 0.0f, z}, (Vector3){x + k01, 0.0f, z}, lineColor);
						}
					}
					for (int i = -60; i <= 60; i ++)
					{
						for (int j = -60; j <= 60; j ++)
						{
							// 计算线段的距离
							int x2=ceil(i+camera.position.x/k);
							int z2=ceil(j+camera.position.z/k);
							real x=x2*k,z=z2*k;
							float distance = sqrtf((x-camera.position.x)*(x-camera.position.x) + (z-camera.position.z) * (z-camera.position.z));
							
							// 根据距离设置线段的颜色
							if(1.0f - distance * 0.03f/abs(camera.position.y)*9<0)continue;
							Color lineColor =(Color){150,150,150,255*(1.0f - distance * 0.03f/abs(camera.position.y)*9)};
							
							// 绘制线段
							if(x2!=0)DrawLine3D((Vector3){x, 0.0f, z}, (Vector3){x, 0.0f, z + k}, lineColor);
							if(z2!=0)DrawLine3D((Vector3){x, 0.0f, z}, (Vector3){x + k, 0.0f, z}, lineColor);
						}
					}
				}
				if(axis_visible){
					/*x*/DrawLine3D((Vector3){10000,0,0},(Vector3){-10000,0,0},Color{231, 162, 154,255});
					/*y*/DrawLine3D((Vector3){0,10000,0},(Vector3){0,-10000,0},Color{140, 128, 191,255});
					/*z*/DrawLine3D((Vector3){0,0,10000},(Vector3){0,0,-10000},Color{255, 128, 192,255});
				}
				if (draw_fun != nullptr)draw_fun(this);
				
				EndMode3D();
				rlViewport(0,0,winW,winH);
				if(x!=x2||y!=y2||w!=w2||h!=h2)EndScissor();
				return h;
			}
			int Draw(int x,int y,int w,bool check=true) {
				x+=dpi,y+=dpi,w-=dpi*2;
				Draw(x,y,w,w*0.8,check);
				special_effect::DrawMouseBox(x,y,w,w*0.8);
				return w*0.8+dpi*2;
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
			string text = "Input box";
			string input = "";
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
								k2 = min(k2, int(input.size()));
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
								string str = GetClipboardText();
								for (int i = 0; i < str.size(); i++)if (str[i] == '\n')str.erase(i, 1);
								input.insert(input_pos, str), input_pos += str.size();
							}
						} else {
							string str = " ";
							str[0] = c;
							if (c)input.insert(input_pos, str), input_pos++;
						}
						if ((input_pos - start_pos)* TextHeight / 2 > w -  SpaceSize * 2)start_pos += w /  TextHeight;
						if ((input_pos - start_pos)* TextHeight / 2 < 0)start_pos -= w /  TextHeight;
						if (start_pos < 0)start_pos = 0;
						for (int i = 1; i <= 350; i++)if (IsKeyDown(i))a = 200, fix_time = clock();
					} else start_pos = 0;
				}
				if(!check&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))start_pos = 0;//, ChooseInputBox = NULL;
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
			string op="insert";
			vector2d pos1;
			vector2d pos2;
			string str;
			real time;
		};
		class MultiInputBox : public  ui::Element {
		public:
			string text = "Input box";
			vector<string> input;
			vector2d input_pos = {0, 0};
			vector2d size = {0, 0};
			int fix_time = 0;
			bool choose = false;
			int choose_start = 0;
			int choose_end = 0;
			int multi_height = 5;
			bool chosen = false;
			Animation ipx, ipy;
			Animation move;
			ui::SliderBar sx, sy;
			Color background_color=BgColor;
			
			bool label_visible=false;
			bool choose_word=false;
			bool choose_word_on=false;
			bool auto_complete=true;
			vector2d choose_pos={0,0};
			vector2d choose_pos2={0,0};
			
			stack<InputHistory> history;
			stack<InputHistory> history2;
			int last_history_len=-1;
			
			MultiInputBox() {
				ipx.sd(200), ipy.sd(200);
				extra = true;
				sx.blank=0,sy.blank=0;
				input.push_back("");
			}
			vector2d GetPos(vector2d v) {
				int tempW=0;
				if(label_visible)tempW=ui::TextHeight*4;
				int tempx = X - sx.now + ui::SpaceSize + tempW;
				int tempy = Y - sy.now + ui::SpaceSize;
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				return vector2d {
					tempx + ui::TextHeight / 2 * v.x,
					tempy + ui::UnitHeight * v.y
				};
			}
			string Copy(vector2d pos1,vector2d pos2) {
				vector2d v1,v2;
				if(pos1.y<pos2.y)v1=pos1,v2=pos2;
				else if(pos1.y>pos2.y)v1=pos2,v2=pos1;
				else  {
					if(pos1.x<pos2.x)v1=pos1,v2=pos2;
					else v2=pos1,v1=pos2;
				}
				string temp_str="";
				if(v1.y!=v2.y) {	
					temp_str+=input[v1.y].substr(v1.x,input[v1.y].size())+"\n";
					for(int i=v1.y+1;i<=v2.y-1;i++)temp_str+=input[i]+"\n";
					temp_str+=input[v2.y].substr(0,v2.x);
				} else {
					temp_str=input[v1.y].substr(v1.x,v2.x-v1.x);
				}
				return temp_str;
			}
			string CopyAll() {
				return Copy({0,0},{input[input.size()-1].size(),input.size()-1});
			}
			vector2d Insert(vector2d pos,string str) {
				if(pos.y>input.size()-1)pos.y=input.size()-1;
				if(pos.x>input[pos.y].size())pos.x=input[pos.y].size();
				if(pos.y<0)pos.y=0;
				if(pos.x<0)pos.x=0;
				string temp_str=input[pos.y].substr(pos.x);
				string backup=str;
				vector2d backup_pos=pos;
				input[pos.y].erase(pos.x);
				int n_pos=-1;
				do {
					n_pos=str.find("\t");
					if(n_pos==-1)break;
					str[n_pos]=' ';
					str.insert(n_pos,"   ");
				} while(n_pos!=-1);
				while(str.find('\n')!=-1) {
					n_pos=str.find('\n');
					string temp_str;
					if(str[n_pos-1]=='\r')temp_str=str.substr(0,n_pos-1);
					else temp_str=str.substr(0,n_pos);
					str.erase(0,n_pos+1);
					input[pos.y].insert(pos.x, temp_str);
					pos.y++;
					input.insert(input.begin()+(int)pos.y,"");
					pos.x=0;
				}
				input[pos.y].insert(pos.x, str), pos.x+=str.size();
				input[pos.y]+=temp_str;
				
				InputHistory temp_history;
				temp_history.op="insert";
				temp_history.pos1=backup_pos;
				temp_history.pos2=pos;
				temp_history.str=backup;
				history.push(temp_history);
				
				return pos;
			}
			vector2d InsertBack(string str) {
				return Insert({input[input.size()-1].size(),input.size()-1},str);
			}
			vector2d InsertLine(int pos,string str) {
				return Insert({input[pos-1].size(),pos-1},"\n"+str);
			}
			vector2d Delete(vector2d pos1,vector2d pos2) {
				vector2d v1,v2;
				if(pos1.y<pos2.y)v1=pos1,v2=pos2;
				else if(pos1.y>pos2.y)v1=pos2,v2=pos1;
				else {
					if(pos1.x<pos2.x)v1=pos1,v2=pos2;
					else v2=pos1,v1=pos2;
				}
				string backup=Copy(v1,v2);
				if(v1.y<v2.y) {
					input[v1.y].erase(v1.x);
					input[v1.y]+=input[v2.y].substr(v2.x);
					for(int i=v1.y+1;i<=v2.y;i++)input.erase(input.begin()+int(v1.y+1));
				} else {
					input[v1.y].erase(v1.x,v2.x-v1.x);
				}
				
				InputHistory temp_history;
				temp_history.op="delete";
				temp_history.pos1=v1;
				temp_history.pos2=v2;
				temp_history.str=backup;
				history.push(temp_history);
				
				return v1;
			}
			vector2d Delete(vector2d pos, int n) {
				return pos;
			}
			vector2d DeleteLine(int pos) {
				if(pos==0)return Delete({0,0},{input[0].size(),0});
				else return Delete({input[pos-1].size(),pos-1},{input[pos].size(),pos});
			}
			vector2d SwapLine(int l1,int l2) {
				swap(input[l1],input[l2]);
				InputHistory temp_history;
				temp_history.op="swap";
				temp_history.pos1.y=l1;
				temp_history.pos2.y=l2;
				history.push(temp_history);
				return {input_pos.x,l2};
			}
			vector2d GetEnd() {
				return {input[input.size()-1].size(),input.size()-1};
			}
			vector2d Clear() {
				return Delete({0,0},GetEnd());
			}
			vector2d Undo() {
				if(last_history_len!=history.size()) {
					stack<InputHistory>().swap(history2);
					last_history_len=history.size();
				}
				if(history.empty())return input_pos;
				InputHistory temp=history.top();
				vector2d v;
				history.pop();
				if(temp.op=="insert") {
					v=Delete(temp.pos1,temp.pos2);
					history.pop();
				} else if(temp.op=="delete") {
					v=Insert(temp.pos1,temp.str);
					history.pop();
				} else if(temp.op=="swap") {
					v=SwapLine(temp.pos2.y,temp.pos1.y);
					history.pop();
				}
				history2.push(temp);
				last_history_len=history.size();
				return v;
			}
			vector2d Redo() {
				if(last_history_len!=history.size()) {
					stack<InputHistory>().swap(history2);
					last_history_len=history.size();
				}
				if(history2.empty())return input_pos;
				InputHistory temp=history2.top();
				vector2d v;
				history2.pop();
				if(temp.op=="insert") {
					v=Insert(temp.pos1,temp.str);
					history.pop();
				} else if(temp.op=="delete") {
					v=Delete(temp.pos1,temp.pos2);
					history.pop();
				} else if(temp.op=="swap") {
					v=SwapLine(temp.pos1.y,temp.pos2.y);
					history.pop();
				}
				history.push(temp);
				last_history_len=history.size();
				return v;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				
				BeginScissor(x,y,w,h);
				
				ipx.stp(input_pos.x), ipy.stp(input_pos.y);
				ipx.update(), ipy.update();
				sx.lx=x,sx.ly=y,sx.lw=w,sx.lh=h;
				sy.lx=x,sy.ly=y,sy.lw=w,sy.lh=h;
				X=x,Y=y,W=w,H=w;
				move.update();
				int start_x=2*(sx.now-ui::SpaceSize)/ui::TextHeight;
				int start_y=(sy.now-ui::SpaceSize)/ui::UnitHeight;
				int end_x=2*(sx.now-ui::SpaceSize+w)/ui::TextHeight+1;
				int end_y=(sy.now-ui::SpaceSize+h)/ui::UnitHeight+1;
				if(background_color.r!=BgColor.r||
					background_color.g!=BgColor.g||
					background_color.b!=BgColor.b)DrawRectangle(x,y,w,h,background_color);
				
				int tempW=0;
				if(label_visible) {
					tempW=ui::TextHeight*4;
					DrawRectangle(x,y,tempW,h,Color{25,25,25,255});
					int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
					int tempx = x - sx.now + ui::SpaceSize;
					int tempy = y - sy.now + ui::SpaceSize;
					for (int i = start_y; i < min((int)input.size(),end_y); i++) {
						size.x=max(size.x,(double)input[i].size());
						string temp_str="";
						for(int j=1;j<=4-int(log10(i+1));j++)temp_str+=' ';
						stringstream a;
						a<<(i+1);
						temp_str+=a.str();
						ui::Print(x+ui::TextHeight*0.5, tempy + tempH + i * ui::UnitHeight, temp_str,WHITE);
					}
					DrawRectangle(x+ui::SpaceSize,tempy + ui::UnitHeight * ipy.gnp(),w-ui::SpaceSize, ui::UnitHeight, Color{100,100,100,100});
					x+=tempW;
					w-=tempW;
				} else {
					int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
					int tempx = x - sx.now + ui::SpaceSize;
					int tempy = y - sy.now + ui::SpaceSize;
					DrawRectangle(x,tempy + ui::UnitHeight * ipy.gnp(),w, ui::UnitHeight, Color{100,100,100,100});
				}
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				int tempx = x - sx.now + ui::SpaceSize;
				int tempy = y - sy.now + ui::SpaceSize;
				char c = ui::GetChar;
				ui::BeginScissor(x, y, w, h);
				size.x=0;
				
				for (int i = start_y; i < min((int)input.size(),end_y); i++)
					ui::Print(tempx, tempy + tempH + i * ui::UnitHeight, input[i]);
				for(int i=0;i<input.size();i++)size.x=max(size.x,(double)input[i].size());
				size.y=input.size();		
				
				int a = (clock() - fix_time) % 1000;
				if (a < 300)a = 200;
				else if (a < 500)a = 500 - a;
				else if (a < 800)a = 0;
				else a = a - 800;
				if (true) {
					if (ui::MouseInRect(x-tempW, y, w+tempW-ui::SpaceSize*3, h-ui::SpaceSize*3)&&InScissor(Mouse.x,Mouse.y)&&check) {
						ui::MouseCursorStyle = MOUSE_CURSOR_IBEAM;
						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ChooseInputBox = this;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ChooseInputBox == this)ChooseInputBox = NULL;
					if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
					if (choose && ChooseInputBox != this)choose = false, move.stp(0);
					if (choose) {
						if(!choose_word&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))choose_word_on=false;
						if (ui::MouseInRect(x, y, w- ui::SpaceSize*3, h-ui::SpaceSize*3)||choose_word) {
							if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0 * ky / ui::UnitHeight);
								if(kx2<0)kx2=0;
								if(ky2<0)ky2=0;
								ky2 = min(ky2, int(input.size()-1));
								kx2 = min(kx2, int(input[ky2].size()));
								input_pos={kx2,ky2};
								ipx.stp(input_pos.x), ipy.stp(input_pos.y);
								ipx.update(),ipy.update();
							}
							if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0 * ky / ui::UnitHeight);
								if(kx2<0)kx2=0;
								if(ky2<0)ky2=0;
								ky2 = min(ky2, int(input.size()-1));
								kx2 = min(kx2, int(input[ky2].size()));
								choose_word=true;
								choose_pos={kx2,ky2};
							}
						}
						if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT))choose_word=false;
						if(choose_word) {
							int kx = ui::Mouse.x - tempx;
							int ky = ui::Mouse.y - tempy;
							int kx2 = round(1.0 * kx * 2 / ui::TextHeight);
							int ky2 = floor(1.0 * ky / ui::UnitHeight);
							if(kx2<0)kx2=0;
							if(ky2<0)ky2=0;
							ky2 = min(ky2, int(input.size()-1));
							kx2 = min(kx2, int(input[ky2].size()));
							if(kx2!=choose_pos.x||ky2!=choose_pos.y) {
								choose_word_on=true;
								choose_pos2=vector2d{kx2,ky2};
							}
						}
						bool delete_choose=false;
						if(choose_word_on) {
							vector2d v1,v2;
							choose_pos2=vector2d{ipx.gnp(),ipy.gnp()};
							if(choose_pos.y<choose_pos2.y)v1=choose_pos,v2=choose_pos2;
							else if(choose_pos.y>choose_pos2.y)v1=choose_pos2,v2=choose_pos;
							else  {
								if(choose_pos.x<choose_pos2.x)v1=choose_pos,v2=choose_pos2;
								else v2=choose_pos,v1=choose_pos2;
							}
							vector2d v3=GetPos(v1),v4=GetPos(v2);
							Color color=ui::MainColor;
							color.a=100;
							if(v2.y-v1.y>1&&v3.y<y+h&&v4.y>y)DrawRectangle(x,max(int(v3.y+ui::UnitHeight),y),w,ceil(min(v4.y,double(y+h))-max(int(v3.y+ui::UnitHeight),y)),color);
							if(v2.y-v1.y<0.9)DrawRectangle(v3.x,v3.y,v4.x-v3.x,ui::UnitHeight,color);
							else {
								DrawRectangle(v3.x,v3.y,x+w-v3.x,ui::UnitHeight,color);
								DrawRectangle(x,v4.y,v4.x-x,ui::UnitHeight,color);
							}
							if(IsKeyDown(KEY_HOME)||IsKeyDown(KEY_END)||IsKeyDown(KEY_UP)||IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_RIGHT)) {
								choose_word_on=false;
							}
							bool flag=false;
							for (int i = 32; i <= 127; i++)if (c==i) {
								flag=true;
								break;
							}
							if(IsKeyDown(KEY_BACKSPACE)||IsKeyDown(KEY_ENTER)||IsKeyDown(KEY_TAB)||IsKeyDown(KEY_DELETE))flag=true;
							if(flag) {
								input_pos=Delete(choose_pos,input_pos);
								choose_word_on=false;
								delete_choose=true;
							}
						}
						if (ui::IsKeyInput(KEY_BACKSPACE)&&!delete_choose){
							if(input_pos.x>0)input_pos=Delete(input_pos-vector2d{1,0},input_pos);
							else if(input_pos.y>0)input_pos=Delete({input[input_pos.y-1].size(),input_pos.y-1},input_pos);
						}
						else if (ui::IsKeyInput(KEY_DELETE)&&!delete_choose) {
							if(input_pos.x<input[input_pos.y].size())input_pos=Delete(input_pos+vector2d{1,0},input_pos);
							else if(input_pos.y<input.size())input_pos=Delete({0,input_pos.y+1},input_pos);
						}
						else if (ui::IsKeyInput(KEY_LEFT)) {
							if(input_pos.x>0)input_pos.x--;
							else if(input_pos.y>0)input_pos.y--,input_pos.x=input[input_pos.y].size();
						}
						else if (ui::IsKeyInput(KEY_RIGHT)) {
							if(input_pos.x<input[input_pos.y].size())input_pos.x++;
							else if(input_pos.y<input.size()-1)input_pos.y++,input_pos.x=0;
						}
						else if (ui::IsKeyInput(KEY_UP) && input_pos.y>0) {
							if(IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyDown(KEY_LEFT_SHIFT)) {
								if(input_pos.y>0)SwapLine(input_pos.y,input_pos.y-1);
							}
							input_pos.y--;
						}
						else if (ui::IsKeyInput(KEY_DOWN) && input_pos.y < input.size()-1) {
							if(IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyDown(KEY_LEFT_SHIFT)) {
								if(input_pos.y<input.size()-1)SwapLine(input_pos.y,input_pos.y+1);
							}
							input_pos.y++;
						}
						else if (ui::IsKeyInput(KEY_END))input_pos.x=input[input_pos.y].size();
						else if (ui::IsKeyInput(KEY_HOME))input_pos.x=0;
						else if (ui::IsKeyInput(KEY_TAB))input[input_pos.y].insert(input_pos.x, "    "), input_pos.x += 4;
						else if (ui::IsKeyInput(KEY_ENTER)) {
							bool flag=true;
							if(input_pos.x<=0||input_pos.x>=input[input_pos.y].size())flag=false;
							if(flag&&input[input_pos.y][input_pos.x-1]=='{'&&input[input_pos.y][input_pos.x]=='}') {
								Insert(input_pos,"\n\n");
								input_pos.y++;
								input_pos.x=0;
								int space_size=0;
								string temp="";
								for(int i=0;i<input[input_pos.y-1].size();i++) {
									if(input[input_pos.y-1][i]==' ')space_size++,temp+=' ';
									else {
										break;
									}
								}
								if(space_size%4==0) {
									Insert(input_pos+vector2d{0,1},temp);
									input_pos=Insert(input_pos,temp+"    ");
								}
							} else {
								input_pos=Insert(input_pos,"\n");
								int space_size=0;
								string temp="";
								for(int i=0;i<input[input_pos.y-1].size();i++) {
									if(input[input_pos.y-1][i]==' ')space_size++,temp+=' ';
									else {
										break;
									}
								}
								if(space_size%4==0)input_pos=Insert(input_pos,temp);
							}
						}
						if (IsKeyDown(KEY_LEFT_CONTROL)&&!IsKeyDown(KEY_LEFT_SHIFT)) {
							if(choose_word_on) {
								if(IsKeyPressed(KEY_C)) {
									choose_pos2=vector2d{input_pos.x,input_pos.y};
									SetClipboardText(Copy(choose_pos,choose_pos2).c_str());
									ui::message::Send("已复制到剪切板");
								} else if(IsKeyPressed(KEY_X)) {
									ui::message::Send("已复制到剪切板");
									choose_pos2=vector2d{input_pos.x,input_pos.y};
									SetClipboardText(Copy(choose_pos,choose_pos2).c_str());
									input_pos=Delete(choose_pos,choose_pos2);
									choose_word_on=false;
								}
							}
							if(IsKeyPressed(KEY_A)) {
								choose_word_on=true;
								choose_pos={0,0};
								choose_pos2={input[input.size()-1].size(),input.size()-1};
								input_pos=choose_pos2;
							}
							if(ui::IsKeyInput(KEY_V)) {
								if(choose_word_on) {
									input_pos=Delete(choose_pos,input_pos);
									choose_word_on=false;
								}
								string str=GetClipboardText();
								input_pos=Insert(input_pos,str);
							}
							if(ui::IsKeyInput(KEY_E)) {
								choose_word_on=false;
								string temp_str=input[input_pos.y];
								InsertLine(input_pos.y+1,temp_str); 
							}
							if(ui::IsKeyInput(KEY_D)) {
								choose_word_on=false;
								DeleteLine(input_pos.y);
							}
							if(ui::IsKeyInput(KEY_Z)) {
								choose_word_on=false;
								input_pos=Undo();
							}
							if(ui::IsKeyInput(KEY_Y)) {
								choose_word_on=false;
								input_pos=Redo();
							}
						}
						else {
							string str = GetCharString;
//							if(GetCharInt)cout<<(wchar_t)GetCharInt<<' '<<str<<endl;
							if (c) {
								input_pos=Insert(input_pos, str);
								if(auto_complete) {
									if(c=='<'&&input[input_pos.y][0]=='#')Insert(input_pos, ">");
									if(c=='(')Insert(input_pos, ")");
									if(c=='[')Insert(input_pos, "]");
									if(c=='{')Insert(input_pos, "}");
									if(c=='\'')Insert(input_pos, "\'");
									if(c=='\"')Insert(input_pos, "\"");
								}
							}
						}
						if(input_pos.y>input.size()-1)input_pos.y=input.size()-1;
						if(input_pos.x>input[input_pos.y].size())input_pos.x=input[input_pos.y].size();
						bool flag=false;
						for (int i = 1; i <= 350; i++)if (IsKeyDown(i)) {
							flag=true;
							break;
						}
						if(flag||ipx.IsRunning()||ipy.IsRunning()||IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							a = 200, fix_time = clock();
							if(input_pos.x*ui::TextHeight/2<sx.now)sx.Set(input_pos.x*ui::TextHeight/2);
							if(input_pos.y*ui::UnitHeight<sy.now)sy.Set(input_pos.y*ui::UnitHeight);
							if(input_pos.x*ui::TextHeight/2+ui::SpaceSize*2>sx.now+w-ui::SpaceSize*3)sx.Set(input_pos.x*ui::TextHeight/2+ui::SpaceSize*2-(w-ui::SpaceSize*3));
							if((input_pos.y+1)*ui::UnitHeight+ui::SpaceSize*2>sy.now+h-ui::SpaceSize*3)sy.Set((input_pos.y+1)*ui::UnitHeight+ui::SpaceSize*2-(h-ui::SpaceSize*3));
						}
					}
				} else ChooseInputBox = NULL;
				if(ipx.IsRunning()||ipy.IsRunning()) {
					a = 200, fix_time = clock();
					if(input_pos.x*ui::TextHeight/2<sx.now)sx.Set(input_pos.x*ui::TextHeight/2);
					if(input_pos.y*ui::UnitHeight<sy.now)sy.Set(input_pos.y*ui::UnitHeight);
					if(input_pos.x*ui::TextHeight/2+ui::SpaceSize*2>sx.now+w-ui::SpaceSize*3)sx.Set(input_pos.x*ui::TextHeight/2+ui::SpaceSize*2-(w-ui::SpaceSize*3));
					if((input_pos.y+1)*ui::UnitHeight+ui::SpaceSize*2>sy.now+h-ui::SpaceSize*3)sy.Set((input_pos.y+1)*ui::UnitHeight+ui::SpaceSize*2-(h-ui::SpaceSize*3));
				}
				if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
				if (choose && ChooseInputBox != this)choose = false, move.stp(0);
				if (choose) {
					a = a * 255 / 200;
					DrawRectangle(
						tempx + ui::TextHeight / 2 * ipx.gnp() - ui::dpi,
						tempy + ui::UnitHeight * ipy.gnp() - tempH,
						2 * ui::dpi, ui::TextHeight + tempH*4, Color{232, 192, 114, a}
						);
				} else {
					DrawRectangle(
						tempx + ui::TextHeight / 2 * ipx.gnp() - ui::dpi,
						tempy + ui::UnitHeight * ipy.gnp() - tempH,
						2 * ui::dpi, ui::TextHeight + tempH*4, Color{70, 70, 70, 255}
						);
				}
				
				if(label_visible) {
					if(sx.now>ui::SpaceSize-1) {
						ui::special_effect::DrawShadowLine(x,y+h,x,y,10*ui::dpi,1);
					}
				}
				
				ui::EndScissor();
				
				sx.sum = size.x*ui::TextHeight/2+ui::SpaceSize*3+tempW; 
				sy.sum = size.y*ui::UnitHeight+h-ui::UnitHeight-ui::SpaceSize*3;
				sx.Draw(x-tempW, y + h - ui::SpaceSize * 4, w - ui::SpaceSize * 3+tempW, ui::SpaceSize * 4);
				sy.Draw(x + w - ui::SpaceSize * 4, y, ui::SpaceSize * 4, h - ui::SpaceSize * 3);
				sx.Update();
				sy.Update();
				DrawRectangle(x + w - ui::SpaceSize * 3, y + h - ui::SpaceSize * 3, ui::SpaceSize * 3, ui::SpaceSize * 3, DARKGRAY);
				
				EndScissor();
				
				return ui::UnitHeight;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h=multi_height*ui::UnitHeight+2*ui::SpaceSize;
				x+=dpi,y+=dpi,w-=dpi*2,h;
				Draw(x,y,w,h,check);
				special_effect::DrawMouseBox(x,y,w,h);
				return h+dpi;
			}
		};
		class CheckBox : public Element {
		public:
			bool choose = false;
			string text = "Check Box";
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
			string text = "Hyperlink";
			string link = "https://www.luogu.com.cn/";
			Animation move;
			Hyperlink() {
				move.sd(300);
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				move.update();
				PrintIcon(x+SpaceSize,y+h,"",Color{177, 164, 246,255});
				Print(x + UnitHeight + SpaceSize, y + h, text, Color{177, 164, 246,255});
				int wi = text.size() * TextHeight / 2;
				DrawLineEx({x + SpaceSize + UnitHeight + wi / 2 - move.gnp()*wi / 2, y + h + TextHeight}, {x + SpaceSize + UnitHeight + wi / 2 + move.gnp()*wi / 2, y + h + TextHeight}, dpi, Color{177, 164, 246,255});
				if (MouseInRect(x + UnitHeight + SpaceSize, y, text.size()*TextHeight / 2, UnitHeight)) {
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
				DrawRing({x + TextHeight / 2, y + h + TextHeight / 2}, min(TextHeight / 2 - int(choose_ani[id].gnp()*TextHeight / 3.0), TextHeight / 2), TextHeight / 2, 0, 360, 30, MainColor);
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
			string text[32];
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
			string text[32];
			string icon[32];
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
				special_effect::DrawMouseRectangle(x, y+SpaceSize/2, w, h-SpaceSize);
				PrintIcon(x + SpaceSize, y + t, icon[id], WHITE);
				Print(x + SpaceSize * 2 + TextHeight, y + t, text[id], WHITE);
				if (MouseInRect(x, y+SpaceSize/2, w, h-SpaceSize)) {
					DrawRectangle(x, y+SpaceSize/2, w, h-SpaceSize, ChooseColor);
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && check)DrawRectangle(x, y+SpaceSize/2, w, h-SpaceSize, ChooseColor);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check)click = id;
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				DrawRectangle(x, y, w, h, Color {50, 50, 50, 255});
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
			string text[10];
			string icon[10];
			Color color[10];
			int click=-1;
			BottomMenu() {
				for(int i=0;i<10;i++)color[i]=Color{47,47,47,255};
			}
			int Draw(int x,int y,int w,int h,bool check=true) {
				click=-1;
				DrawRectangle(x,y,w,h,Color{35,35,35,255});
				DrawLineEx({x,y+dpi/2},{x+w,y+dpi/2},dpi,Color{255,255,255,30});
				int t=UnitHeight*0.6;
				int width=t;
				for(int i=0;i<n;i++) {
					button[i].text=text[i];
					button[i].icon=icon[i];
					button[i].color=color[i];
					int k=max(button[i].GetWidth(),UnitHeight*4);
					button[i].Draw_Auto_Extra(x+w-width-k,y+t,k,UnitHeight*1.3);
					if(button[i].click)click=i;
					width+=k+SpaceSize;
				}
				return UnitHeight*2.5;
			}
		};
		class Tip : public Priority {
		public:
			string text = "This is a tip.";
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
				last_draw = true;
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
					DrawRectangleRounded(Rectangle{tx, ty, tw, th}, 0.4, 10, Fade(BgColor, a * 0.7));
					DrawRectangleRoundedLines(Rectangle{tx, ty, tw, th}, 0.4, 10, dpi, Fade(MainColor, a * 0.7));
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
				extra=true;
				camera.target = (Vector2){ winW/2, winH/2 };
				camera.offset = (Vector2){ winW/2.0f, winH/2.0f };
				camera.rotation = 0.0f;
				camera.zoom = 1.0f;
			}
			int Draw(int x,int y,int w,int h,bool check=true) {
				
				camera.target={0,0};
				camera.offset={x,y};
				BeginMode2D(camera);
				
				draw_fun(this);
				
				EndMode2D();
				
				return h;
			}	
		};
		class Interface : public Element {
		private:
			Animation width,height_;
			Animation xani, yani;
			Animation heightAni;
			int Height = 0;
			bool sbar_added = false;
			bool swapping = false;
		public:
			bool visible = true;
			bool insert_ani = false;
			bool moving_ani = true;
			bool sbar_visible = true;
			int interval = ui::SpaceSize * 4;
			real blank = 0.3;
			vector<Sider> sider;
			SliderBar sbar;
			Position pos = pos_full;
			int max_width = 500;
			void AddSider(Element* ele, SiderPosition spos, int occupy = -1) {
				Sider temp;
				temp.ele = ele;
				temp.spos = spos;
				temp.occupy = occupy;
				sider.push_back(temp);
			}
			interface() {
				heightAni.sd(500);
				xani.sd(300);
				yani.sd(300);
				xani.ssp(0);
				yani.ssp(0);
				width.sd(300);
				height_.sd(300);
			}
			void Set(int tx, int ty, int tw, int th, int fx = INT_MAX, int fy = INT_MAX, int fw = INT_MAX, int fh = INT_MAX) {
				if (fx == INT_MAX)fx = tx;
				if (fy == INT_MAX)fy = tx;
				if (fw == INT_MAX)fw = tx;
				if (fh == INT_MAX)fh = tx;
				xani.ssp(fx), xani.stp(tx);
				yani.ssp(fy), yani.stp(ty);
				width.ssp(fw), width.stp(tw);
			}
			int Draw(int x, int y, int w = 600, int h = 600, bool check = true) {
				bool draw_sider=true;
				for (int i = 0; i < key.size(); i++) {
					if (key[i]->extra) {
						draw_sider=false;
						break;
					}
				}
				if (!sbar_added&&draw_sider&&sbar_visible) {
					sbar_added = true;
					AddSider(&sbar, spos_right);
				}
				swapping = false;
				heightAni.Update();
				width.Update();
				xani.Update();
				yani.Update();
				height_.Update();
				width.stp(w);
				height_.stp(h);
				if(moving_ani) {
					xani.stp(x);
					yani.stp(y);
				} else {
					xani.ssp(x);
					yani.ssp(y);
					xani.update();
					yani.update();
				}
				BeginScissor(x,y,w,h);
				x = xani.gnp();
				y = yani.gnp();
				w = width.gnp();
				h = height_.gnp();
				X = x, Y = y, W = w, H = h;
				if (!visible)return 0;
				Height = 0;
				for (int i = 0; i < key.size(); i++)if (!key[i]->extra)Height += key[i]->height;
				heightAni.stp(Height);
				Height = heightAni.gnp();
				sbar.lx = X, sbar.ly = Y, sbar.lw = W, sbar.lh = H;
				sbar.sum = Height;
				sbar.blank = blank;
				int dx = 0, dy = 0, dw = 0, dh = 0;
				
				for (int i = 0; i < sider.size(); i++) {
					if (sider[i].spos == spos_left) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, sider[i].occupy, height_.gtp() + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, sider[i].occupy, height_.gtp() + dh, check);
						dx += sider[i].occupy, dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_top) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, width.gtp() + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, width.gtp() + dw, sider[i].occupy, check);
						dy += sider[i].occupy, dh -= sider[i].occupy;
					}
					if (sider[i].spos == spos_right) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx + width.gtp() + dw - sider[i].occupy, yani.gtp() + dy, sider[i].occupy, height_.gtp() + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx + width.gtp() + dw - sider[i].occupy, yani.gtp() + dy, sider[i].occupy, height_.gtp() + dh, check);
						dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_bottom) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy + height_.gtp() + dh - sider[i].occupy, width.gtp() + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy + height_.gtp() + dh - sider[i].occupy, width.gtp() + dw, sider[i].occupy, check);
						dh -= sider[i].occupy;
					}
				}
				
				int tx=x,ty=y,tw=w,th=h;
				real nowh = -sbar.now;
				x += dx, y += dy, w += dw, h += dh;
				x += interval;
				w -= interval * 2;
				if (pos != pos_full) {
					int w2 = min(max_width, w);
					if (pos == pos_mid)x = x + w / 2.0 - w2 / 2;
					if (pos == pos_right)x = x + w - w2;
					w = w2;
				}
				
				for (int i = 0; i < key.size(); i++) {
					if (key[i]->extra && !key[i]->last_draw)key[i]->Draw_Auto_Extra(tx+dx, ty+dy, tw+dw, th+dh, check);
				}
				BeginScissor(x, y, w + interval, h);
				for (int i = 0; i < key.size(); i++) {
					if (insert_ani) {
						key[i]->prelAniX.stp(0, 300);
						key[i]->prelAniY.stp(nowh + sbar.now, 0);
					} else {
						key[i]->prelAniX.ssp(0);
						key[i]->prelAniY.ssp(nowh + sbar.now);
					}
					Vector2 ve = key[i]->GetPRel();
					if (!key[i]->extra && !key[i]->last_draw)nowh += key[i]->Draw_Auto(x + ve.x, y + ve.y - sbar.now + interval, w, check && !swapping && MouseInRect(x,y,w+interval,h));
				}
				EndScissor();
				for (int i = 0; i < key.size(); i++) {
					if (key[i]->last_draw)key[i]->Draw_Auto_Extra(tx+dx, ty+dy, tw+dw, th+dh, check);
				}
				sbar.Update();
				
				EndScissor();
				height = Height;
				return height;
			}
			void Add(Element* a) {
				key.push_back(a);
				a->prelAniX.ssp(0);
				a->prelAniY.ssp(Height + winH);
			}
			void Insert(int position, Element* a) {
				key.insert(key.begin() + position, a);
				a->prelAniX.ssp(-width.gtp());
				if (position != 0)a->prelAniY.ssp(key[position - 1]->GetPRel().y + key[position - 1]->height);
				else a->prelAniY.ssp(0);
			}
			void Swap(int a, int b) {
				swap(key[a], key[b]);
				swapping = true;
			}
		};
		using interface = Interface;
		class Layout {
		public:
			ui::interface* intf=nullptr;
			Layout* lo1 = nullptr;
			Layout* lo2 = nullptr;
			double split = 0.5;
			bool movable=true;
			bool moving=false;
			SplitStyle split_style = split_main;
			
			~Layout() {
				delete lo1;
				delete lo2;
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
			string title = "Window";
			bool moving = false;
			bool rx = false, ry = false, rw = false, rh = false;
			bool pop = true;
			bool draw_title = true;
			bool draw_body = true;
			bool draw_dark=false;
			bool is_mainwin = false;
			int title_height = 25 * dpi;
			int ani_state = AniEnabled;
			int valid_x, valid_y, valid_w, valid_h;
			Vector2 move_start, pos_start;
			Animation xani, yani, wani, hani, darkani;
			Layout layout;
			
			vector<Sider> sider;
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
			}
			void Pop(int tx=0, int ty=0, int tw=winW, int th=winH, int fx = INT_MAX, int fy = INT_MAX, int fw = INT_MAX, int fh = INT_MAX) {
				X = tx, Y = ty, W = tw, H = th;
				if (fx == INT_MAX)fx = tx+tw/4;
				if (fy == INT_MAX)fy = winH*1.2;
				if (fw == INT_MAX)fw = tw/2;
				if (fh == INT_MAX)fh = th;
				xani.ssp(fx), xani.stp(tx), xani.sd(500);
				yani.ssp(fy), yani.stp(ty), yani.sd(500);
				wani.ssp(fw), wani.stp(tw), wani.sd(500);
				hani.ssp(fh), hani.stp(th), hani.sd(500);
				priority=++TopPriority;
				pop = true;
				darkani.stp(0.7);
			}
			void Close() {
				xani.stp(X+W/4);
				yani.stp(winH*1.2);
				wani.stp(W/2);
				hani.stp(H);
				pop = false;
				darkani.stp(0);
			}
			void Hide() {
				xani.ssp(X+W/4);
				yani.ssp(winH*1.2);
				wani.ssp(W/2);
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
			void DrawLayout(Layout* lo, int x, int y, int w, int h,bool check=true) {
				int k = SpaceSize;
				if (lo->split_style == split_main && lo->intf != nullptr) {
					if(moving)lo->intf->moving_ani=false;
					else lo->intf->moving_ani=true;
					lo->intf->Draw_Auto_Extra(x, y, w, h, check);
				} else if (lo->split_style == split_row) {
					if(lo->movable) {
						if(lo->moving) {
							MouseCursorStyle=MOUSE_CURSOR_RESIZE_EW;
							lo->split=1.0*(GetMouseX()-x-4*dpi)/(w-8*dpi);
							if(lo->split<0)lo->split=0;
							if(lo->split>1)lo->split=1;
							DrawLayout(lo->lo1, x, y, (w-8*dpi) * lo->split, h,check&&!lo->moving);
							DrawLayout(lo->lo2, x + (w-8*dpi) * lo->split+8*dpi, y, (w-8*dpi) * (1 - lo->split), h,check&&!lo->moving);
							DrawRectangle(x + (w-8*dpi) * lo->split,y,8*dpi,h,LIGHTGRAY);
							DrawLine(x+ (w-8*dpi) * lo->split+2*dpi,y+h/2-10*dpi,x+ (w-8*dpi) * lo->split+2*dpi,y+h/2+10*dpi,BLACK);
							DrawLine(x+ (w-8*dpi) * lo->split+6*dpi,y+h/2-10*dpi,x+ (w-8*dpi) * lo->split+6*dpi,y+h/2+10*dpi,BLACK);
							MouseCursorStyle=MOUSE_CURSOR_RESIZE_EW;
							if(IsMouseButtonUp(MOUSE_BUTTON_LEFT))lo->moving=false;
						} else {
							DrawLayout(lo->lo1, x, y, (w-8*dpi) * lo->split, h,check&&!lo->moving);
							DrawLayout(lo->lo2, x + (w-8*dpi) * lo->split+8*dpi, y, (w-8*dpi) * (1 - lo->split), h,check&&!lo->moving);
							special_effect::DrawMouseRectangle_onlyLight(x + (w-8*dpi) * lo->split,y,8*dpi,h);
							DrawLine(x+ (w-8*dpi) * lo->split+2*dpi,y+h/2-10*dpi,x+ (w-8*dpi) * lo->split+2*dpi,y+h/2+10*dpi,DARKGRAY);
							DrawLine(x+ (w-8*dpi) * lo->split+6*dpi,y+h/2-10*dpi,x+ (w-8*dpi) * lo->split+6*dpi,y+h/2+10*dpi,DARKGRAY);
							if(MouseInRect(x + (w-8*dpi) * lo->split,y,8*dpi,h)&&check) {
								DrawRectangle(x + (w-8*dpi) * lo->split+dpi,y,6*dpi,h,Fade(LIGHTGRAY,0.25));
								MouseCursorStyle=MOUSE_CURSOR_RESIZE_EW;
								if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))lo->moving=true;
							}
						}
					} else {
						DrawLayout(lo->lo1, x, y, w * lo->split, h,check);
						DrawLayout(lo->lo2, x + w * lo->split, y, w * (1 - lo->split), h,check);
					}
				} else if (lo->split_style == split_col) {
					if(lo->movable) {
						if(lo->moving) {
							MouseCursorStyle=MOUSE_CURSOR_RESIZE_NS;
							lo->split=1.0*(GetMouseY()-y-4*dpi)/(h-8*dpi);
							if(lo->split<0)lo->split=0;
							if(lo->split>1)lo->split=1;
							DrawLayout(lo->lo1, x, y, w, (h-8*dpi) * lo->split,check&&!lo->moving);
							DrawLayout(lo->lo2, x, y + (h-8*dpi) * lo->split+8*dpi, w, (h-8*dpi) * (1 - lo->split),check&&!lo->moving);
							DrawRectangle(x,y + (h-8*dpi) * lo->split,w,8*dpi,LIGHTGRAY);
							DrawLine(x+w/2-10*dpi,y + (h-8*dpi) * lo->split+2*dpi,x+w/2+10*dpi,y + (h-8*dpi) * lo->split+2*dpi,BLACK);
							DrawLine(x+w/2-10*dpi,y + (h-8*dpi) * lo->split+6*dpi,x+w/2+10*dpi,y + (h-8*dpi) * lo->split+6*dpi,BLACK);
							if(IsMouseButtonUp(MOUSE_BUTTON_LEFT))lo->moving=false;
						} else {
							DrawLayout(lo->lo1, x, y, w, (h-8*dpi) * lo->split,check&&!lo->moving);
							DrawLayout(lo->lo2, x, y + (h-8*dpi) * lo->split+8*dpi, w, (h-8*dpi) * (1 - lo->split),check&&!lo->moving);
							special_effect::DrawMouseRectangle_onlyLight(x,y + (h-8*dpi) * lo->split,w,8*dpi);
							DrawLine(x+w/2-10*dpi,y + (h-8*dpi) * lo->split+2*dpi,x+w/2+10*dpi,y + (h-8*dpi) * lo->split+2*dpi,DARKGRAY);
							DrawLine(x+w/2-10*dpi,y + (h-8*dpi) * lo->split+6*dpi,x+w/2+10*dpi,y + (h-8*dpi) * lo->split+6*dpi,DARKGRAY);
							if(MouseInRect(x,y + (h-8*dpi) * lo->split,w,8*dpi)&&check) {
								DrawRectangle(x,y + (h-8*dpi) * lo->split+dpi,w,6*dpi,Fade(LIGHTGRAY,0.25));
								MouseCursorStyle=MOUSE_CURSOR_RESIZE_NS;
								if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))lo->moving=true;
							}
						}
					} else {
						DrawLayout(lo->lo1, x, y, w, h * lo->split,check);
						DrawLayout(lo->lo2, x, y + h * lo->split, w, h * (1 - lo->split),check);
					}
				}
			}
			int Draw(int x, int y, int w, int h, bool check=true) {
				if (is_mainwin) {
					xani.sd(0);
					yani.sd(0);
					wani.sd(0);
					hani.sd(0);
				} else {
					if (pop) {
						xani.stp(X);
						yani.stp(Y);
						wani.stp(W);
						hani.stp(H);
						if(moving||rx||ry||rw||rh) {
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
				x = xani.gnp();
				y = yani.gnp();
				w = wani.gnp();
				h = hani.gnp();
				
				if(!pop&&!xani.IsRunning())return 0;
				if(draw_dark&&!is_mainwin) {
					DrawRectangle(0,0, winW, winH, Fade(BLACK,darkani.gnp()));
				}
				if (draw_body) {
					special_effect::DrawShadowRectangle(x, y, w, h, 15 * dpi);
					DrawRectangle(x, y, w, h, BgColor);
					DrawRectangleLines(x - 1, y - 1, w + 2, h + 2, Color{255,255,255,30});
					DrawRectangleLines(x - 2, y - 2, w + 4, h + 4, Color{255,255,255,30});
					if (draw_title) {
						if (priority == WindowTopPriority) {
							DrawRectangle(x, y, w, title_height, MainColor);
						} else {
							Color c = MainColor;
							c.r * 0.7, c.g *= 0.7, c.b *= 0.7;
							DrawRectangle(x, y, w, title_height, c);
						}
						int t = (title_height - TextHeight) / 2;
						int tw=TextHeight+SpaceSize*2+GetStringLength(title)*TextHeight/2;
						PrintIcon(x+(w-tw)/2,y+t,"",TextColor2);
						Print(x+(w-tw)/2 + TextHeight + SpaceSize * 2, y + t, title, TextColor2);
					}
					if (priority == WindowTopPriority) {
						if(draw_title) {
							if ( MouseInRect(x, y, w, title_height) && !rx && !ry && !rw && !rh) {
								if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))ani_state = AniEnabled, moving = true, move_start = Mouse, pos_start = {X, Y};
							}
						}
						if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))moving = false;
						if (moving&&pop) {
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
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, sider[i].occupy, hani.gtp() + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, sider[i].occupy, hani.gtp() + dh, check);
						dx += sider[i].occupy, dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_top) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, wani.gtp() + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy, wani.gtp() + dw, sider[i].occupy, check);
						dy += sider[i].occupy, dh -= sider[i].occupy;
					}
					if (sider[i].spos == spos_right) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx + wani.gtp() + dw - sider[i].occupy, yani.gtp() + dy, sider[i].occupy, hani.gtp() + dh, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx + wani.gtp() + dw - sider[i].occupy, yani.gtp() + dy, sider[i].occupy, hani.gtp() + dh, check);
						dw -= sider[i].occupy;
					}
					if (sider[i].spos == spos_bottom) {
						if(sider[i].occupy<=0)sider[i].occupy=25*dpi,sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy + hani.gtp() + dh - sider[i].occupy, wani.gtp() + dw, sider[i].occupy, check);
						else sider[i].occupy = sider[i].ele->Draw_Auto_Extra(xani.gtp() + dx, yani.gtp() + dy + hani.gtp() + dh - sider[i].occupy, wani.gtp() + dw, sider[i].occupy, check);
						dh -= sider[i].occupy;
					}
				}
				
				int tx=x,ty=y,tw=w,th=h;
				x += dx, y += dy, w += dw, h += dh;
				
				xani.update();
				yani.update();
				wani.update();
				hani.update();
				BeginScissor(x, y, w, h);
				valid_x = x, valid_y = y, valid_w = w, valid_h = h;
				DrawLayout(&layout, x, y, w, h,check&&(!(rx||ry||rw||rh)|!IsMouseButtonDown(MOUSE_BUTTON_LEFT)));
				EndScissor();
				EndScissor();
				xani.update();
				yani.update();
				wani.update();
				hani.update();
				
				if (draw_title) {
					if (priority == WindowTopPriority||check) {
						if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							if(!is_mainwin) {
								bool cx = false, cy = false, cw = false, ch = false;
								int k = 5 * dpi;
								if ( Mouse.y >= Y - k && Mouse.y <= Y + H + k) {
									if ( Mouse.x >= X - k && Mouse.x < X)cx = true;
									if ( Mouse.x > X + W && Mouse.x <= X + W+k)cw = true;
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
							if(!is_mainwin) {
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
				if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
					if (Y < 0)Y = 0;
					if (X < 0)X = 0;
					if (X + W > winW)X = winW - W;
					if (Y + H > winH)Y = winH - H;
				}
				
				if(pop) {
					xani.stp(X);
					yani.stp(Y);
					wani.stp(W);
					hani.stp(H);
				}
				
				return 0;
			}
		};
		
		bool System::CMP_Window(Window* w1, Window* w2) {
			return w1->priority > w2->priority;
		}
		void System::Update() {
			sort(win.begin(), win.end(), CMP_Window);
			TopPriority = win[0]->priority;
			bool c[1005],flag=false;
			int k = 5 * dpi;
			for (int i = 0; i < win.size(); i++) {
				if ( MouseInRect(win[i]->X - k, win[i]->Y - k, win[i]->W + k * 2, win[i]->H + k * 2)) {
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&win[i]->pop&&(!win[i]->is_mainwin||!flag)) {
						if(win[i]->priority!=TopPriority)win[i]->priority = ++TopPriority;
						break;
					}
				}
				if(win[i]->pop)flag=true;
			}
			sort(win.begin(), win.end(), CMP_Window);
			for (int i = 0; i < win.size(); i++) {
				if (win[i]->prio_flag == "Window"&&win[i]->pop) {
					WindowTopPriority = win[i]->priority;
					break;
				}
			}
			memset(c, 0,sizeof(c));
			for (int i = 0; i < win.size(); i++) {
				c[i] = false;
				if(!win[i]->pop)continue;
				if ( MouseInRect(win[i]->X - k, win[i]->Y - k, win[i]->W + k * 2, win[i]->H + k * 2)
					&&(win[i]->priority==WindowTopPriority||!win[i]->is_mainwin)) {
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
			string text[32];
			string icon[32];
			int last_choose = -1;
			int choose = 0;
			bool draw_full = true;
			bool full_alltime = false;
			interface* intf[32];
			Window* target = nullptr;
			Animation move;
			bool move_inited = false;
			int choise = -1;
			int choose_time = 0;
			int menu_width=250;
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
				if (draw_full||full_alltime)Print(x + SpaceSize * 6 + TextHeight, y + t, text[id], WHITE);
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
				if(full_alltime)draw_full=true;
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
						intf[choose]->Set(target->valid_x, target->valid_y, target->valid_w, target->valid_h, target->valid_x, target->valid_y + 500, target->valid_w, target->valid_h);
						intf[choose]->sbar.move.ssp(0);
						last_choose = choose;
					}
				}
				if (target->W > 700 * dpi)draw_full = true;
				else draw_full = false;
				return move.gnp();
			}
		};
		
		Window mainwin;
		
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
			DPI.x *= zoom*Scale;
			TextHeight *= DPI.x;
			UnitHeight *= DPI.x;
			SpaceSize *= DPI.x;
			dpi = DPI.x;
			// 虚拟窗口
			mainwin.draw_body = false;
			mainwin.is_mainwin = true;
			// 字体
			if(FontName=="仿宋")fontFileData = LoadFileData("C:/windows/fonts/simfang.ttf", &fileSize);
			if(FontName=="宋体")fontFileData = LoadFileData("C:/windows/fonts/SIMSUN.ttf", &fileSize);
			if(FontName=="微软雅黑")fontFileData = LoadFileData("C:/windows/fonts/simhei.ttf", &fileSize);
			if(FontName=="隶书")fontFileData = LoadFileData("C:/windows/fonts/simli.ttf", &fileSize);
			if(FontName=="楷体")fontFileData = LoadFileData("C:/windows/fonts/simkai.ttf", &fileSize);
			SetTraceLogLevel(LOG_WARNING);
			char text[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;\':\",./<>? 。？“”‘’；：×°（）》《，！、】【￥……＋⊙◢〓▼◆→一乙二十丁厂七卜人入八九几儿了力乃刀又三于干亏士工土才寸下大丈与万上小口巾山千乞川亿个勺久凡及夕丸么广亡门义之尸弓己已子卫也女飞刃习叉马乡丰王井开夫天无元专云扎艺木五支厅不太犬区历尤友匹车巨牙屯比互切瓦止少日中冈贝内水见午牛手毛气升长仁什片仆化仇币仍仅斤爪反介父从今凶分乏公仓月氏勿欠风丹匀乌凤勾文六方火为斗忆订计户认心尺引丑巴孔队办以允予劝双书幻玉刊示末未击打巧正扑扒功扔去甘世古节本术可丙左厉右石布龙平灭轧东卡北占业旧帅归且旦目叶甲申叮电号田由史只央兄叼叫另叨叹四生失禾丘付仗代仙们仪白仔他斥瓜乎丛令用甩印乐句匆册犯外处冬鸟务包饥主市立闪兰半汁汇头汉宁穴它讨写让礼训必议讯记永司尼民出辽奶奴加召皮边发孕圣对台矛纠母幼丝式刑动扛寺吉扣考托老执巩圾扩扫地扬场耳共芒亚芝朽朴机权过臣再协西压厌在有百存而页匠夸夺灰达列死成夹轨邪划迈毕至此贞师尘尖劣光当早吐吓虫曲团同吊吃因吸吗屿帆岁回岂刚则肉网年朱先丢舌竹迁乔伟传乒乓休伍伏优伐延件任伤价份华仰仿伙伪自血向似后行舟全会杀合兆企众爷伞创肌朵杂危旬旨负各名多争色壮冲冰庄庆亦刘齐交次衣产决充妄闭问闯羊并关米灯州汗污江池汤忙兴宇守宅字安讲军许论农讽设访寻那迅尽导异孙阵阳收阶阴防奸如妇好她妈戏羽观欢买红纤级约纪驰巡寿弄麦形进戒吞远违运扶抚坛技坏扰拒找批扯址走抄坝贡攻赤折抓扮抢孝均抛投坟抗坑坊抖护壳志扭块声把报却劫芽花芹芬苍芳严芦劳克苏杆杠杜材村杏极李杨求更束豆两丽医辰励否还歼来连步坚旱盯呈时吴助县里呆园旷围呀吨足邮男困吵串员听吩吹呜吧吼别岗帐财针钉告我乱利秃秀私每兵估体何但伸作伯伶佣低你住位伴身皂佛近彻役返余希坐谷妥含邻岔肝肚肠龟免狂犹角删条卵岛迎饭饮系言冻状亩况床库疗应冷这序辛弃冶忘闲间闷判灶灿弟汪沙汽沃泛沟没沈沉怀忧快完宋宏牢究穷灾良证启评补初社识诉诊词译君灵即层尿尾迟局改张忌际陆阿陈阻附妙妖妨努忍劲鸡驱纯纱纳纲驳纵纷纸纹纺驴纽奉玩环武青责现表规抹拢拔拣担坦押抽拐拖拍者顶拆拥抵拘势抱垃拉拦拌幸招坡披拨择抬其取苦若茂苹苗英范直茄茎茅林枝杯柜析板松枪构杰述枕丧或画卧事刺枣雨卖矿码厕奔奇奋态欧垄妻轰顷转斩轮软到非叔肯齿些虎虏肾贤尚旺具果味昆国昌畅明易昂典固忠咐呼鸣咏呢岸岩帖罗帜岭凯败贩购图钓制知垂牧物乖刮秆和季委佳侍供使例版侄侦侧凭侨佩货依的迫质欣征往爬彼径所舍金命斧爸采受乳贪念贫肤肺肢肿胀朋股肥服胁周昏鱼兔狐忽狗备饰饱饲变京享店夜庙府底剂郊废净盲放刻育闸闹郑券卷单炒炊炕炎炉沫浅法泄河沾泪油泊沿泡注泻泳泥沸波泼泽治怖性怕怜怪学宝宗定宜审宙官空帘实试郎诗肩房诚衬衫视话诞询该详建肃录隶居届刷屈弦承孟孤陕降限妹姑姐姓始驾参艰线练组细驶织终驻驼绍经贯奏春帮珍玻毒型挂封持项垮挎城挠政赴赵挡挺括拴拾挑指垫挣挤拼挖按挥挪某甚革荐巷带草茧茶荒茫荡荣故胡南药标枯柄栋相查柏柳柱柿栏树要咸威歪研砖厘厚砌砍面耐耍牵残殃轻鸦皆背战点临览竖省削尝是盼眨哄显哑冒映星昨畏趴胃贵界虹虾蚁思蚂虽品咽骂哗咱响哈咬咳哪炭峡罚贱贴骨钞钟钢钥钩卸缸拜看矩怎牲选适秒香种秋科重复竿段便俩贷顺修保促侮俭俗俘信皇泉鬼侵追俊盾待律很须叙剑逃食盆胆胜胞胖脉勉狭狮独狡狱狠贸怨急饶蚀饺饼弯将奖哀亭亮度迹庭疮疯疫疤姿亲音帝施闻阀阁差养美姜叛送类迷前首逆总炼炸炮烂剃洁洪洒浇浊洞测洗活派洽染济洋洲浑浓津恒恢恰恼恨举觉宣室宫宪突穿窃客冠语扁袄祖神祝误诱说诵垦退既屋昼费陡眉孩除险院娃姥姨姻娇怒架贺盈勇怠柔垒绑绒结绕骄绘给络骆绝绞统耕耗艳泰珠班素蚕顽盏匪捞栽捕振载赶起盐捎捏埋捉捆捐损都哲逝捡换挽热恐壶挨耻耽恭莲莫荷获晋恶真框桂档桐株桥桃格校核样根索哥速逗栗配翅辱唇夏础破原套逐烈殊顾轿较顿毙致柴桌虑监紧党晒眠晓鸭晃晌晕蚊哨哭恩唤啊唉罢峰圆贼贿钱钳钻铁铃铅缺氧特牺造乘敌秤租积秧秩称秘透笔笑笋债借值倚倾倒倘俱倡候俯倍倦健臭射躬息徒徐舰舱般航途拿爹爱颂翁脆脂胸胳脏胶脑狸狼逢留皱饿恋桨浆衰高席准座脊症病疾疼疲效离唐资凉站剖竞部旁旅畜阅羞瓶拳粉料益兼烤烘烦烧烛烟递涛浙涝酒涉消浩海涂浴浮流润浪浸涨烫涌悟悄悔悦害宽家宵宴宾窄容宰案请朗诸读扇袜袖袍被祥课谁调冤谅谈谊剥恳展剧屑弱陵陶陷陪娱娘通能难预桑绢绣验继球理捧堵描域掩捷排掉堆推掀授教掏掠培接控探据掘职基著勒黄萌萝菌菜萄菊萍菠营械梦梢梅检梳梯桶救副票戚爽聋袭盛雪辅辆虚雀堂常匙晨睁眯眼悬野啦晚啄距跃略蛇累唱患唯崖崭崇圈铜铲银甜梨犁移笨笼笛符第敏做袋悠偿偶偷您售停偏假得衔盘船斜盒鸽悉欲彩领脚脖脸脱象够猜猪猎猫猛馅馆凑减毫麻痒痕廊康庸鹿盗章竟商族旋望率着盖粘粗粒断剪兽清添淋淹渠渐混渔淘液淡深婆梁渗情惜惭悼惧惕惊惨惯寇寄宿窑密谋谎祸谜逮敢屠弹随蛋隆隐婚婶颈绩绪续骑绳维绵绸绿琴斑替款堪搭塔越趁趋超提堤博揭喜插揪搜煮援裁搁搂搅握揉斯期欺联散惹葬葛董葡敬葱落朝辜葵棒棋植森椅椒棵棍棉棚棕惠惑逼厨厦硬确雁殖裂雄暂雅辈悲紫辉敞赏掌晴暑最量喷晶喇遇喊景践跌跑遗蛙蛛蜓喝喂喘喉幅帽赌赔黑铸铺链销锁锄锅锈锋锐短智毯鹅剩稍程稀税筐等筑策筛筒答筋筝傲傅牌堡集焦傍储奥街惩御循艇舒番释禽腊脾腔鲁猾猴然馋装蛮就痛童阔善羡普粪尊道曾焰港湖渣湿温渴滑湾渡游滋溉愤慌惰愧愉慨割寒富窜窝窗遍裕裤裙谢谣谦属屡强粥疏隔隙絮嫂登缎缓编骗缘瑞魂肆摄摸填搏塌鼓摆携搬摇搞塘摊蒜勤鹊蓝墓幕蓬蓄蒙蒸献禁楚想槐榆楼概赖酬感碍碑碎碰碗碌雷零雾雹输督龄鉴睛睡睬鄙愚暖盟歇暗照跨跳跪路跟遣蛾蜂嗓置罪罩错锡锣锤锦键锯矮辞稠愁筹签简毁舅鼠催傻像躲微愈遥腰腥腹腾腿触解酱痰廉新韵意粮数煎塑慈煤煌满漠源滤滥滔溪溜滚滨粱滩慎誉塞谨福群殿辟障嫌嫁叠缝缠静碧璃墙撇嘉摧截誓境摘摔聚蔽慕暮蔑模榴榜榨歌遭酷酿酸磁愿需弊裳颗嗽蜻蜡蝇蜘赚锹锻舞稳算箩管僚鼻魄貌膜膊膀鲜疑馒裹敲豪膏遮腐瘦辣竭端旗精歉熄熔漆漂漫滴演漏慢寨赛察蜜谱嫩翠熊凳骡缩慧撕撒趣趟撑播撞撤增聪鞋蕉蔬横槽樱橡飘醋醉震霉瞒题暴瞎影踢踏踩踪蝶蝴嘱墨镇靠稻黎稿稼箱箭篇僵躺僻德艘膝膛熟摩颜毅糊遵潜潮懂额慰劈操燕薯薪薄颠橘整融醒餐嘴蹄器赠默镜赞篮邀衡膨雕磨凝辨辩糖糕燃澡激懒壁避缴戴擦鞠藏霜霞瞧蹈螺穗繁辫赢糟糠燥臂翼骤鞭覆蹦镰翻鹰警攀蹲颤瓣爆疆壤耀躁嚼嚷籍魔灌蠢霸露囊罐匕刁丐歹戈夭仑讥冗邓艾夯凸卢叭叽皿凹囚矢乍尔冯玄邦迂邢芋芍吏夷吁吕吆屹廷迄臼仲伦伊肋旭匈凫妆亥汛讳讶讹讼诀弛阱驮驯纫玖玛韧抠扼汞扳抡坎坞抑拟抒芙芜苇芥芯芭杖杉巫杈甫匣轩卤肖吱吠呕呐吟呛吻吭邑囤吮岖牡佑佃伺囱肛肘甸狈鸠彤灸刨庇吝庐闰兑灼沐沛汰沥沦汹沧沪忱诅诈罕屁坠妓姊妒纬玫卦坷坯拓坪坤拄拧拂拙拇拗茉昔苛苫苟苞茁苔枉枢枚枫杭郁矾奈奄殴歧卓昙哎咕呵咙呻咒咆咖帕账贬贮氛秉岳侠侥侣侈卑刽刹肴觅忿瓮肮肪狞庞疟疙疚卒氓炬沽沮泣泞泌沼怔怯宠宛衩祈诡帚屉弧弥陋陌函姆虱叁绅驹绊绎契贰玷玲珊拭拷拱挟垢垛拯荆茸茬荚茵茴荞荠荤荧荔栈柑栅柠枷勃柬砂泵砚鸥轴韭虐昧盹咧昵昭盅勋哆咪哟幽钙钝钠钦钧钮毡氢秕俏俄俐侯徊衍胚胧胎狰饵峦奕咨飒闺闽籽娄烁炫洼柒涎洛恃恍恬恤宦诫诬祠诲屏屎逊陨姚娜蚤骇耘耙秦匿埂捂捍袁捌挫挚捣捅埃耿聂荸莽莱莉莹莺梆栖桦栓桅桩贾酌砸砰砾殉逞哮唠哺剔蚌蚜畔蚣蚪蚓哩圃鸯唁哼唆峭唧峻赂赃钾铆氨秫笆俺赁倔殷耸舀豺豹颁胯胰脐脓逛卿鸵鸳馁凌凄衷郭斋疹紊瓷羔烙浦涡涣涤涧涕涩悍悯窍诺诽袒谆祟恕娩骏琐麸琉琅措捺捶赦埠捻掐掂掖掷掸掺勘聊娶菱菲萎菩萤乾萧萨菇彬梗梧梭曹酝酗厢硅硕奢盔匾颅彪眶晤曼晦冕啡畦趾啃蛆蚯蛉蛀唬唾啤啥啸崎逻崔崩婴赊铐铛铝铡铣铭矫秸秽笙笤偎傀躯兜衅徘徙舶舷舵敛翎脯逸凰猖祭烹庶庵痊阎阐眷焊焕鸿涯淑淌淮淆渊淫淳淤淀涮涵惦悴惋寂窒谍谐裆袱祷谒谓谚尉堕隅婉颇绰绷综绽缀巢琳琢琼揍堰揩揽揖彭揣搀搓壹搔葫募蒋蒂韩棱椰焚椎棺榔椭粟棘酣酥硝硫颊雳翘凿棠晰鼎喳遏晾畴跋跛蛔蜒蛤鹃喻啼喧嵌赋赎赐锉锌甥掰氮氯黍筏牍粤逾腌腋腕猩猬惫敦痘痢痪竣翔奠遂焙滞湘渤渺溃溅湃愕惶寓窖窘雇谤犀隘媒媚婿缅缆缔缕骚瑟鹉瑰搪聘斟靴靶蓖蒿蒲蓉楔椿楷榄楞楣酪碘硼碉辐辑频睹睦瞄嗜嗦暇畸跷跺蜈蜗蜕蛹嗅嗡嗤署蜀幌锚锥锨锭锰稚颓筷魁衙腻腮腺鹏肄猿颖煞雏馍馏禀痹廓痴靖誊漓溢溯溶滓溺寞窥窟寝褂裸谬媳嫉缚缤剿赘熬赫蔫摹蔓蔗蔼熙蔚兢榛榕酵碟碴碱碳辕辖雌墅嘁踊蝉嘀幔镀舔熏箍箕箫舆僧孵瘩瘟彰粹漱漩漾慷寡寥谭褐褪隧嫡缨撵撩撮撬擒墩撰鞍蕊蕴樊樟橄敷豌醇磕磅碾憋嘶嘲嘹蝠蝎蝌蝗蝙嘿幢镊镐稽篓膘鲤鲫褒瘪瘤瘫凛澎潭潦澳潘澈澜澄憔懊憎翩褥谴鹤憨履嬉豫缭撼擂擅蕾薛薇擎翰噩橱橙瓢蟥霍霎辙冀踱蹂蟆螃螟噪鹦黔穆篡篷篙篱儒膳鲸瘾瘸糙燎濒憾懈窿缰壕藐檬檐檩檀礁磷了瞬瞳瞪曙蹋蟋蟀嚎赡镣魏簇儡徽爵朦臊鳄糜癌懦豁臀藕藤瞻嚣鳍癞瀑襟璧戳攒孽蘑藻鳖蹭蹬簸簿蟹靡癣羹鬓攘蠕巍鳞糯譬霹躏髓蘸镶瓤矗";
			int codepointsCount;
			int *codepoints = LoadCodepoints(text, &codepointsCount);
			font = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
			ui::UseIcon(" ");
			// 字幕
			cout << "UI started successfully!" << endl;
			cout << "UI System : " << UIVer << endl;
			// 鼠标动画
			MouseXAni.sd(500);
			MouseYAni.sd(500);
			// 启动动画
			if(StartAni) {
				int _time=clock()+3100;
				Animation logo_ani,cir_ani,a_ani;
				logo_ani.ssp(0);
				logo_ani.sd(600);
				logo_ani.sms(anif::sine);
				logo_ani.stp(1,3100);
				cir_ani.ssp(0);
				cir_ani.sd(600);
				cir_ani.sms(anif::sine);
				cir_ani.stp(1,3000);
				a_ani.ssp(255);
				a_ani.stp(0,300);
				a_ani.sms(anif::linear);
				a_ani.sd(500);
				while(clock()-_time<300&&!WindowShouldClose()) {
					logo_ani.update();
					a_ani.update();
					cir_ani.update();
					winW = GetScreenWidth();
					winH = GetScreenHeight();
					int k=min(int(winW*0.1),int(80*dpi));
					if(clock()-_time<0){
						BeginDrawing();
						ClearBackground(BgColor);
						Logo logo;
						logo.ftcolor=LIGHTGRAY;
						logo.bgcolor=BgColor;
						logo.Draw(winW/2-k,winH/2-k,k*2,k*2);
					} else {
						real a=(300-(clock()-_time))/300.0;
						BeginDrawing();
						ClearBackground(BgColor);
						Logo logo;
						logo.ftcolor.r=200*a+BgColor.r*(1-a);
						logo.ftcolor.g=200*a+BgColor.g*(1-a);
						logo.ftcolor.b=200*a+BgColor.b*(1-a);
						logo.bgcolor=BgColor;
						logo.Draw(winW/2-k,winH/2-k+logo_ani.gnp()*(winH*0.5+winW*0.1),k*2,k*2);
					}
					Color c=BgColor;
					c.a=a_ani.gnp();
					special_effect::DrawLoadingCircle(winW/2,winH*4/5+cir_ani.gnp()*(winH*0.5+winW*0.1),k/5);
					DrawRectangle(0,0,winW,winH,c);
					EndDrawing();
					if(WindowShouldClose()) {
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
			special_effect::Draw();
			winW = GetScreenWidth();
			winH = GetScreenHeight();
			Mouse = GetMousePosition();
			MouseXAni.update();
			MouseYAni.update();
			MouseXAni.stp(Mouse.x);
			MouseYAni.stp(Mouse.y);
			MouseShadow.x=MouseXAni.gnp();
			MouseShadow.y=MouseYAni.gnp();
			
			int key = GetCharPressed();
			GetChar = key;
#ifdef USE_CHINESE_INPUT
			GetCharString = "";
			while (key>0) {
				GetCharString+=to_utf8::GetChar(key);
				key = GetCharPressed();
			}
#else
			GetCharString=" ";
			GetCharString[0]=key;
#endif
			
			UseSliderX=false;
			UseSliderY=false;
			MainSystem.Update();
			message::Draw();
			mainwin.SetPos(0, 0, winW, winH);
			mainwin.priority = 0;
			if(MouseCursorStyle>=0) {
				ShowCursor();
				SetMouseCursor(MouseCursorStyle);
			}
			else HideCursor();
			MouseCursorStyle = MOUSE_CURSOR_ARROW;
		}
		void Run(void (*script)() = nullptr) {
			while (!WindowShouldClose()) {
				BeginDrawing();
				//rlViewport(0,0,ui::winW,ui::winH);
				ClearBackground(ui::BgColor);
				ui::Update();
				special_effect::Draw();
				if (script != nullptr)script();
				tick++;
				EndDrawing();
			}
			Running=true;
		}
		
	}
	
}

#endif
