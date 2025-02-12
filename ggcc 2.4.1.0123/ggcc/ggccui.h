// ggccui.h
// ggcc用户界面库（调试器风格）（raylib）

#pragma once
// #pragma warning(disable: 4996)
// 以下是当前版本号
#define UIVer "GGCC UI 2.4.1.0123"

#include <raylib.h>
#include <rlgl.h>
#include "animation.h"
#include "math/geometry.h"
#include "math/evaluate.h"
#include "word_process.h"
#include "ggccalgo.h"

#include <vector>
#include <stack>
#include <map>
#include <functional>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>

#define	ALICEBLUE              CLITERAL(Color){ 0xF0, 0xF8, 0xFF, 255 }
#define	ANTIQUEWHITE           CLITERAL(Color){ 0xFA, 0xEB, 0xD7, 255 }
#define	AQUA                   CLITERAL(Color){ 0x00, 0xFF, 0xFF, 255 }
#define	AQUAMARINE             CLITERAL(Color){ 0x7F, 0xFF, 0xD4, 255 }
#define	AZURE                  CLITERAL(Color){ 0xF0, 0xFF, 0xFF, 255 }
#define	BISQUE                 CLITERAL(Color){ 0xFF, 0xE4, 0xC4, 255 }
#define	BLANCHEDALMOND         CLITERAL(Color){ 0xFF, 0xEB, 0xCD, 255 }
#define	BLUEVIOLET             CLITERAL(Color){ 0x8A, 0x2B, 0xE2, 255 }
#define	BURLYWOOD              CLITERAL(Color){ 0xDE, 0xB8, 0x87, 255 }
#define	CADETBLUE              CLITERAL(Color){ 0x5F, 0x9E, 0xA0, 255 }
#define	CHARTREUSE             CLITERAL(Color){ 0x7F, 0xFF, 0x00, 255 }
#define	CHOCOLATE              CLITERAL(Color){ 0xD2, 0x69, 0x1E, 255 }
#define	CORAL                  CLITERAL(Color){ 0xFF, 0x7F, 0x50, 255 }
#define	CORNFLOWERBLUE         CLITERAL(Color){ 0x64, 0x95, 0xED, 255 }
#define	CORNSILK               CLITERAL(Color){ 0xFF, 0xF8, 0xDC, 255 }
#define	CRIMSON                CLITERAL(Color){ 0xDC, 0x14, 0x3C, 255 }
#define	CYAN                   CLITERAL(Color){ 0x00, 0xFF, 0xFF, 255 }
#define	DARKCYAN               CLITERAL(Color){ 0x00, 0x8B, 0x8B, 255 }
#define	DARKGOLDENROD          CLITERAL(Color){ 0xB8, 0x86, 0x0B, 255 }
#define	DARKKHAKI              CLITERAL(Color){ 0xBD, 0xB7, 0x6B, 255 }
#define	DARKMAGENTA            CLITERAL(Color){ 0x8B, 0x00, 0x8B, 255 }
#define	DARKOLIVEGREEN         CLITERAL(Color){ 0x55, 0x6B, 0x2F, 255 }
#define	DARKORANGE             CLITERAL(Color){ 0xFF, 0x8C, 0x00, 255 }
#define	DARKORCHID             CLITERAL(Color){ 0x99, 0x32, 0xCC, 255 }
#define	DARKRED                CLITERAL(Color){ 0x8B, 0x00, 0x00, 255 }
#define	DARKSALMON             CLITERAL(Color){ 0xE9, 0x96, 0x7A, 255 }
#define	DARKSEAGREEN           CLITERAL(Color){ 0x8F, 0xBC, 0x8F, 255 }
#define	DARKSLATEBLUE          CLITERAL(Color){ 0x48, 0x3D, 0x8B, 255 }
#define	DARKSLATEGRAY          CLITERAL(Color){ 0x2F, 0x4F, 0x4F, 255 }
#define	DARKTURQUOISE          CLITERAL(Color){ 0x00, 0xCE, 0xD1, 255 }
#define	DARKVIOLET             CLITERAL(Color){ 0x94, 0x00, 0xD3, 255 }
#define	DEEPPINK               CLITERAL(Color){ 0xFF, 0x14, 0x93, 255 }
#define	DEEPSKYBLUE            CLITERAL(Color){ 0x00, 0xBF, 0xFF, 255 }
#define	DIMGRAY                CLITERAL(Color){ 0x69, 0x69, 0x69, 255 }
#define	DODGERBLUE             CLITERAL(Color){ 0x1E, 0x90, 0xFF, 255 }
#define	FIREBRICK              CLITERAL(Color){ 0xB2, 0x22, 0x22, 255 }
#define	FLORALWHITE            CLITERAL(Color){ 0xFF, 0xFA, 0xF0, 255 }
#define	FORESTGREEN            CLITERAL(Color){ 0x22, 0x8B, 0x22, 255 }
#define	FUCHSIA                CLITERAL(Color){ 0xFF, 0x00, 0xFF, 255 }
#define	GAINSBORO              CLITERAL(Color){ 0xDC, 0xDC, 0xDC, 255 }
#define	GHOSTWHITE             CLITERAL(Color){ 0xF8, 0xF8, 0xFF, 255 }
#define	GOLDENROD              CLITERAL(Color){ 0xDA, 0xA5, 0x20, 255 }
#define	GREENYELLOW            CLITERAL(Color){ 0xAD, 0xFF, 0x2F, 255 }
#define	HONEYDEW               CLITERAL(Color){ 0xF0, 0xFF, 0xF0, 255 }
#define	HOTPINK                CLITERAL(Color){ 0xFF, 0x69, 0xB4, 255 }
#define	INDIANRED              CLITERAL(Color){ 0xCD, 0x5C, 0x5C, 255 }
#define	INDIGO                 CLITERAL(Color){ 0x4B, 0x00, 0x82, 255 }
#define	IVORY                  CLITERAL(Color){ 0xFF, 0xFF, 0xF0, 255 }
#define	KHAKI                  CLITERAL(Color){ 0xF0, 0xE6, 0x8C, 255 }
#define	LAVENDER               CLITERAL(Color){ 0xE6, 0xE6, 0xFA, 255 }
#define	LAVENDERBLUSH          CLITERAL(Color){ 0xFF, 0xF0, 0xF5, 255 }
#define	LAWNGREEN              CLITERAL(Color){ 0x7C, 0xFC, 0x00, 255 }
#define	LEMONCHIFFON           CLITERAL(Color){ 0xFF, 0xFA, 0xCD, 255 }
#define	LIGHTBLUE              CLITERAL(Color){ 0xAD, 0xD8, 0xE6, 255 }
#define	LIGHTCORAL             CLITERAL(Color){ 0xF0, 0x80, 0x80, 255 }
#define	LIGHTCYAN              CLITERAL(Color){ 0xE0, 0xFF, 0xFF, 255 }
#define	LIGHTGOLDENRODYELLOW   CLITERAL(Color){ 0xFA, 0xFA, 0xD2, 255 }
#define	LIGHTGREEN             CLITERAL(Color){ 0x90, 0xEE, 0x90, 255 }
#define	LIGHTPINK              CLITERAL(Color){ 0xFF, 0xB6, 0xC1, 255 }
#define	LIGHTSALMON            CLITERAL(Color){ 0xFF, 0xA0, 0x7A, 255 }
#define	LIGHTSEAGREEN          CLITERAL(Color){ 0x20, 0xB2, 0xAA, 255 }
#define	LIGHTSKYBLUE           CLITERAL(Color){ 0x87, 0xCE, 0xFA, 255 }
#define	LIGHTSLATEGRAY         CLITERAL(Color){ 0x77, 0x88, 0x99, 255 }
#define	LIGHTSTEELBLUE         CLITERAL(Color){ 0xB0, 0xC4, 0xDE, 255 }
#define	LIGHTYELLOW            CLITERAL(Color){ 0xFF, 0xFF, 0xE0, 255 }
#define	LIGHTRED               CLITERAL(Color){ 0xFC, 0x54, 0x54, 255 }
#define	LIGHTMAGENTA           CLITERAL(Color){ 0xFC, 0x54, 0xFC, 255 }
#define	LIMEGREEN              CLITERAL(Color){ 0x32, 0xCD, 0x32, 255 }
#define	LINEN                  CLITERAL(Color){ 0xFA, 0xF0, 0xE6, 255 }
#define	MEDIUMAQUAMARINE       CLITERAL(Color){ 0x66, 0xCD, 0xAA, 255 }
#define	MEDIUMBLUE             CLITERAL(Color){ 0x00, 0x00, 0xCD, 255 }
#define	MEDIUMORCHID           CLITERAL(Color){ 0xBA, 0x55, 0xD3, 255 }
#define	MEDIUMPURPLE           CLITERAL(Color){ 0x93, 0x70, 0xDB, 255 }
#define	MEDIUMSEAGREEN         CLITERAL(Color){ 0x3C, 0xB3, 0x71, 255 }
#define	MEDIUMSLATEBLUE        CLITERAL(Color){ 0x7B, 0x68, 0xEE, 255 }
#define	MEDIUMSPRINGGREEN      CLITERAL(Color){ 0x00, 0xFA, 0x9A, 255 }
#define	MEDIUMTURQUOISE        CLITERAL(Color){ 0x48, 0xD1, 0xCC, 255 }
#define	MEDIUMVIOLETRED        CLITERAL(Color){ 0xC7, 0x15, 0x85, 255 }
#define	MIDNIGHTBLUE           CLITERAL(Color){ 0x19, 0x19, 0x70, 255 }
#define	MINTCREAM              CLITERAL(Color){ 0xF5, 0xFF, 0xFA, 255 }
#define	MISTYROSE              CLITERAL(Color){ 0xFF, 0xE4, 0xE1, 255 }
#define	MOCCASIN               CLITERAL(Color){ 0xFF, 0xE4, 0xB5, 255 }
#define	NAVAJOWHITE            CLITERAL(Color){ 0xFF, 0xDE, 0xAD, 255 }
#define	NAVY                   CLITERAL(Color){ 0x00, 0x00, 0x80, 255 }
#define	OLDLACE                CLITERAL(Color){ 0xFD, 0xF5, 0xE6, 255 }
#define	OLIVE                  CLITERAL(Color){ 0x80, 0x80, 0x00, 255 }
#define	OLIVEDRAB              CLITERAL(Color){ 0x6B, 0x8E, 0x23, 255 }
#define	ORANGERED              CLITERAL(Color){ 0xFF, 0x45, 0x00, 255 }
#define	ORCHID                 CLITERAL(Color){ 0xDA, 0x70, 0xD6, 255 }
#define	PALEGOLDENROD          CLITERAL(Color){ 0xEE, 0xE8, 0xAA, 255 }
#define	PALEGREEN              CLITERAL(Color){ 0x98, 0xFB, 0x98, 255 }
#define	PALETURQUOISE          CLITERAL(Color){ 0xAF, 0xEE, 0xEE, 255 }
#define	PALEVIOLETRED          CLITERAL(Color){ 0xDB, 0x70, 0x93, 255 }
#define	PAPAYAWHIP             CLITERAL(Color){ 0xFF, 0xEF, 0xD5, 255 }
#define	PEACHPUFF              CLITERAL(Color){ 0xFF, 0xDA, 0xB9, 255 }
#define	PERU                   CLITERAL(Color){ 0xCD, 0x85, 0x3F, 255 }
#define	PLUM                   CLITERAL(Color){ 0xDD, 0xA0, 0xDD, 255 }
#define	POWDERBLUE             CLITERAL(Color){ 0xB0, 0xE0, 0xE6, 255 }
#define	ROSYBROWN              CLITERAL(Color){ 0xBC, 0x8F, 0x8F, 255 }
#define	ROYALBLUE              CLITERAL(Color){ 0x41, 0x69, 0xE1, 255 }
#define	SADDLEBROWN            CLITERAL(Color){ 0x8B, 0x45, 0x13, 255 }
#define	SALMON                 CLITERAL(Color){ 0xFA, 0x80, 0x72, 255 }
#define	SANDYBROWN             CLITERAL(Color){ 0xF4, 0xA4, 0x60, 255 }
#define	SEAGREEN               CLITERAL(Color){ 0x2E, 0x8B, 0x57, 255 }
#define	SEASHELL               CLITERAL(Color){ 0xFF, 0xF5, 0xEE, 255 }
#define	SIENNA                 CLITERAL(Color){ 0xA0, 0x52, 0x2D, 255 }
#define	SILVER                 CLITERAL(Color){ 0xC0, 0xC0, 0xC0, 255 }
#define	SLATEBLUE              CLITERAL(Color){ 0x6A, 0x5A, 0xCD, 255 }
#define	SLATEGRAY              CLITERAL(Color){ 0x70, 0x80, 0x90, 255 }
#define	SNOW                   CLITERAL(Color){ 0xFF, 0xFA, 0xFA, 255 }
#define	SPRINGGREEN            CLITERAL(Color){ 0x00, 0xFF, 0x7F, 255 }
#define	STEELBLUE              CLITERAL(Color){ 0x46, 0x82, 0xB4, 255 }
#define	TAN                    CLITERAL(Color){ 0xD2, 0xB4, 0x8C, 255 }
#define	TEAL                   CLITERAL(Color){ 0x00, 0x80, 0x80, 255 }
#define	THISTLE                CLITERAL(Color){ 0xD8, 0xBF, 0xD8, 255 }
#define	TOMATO                 CLITERAL(Color){ 0xFF, 0x63, 0x47, 255 }
#define	TURQUOISE              CLITERAL(Color){ 0x40, 0xE0, 0xD0, 255 }
#define	WHEAT                  CLITERAL(Color){ 0xF5, 0xDE, 0xB3, 255 }
#define	WHITESMOKE             CLITERAL(Color){ 0xF5, 0xF5, 0xF5, 255 }
#define	YELLOWGREEN            CLITERAL(Color){ 0x9A, 0xCD, 0x32, 255 }
#define STD_LIGHTGRAY 		CLITERAL(Color){ 0xD3, 0xD3, 0xD3, 255 }   // Light Gray
#define STD_GRAY      		CLITERAL(Color){ 130, 130, 130, 255 }   // Gray
#define STD_DARKGRAY  		CLITERAL(Color){ 80, 80, 80, 255 }      // Dark Gray
#define STD_YELLOW    		CLITERAL(Color){ 0xFF, 0xFF, 0, 255 }     // Yellow
#define STD_GOLD      		CLITERAL(Color){ 255, 203, 0, 255 }     // Gold
#define STD_ORANGE    		CLITERAL(Color){ 0xFF, 0xA5, 0, 255 }     // Orange
#define STD_PINK      		CLITERAL(Color){ 255, 109, 194, 255 }   // Pink
#define STD_RED       		CLITERAL(Color){ 0xFF, 0x00, 0x00, 255 }     // Red
#define STD_MAROON    		CLITERAL(Color){ 190, 33, 55, 255 }     // Maroon
#define STD_GREEN     		CLITERAL(Color){ 0, 228, 48, 255 }      // Green
#define STD_LIME      		CLITERAL(Color){ 0, 158, 47, 255 }      // Lime
#define STD_DARKGREEN 		CLITERAL(Color){ 0, 117, 44, 255 }      // Dark Green
#define STD_SKYBLUE   		CLITERAL(Color){ 0x87, 0xCE, 0xEB, 255 }   // Sky Blue
#define STD_BLUE      		CLITERAL(Color){ 0, 121, 241, 255 }     // Blue
#define STD_DARKBLUE  		CLITERAL(Color){ 0, 82, 172, 255 }      // Dark Blue
#define STD_PURPLE    		CLITERAL(Color){ 200, 122, 255, 255 }   // Purple
#define STD_VIOLET    		CLITERAL(Color){ 135, 60, 190, 255 }    // Violet
#define STD_DARKPURPLE		CLITERAL(Color){ 112, 31, 126, 255 }    // Dark Purple
#define STD_BEIGE     		CLITERAL(Color){ 211, 176, 131, 255 }   // Beige
#define STD_BROWN     		CLITERAL(Color){ 127, 106, 79, 255 }    // Brown
#define STD_DARKBROWN 		CLITERAL(Color){ 76, 63, 47, 255 }      // Dark Brown

// 颜色辅助功能
bool operator ==(const Color& a, const Color& b) {
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
bool operator !=(const Color& a, const Color& b) {
	return a.r != b.r || a.g != b.g || a.b != b.b || a.a == b.a;
}
Color operator +(const Color& a, const Color& b) {
	return Color {
		(unsigned char)(a.r + b.r),
		(unsigned char)(a.g + b.g),
		(unsigned char)(a.b + b.b),
		a.a
	};
}
Color operator *(const Color& a, const float& b) {
	return Color {
		(unsigned char)round(a.r * b),
		(unsigned char)round(a.g * b),
		(unsigned char)round(a.b * b),
		a.a
	};
}
Color operator * (const float& b, const Color& a) {
	return Color {
		(unsigned char)round(a.r * b),
		(unsigned char)round(a.g * b),
		(unsigned char)round(a.b * b),
		a.a
	};
}

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
		enum InputBoxOperation {
			operation_insert = 0,
			operation_delete = 1,
			operation_swap = 2
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
		int winW;										// 窗口宽
		int winH;										// 窗口高
		Vector2 Mouse;									// 鼠标位置
		Vector2 MouseShadow;							// 鼠标残影位置
		Vector2 WindowPos;								// 窗口位置
		Vector2 WindowSize;								// 窗口大小
		Vector2 LastWindowPos;							// 上次窗口位置
		Vector2 LastWindowSize;							// 上次更新时窗口大小
		WinState WindowState;							// 窗口状态
		char GetChar = 0;								// 字符输入
		std::string GetCharString = "";					// 字符输入
		int MouseCursorStyle = MOUSE_CURSOR_ARROW;		// 鼠标样式
		bool AutoPage = true;							// 是否开启自动添加至主界面
		bool DrawSpecialEffect = true;					// 是否开启特效
		bool DebugMode = false;							// 是否开启调试模式
		bool StartAni = false;							// 是否开启启动动画
		bool Running = true;							// 程序是否在运行
		bool UseSliderX = false;						// 是否有Slider正在使用
		bool UseSliderY = false;						// 是否有Slider正在使用
		bool PrintChecking = true;						// 打印检查
		bool FasterInput = false;						// 是否启用英文高速键入
		bool RepetitivenessCheck = false;				// 控件绘制重复性检查
		bool AlphaModeEnable = true;					// 是否允许透明模式
		bool InitFinished = false;						// 是否已经初始化
		bool MouseEventLock = false;					// 是否关闭鼠标事件检测
		bool EnableRaylibLog = false;					// 是否启用raylib日志
		bool DocumentMode = false;						// 是否启用文档模式
		realn dpi = 1.0;								// dpi
		Animation MouseXAni, MouseYAni;					// 鼠标阴影动画

		// 配色方案
		unsigned rgb(int r, int g, int b) {
			return 0xff000000 | (r << 16) | (g << 8) | b;
		}
		unsigned argb(int a, int r, int g, int b) {
			return (a << 24) | (r << 16) | (g << 8) | b;
		}
		struct ColorScheme {
			unsigned theme;			// 主题色
			unsigned main;			// 主要色
			unsigned bg;			// 背景色
			unsigned highlight;		// 强调色
			unsigned content;		// 内容字体色
			unsigned line;			// 分割线颜色
			// 窗口
			struct window {
				unsigned titleBg;	// 窗口标题背景色
				unsigned titleFg;	// 窗口标题前景色
			};
			// 场景
			struct scene {
				unsigned mesh;		// 网络
				unsigned axis;		// 坐标轴
				unsigned line;		// 线条默认色彩
			};
			// 单元格
			struct unit {
				unsigned bg;		// 背景色
				unsigned text;		// 文本色
			};
			// 菜单栏
			struct menu {
				unsigned bg;		// 菜单颜色
				unsigned text;		// 文本色
			};
		};
		Color ThemeColor = BLUE;						// 主题色
		Color MainColor = Color {43, 74, 121, 255};		// 主要色
		Color UnitBgColor = Color {43, 74, 121, 150};	// 单元格背景色
		Color ChooseColor = Color {128, 128, 128, 70};	// 选择背景色
		Color BgColor = Color {32, 32, 32, 255};		// 背景色
		Color TextColor = WHITE;						// 字体色
		Color TextColor2 = LIGHTGRAY;					// 辅助字体色
		Color LineColor = DARKGRAY;						// 分割线颜色
		Color MenuColor = Color {50, 50, 50, 255};		// 菜单颜色
		Color MenuFtColor = WHITE;						// 菜单字体颜色

		// 字体相关定义
		Font font;										// 字体
		Font IconFont;									// 图标字体
		Font EmojiFont;									// Emoji字体
		std::string FontName = "微软雅黑";				// 字体
		int CharactorLoadMaximum = 300;					// 最大加载字体长度
		wp::TextBuffer UseCharacter{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;\':\",./<>?"};
		wp::TextBuffer UseIcon{" "};
		wp::TextBuffer UseEmoji{" "};

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
		class Slider;									// 拉动条
		class Slider_Int;								// 拉动条(整型)
		class Switch;									// 开关
		class Choose;									// 选择框
		class Collapse;									// 折叠面板
		class Page;										// 界面
		class InputBox;									// 输入框
		class CheckBox;									// 复选框
		class Scene;									// 图形调试器
		class Scene3D;									// 3D图形调试器
		class Free;										// 自由界面
		class System;									// 系统
		class Window;									// 窗口
		class SiderManager;								// 侧边栏管理器
		class Priority;									// 优先级处理方法
		class Layout;									// 布局
		class Navigation;								// 导航目录
		Element* ChooseInputBox = nullptr;				// 选择的输入框
		Slider* ChooseSlider = nullptr;					// 选择的拉动条

		void BeginScissor(float x, float y, float w, float h);
		void GetScissor(float* x, float* y, float* w, float* h);
		bool InScissor(float x, float y, float w, float h);
		bool InScissor(float x, float y);
		void EndScissor();
		void BeginAlphaMode(realn alpha);
		void EndAlphaMode();
		realn GetAlpha();

		// 附属功能
		// 自动释放函数
		typedef void (*ReleaseFunc)(Element* ele);
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
					key_down_time[key] = gclock();
					key_down_tick[key] = tick;
				} else if (key_state[key] == 1) {
					if (gclock() - key_down_time[key] > 500) {
						key_state[key] = 2, input = true;
						key_down_time[key] = gclock();
						key_down_tick[key] = tick;
					}
				} else {
					if (gclock() - key_down_time[key] > 30) {
						key_state[key] = 2, input = true;
						key_down_time[key] = gclock();
						key_down_tick[key] = tick;
					}
				}
			} else key_state[key] = 0;
			return input;
		}
		// 鼠标输入功能
		std::map <int, short> mouse_state;
		std::map <int, int> mouse_down_time;
		bool IsMousePressed(int mouse) {
			return IsMouseButtonPressed(mouse) && !MouseEventLock;
		}
		bool IsMouseReleased(int mouse) {
			return IsMouseButtonReleased(mouse) && !MouseEventLock;
		}
		bool IsMouseDown(int mouse) {
			return IsMouseButtonDown(mouse) && !MouseEventLock;
		}
		bool IsMouseInput(int mouse) {
			bool input = false;
			if (IsMouseDown(mouse)) {
				if (mouse_state[mouse] == 0) {
					mouse_state[mouse] = 1, input = true;
					mouse_down_time[mouse] = gclock();
				} else if (mouse_state[mouse] == 1) {
					if (gclock() - mouse_down_time[mouse] > 500) {
						mouse_state[mouse] = 2, input = true;
						mouse_down_time[mouse] = gclock();
					}
				} else {
					if (gclock() - mouse_down_time[mouse] > 30) {
						mouse_state[mouse] = 2, input = true;
						mouse_down_time[mouse] = gclock();
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
				std::string text = "DEEP=" + wp::tostr(ScissorDeep) + ",SIZE=" + wp::tostr(vector2d(aw, ah));
				DrawRectangle(ax, ay, aw, ah, Fade(RED, 0.02));
				Print(
				    ax + aw / 2 - text.size() * TextHeight / 4,
				    ay + ah / 2 - TextHeight / 2 + UnitHeight * (ScissorDeep - 1),
				    text, BLUE
				);
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
			if (alpha < 0)alpha = 0;
			if (alpha > 1)alpha = 1;
			if (AlphaDeep == 0)AlphaStack.push(alpha);
			else AlphaStack.push(alpha * AlphaStack.top());
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
			if (!AlphaModeEnable)return 1;
			if (Alpha > 1)Alpha = 1;
			if (Alpha < 0)Alpha = 0;
			return Alpha;
		}
		int Char2Int(char a) {
			if (isalpha(a))return a - 'A' + 10;
			return a - '0';
		}
		inline unsigned Color2Int(Color color) {
			return ((unsigned)color.a << 24) | ((unsigned)color.r << 16) | ((unsigned)color.g << 8) | (unsigned)color.b;
		}
		template <typename T, typename T2>
		Color ColorF(T r, T g, T b, T2 a) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(a * GetAlpha())};
		}
		template <typename T>
		Color ColorF(T r, T g, T b) {
			return Color{(unsigned char)(r), (unsigned char)(g), (unsigned char)(b), (unsigned char)(255 * GetAlpha())};
		}
		Color ColorF(Color color) {
			return Color{(unsigned char)(color.r), (unsigned char)(color.g), (unsigned char)(color.b), (unsigned char)(color.a * GetAlpha())};
		}
		Color ColorF(unsigned color) {
			return Color{
				(unsigned char)(((unsigned)color & 0x00ff0000) >> 16),
				(unsigned char)(((unsigned)color & 0x0000ff00) >> 8),
				(unsigned char)((unsigned)color & 0x000000ff),
				(unsigned char)(((unsigned)color & 0xff000000) >> 24)
			};
		}
		Color ColorF(Color color, realn a) {
			return Color{(unsigned char)(color.r), (unsigned char)(color.g), (unsigned char)(color.b), (unsigned char)(color.a*a * GetAlpha())};
		}
		Color ColorF(unsigned color, realn a) {
			return ColorF(ColorF(color), a);
		}
		Color ColorF(std::string str) {
			if (str.size() == 7) {
				int r = (Char2Int(str[1]) << 4) | Char2Int(str[2]);
				int g = (Char2Int(str[3]) << 4) | Char2Int(str[4]);
				int b = (Char2Int(str[5]) << 4) | Char2Int(str[6]);
				return Color {(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
			}
			return WHITE;
		}
		Color MixColor(Color c1, Color c2, realn k) {
			if (k > 1)k = 1;
			if (k < 0)k = 0;
			return Color{
				(unsigned char)(c1.r * k + c2.r * (1.0 - k)),
				(unsigned char)(c1.g * k + c2.g * (1.0 - k)),
				(unsigned char)(c1.b * k + c2.b * (1.0 - k)),
				(unsigned char)255
			};
		}
		Color RandColor() {
			return ColorF(rand() % 256, rand() % 256, rand() % 256);
		}
		// 其他功能
		bool operator ==(const Vector2& a, const Vector2& b) {
			return a.x == b.x && a.y == b.y;
		}
		bool operator ==(const Vector3& a, const Vector3& b) {
			return a.x == b.x && a.y == b.y && a.z == b.z;
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
		// 坐标转换相关函数
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
			return vector2d(v.x * cos(v.y), v.x * sin(v.y));
		}
		vector2d get_rel(vector2d p, vector2d rfrc, realn rotate) {
			return p.Rotate(rotate) + rfrc;
		}
		vector2d get_rel(vector2d p, vector2d rfrc, vector2d dir) {
			return p.Rotate(atan2(dir.y, dir.x)) + rfrc;
		}
		// 输出相关功能
		void LoadIcon(Font* font, std::string str, int size) {
			int fileSize;
			unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\segmdl2.ttf", &fileSize);
			int codepointsCount;
			int *codepoints = LoadCodepoints((str + std::string(u8"")).c_str(), &codepointsCount);
			(*font) = LoadFontFromMemory(".ttf", fontFileData, fileSize, size, codepoints, codepointsCount);
			UnloadCodepoints(codepoints);
			UnloadFileData(fontFileData);
		}
		void PrintIcon(int x, int y, std::string text, Color color = ui::TextColor, Font* font = &IconFont, int size = ui::TextHeight) {
			if (PrintChecking)UseIcon.Check(text);
			DrawTextEx((*font), text.c_str(), Vector2 {(float)x, (float)y}, size, 0, ColorF(color));
		}
		void PrintEmoji(int x, int y, std::string text, Color color = ui::TextColor, Font* font = &EmojiFont, int size = ui::TextHeight) {
			if (PrintChecking)UseEmoji.Check(text);
			DrawTextEx((*font), text.c_str(), Vector2 {(float)x, (float)y}, size, 0, ColorF(color));
		}
		void Print(int x, int y, std::string text, Color color = TextColor2) {
			if (PrintChecking)UseCharacter.Check(text);
			DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, ColorF(color));
		}
		void Print_All(int x, int y, std::string text, Color color = TextColor2) {
			if (PrintChecking)UseCharacter.Check(text);
			if (wp::IsIcon(text)) {
				PrintIcon(x, y, text, color, &IconFont, TextHeight);
			} else if (wp::IsEmoji(text)) {
				PrintEmoji(x, y, text, color, &IconFont, TextHeight);
			} else {
				DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, ColorF(color));
			}
		}
		void Print_All_String(int x, int y, std::string text, Color color = TextColor2) {
			if (PrintChecking)UseCharacter.Check(text);
			int width = 0;
			for (int i = 0; i < text.size();) {
				int s = wp::GetNextCharacter(text, i);
				std::string one = text.substr(i, s);
				int w = wp::strLen(one);
				Print_All(x + width, y, one, color);
				i += s;
				width += w * ui::TextHeight / 2;
			}
		}
		void Print_Format(int x, int y, std::string text, int startx = 0, Color color = TextColor2) {
			if (PrintChecking)UseCharacter.Check(text);
			std::string text2;
			int j = startx;
			for (int i = 0; i < text.size(); i++) {
				if (text[i] == '\t') {
					int count = 4 - j % 4;
					if (count == 1)text2 += " ", j += 1;
					if (count == 2)text2 += "  ", j += 2;
					if (count == 3)text2 += "   ", j += 3;
					if (count == 4)text2 += "    ", j += 4;
				} else text2 += text[i], j++;
			}
			if (wp::IsIcon(text)) {
				PrintIcon(x, y, text, color, &IconFont, TextHeight);
			}
			DrawTextEx(font, text2.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, ColorF(color));
		}
		void Print_withoutCheck(int x, int y, std::string text, Color color = TextColor2) {
			std::string text2;
			int j = 0;
			for (int i = 0; i < text.size(); i++) {
				if (text[i] == '\t') {
					int count = 4 - j % 4;
					if (count == 1)text2 += " ", j += 1;
					if (count == 2)text2 += "  ", j += 2;
					if (count == 3)text2 += "   ", j += 3;
					if (count == 4)text2 += "    ", j += 4;
				} else text2 += text[i], j++;
			}
			DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, TextHeight, 0, ColorF(color));
		}
		void PrintMiddle(int x, int y, std::string text, Color color = TextColor2) {
			Print(x - wp::strLen(text)*TextHeight / 4, y - TextHeight / 2, text, color);
		}
		void PrintMiddle(int x, int y, int w, int h, std::string text, Color color = TextColor2) {
			PrintMiddle(x + w / 2, y + h / 2, text, color);
		}
		int PrintRect(int x, int y, int w, std::string text, Color color = TextColor2) {
			if (w < ui::TextHeight) return 1;
			int len = 0, last = 0, line = 0;
			int h = (UnitHeight - TextHeight) / 2;
			for (int i = 0; i < text.size(); i++) {
				int j = i, temp = 0;
				if ((text[i] & 0xE0) == 0xE0)temp = 2, len += 2, i += 2;
				else if (text[i] == '\n' && len * ui::TextHeight / 2 <= w) {
					Print(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight + ui::SpaceSize;
					len = 0;
					line++;
					last = i + 1;
				} else temp = 1, len++;
				if (len * ui::TextHeight / 2 > w) {
					Print(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight + ui::SpaceSize;
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
		int PrintRect_withoutCheck(int x, int y, int w, std::string text, Color color = TextColor2) {
			if (w < ui::TextHeight)return ui::UnitHeight;
			int len = 0, last = 0, line = 0;
			int h = (UnitHeight - TextHeight) / 2;
			for (int i = 0; i < text.size(); i++) {
				int j = i, temp = 0;
				if ((text[i] & 0xE0) == 0xE0)temp = 2, len += 2, i += 2;
				else if (text[i] == '\n' && len * ui::TextHeight / 2 <= w) {
					Print_withoutCheck(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight;
					len = 0;
					line++;
					last = i + 1;
				} else temp = 1, len++;
				if (len * ui::TextHeight / 2 > w) {
					Print_withoutCheck(x, y + h, text.substr(last, j - last), ColorF(color));
					y += ui::UnitHeight;
					len = temp;
					if (temp == 1)last = i;
					if (temp == 2)last = i - 2;
					line++;
				}
			}
			if (last != text.size()) {
				Print_withoutCheck(x, y + h, text.substr(last), ColorF(color));
				line++;
			}
			return line;
		}
		int GetPrintRectLine(int x, int y, int w, std::string text) {
			if (w < TextHeight)return ui::UnitHeight;
			int len = 0, last = 0, line = 0;
			int h = (UnitHeight - TextHeight) / 2;
			for (int i = 0; i < text.size(); i++) {
				int j = i, temp = 0;
				if ((text[i] & 0xE0) == 0xE0)temp = 2, len += 2, i += 2;
				else if (text[i] == '\n' && len * TextHeight / 2 <= w) {
					y += UnitHeight;
					len = 0;
					line++;
					last = i + 1;
				} else temp = 1, len++;
				if (len * TextHeight / 2 > w) {
					y += UnitHeight;
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
		vector2d GetPrintRectSize(int x, int y, int w, std::string text) {
			int h = GetPrintRectLine(x, y, w, text);
			if (h == 1) return vector2d(wp::strLen(text) * TextHeight / 2, UnitHeight);
			else return vector2d(w, h * (UnitHeight + SpaceSize) - SpaceSize);
		}
		void PrintUsedCharacter() {
			int h = GetPrintRectLine(0, winH, winW, UseCharacter.Text());
			DrawRectangle(0, winH - UnitHeight * (h + 1), winW, UnitHeight * (h + 1), ColorF(0, 0, 0, 150));
			PrintRect_withoutCheck(0, winH - UnitHeight * h, winW, UseCharacter.Text());
			std::stringstream ss;
			ss << "已加载的字体: (" << UseCharacter.Text().size() << "/" << UseCharacter.GetMaximum() << ")";
			Print(0, winH - UnitHeight * (h + 1), ss.str(), ThemeColor);
		}
		bool MouseInRect(realn x1, realn y1, realn w, realn h) {
			realn x2 = x1 + w, y2 = y1 + h;
			if (Mouse.x >= x1 && Mouse.x < x2 && Mouse.y >= y1 && Mouse.y < y2)return true;
			return false;
		}
		bool MouseInCircle(realn x, realn y, realn r) {
			realn dx = Mouse.x - x, dy = Mouse.y - y;
			if (dx * dx + dy * dy <= r * r)return true;
			return false;
		}

		// 代码高亮功能
		namespace highlight {

			enum Type {
				Type_Default = 0,			//编辑器默认
				Type_Gutter = 1,			//行号
				Type_Gutter_AL = 2,			//当前行号
				Type_Comment = 3,			//注释
				Type_Symbol = 4,			//符号
				Type_Bracket_L1 = 5,		//1级括号
				Type_Bracket_L2 = 6,		//2级括号
				Type_Bracket_L3 = 7,		//3级括号
				Type_Bracket_L4 = 8,		//4级括号
				Type_Number = 9,			//数字
				Type_Preprocessor = 10,		//预处理指令
				Type_Character = 11,		//字符
				Type_String = 12,			//字符串
				Type_EscapeSequences = 13,	//转义序列
				Type_ReservedWord = 14,		//关键字
				Type_ReservedWord_T = 15,	//类型关键字
				Type_Function = 16,			//函数
				Type_Variable = 17,			//变量
				Type_Variable_G = 18,		//全局变量
				Type_Variable_L = 19		//局部变量
			};

			Color color_default[20] = {
				TextColor2,					//编辑器默认
				Color{ 73,  81,  98, 255},	//行号
				Color{171, 178, 191, 255},	//当前行号
				TextColor2,					//注释
				TextColor2,					//符号
				TextColor2,					//1级括括号
				TextColor2,					//2级括括号
				TextColor2,					//3级括括号
				TextColor2,					//4级括括号
				TextColor2,					//数字
				TextColor2,					//预处理指令
				TextColor2,					//字符
				TextColor2,					//字符串
				TextColor2,					//转义序列0x06
				TextColor2,					//关键字
				TextColor2,					//类型关键字
				TextColor2,					//函数
				TextColor2,					//变量
				TextColor2,					//全局变量
				TextColor2					//局部变量
			};
			Color color_console[20] = {
				TextColor2,					//编辑器默认
				Color{ 73,  81,  98, 255},	//行号
				Color{171, 178, 191, 255},	//当前行号
				TextColor2,					//注释
				TextColor2,					//符号
				TextColor2,					//1级括括号
				TextColor2,					//2级括括号
				TextColor2,					//3级括括号
				TextColor2,					//4级括括号
				TextColor2,					//数字
				TextColor2,					//预处理指令
				TextColor2,					//字符
				TextColor2,					//字符串
				TextColor2,					//转义序列0x06
				TextColor2,					//关键字
				TextColor2,					//类型关键字
				TextColor2,					//函数
				TextColor2,					//变量
				TextColor2,					//全局变量
				TextColor2					//局部变量
			};
			Color color_one_dark[20] = {
				Color{171, 178, 191, 255},	//编辑器默认
				Color{ 73,  81,  98, 255},	//行号
				Color{171, 178, 191, 255},	//当前行号
				Color{127, 132, 142, 255},	//注释
				Color{171, 178, 191, 255},	//符号
				Color{152, 195, 121, 255},	//1级括括号
				Color{209, 154, 102, 255},	//2级括括号
				Color{198, 120, 221, 255},	//3级括括号
				Color{ 86, 182, 194, 255},	//4级括括号
				Color{209, 154, 102, 255},	//数字
				Color{198, 120, 221, 255},	//预处理指令
				Color{152, 195, 121, 255},	//字符
				Color{152, 195, 121, 255},	//字符串
				Color{ 86, 182, 194, 255},	//转义序列0x06
				Color{198, 120, 221, 255},	//关键字
				Color{198, 120, 221, 255},	//类型关键字
				Color{ 97, 175, 239, 255},	//函数
				Color{224, 108, 117, 255},	//变量
				Color{224, 108, 117, 255},	//全局变量
				Color{224, 108, 117, 255}	//局部变量
			};
			Color color_molo_codeblack[20] = {
				Color{255, 255, 255, 255},	//编辑器默认
				Color{150, 150, 150, 255},	//行号
				Color{  0, 217, 217, 255},	//当前行号
				Color{105, 152,  86, 255},	//注释
				Color{255, 125, 138, 255},	//符号
				Color{255, 105, 105, 255},	//1级括括号
				Color{255, 230,   0, 255},	//2级括括号
				Color{226, 108, 255, 255},	//3级括括号
				Color{  0, 128, 255, 255},	//4级括括号
				Color{235, 235, 235, 255},	//数字
				Color{230, 159, 238, 255},	//预处理指令
				Color{181, 206, 168, 255},	//字符
				Color{251, 142,  98, 255},	//字符串
				Color{255, 238,  55, 255},	//转义序列0x06
				Color{171, 144, 255, 255},	//关键字
				Color{171, 144, 255, 255},	//类型关键字
				Color{238, 238, 149, 255},	//函数
				Color{174, 227, 254, 255},	//变量
				Color{ 35, 152, 255, 255},	//全局变量
				Color{ 35, 152, 255, 255}	//局部变量
			};
			Color color_vs_modern_dark[20] = {
				Color{255, 255, 255, 255},	//编辑器默认
				Color{ 60,  60,  60, 255},	//行号
				Color{204, 204, 204, 255},	//当前行号
				Color{106, 152,  85, 255},	//注释
				Color{212, 212, 212, 255},	//符号
				Color{212, 212, 212, 255},	//1级括括号
				Color{255, 230,   0, 255},	//2级括括号
				Color{218, 112, 214, 255},	//3级括括号
				Color{ 23, 159, 255, 255},	//4级括括号
				Color{181, 206, 168, 255},	//数字
				Color{197, 134, 192, 255},	//预处理指令
				Color{206, 145, 120, 255},	//字符
				Color{206, 145, 120, 255},	//字符串
				Color{215, 186, 125, 255},	//转义序列0x06
				Color{197, 134, 192, 255},	//关键字
				Color{ 86, 156, 214, 255},	//类型关键字
				Color{220, 220, 170, 255},	//函数
				Color{156, 220, 254, 255},	//变量
				Color{156, 220, 254, 255},	//全局变量
				Color{156, 220, 254, 255}	//局部变量
			};
			Color color_monokai_pro[20] = {
				Color{252, 252, 250, 255},	//编辑器默认
				Color{ 91,  89,  92, 255},	//行号
				Color{193, 192, 192, 255},	//当前行号
				Color{114, 112, 114, 255},	//注释
				Color{255,  97, 136, 255},	//符号
				Color{169, 220, 118, 255},	//1级括括号
				Color{255,  97, 136, 255},	//2级括括号
				Color{252, 152, 103, 255},	//3级括括号
				Color{255, 216, 102, 255},	//4级括括号
				Color{171, 157, 242, 255},	//数字
				Color{255,  97, 136, 255},	//预处理指令
				Color{255, 216, 102, 255},	//字符
				Color{255, 216, 102, 255},	//字符串
				Color{171, 157, 242, 255},	//转义序列0x06
				Color{255,  97, 136, 255},	//关键字
				Color{120, 220, 232, 255},	//类型关键字
				Color{169, 220, 118, 255},	//函数
				Color{252, 252, 250, 255},	//变量
				Color{252, 252, 250, 255},	//全局变量
				Color{252, 252, 250, 255}	//局部变量
			};
			Color color_mariana[20] = {
				Color{249, 174,  88, 255},	//编辑器默认
				Color{136, 144, 155, 255},	//行号
				Color{174, 180, 191, 255},	//当前行号
				Color{166, 173, 185, 255},	//注释
				Color{249, 123,  88, 255},	//符号
				Color{249, 123,  88, 255},	//1级括括号
				Color{255, 215,   0, 255},	//2级括括号
				Color{218, 112, 214, 255},	//3级括括号
				Color{ 23, 159, 255, 255},	//4级括括号
				Color{249, 174,  88, 255},	//数字
				Color{198, 149, 198, 255},	//预处理指令
				Color{152, 199, 148, 255},	//字符
				Color{152, 199, 148, 255},	//字符串
				Color{198, 149, 198, 255},	//转义序列0x06
				Color{198, 149, 198, 255},	//关键字
				Color{198, 149, 198, 255},	//类型关键字
				Color{ 95, 180, 180, 255},	//函数
				Color{216, 222, 233, 255},	//变量
				Color{216, 222, 233, 255},	//全局变量
				Color{216, 222, 233, 255}	//局部变量
			};
			Color color_codesong[20] = {
				ColorF("#EBD1B7"),			//编辑器默认
				Color{ 91,  89,  92, 255},	//行号
				Color{193, 192, 192, 255},	//当前行号
				ColorF("#7A7267"),			//注释
				ColorF("#DB784D"),			//符号
				ColorF("#95CC5E"),			//1级括括号
				ColorF("#D76538"),			//2级括括号
				ColorF("#F8BB39"),			//3级括括号
				ColorF("#00A8C6"),			//4级括括号
				ColorF("#F8BB39"),			//数字
				ColorF("#DB784D"),			//预处理指令
				ColorF("#F8BB39"),			//字符
				ColorF("#F8BB39"),			//字符串
				ColorF("#F8BB39"),			//转义序列0x06
				ColorF("#DB784D"),			//关键字
				ColorF("#95CC5E"),			//类型关键字
				ColorF("#60A365"),			//函数
				ColorF("#EBD1B7"),			//变量
				ColorF("#EBD1B7"),			//全局变量
				ColorF("#EBD1B7")			//局部变量
			};

			std::string ThemeName = "Default";	// 当前配色名称
			int ThemeID = 0;					// 当前配色编号
			Color last_color[19];				// 上次配色方案
			Color last_bgcolor;					// 上次背景色
			int change_time = -2000;			// 更改时间

			// 根据当前配色获取背景色
			Color GetBgColorT() {
				if (ThemeID == 0)return BgColor;
				if (ThemeID == 1)return Color {40, 44, 52, 255};
				if (ThemeID == 2)return Color {15, 15, 15, 255};
				if (ThemeID == 3)return Color {31, 31, 31, 255};
				if (ThemeID == 4)return Color {45, 42, 46, 255};
				if (ThemeID == 5)return Color {48, 56, 65, 255};
				if (ThemeID == 6)return ColorF("#36312C");
				if (ThemeID == 7)return BLACK;
				return BLACK;
			}
			Color GetBgColor() {
				return GetBgColorT();
			}
			// 根据当前配色获取颜色
			Color GetColorT(int type) {
				if (ThemeID == 0)return color_default[type];
				if (ThemeID == 1)return color_one_dark[type];
				if (ThemeID == 2)return color_molo_codeblack[type];
				if (ThemeID == 3)return color_vs_modern_dark[type];
				if (ThemeID == 4)return color_monokai_pro[type];
				if (ThemeID == 5)return color_mariana[type];
				if (ThemeID == 6)return color_codesong[type];
				if (ThemeID == 7)return color_console[type];
				return BLACK;
			}
			Color GetColor(int type) {
				return GetColorT(type);
			}
			// 设置配色方案
			void SetColorTheme(std::string theme) {
				if (theme == ThemeName)return;
				ThemeName = theme;
				if (theme == "Default") ThemeID = 0;
				if (theme == "One Dark") ThemeID = 1;
				if (theme == "MoLo CodeBlack") ThemeID = 2;
				if (theme == "VS Modern Dark") ThemeID = 3;
				if (theme == "Monokai Pro") ThemeID = 4;
				if (theme == "Mariana") ThemeID = 5;
				if (theme == "Codesong") ThemeID = 6;
				if (theme == "Console") ThemeID = 7;
			}

			// 颜色分析
			void AnalysisColor(std::vector<std::string>& content, std::vector<std::vector<Type> >& type) {
				int r, c, start, end;
				int bLevel = 0, w;
				static std::string word[58] = {
					// C语言33关键字
					"auto", "break", "case", "char", "const",
					"continue", "default", "do", "double", "else",
					"enum", "extern", "float", "for", "goto",
					"if", "inline", "int", "long", "register",
					"return", "short", "signed", "sizeof", "static",
					"struct", "switch", "typedef", "union", "unsigned",
					"void", "volatile", "while",
					// 常见C++关键字增补18
					"and", "bool", "class", "delete", "false",
					"friend", "namespace", "new", "not", "operator",
					"or", "private", "public", "template", "this",
					"true", "typename", "using",
					// 常见Python关键字增补7
					"False", "True", "def", "elif", "from",
					"import", "in"
				};
				static int isTypeWord[58] = {
					1, 0, 0, 1, 0,
					0, 0, 0, 1, 0,
					0, 0, 1, 0, 0,
					0, 0, 1, 1, 0,
					0, 1, 1, 0, 0,
					0, 0, 0, 0, 1,
					1, 0, 0,
					0, 1, 0, 0, 0,
					0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,
					0, 0, 0,
					0, 0, 0, 0, 0,
					0, 0
				};//是否为类型关键字
				//符号着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
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
						//33-47除"#$'，58-64除@，91-96除\_`，123-126
						if ((content[r][c] >= 'a' && content[r][c] <= 'z')
						    || (content[r][c] >= 'A' && content[r][c] <= 'Z')
						    || content[r][c] <= ' ') { //对于大多数字母，不进行后续比较
							type[r][c] = Type_Default;
						}
						/*else if(content[r][c] >= '0' && content[r][c] <= '9')
						{
						type[r][c] = Type_Number;
						}*/
						else if ((content[r][c] >= '(' && content[r][c] <= '/')
						         || (content[r][c] >= ':' && content[r][c] <= '?')
						         || (content[r][c] >= '{' && content[r][c] <= '~')
						|| content[r][c] == '!' || content[r][c] == '%' || content[r][c] == '&'
						|| content[r][c] == '[' || content[r][c] == ']'
						|| content[r][c] == '^') { //优先比较常见字符以加速
							type[r][c] = Type_Symbol;
						} else {
							type[r][c] = Type_Default;
						}
					}
				}
				//数字着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
						if (content[r][c] >= '0' && content[r][c] <= '9') {
							if (c > 0 && ((content[r][c - 1] >= 'A' && content[r][c - 1] <= 'Z')
							              || (content[r][c - 1] >= 'a' && content[r][c - 1] <= 'z')
							|| content[r][c - 1] == '_')) {
								while (content[r][c + 1] >= '0' && content[r][c + 1] <= '9') {
									c++;//连续跳过多个数字
								}
							} else { //数字前面不是字母或下划线
								type[r][c] = Type_Number;
							}
						}
						if (content[r][c] == '.' && c > 0 && c + 1 < content[r].size()) { //小数点
							if (content[r][c - 1] >= '0' && content[r][c - 1] <= '9'
							                         && content[r][c + 1] >= '0' && content[r][c + 1] <= '9') {
								type[r][c] = Type_Number;
							}
						}
						if (content[r][c] == '0' && type[r][c] == Type_Number && c + 1 < content[r].size() && content[r][c + 1] == 'x') { //十六进制数
							if (c + 2 < content[r].size()) {
								if ((content[r][c + 2] >= '0' && content[r][c + 2] <= '9')
								    || (content[r][c + 2] >= 'A' && content[r][c + 2] <= 'F')
								    || (content[r][c + 2] >= 'a' && content[r][c + 2] <= 'f')) {
									type[r][c + 1] = Type_Number;
									for (c += 2; c < content[r].size(); c++) {
										if ((content[r][c] >= '0' && content[r][c] <= '9')
										    || (content[r][c] >= 'A' && content[r][c] <= 'F')
										    || (content[r][c] >= 'a' && content[r][c] <= 'f')) {
											type[r][c] = Type_Number;
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
				for (r = 0; r < content.size(); r++) {
					if (content[r].size() > 0 && content[r][0] == '#') {
						for (c = 0; c < content[r].size(); c++) {
							if (content[r][c] == '<') { //将<>内以字符串着色
								start = c;
								end = -1;
								for (c++; c < content[r].size(); c++) {
									if (content[r][c] == '>') {
										end = c;
										break;
									}
								}
								c = start;
								if (end != -1) {
									for (c++; c < end; c++) {
										if (type[r][c] == Type_Default) {
											type[r][c] = Type_String;
										}
									}
								}
								break;
							} else if (content[r][c] == '"') {
								break;
							} else {
								type[r][c] = Type_Preprocessor;
							}
						}
					}//行首为#且在<前的内容
				}
				//注释着色
				start = 0;
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
						if (content[r][c] == '/' && c + 1 < content[r].size()) {
							if (content[r][c + 1] == '*') start = 1;
							else if (content[r][c + 1] == '/' && start == 0) {
								for (; c < content[r].size(); c++) {
									type[r][c] = Type_Comment;
								}
								continue;
							}
						}
						if (start == 1) type[r][c] = Type_Comment;
						if (content[r][c] == '*' && c + 1 < content[r].size() && content[r][c + 1] == '/') {
							start = 0;
							type[r][c + 1] = Type_Comment;
							c++;
						}
					}
				}
				//字符和字符串着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
						if (content[r][c] == '\'' && type[r][c] == Type_Default) {
							start = c;
							end = -1;
							for (c++; c < content[r].size(); c++) {
								/*if(content[r][c] == '\\' && type[r][c] == Type_Default && c+1 < content[r].size())
								{
								c++;//判断'\''和'\\'
								}
								else */if (content[r][c] == '\'' && type[r][c] == Type_Default) {
									if (content[r][c - 1] == '\\' && c - 2 >= 0 && content[r][c - 2] != '\\') {
										continue;//判断'\''和'\\'
									}
									end = c;
									break;
								}
							}
							c = start;
							if (end != -1) {
								for (; c <= end; c++) {
									type[r][c] = Type_Character;
								}
								c--;
							}
						}
					}
					for (c = 0; c < content[r].size(); c++) {
						if (content[r][c] == '"' && type[r][c] == Type_Default) {
							start = c;
							end = -1;
							for (c++; c < content[r].size(); c++) {
								if (content[r][c] == '"' && type[r][c] == Type_Default) {
									if (content[r][c - 1] == '\\' && c - 2 >= 0 && content[r][c - 2] != '\\') {
										continue;//判断"\""和"\\"
									}
									end = c;
									break;
								}
							}
							c = start;
							if (end != -1) {
								start = c;
								for (; c <= end; c++) {
									type[r][c] = Type_String;
								}
								c = start;
								//转义序列着色
								for (c++; c < end; c++) {
									if (content[r][c] == '\\') {
										if (content[r][c + 1] == '\''
										|| content[r][c + 1] == '"'
										|| content[r][c + 1] == '?'
										|| content[r][c + 1] == '\\'
										|| content[r][c + 1] == 'a'
										|| content[r][c + 1] == 'b'
										|| content[r][c + 1] == 'f'
										|| content[r][c + 1] == 'n'
										|| content[r][c + 1] == 'r'
										|| content[r][c + 1] == 't'
										|| content[r][c + 1] == 'v') {
											type[r][c] = Type_EscapeSequences;
											type[r][c + 1] = Type_EscapeSequences;
											c++;
										} else if (content[r][c + 1] >= '0' && content[r][c + 1] <= '7' && c + 3 < end
										                                && content[r][c + 2] >= '0' && content[r][c + 2] <= '7'
										                                    && content[r][c + 3] >= '0' && content[r][c + 3] <= '7') {
											type[r][c] = Type_EscapeSequences;
											type[r][c + 1] = Type_EscapeSequences;
											type[r][c + 2] = Type_EscapeSequences;
											type[r][c + 3] = Type_EscapeSequences;
											c += 3;
										} else if (content[r][c + 1] == '0') {
											type[r][c] = Type_EscapeSequences;
											type[r][c + 1] = Type_EscapeSequences;
											c++;
										} else if (content[r][c + 1] == 'x') {
											type[r][c] = Type_EscapeSequences;
											type[r][c + 1] = Type_EscapeSequences;
											for (c++; c + 1 < content[r].size(); c++) {
												if ((content[r][c + 1] >= '0' && content[r][c + 1] <= '9')
												    || (content[r][c + 1] >= 'A' && content[r][c + 1] <= 'F')
												    || (content[r][c + 1] >= 'a' && content[r][c + 1] <= 'f')) {
													type[r][c + 1] = Type_EscapeSequences;
												} else {
													break;
												}
											}
										}
									}
								}
								//c = end;
							}
						}
					}
				}
				//彩虹括号着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
						if (type[r][c] == Type_Symbol) {
							if (content[r][c] == '(' || content[r][c] == ')'
							|| content[r][c] == '[' || content[r][c] == ']'
							|| content[r][c] == '{' || content[r][c] == '}') {
								if (content[r][c] == '(' || content[r][c] == '[' || content[r][c] == '{') {
									bLevel++;
								}
								if (bLevel % 4 == 0) type[r][c] = Type_Bracket_L1;
								else if (bLevel % 4 == 1) type[r][c] = Type_Bracket_L2; //保持底层为L2
								else if (bLevel % 4 == 2) type[r][c] = Type_Bracket_L3;
								else if (bLevel % 4 == 3) type[r][c] = Type_Bracket_L4;
								if (content[r][c] == ')' || content[r][c] == ']' || content[r][c] == '}') {
									bLevel--;
								}
							}
						}
					}
				}
				//关键字着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c < content[r].size(); c++) {
						if (c > 0 && ((content[r][c - 1] >= '0' && content[r][c - 1] <= '9')
						              || (content[r][c - 1] >= 'A' && content[r][c - 1] <= 'Z')
						              || (content[r][c - 1] >= 'a' && content[r][c - 1] <= 'z')
						|| content[r][c - 1] == '_'));
						else if (type[r][c] == Type_Default) { //仅搜索未着色部分
							start = c;
							end = start;
							for (w = 0; w < 58; w++) {
								for (; word[w][end - start] != 0; end++) {
									if (end < content[r].size() && content[r][end] == word[w][end - start]);
									else break;
								}
								if (word[w][end - start] == 0) {
									if (end < content[r].size() && ((content[r][end] >= '0' && content[r][end] <= '9')
									                                || (content[r][end] >= 'A' && content[r][end] <= 'Z')
									                                || (content[r][end] >= 'a' && content[r][end] <= 'z')
									|| content[r][end] == '_')) {
										end = start;
										continue;
									} else {
										end--;
										break;
									}
								}
								end = start;
							}
							c = start;
							if (end > start) {
								for (start = c; c <= end; c++) {
									if (isTypeWord[w] == 1) type[r][c] = Type_ReservedWord_T;
									else type[r][c] = Type_ReservedWord;
								}
								c--;
							}
						}
					}
				}
				//标识符着色
				for (r = 0; r < content.size(); r++) {
					for (c = 0; c + 1 < content[r].size(); c++) {
						if (type[r][c] == Type_Default && content[r][c + 1] == '(') {
							for (end = c; c >= 0; c--) { //(前为函数
								if ((content[r][c] >= '0' && content[r][c] <= '9')
								    || (content[r][c] >= 'A' && content[r][c] <= 'Z')
								    || (content[r][c] >= 'a' && content[r][c] <= 'z')
								|| content[r][c] == '_') {
									type[r][c] = Type_Function;
								} else {
									break;
								}
							}
							c = end;//防止死循环
						}
					}
					for (c = 0; c + 1 < content[r].size(); c++) { //.后为变量
						if (content[r][c] == '.' && type[r][c + 1] == Type_Default) {
							for (c++; c < content[r].size(); c++) {
								if ((content[r][c] >= '0' && content[r][c] <= '9')
								    || (content[r][c] >= 'A' && content[r][c] <= 'Z')
								    || (content[r][c] >= 'a' && content[r][c] <= 'z')
								|| content[r][c] == '_') {
									type[r][c] = Type_Variable;
								} else {
									break;
								}
							}
							c--;//连续.处理
						}
					}
					for (c = 0; c + 2 < content[r].size(); c++) { //->后为变量
						if (content[r][c] == '-' && content[r][c + 1] == '>' && type[r][c + 2] == Type_Default) {
							for (c += 2; c < content[r].size(); c++) {
								if ((content[r][c] >= '0' && content[r][c] <= '9')
								    || (content[r][c] >= 'A' && content[r][c] <= 'Z')
								    || (content[r][c] >= 'a' && content[r][c] <= 'z')
								|| content[r][c] == '_') {
									type[r][c] = Type_Variable;
								} else {
									break;
								}
							}
							c--;//连续->处理
						}
					}
					for (c = 0; c + 2 < content[r].size(); c++) { //::前为字符串(命名空间)
						if (type[r][c] == Type_Default && content[r][c + 1] == ':' && content[r][c + 2] == ':') {
							for (end = c; c >= 0; c--) {
								if ((content[r][c] >= '0' && content[r][c] <= '9')
								    || (content[r][c] >= 'A' && content[r][c] <= 'Z')
								    || (content[r][c] >= 'a' && content[r][c] <= 'z')
								|| content[r][c] == '_') {
									type[r][c] = Type_String;
								} else {
									break;
								}
							}
							c = end;
						}
					}
					for (c = 0; c < content[r].size(); c++) { //开头为大写字母或下划线视为全局变量
						if (type[r][c] == Type_Default && content[r][c] != ' ' && content[r][c] != '\t') {
							if ((content[r][c] >= 'A' && content[r][c] <= 'Z')
							|| content[r][c] == '_') {
								for (; c < content[r].size(); c++) {
									if (type[r][c] == Type_Default && content[r][c] != ' ' && content[r][c] != '\t') {
										type[r][c] = Type_Variable_G;
									} else {
										break;
									}
								}
							} else { //剩余内容均视为局部变量
								for (; c < content[r].size(); c++) {
									if (type[r][c] == Type_Default && content[r][c] != ' ' && content[r][c] != '\t') {
										type[r][c] = Type_Variable_L;
									} else {
										break;
									}
								}
							}
						}
					}
				}
			}

		}
		// 消息
		namespace message {
			class Message {
			public:
				std::string text = "[Message]";
				bool pop = false;
				int width;
				Animation xAni, yAni, aAni;
				int textsize = 0;
				Color bgcolor = {255, 207, 73, 255};
				Color ftcolor = DARKGRAY;
				int duration = 5000;
				int pop_time = 0;
				Message() {
					xAni.sms(anif::bounce2);
					xAni.ssp(0);
					xAni.sd(400);
					yAni.sd(300);
					yAni.ssp(winH);
					aAni.sd(400);
					aAni.ssp(0);
					aAni.sms(anif::sine);
				}
				void Pop() {
					if (textsize == 0)textsize = wp::strLen(text);
					xAni.stp(textsize * TextHeight / 2 + UnitHeight * 2);
					aAni.ssp(0);
					aAni.stp(1);
					pop = true;
					pop_time = gclock();
				}
				void Close() {
					xAni.sms(anif::classics_r);
					xAni.sd(200);
					xAni.stp(0);
					aAni.sd(400);
					aAni.stp(0);
					pop = false;
				}
				int Draw(int y) {
					if (textsize == 0)textsize = text.size();
					width = textsize * TextHeight / 2 + UnitHeight * 2;
					xAni.Update();
					yAni.Update();
					aAni.Update();
					int h = (UnitHeight - TextHeight) / 2;
					if (!pop && !xAni.IsRunning())yAni.stp(winH - UnitHeight * 4);
					yAni.stp(y);
					BeginAlphaMode(aAni.gnp());
					DrawRectangleRounded({float(-UnitHeight), yAni.gnp(), xAni.gnp() + UnitHeight, float(UnitHeight)}, 0.5, 0, ColorF(bgcolor));
					Print(SpaceSize - width + xAni.gnp(), yAni.gnp() + h, text.c_str(), ftcolor);
					Print(-UnitHeight + xAni.gnp() + TextHeight * 0.15, yAni.gnp() + h, "×", ftcolor);
					if (gclock() - pop_time >= duration)Close();
					if (!pop) {
						EndAlphaMode();
						if (MouseInRect(-UnitHeight, yAni.gnp(), xAni.gnp() + UnitHeight, UnitHeight)) MouseEventLock = true;
						return 0;
					}
					if (MouseInRect(-UnitHeight, yAni.gnp(), xAni.gnp() + UnitHeight, UnitHeight)) {
						if (MouseInRect(-UnitHeight + xAni.gnp(), yAni.gnp(), UnitHeight, UnitHeight)) {
							DrawRectangleRounded({-UnitHeight + xAni.gnp(), yAni.gnp(), float(UnitHeight), float(UnitHeight)}, 0.5, 0, ColorF(ChooseColor));
							if (IsMousePressed(MOUSE_BUTTON_LEFT)) Close(), MouseEventLock = true;
							MouseEventLock = true;
						}
						MouseEventLock = true;
					}
					EndAlphaMode();
					return UnitHeight;
				}
			};
			std::deque<Message> Message_queue;
			void Send(std::string a, int duration = 5000, Color _color = {255, 207, 73, 255}) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.bgcolor = _color;
				m.Pop();
				Message_queue.push_front(m);
			}
			void Send_Warning(std::string a, int duration = 5000) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.bgcolor = {255, 207, 73, 255};
				m.Pop();
				Message_queue.push_front(m);
			}
			void Send_Error(std::string a, int duration = 5000) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.bgcolor = ui::ColorF(0xF0, 0x80, 0x80);
				m.Pop();
				Message_queue.push_front(m);
			}
			void Send_Tip(std::string a, int duration = 5000) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.bgcolor = ui::ColorF(0x64, 0x95, 0xED);
				m.Pop();
				Message_queue.push_front(m);
			}
			void Send_Correct(std::string a, int duration = 5000) {
				Message m;
				m.text = a;
				m.duration = duration;
				m.bgcolor = GREEN;
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
		// 特效
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
					DrawCircle(x, y, r, ColorF(200, 200, 200, a));
				}
			};
			class LoadingCircle {
			public:
				Animation angle;
				int duration = 2000;
				LoadingCircle() {
					angle.sd(duration);
					angle.sms(anif::tanf);
					angle.ssp(0);
					angle.stp(3.14159265359 * 2);
					angle.repeat(true);
				}
				void Draw(int x, int y, int r) {
					angle.Update();
					for (int i = 0; i < 5; i++) {
						vector2d v(0, -r);
						v = v.Rotate(-angle.gp(gclock() - i * duration / 10) + (i - 2) * 0.2);
						DrawCircle(x + v.x, y - v.y, ceil(r / 7.0), ColorF(WHITE));
					}
				}
			};
			class LoadingLine {
			public:
				Animation angle;
				int duration = 2000;
				LoadingLine() {
					angle.sd(duration);
					angle.sms(anif::tanf);
					angle.ssp(0);
					angle.stp(1);
					angle.repeat(true, duration / 2);
				}
				void Draw(int x, int y, int w, realn r = 2.5 * DPI.x) {
					angle.Update();
					BeginScissor(x, y - r, w, r * 2);
					for (int i = 0; i < 5; i++)DrawCircle(x + angle.gp(gclock() - i * duration / 10) * w + r, y, r, ColorF(WHITE));
					EndScissor();
				}
			};
			class LoadingLineSolid {
			public:
				Animation a1, a2;
				int duration = 1500;
				LoadingLineSolid() {
					a1.sd(duration), a1.sms(anif::AniPara(-5, 5, (realn(*)(realn))std::atan)), a1.ssp(-0.2), a1.stp(1.2), a1.Repeat(true);
					a2.sd(duration), a2.sms(anif::AniPara(-5, 5, (realn(*)(realn))std::atan)), a2.ssp(-0.2), a2.stp(1.2, duration / 7.0), a2.Repeat(true);
				}
				void Draw(int x, int y, int w, double r = 1.5 * DPI.x) {
					a1.update();
					a2.update();
					double x1 = std::max((realn)0.0, a2.gnp()), x2 = std::min((realn)1.0, a1.gnp());
					BeginScissor(x, y - r, w, r * 2);
					DrawRectangleRounded(Rectangle{float(x1 * w + x), float(y - r), float(x2 * w - x1 * w), float(r * 2)}, 1, 0, ColorF(WHITE));
					EndScissor();
				}
			};
			ClickCircle clickcircle;
			LoadingCircle loading_circle;
			LoadingLine loading_line;
			LoadingLineSolid loading_line_solid;
			void Draw() {
			}
			void DrawMouseRectangle(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
					a = vector2d{MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
				}
				for (int i = y + s; i < y + h - s; i += s) {
					int s1 = s, s2 = s;
					if (i + s > y + h - s)s2 = y + h - s - i;
					vector2d a = {MouseShadow.x - x, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x, i, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
					a = vector2d{MouseShadow.x - x - w, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x + w - s, i, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
				}
				if (MouseInRect(x, y, w, h)) {
					DrawRectangleLinesEx({float(x), float(y), float(w), float(h)}, s, ColorF(255, 255, 255, 40));
				}
			}
			void DrawMouseRectangle_onlyLight(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
					a = vector2d{MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
				}
				for (int i = y + s; i < y + h - s; i += s) {
					int s1 = s, s2 = s;
					if (i + s > y + h - s)s2 = y + h - s - i;
					vector2d a = {MouseShadow.x - x, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x, i, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
					a = vector2d{MouseShadow.x - x - w, MouseShadow.y - i};
					if (Mod(a) <= r)DrawRectangle(x + w - s, i, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
				}
			}
			void DrawMouseRectangle_onlyLevel(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				for (int i = x; i < x + w; i += s) {
					int s1 = s, s2 = s;
					if (i + s > x + w)s1 = x + w - i;
					vector2d a = {MouseShadow.x - i, MouseShadow.y - y};
					if (Mod(a) <= r)DrawRectangle(i, y, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
					a = vector2d{MouseShadow.x - i, MouseShadow.y - y - h};
					if (Mod(a) <= r)DrawRectangle(i, y + h - s, s1, s2, ColorF(255, 255, 255, 255 * (1.0f * (r - Mod(a)) / r * 0.4)));
				}
			}
			void DrawMouseCircle(int x, int y, int rad, double r = 70 * DPI.x, double s = DPI.x) {
				if (!DrawSpecialEffect)return;
				vector2d v(0, rad);
				vector2d mouse = {MouseShadow.x, MouseShadow.y};
				double d = 2 * 3.1415926 / 10.0;
				for (double i = d; i < 2 * 3.1415926; i += d) {
					vector2d v2 = v.Rotate(-i) + vector2d(x, y);
					vector2d temp = mouse - v2;
					double dist = Mod(temp);
					if (dist <= r)DrawRing({float(x), float(y)}, rad - s, rad, R2A * i, R2A * (i + d), 3, ColorF(255, 255, 255, 255 * (1.0f * (r - dist) / r * 0.4)));
				}
				if (Mod2(mouse - vector2d(x, y)) <= rad * rad)DrawCircleLines(x, y, rad, ColorF(255, 255, 255, 40));
			}
			void DrawMouseBox(int x, int y, int w, int h, double r = 70 * DPI.x, double s = DPI.x) {
				DrawRectangleLinesEx({float(x - s), float(y - s), float(w + s * 2), float(h + s * 2)}, s, ColorF(255, 255, 255, 30));
				DrawMouseRectangle_onlyLight(x - s, y - s, w + s * 2, h + s * 2, r, s);
			}
			void DrawFrame(int x, int y, int w, int h) {
				DrawRectangleLinesEx({float(x), float(y), float(w), float(h)}, dpi, ColorF(30, 30, 30, 255));
			}
			void DrawLoadingCircle(int x, int y, int r, std::string text = "", int size = 0) {
				loading_circle.Draw(x, y, r);
				if (size == 0)size = text.size();
				Print(x - wp::strLen(text) * TextHeight / 4, y + r * 2.1, text, ColorF(WHITE));
			}
			void DrawLoadingLine(int x, int y, int w, std::string text = "", int size = 0) {
				loading_line.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, ColorF(WHITE));
			}
			void DrawLoadingLineSolid(int x, int y, int w, std::string text = "", int size = 0) {
				loading_line_solid.Draw(x, y, w);
				if (size == 0)size = text.size();
				double r = ceil(w / 100.0);
				Print(x + w / 2 - size * TextHeight / 4, y + r * 2.5, text, ColorF(WHITE));
			}
			void DrawShadowLine(int x1, int y1, int x2, int y2, int r, double dark = 0.5) {
				if (!DrawSpecialEffect)return;
				vector2d v(x2 - x1, y2 - y1);
				v = v.Rotate(3.1415927 / 2.0);
				v = VecUnit(v);
				v *= r / 5.0;
				x1 += (v / 2).x, x2 += (v / 2).x, y1 += (v / 2).y, y2 += (v / 2).y;
				for (int i = 0; i < 5; i++)DrawLineEx({x1 + v.x * i, y1 + v.y * i}, {x2 + v.x * i, y2 + v.y * i}, r / 5.0, ColorF(0, 0, 0, 100 * dark - i * 20 * dark));
			}
			void DrawShadowRectangle(int x, int y, int w, int h, int r = 15 * dpi) {
				if (!DrawSpecialEffect)return;
				double r1 = r;
				for (int i = 0; i < 5; i++) {
					DrawRectangleRoundedLines({float(x), float(y), float(w), float(h)}, 1.0f * r1 / std::min(w, h), 30, ColorF(0, 0, 0, (unsigned char)(50 - i * 10)));
					x -= r / 5.0, y -= r / 5.0, w += r / 2.5, h += r / 2.50;
					r1 += r / 5.0 * 2;
				}
			}
		};

		// 实现
		class System {
		public:
			std::vector<std::pair<Priority*, ReleaseFunc> > win;
			~System();
			static bool CMP_Window(std::pair<Priority*, ReleaseFunc> w1, std::pair<Priority*, ReleaseFunc> w2);
			void Update();
			void Add(Priority* w, ReleaseFunc fun = nullptr) {
				win.push_back(std::make_pair(w, fun));
			}
			void Erase(Priority* w);
		} MainSystem;

		// 侧边栏处理类
		class Sider {
		public:
			Element* ele = nullptr;
			SiderPosition spos = spos_top;
			int occupy = 50;
			ReleaseFunc rlf = nullptr;
		};
		class SiderManager {
		public:
			std::vector<Sider> sider;
			int X = 0;			// 绘制Sider后剩余矩形x
			int Y = 0;			// 绘制Sider后剩余矩形y
			int W = winW;		// 绘制Sider后剩余矩形w
			int H = winH;		// 绘制Sider后剩余矩形h
			~SiderManager() {
				for (int i = 0; i < sider.size(); i++) {
					if (sider[i].rlf)sider[i].rlf(sider[i].ele);
				}
			}
			SiderManager& AddSider(Element* ele, SiderPosition spos = ui::spos_top, ReleaseFunc fun = nullptr) {
				Sider temp;
				temp.ele = ele;
				temp.spos = spos;
				temp.occupy = -1;
				temp.rlf = fun;
				sider.push_back(temp);
				return *this;
			}
			SiderManager& EraseSider(int id) {
				sider[id].rlf(sider[id].ele);
				sider.erase(sider.begin() + id);
				return *this;
			}
			SiderManager& EraseSider(Element* ele_) {
				for (int i = 0; i < sider.size(); i++)if (sider[i].ele == ele_) {
						sider[i].rlf(sider[i].ele);
						sider.erase(sider.begin() + i);
					}
				return *this;
			}
			SiderManager& InsertSider(int id, Element* ele, SiderPosition spos = ui::spos_top, ReleaseFunc fun = nullptr) {
				Sider temp;
				temp.ele = ele;
				temp.spos = spos;
				temp.occupy = -1;
				temp.rlf = fun;
				sider.insert(sider.begin() + id, temp);
				return *this;
			}
			int Size() {
				return sider.size();
			}
			int Draw(int, int, int, int, bool);
		};

		// 控件基类
		class Element {
		private:
		public:
			int height = UnitHeight;				// 控件高度
			int width = UnitHeight * 5;				// 控件宽度
			realn X, Y, W, H;						// 位置
			bool CHECK = true;						// 是否检查鼠标键盘事件
			bool extra = false;						// 是否扩展
			bool init_height = false;				// 是否已经初始化高度
			bool restart_animation = false;			// 是否重置动画
			std::vector<Element*> key;				// 嵌套控件
			std::vector<ReleaseFunc> rlf;			// 自动释放函数
			int update_tick = GetTick() - 100;		// 上次更新时间刻
			SiderManager sider;						// 侧边栏管理器
			std::string content = "";				// 文本
			Element() {}
			virtual ~Element() {
				for (int i = 0; i < rlf.size(); i++) {
					if (rlf[i])rlf[i](key[i]);
				}
			}
			virtual int Draw(int x, int y, int w, bool check = true) {
				DrawRectangleLines(x, y, w, UnitHeight * 2, ColorF(RED));
				PrintMiddle(x, y, w, UnitHeight * 2, ":( 你使用的控件似乎没有提供基础功能", RED);
				return UnitHeight * 2;
			}
			virtual int Draw(int x, int y, int w, int h, bool check = true) {
				DrawRectangleLines(x, y, w, h, ColorF(RED));
				PrintMiddle(x, y, w, h, ":( 你使用的控件似乎没有提供扩展功能", RED);
				return UnitHeight;
			}
			int Draw_Auto(int x, int y, int w, bool check = true) {
				if (GetTick() == update_tick && RepetitivenessCheck)return 0;
				int h = 0;
				if (!init_height) {
					BeginScissor(0, 0, 0, 0);
					CHECK = check;
					height = Draw(x, y, w, check);
					EndScissor();
					init_height = true;
				}
				if (w <= 0) return height;				// 无法绘制，舍弃
				X = x, Y = y, W = w;
				// 在裁剪区外，舍弃
				if (GetTick() - update_tick > 10) restart_animation = true;
				update_tick = GetTick();
				if (InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, height + height * 0.4))height = Draw(x, y, w, check);
				if (DebugMode) DrawRectangleLines(x, y, width, height, YELLOW);
				H = height;
				if (height < 1)height = 1;
				return height;
			}
			int Draw_Auto_Extra(int x, int y, int w, int h, bool check = true) {
				if (GetTick() == update_tick && RepetitivenessCheck)return 0;
				if (w <= 0 || h <= 0) return 0;			// 无法绘制，舍弃
				CHECK = check;
				X = x, Y = y, W = w, H = h;
				// 在裁剪区外，舍弃
				if (GetTick() - update_tick > 10) restart_animation = true;
				update_tick = GetTick();
				if (InScissor(x - w * 0.2, y - height * 0.2, w + w * 0.4, h + height * 0.4)) height = Draw(x, y, w, h, check);
				if (height < 1)height = 1;
				return height;
			}
			int Size() {
				return key.size();
			}
			int GetHeight() {
				if (!init_height) {
					BeginScissor(0, 0, 0, 0);
					height = Draw(10, 10, winW * 2);
					EndScissor();
					init_height = true;
				}
				return height;
			}
			virtual Element& Add(Element* a, ReleaseFunc fun = nullptr) {
				key.push_back(a);
				rlf.push_back(fun);
				return *this;
			}
			virtual Element& Insert(int position, Element* a, ReleaseFunc fun = nullptr) {
				key.insert(key.begin() + position, a);
				rlf.insert(rlf.begin() + position, fun);
				return *this;
			}
			virtual Element& Erase(int position) {
				if (rlf[position])rlf[position](key[position]);
				key.erase(key.begin() + position);
				rlf.erase(rlf.begin() + position);
				return *this;
			}
			virtual Element& Erase(Element* e) {
				for (int i = 0; i < Size(); i++) {
					if (key[i] == e) {
						if (rlf[i])rlf[i](key[i]);
						key.erase(key.begin() + i);
						rlf.erase(rlf.begin() + i);
					}
				}
				return *this;
			}
			virtual Element& Swap(int p1, int p2) {
				std::swap(key[p1], key[p2]);
				std::swap(rlf[p1], rlf[p2]);
				return *this;
			}
			virtual Element& ClearKey() {
				while (Size()) {
					Erase(0);
				}
				return *this;
			}
		};
		Element TemporaryMemorizer;			// 临时储存器（结束后释放所有元素）
		void auto_release(Element* ele) {
			delete ele;
			TraceLog(LOG_INFO, ("GGCCUI: [Delete] " + wp::tostr(ele)).c_str());
			ele = nullptr;
		}

		int SiderManager::Draw(int x, int y, int w, int h, bool check = true) {
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
			X = x + dx, Y = y + dy, W = w + dw, H = h + dh;
			return h;
		}

		// 优先级处理类
		double TopPriority = 0;
		double WindowTopPriority = 0;
		class Priority : public Element {
		public:
			bool pop = true;									// 是否弹出
			bool is_mainwin = false;							// 是否是主窗口
			double priority;									// 优先级
			std::string prio_flag = "Window";					// 优先级控件类型
			ReleaseFunc rlf = nullptr;							// 自动释放函数
			bool deleted = false;								// 是否销毁

			Priority() {
				priority = ++TopPriority;
				prio_flag = "Window";
				MainSystem.Add(this);
			}
			Priority& SetReleaseFunc(ReleaseFunc fun) {
				rlf = fun;
				return *this;
			}
			Priority& SetTopPriority() {
				priority = ++TopPriority;
				return *this;
			}
			int GetTopPriority() {
				return TopPriority;
			}
			void DeleteThis() {
				deleted = true;
			}

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
			bool draw_background = true;	// 是否绘制背景
			bool useless = false;			// 是否没有用qwq
			Color SliderBgColor = ColorF(27, 27, 27, 255);// 背景色

		public:
			SliderBar() {
				move.sd(750);
				move.sms(anif::AniPara(0, 20, [](realn x) {
					return std::exp(-x);
				}));
				extra = true;
			}
			SliderBar& Set(int x) {
				if (x < 0)x = 0;
				if (x > sum)x = sum;
				move.update();
				move.stp(x);
				return *this;
			}
			SliderBar& Shift(int x) {
				move.update();
				move.gt(x);
				now = x;
				return *this;
			}
			SliderBar& GotoTop() {
				move.stp(0);
				return *this;
			}
			SliderBar& GotoBottom() {
				move.stp(sum + blank * H - H);
				return *this;
			}
			int Now() {
				return now;
			}
			int InputNow() {
				now = move.gnp();
				return move.gnp();
			}
			int Target() {
				return move.gtp();
			}
			int Sum() {
				return sum;
			}
			SliderBar& SetControl(int x, int y, int w, int h) {
				lx = x, ly = y, lw = w, lh = h;
				return *this;
			}
			SliderBar& SetBgColor(Color color) {
				SliderBgColor = color;
				return *this;
			}
			SliderBar& SetDrawBackground(bool on) {
				draw_background = on;
				return *this;
			}
			SliderBar& SetBlank(realn blank_) {
				blank = blank_;
				return *this;
			}
			SliderBar& SetSum(realn sum_) {
				sum = sum_;
				return *this;
			}
			SliderBar& SetCursorPos(realn pos) {
				cursor_pos = pos;
				return *this;
			}
			SliderBar& SetDrawCursor(bool on) {
				draw_cursor = on;
				return *this;
			}
			SliderBar& SetFixed(bool on) {
				fixed = on;
				return *this;
			}
			bool Useless() {
				return useless;
			}
			void Update() {
				// 通过鼠标滚轮更新
				int sum2 = sum;
				realn wx = GetMouseWheelMoveV().x;
				realn wy = GetMouseWheelMoveV().y;
				wx = wx * std::pow(1.3, std::fabs(wx));
				wy = wy * std::pow(1.3, std::fabs(wy));
				if (wx > 5) wx = 5;
				if (wy > 5) wy = 5;
				if (wx < -5) wx = -5;
				if (wy < -5) wy = -5;
				if (H >= W) {
					sum2 += H * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderY)move.stp(move.gtp() - wy * 100);
					if (move.gtp() > sum2 - H)move.stp(sum2 - H);
					if (move.gtp() < 0)move.stp(0);
					sum2 -= H * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderY && wy != 0)UseSliderY = true;
				} else {
					sum2 += W * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderX)move.stp(move.gtp() - wx * 100);
					if (move.gtp() > sum2 - W)move.stp(sum2 - W);
					if (move.gtp() < 0)move.stp(0);
					sum2 -= W * blank;
					if (CHECK && MouseInRect(lx, ly, lw, lh) && !UseSliderX && wx != 0)UseSliderX = true;
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
						useless = true;
						if (fixed) {
							// 绘制整体
							if (draw_background)DrawRectangle(x, y, w, h, ColorF(SliderBgColor));
							// 绘制箭头
							DrawLine(x + w / 2, y + w * 3 / 8, x + w / 4, y + w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + w * 3 / 8, x + w * 3  / 4, y + w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + h - w * 3 / 8, x + w / 4, y + h - w * 5 / 8, ColorF(WHITE));
							DrawLine(x + w / 2, y + h - w * 3 / 8, x + w * 3 / 4, y + h - w * 5 / 8, ColorF(WHITE));
							return SliderWidth;
						} else return SliderWidth;
					}
					// 绘制整体
					if (draw_background)DrawRectangle(x, y, w, h, ColorF(SliderBgColor));
					// 绘制箭头
					DrawLine(x + w / 2, y + w * 3 / 8, x + w / 4, y + w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + w * 3 / 8, x + w * 3  / 4, y + w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w / 4, y + h - w * 5 / 8, ColorF(WHITE));
					DrawLine(x + w / 2, y + h - w * 3 / 8, x + w * 3 / 4, y + h - w * 5 / 8, ColorF(WHITE));
					// 绘制拖动条
					double k = 1.0f * now / sum2;
					double k2 = 1.0f * h / sum2;
					double h2 = 0;
					if (choose) k = 1.0f * move.gtp() / sum2;
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
						if (check && IsMouseDown(MOUSE_BUTTON_LEFT))realn_mouse_input = false;
						else realn_mouse_input = true;
					}
					// 检查鼠标拖动事件
					if (MouseInRect(x, y + k * (h - w * 2 - h2) + w, w, k2 * (h - 2 * w - h2)) && check && IsMousePressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = y + w + (Mouse.y - (y + k * (h - w * 2 - h2) + w));
					if (!IsMouseDown(MOUSE_BUTTON_LEFT))choose = false;
					// 检查鼠标点击跳转事件
					if (MouseInRect(x, y + w, w, h - w * 2) && check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
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
					if (draw_cursor) DrawRectangle(x, y + k * (h - w * 2 - h2) + w + (cursor_pos - now) * k2 * (h - 2 * w - h2) / h - dpi, w, 2 * dpi, ColorF(BLUE));
				} else {
					sum2 += w * blank;
					if (w >= sum2) {
						if (fixed) {
							if (draw_background)DrawRectangle(x, y, w, h, ColorF(SliderBgColor));
							DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h / 4, ColorF(WHITE));
							DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
							DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h / 4, ColorF(WHITE));
							DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
							return SliderWidth;
						} else return SliderWidth;
					}
					if (draw_background)DrawRectangle(x, y, w, h, ColorF(SliderBgColor));
					DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h / 4, ColorF(WHITE));
					DrawLine(x + h * 3 / 8, y + h / 2, x + h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
					DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h / 4, ColorF(WHITE));
					DrawLine(x + w - h * 3 / 8, y + h / 2, x + w - h * 5 / 8, y + h * 3 / 4, ColorF(WHITE));
					double k = 1.0 * now / sum2;
					double k2 = 1.0 * w / sum2;
					double w2 = 0;
					if (choose) k = 1.0 * move.gtp() / sum2;
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
						if (check && IsMouseDown(MOUSE_BUTTON_LEFT))realn_mouse_input = false;
						else realn_mouse_input = true;
					}
					if (MouseInRect(x + k * (w - h * 2 - w2) + h, y, k2 * (w - 2 * h - w2), h) && check && IsMousePressed(MOUSE_BUTTON_LEFT))
						choose = true, chooseh = x + h + (Mouse.x - (x + k * (w - h * 2 - w2) + h));
					if (!IsMouseDown(MOUSE_BUTTON_LEFT))choose = false;
					if (MouseInRect(x + h, y, w - h * 2, h) && check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
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
		Layout* this_layout = nullptr;
		class Layout : public Element {
		private:
			realn position = 0.5;
			bool movable = true;
			bool moving = false;
			bool is_ratio = true;
			bool from_left = true;
			SplitStyle split_style = split_col;
		public:
			Layout() {
				Add(nullptr);
				extra = true;
				content = "Layout";
			}
			bool IsMoving() {
				return moving;
			}
			Layout& SetMode_byRow() {
				split_style = split_row;
				return *this;
			}
			Layout& SetMode_byCol() {
				split_style = split_col;
				return *this;
			}
			Layout& SetPosition_byRatio(realn ratio) {
				position = ratio;
				is_ratio = true;
				return *this;
			}
			Layout& SetPosition_byPixel_fromLeft(int pixel) {
				position = realn(pixel);
				is_ratio = false;
				from_left = true;
				return *this;
			}
			Layout& SetPosition_byPixel_fromRight(int pixel) {
				position = realn(pixel);
				is_ratio = false;
				from_left = false;
				return *this;
			}
			Layout& SetMovable(bool on) {
				movable = on;
				return *this;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (key.size() < 2) return h;
				Element* lo1 = key[0];
				Element* lo2 = key[1];
				realn pos = position;
				if (!is_ratio) {
					if (from_left) pos = position / w;
					else pos = 1 - position / w;
				}
				if (pos > 1) pos = 1;
				if (pos < 0) pos = 0;
				realn backup_pos = pos;
				int k = SpaceSize;
				if (split_style == split_main && key[0]) {
					key[0]->Draw_Auto_Extra(x, y, w, h, check);
				} else if (split_style == split_row) {
					if (movable) {
						if (moving) {
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
							pos = 1.0 * (GetMouseX() - x - 4 * dpi) / (w - 8 * dpi);
							if (pos < 0)pos = 0;
							if (pos > 1)pos = 1;
							lo1->Draw_Auto_Extra(x, y, (w - 8 * dpi) * pos, h, check && !moving);
							lo2->Draw_Auto_Extra(x + (w - 8 * dpi) * pos + 8 * dpi, y, (w - 8 * dpi) * (1 - pos), h, check && !moving);
							DrawRectangle(x + (w - 8 * dpi) * pos, y, 8 * dpi, h, ColorF(LIGHTGRAY));
							DrawLine(x + (w - 8 * dpi) * pos + 2 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * pos + 2 * dpi, y + h / 2 + 10 * dpi, ColorF(BLACK));
							DrawLine(x + (w - 8 * dpi) * pos + 6 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * pos + 6 * dpi, y + h / 2 + 10 * dpi, ColorF(BLACK));
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
							if (!IsMouseDown(MOUSE_BUTTON_LEFT))moving = false;
						} else {
							lo1->Draw_Auto_Extra(x, y, (w - 8 * dpi) * pos, h, check && !moving);
							lo2->Draw_Auto_Extra(x + (w - 8 * dpi) * pos + 8 * dpi, y, (w - 8 * dpi) * (1 - pos), h, check && !moving);
							special_effect::DrawMouseRectangle_onlyLight(x + (w - 8 * dpi) * pos, y, 8 * dpi, h);
							DrawLine(x + (w - 8 * dpi) * pos + 2 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * pos + 2 * dpi, y + h / 2 + 10 * dpi, ColorF(DARKGRAY));
							DrawLine(x + (w - 8 * dpi) * pos + 6 * dpi, y + h / 2 - 10 * dpi, x + (w - 8 * dpi) * pos + 6 * dpi, y + h / 2 + 10 * dpi, ColorF(DARKGRAY));
							if (MouseInRect(x + (w - 8 * dpi) * pos, y, 8 * dpi, h) && check) {
								DrawRectangle(x + (w - 8 * dpi) * pos + dpi, y, 6 * dpi, h, ColorF(LIGHTGRAY, 0.25));
								MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								if (IsMousePressed(MOUSE_BUTTON_LEFT))moving = true;
							}
						}
					} else {
						lo1->Draw_Auto_Extra(x, y, w * pos, h, check);
						lo2->Draw_Auto_Extra(x + w * pos, y, w * (1 - pos), h, check);
					}
				} else if (split_style == split_col) {
					if (movable) {
						if (moving) {
							MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
							pos = 1.0 * (GetMouseY() - y - 4 * dpi) / (h - 8 * dpi);
							if (pos < 0)pos = 0;
							if (pos > 1)pos = 1;
							lo1->Draw_Auto_Extra(x, y, w, (h - 8 * dpi) * pos, check && !moving);
							lo2->Draw_Auto_Extra(x, y + (h - 8 * dpi) * pos + 8 * dpi, w, (h - 8 * dpi) * (1 - pos), check && !moving);
							DrawRectangle(x, y + (h - 8 * dpi) * pos, w, 8 * dpi, ColorF(LIGHTGRAY));
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * pos + 2 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * pos + 2 * dpi, ColorF(BLACK));
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * pos + 6 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * pos + 6 * dpi, ColorF(BLACK));
							if (!IsMouseDown(MOUSE_BUTTON_LEFT))moving = false;
						} else {
							lo1->Draw_Auto_Extra(x, y, w, (h - 8 * dpi) * pos, check && !moving);
							lo2->Draw_Auto_Extra(x, y + (h - 8 * dpi) * pos + 8 * dpi, w, (h - 8 * dpi) * (1 - pos), check && !moving);
							special_effect::DrawMouseRectangle_onlyLight(x, y + (h - 8 * dpi) * pos, w, 8 * dpi);
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * pos + 2 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * pos + 2 * dpi, ColorF(DARKGRAY));
							DrawLine(x + w / 2 - 10 * dpi, y + (h - 8 * dpi) * pos + 6 * dpi, x + w / 2 + 10 * dpi, y + (h - 8 * dpi) * pos + 6 * dpi, ColorF(DARKGRAY));
							if (MouseInRect(x, y + (h - 8 * dpi) * pos, w, 8 * dpi) && check) {
								DrawRectangle(x, y + (h - 8 * dpi) * pos + dpi, w, 6 * dpi, ColorF(LIGHTGRAY, 0.25));
								MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
								if (IsMousePressed(MOUSE_BUTTON_LEFT))moving = true;
							}
						}
					} else {
						lo1->Draw_Auto_Extra(x, y, w, h * pos, check);
						lo2->Draw_Auto_Extra(x, y + h * pos, w, h * (1 - pos), check);
					}
				}
				if (!is_ratio) {
					if (backup_pos != pos) {
						if (from_left) position = pos * w;
						else position = w - pos * w;
					}
				} else position = pos;
				return h;
			}
		};
		class Head : public Element {
		private:
			Font ofont;
			int h = 1;
			std::string last_text = "";
			void LoadNewFont() {
				int fileSize;
				unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\simhei.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints((content + "啊看见对方").c_str(), &codepointsCount);
				realn size = 2, fade = 1;
				if (h == 1) size = 2, fade = 1;
				else if (h == 2) size = 1.7, fade = 0.7;
				else if (h == 3) size = 1.4, fade = 0.6;
				else if (h == 4) size = 1.2, fade = 0.5;
				ofont = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight * size, codepoints, codepointsCount);
				UnloadFileData(fontFileData);
				UnloadCodepoints(codepoints);
			}
		public:
			Color color = TextColor;
			Head(std::string str = "Head") {
				h = 1;
				content = str;
			}
			Head(int head, std::string str = "Head") {
				h = head;
				content = str;
			}
			~Head() {
				UnloadFont(ofont);
			}
			Head& SetSize(int size) {
				h = size;
				return *this;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				if (content != last_text) {
					LoadNewFont();
					last_text = content;
				}
				realn size = 2, fade = 1;
				if (h == 1) size = 2, fade = 1;
				else if (h == 2) size = 1.7, fade = 0.7;
				else if (h == 3) size = 1.4, fade = 0.6;
				else if (h == 4) size = 1.2, fade = 0.5;
				DrawTextEx(ofont, content.c_str(), Vector2 {(float)x, (float)y + TextHeight * size / 2}, TextHeight * size, 0, ColorF(color, fade));
				width = wp::strLen(content) * size * TextHeight / 2;
				return TextHeight * size * 2;
			}
		};
		class Text : public Element {
		public:
			Text(std::string text_ = "text") {
				content = text_;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				height = PrintRect(x, y, w, content) * (ui::UnitHeight + ui::SpaceSize);
				width = wp::strLen(content) * TextHeight / 2;
				return height;
			}
		};
		class OrderedText : public Element {
		private:
			std::string number = "·";
		public:
			OrderedText(std::string num_, std::string text_) {
				content = text_;
				number = num_;
			}
			OrderedText(std::string text_) {
				content = text_;
				number = "·";
			}
			OrderedText() {}
			int Draw(int x, int y, int w = 600, bool check = true) {
				ui::Print_All_String(x, y + (UnitHeight - TextHeight) / 2, number, ThemeColor);
				if (content == "") return UnitHeight + SpaceSize;
				int occupy = wp::strLen(number) * ui::TextHeight / 2 + SpaceSize;
				height = PrintRect(x + occupy, y, w - occupy, content) * (ui::UnitHeight + ui::SpaceSize);
				width = wp::strLen(content) * TextHeight / 2 + TextHeight;
				return height;
			}
		};
		class ColorText : public Element {
		private:
			std::string icon = "";					// 显示图标
			bool underline_visible = false;			// 是否显示下划线
			bool strikeoutline_visible = false;		// 是否显示删除线
			bool sparkle_enable = false;			// 是否闪烁
			bool click_enable = false;				// 是否可以点击（设为true后，悬浮会有阴影）
			bool click = false;						// 是否点击
			int interval = 0;						// 间隔大小
			Color color = ui::TextColor2;			// 文本颜色
			Color bgcolor = BLANK;					// 背景颜色
			std::function <void()> callback = nullptr; // 回调函数
		public:
			ColorText() {}
			ColorText(std::string text_, Color color_ = ui::TextColor2, Color bgcolor_ = BLANK) {
				if (text_.find('[') == 0 && text_.find(']') != -1) {
					icon = text_.substr(1, text_.find(']') - 1);
					content = text_.substr(text_.find(']') + 1);
				} else {
					content = text_;
					icon = "";
				}
				color = color_;
				bgcolor = bgcolor_;
			}
			ColorText& SetColor(Color color_) {
				color = color_;
				return *this;
			}
			ColorText& SetBgColor(Color bgcolor_) {
				bgcolor = bgcolor_;
				return *this;
			}
			ColorText& SetUnderlineVisible(bool on) {
				underline_visible = on;
				return *this;
			}
			ColorText& SetStrikeoutlineVisible(bool on) {
				strikeoutline_visible = on;
				return *this;
			}
			ColorText& SetSparkleEnable(bool on) {
				sparkle_enable = on;
				return *this;
			}
			ColorText& SetClickEnable(bool on) {
				click_enable = on;
				return *this;
			}
			ColorText& SetInterval(int interval_) {
				interval = interval_;
				return *this;
			}
			ColorText& withCallback(std::function <void()> callback_) {
				callback = callback_;
				return *this;
			}
			bool Click() {
				return click;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				int rx = 0;
				Color color2 = color;
				if (sparkle_enable) color2 = ColorF(color, sin(GetTime() * PI) * 0.4f + 0.6f);
				if (bgcolor.a != 0) DrawRectangle(x, y, std::min(width, w), height, ColorF(bgcolor));
				if (icon != "") {
					int t = (UnitHeight - TextHeight) / 2;
					PrintIcon(x + interval, y + t + interval, icon, color2);
					rx = TextHeight + SpaceSize;
					x += rx;
				}
				int lines = PrintRect(x + interval, y + interval, w - rx - interval * 2, content, color2);
				height = lines * (UnitHeight + SpaceSize) - SpaceSize;
				vector2d size = GetPrintRectSize(x + interval, y + interval, w - rx - interval * 2, content);
				if (underline_visible) {
					for (int i = 0; i < lines; i++) {
						DrawLineEx(
						    Vector2{(x - rx + interval) * 1.0f, (y + i * (UnitHeight + SpaceSize) + interval) * 1.0f + UnitHeight * 1.0f},
						    Vector2{(x + std::min(size.x, realn(w - rx - interval * 2))) * 1.0f, (y + i * (UnitHeight + SpaceSize) + interval) * 1.0f + UnitHeight * 1.0f},
						    dpi, color2
						);
					}
				}
				if (strikeoutline_visible) {
					for (int i = 0; i < lines; i++) {
						DrawLineEx(
						    Vector2{(x - rx + interval) * 1.0f, (y + i * (UnitHeight + SpaceSize) + interval) * 1.0f + UnitHeight * 0.5f},
						    Vector2{(x + std::min(size.x, realn(w - rx - interval * 2))) * 1.0f, (y + i * (UnitHeight + SpaceSize) + interval) * 1.0f + UnitHeight * 0.5f},
						    dpi, color2
						);
					}
				}
				click = false;
				if (click_enable) {
					ui::special_effect::DrawMouseBox(x - rx, y, size.x + rx + interval * 2, size.y + interval * 2);
					if (MouseInRect(x - rx, y, size.x + rx + interval * 2, size.y + interval * 2)) {
						DrawRectangle(x - rx, y, size.x + rx + interval * 2, size.y + interval * 2, ColorF(ChooseColor));
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							click = true;
							if (callback) callback();
						}
						if (IsMouseDown(MOUSE_BUTTON_LEFT))DrawRectangle(x - rx, y, size.x + rx + interval * 2, size.y + interval * 2, ColorF(ChooseColor));
					}
				}
				width = wp::strLen(content) * TextHeight / 2;
				if (icon != "") width += TextHeight + SpaceSize + interval * 2;
				return height + interval * 2;
			}
		};
		class Line : public Element {
		public:
			int Draw(int x, int y, int w = 600, bool check = true) {
				DrawLine(x, y + UnitHeight / 4, x + w, y + UnitHeight / 4, ColorF(LineColor));
				return UnitHeight / 2;
			}
		};
		class Space : public Element {
		public:
			int space = 1;
			Space(int sum = 1) {
				space = sum;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				return space * UnitHeight / 2;
			}
		};
		class Logo : public Element {
		private:
			Animation a, b;
		public:
			Logo() {
				a.ssp(0).stp(1).sd(300).sms(anif::sine);
				b.ssp(1).stp(0).sd(300);
				extra = true;
			}
			int Draw(int x, int y, int w, bool check = true) {
				realn r1 = w / sqrt(3), r2 = r1 * 0.3;
				vector2d i = vector2d(r1 / 2 * sqrt(3), -r1 / 2);
				vector2d j = vector2d(0, -r1);
				vector2d k = j - i;
				vector2d o = vector2d(x + w / 2, y + r1);
				vector2d P1 = o + i, P2 = o + j, P3 = o + k, P4 = o - i, P5 = o - j, P6 = o - k;
				vector2d p1 = o + i * 0.3, p2 = o + j * 0.3, p3 = o + k * 0.3, p4 = o - i * 0.3, p5 = o - j * 0.3, p6 = o - k * 0.3;
				vector2d pp1 = o + i * 0.4, pp2 = o + j * 0.4, pp3 = o + k * 0.4, pp4 = o - i * 0.4, pp5 = o - j * 0.4, pp6 = o - k * 0.4;
				vector2d f1 = 0.7 * i + 0.3 * j + o, f2 = 0.6 * i + 0.4 * j + o, f3 = pp6 + j * 0.1;
				vector2d b0 = vector2d(w / 10, w / 10);
				vector2d b1 = vector2d(j * b.gp(gclock()));
				vector2d b2 = vector2d(i * b.gp(gclock() - 300));
				vector2d b3 = vector2d(k * b.gp(gclock() - 600));
				Vector2 k0[6] = {_V(P1 + b0), _V(P2 + b0), _V(P3 + b0), _V(P4 + b0), _V(P5 + b0), _V(P6 + b0)};
				Vector2 k1[4] = {_V(f2 + b1), _V(P2 + b1), _V(P3 + b1), _V(pp3 + b1)};
				Vector2 k2[4] = {_V(pp3 + b2), _V(P3 + b2), _V(P4 + b2), _V(pp4 + b2)};
				Vector2 k3[4] = {_V(pp4 + b2), _V(P4 + b2), _V(P5 + b2), _V(pp5 + b2)};
				Vector2 k4[4] = {_V(pp5 + b3), _V(P5 + b3), _V(P6 + b3), _V(pp6 + b3)};
				Vector2 k5[5] = {_V(pp6 + b3), _V(P6 + b3), _V(P1 + b3), _V(f3 + b3), _V(pp6 + b3)};
				Vector2 k6[4] = {_V(P1 + b3), _V(o + b3), _V(p5 + b3), _V(f3 + b3)};
				Vector2 k7[4] = {_V(o + b2), _V(p3 + b2), _V(p4 + b2), _V(p5 + b2)};
				Vector2 k8[4] = {_V(o + b1), _V(P1 + b1), _V(f1 + b1), _V(p3 + b1)};
				BeginAlphaMode(a.gp(gclock() - 700));
				DrawTriangleFan(k0, 6, ColorF(20, 20, 20, 255));
				EndAlphaMode();
				BeginAlphaMode(a.gp(gclock() - 600));
				DrawTriangleFan(k4, 4, ColorF(DARKGRAY));
				DrawTriangleFan(k5, 5, ColorF(DARKGRAY));
				DrawTriangleFan(k6, 4, ColorF(DARKGRAY));
				EndAlphaMode();
				BeginAlphaMode(a.gp(gclock() - 300));
				DrawTriangleFan(k2, 4, ColorF(GRAY));
				DrawTriangleFan(k3, 4, ColorF(GRAY));
				DrawTriangleFan(k7, 4, ColorF(GRAY));
				EndAlphaMode();
				BeginAlphaMode(a.gp(gclock()));
				DrawTriangleFan(k1, 4, ColorF(LIGHTGRAY));
				DrawTriangleFan(k8, 4, ColorF(LIGHTGRAY));
				EndAlphaMode();
				return w;
			}
		};
		class Button : public ui::Element {
		private:
			Font iconf;
			int isize = ui::TextHeight * 1;
			std::string last_icon = "";
			bool draw_background = true;
			bool click = false;
			Color color = Color{47, 47, 47, 255};
			int but_height = 1.5 * ui::UnitHeight;

		public:
			std::string icon = "";
			std::function <void()> callback = nullptr;
			Button(std::string text_) {
				if (text_.find('[') == 0 && text_.find(']') != -1) {
					icon = text_.substr(1, text_.find(']') - 1);
					content = text_.substr(text_.find(']') + 1);
				} else {
					icon = "";
					content = text_;
				}
			}
			Button() {}
			Button& withCallback(std::function <void()> callback_) {
				callback = callback_;
				return *this;
			}
			Button& SetColor(Color color_) {
				color = color_;
				return *this;
			}
			Button& SetDrawBackground(bool on) {
				draw_background = on;
				return *this;
			}
			Button& SetButtonHeight(int h) {
				but_height = h;
				return *this;
			}
			bool Click() {
				return click;
			}
			int GetWidth() {
				int t = (ui::UnitHeight * 1.5 - ui::TextHeight) / 2;
				int w = t;
				if (icon != "")w += wp::strLen(icon) * ui::TextHeight / 2 + t;
				if (content != "")w += wp::strLen(content) * ui::TextHeight / 2 + t;
				return w;
			}
			int Draw(int x, int y, int w, bool check = true) {
				click = false;
				int h = but_height;
				int t = (h - TextHeight) / 2;
				if (draw_background) {
					w = t;
					y += SpaceSize / 2;
					if (icon != "")w += wp::strLen(icon) * TextHeight / 2 + t;
					if (content != "")w += wp::strLen(content) * TextHeight / 2 + t;
					DrawRectangle(x, y, w, h, ColorF(color));
				}
				w = t;
				PrintIcon(x + w, y + t, icon);
				if (icon != "")w += wp::strLen(icon) * TextHeight / 2 + t;
				Print(x + w, y + t, content);
				if (content != "")w += wp::strLen(content) * TextHeight / 2 + t;
				special_effect::DrawMouseRectangle(x, y, w, h);
				if (ui::MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ColorF(ChooseColor));
					if (IsMousePressed(MOUSE_BUTTON_LEFT) && check) {
						click = true;
						if (callback) callback();
					}
					if (IsMouseDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, h, ColorF(ChooseColor));
				}
				if (draw_background)h += ui::SpaceSize;
				width = w;
				return h;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				click = false;
				int t = (UnitHeight * 1.5 - TextHeight) / 2;
				int w2 = t, w3;
				if (icon != "")w2 += wp::strLen(icon) * TextHeight / 2 + t;
				if (content != "")w2 += wp::strLen(content) * TextHeight / 2 + t;
				if (draw_background)DrawRectangle(x, y, w, h, ColorF(color));
				w3 = t;
				PrintIcon(x + w / 2 - w2 / 2 + w3, y + h / 2 - TextHeight / 2, icon);
				if (icon != "")w3 += wp::strLen(icon) * TextHeight / 2 + t;
				Print(x + w / 2 - w2 / 2 + w3, y + h / 2 - TextHeight / 2, content);
				if (content != "")w3 += wp::strLen(content) * TextHeight / 2 + t;
				special_effect::DrawMouseRectangle(x, y, w, h);
				if (ui::MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ColorF(ChooseColor));
					if (IsMousePressed(MOUSE_BUTTON_LEFT) && check) {
						click = true;
						if (callback) callback();
					}
					if (IsMouseDown(MOUSE_BUTTON_LEFT))DrawRectangle(x, y, w, h, ColorF(ChooseColor));
				}
				return h;
			}
		};
		class Warning : public ui::Element {
		public:
			Warning(std::string text_) {
				content = text_;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				height = GetPrintRectSize(x + SpaceSize + UnitHeight, y + SpaceSize * 3 / 2, w - SpaceSize * 2 - UnitHeight, content).y;
				DrawRectangle(x, y + SpaceSize / 2, w, height + SpaceSize * 2, ColorF(255, 153, 0, 100));
				PrintIcon(x + SpaceSize * 2, y + SpaceSize * 3 / 2 + height / 2 - TextHeight / 2, u8"");
				PrintRect(x + SpaceSize * 4 + TextHeight, y + SpaceSize * 3 / 2, w - SpaceSize * 4 - UnitHeight, content);
				height += SpaceSize * 3;
				return height + SpaceSize;
			}
		};
		class Error : public ui::Element {
		public:
			Error(std::string text_) {
				content = text_;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				height = GetPrintRectSize(x + SpaceSize + UnitHeight, y + SpaceSize * 3 / 2, w - SpaceSize * 2 - UnitHeight, content).y;
				DrawRectangle(x, y + SpaceSize / 2, w, height + SpaceSize * 2, ColorF(192, 44, 56, 100));
				PrintIcon(x + SpaceSize * 2, y + SpaceSize * 3 / 2 + height / 2 - TextHeight / 2, u8"");
				PrintRect(x + SpaceSize * 4 + TextHeight, y + SpaceSize * 3 / 2, w - SpaceSize * 4 - UnitHeight, content);
				height += SpaceSize * 3;
				return height + SpaceSize;
			}
		};
		class LoadingBar : public Element {
		private:
			Animation move, color;
			Font icon_font;
			std::string last_icon = "";
			std::function <realn()> fun = nullptr;
		public:
			realn now = 0;
			std::string icon = "";
			bool draw_loading_circle = true;
			LoadingBar(std::string icon_, std::string text_, std::function <realn()> fun_ = nullptr) {
				icon = icon_;
				content = text_;
				fun = fun_;
				move.sd(300);
			}
			LoadingBar(std::string text_, std::function <realn()> fun_ = nullptr) {
				content = text_;
				fun = fun_;
				move.sd(300);
			}
			LoadingBar() {
				move.sd(300);
			}
			int Draw(int x, int y, int w, bool check = true) {
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				int tempH2 = (ui::UnitHeight * 1.5 - ui::TextHeight * 1.5) / 2;
				if (fun) now = fun();
				if (now > 1)now = 1;
				if (now < 0)now = 0;
				move.update();
				move.stp(now);
				y += ui::SpaceSize / 2;
				// 图标
				if (icon != "") {
					if (last_icon != icon) {
						ui::LoadIcon(&icon_font, icon, ui::TextHeight * 1.5);
						last_icon = icon;
					}
					ui::PrintIcon(x, y + tempH2, icon, ThemeColor, &icon_font, ui::TextHeight * 1.5);
					x += ui::UnitHeight * 1.5 + ui::SpaceSize * 2, w -= ui::UnitHeight * 1.5 + ui::SpaceSize * 2;
				}
				// 字幕
				ui::Print(x, y + tempH, content, ui::TextColor);
				std::stringstream ss;
				ss << "已完成 " << int(now * 100) << "." << int(now * 1000) % 10 << "%";
				std::string text2 = ss.str();
				ui::Print(x + w - wp::strLen(text2)*ui::TextHeight / 2, y + tempH, text2, ui::MixColor({100, 100, 100, 255}, ui::TextColor2, color.gnp()));
				if (fabs(now - 1) > 0.0001 && draw_loading_circle)
					ui::special_effect::DrawLoadingCircle(x + wp::strLen(content) * ui::TextHeight / 2 + ui::UnitHeight, y + ui::UnitHeight / 2, ui::UnitHeight * 0.4);
				// 进度条
				y += ui::UnitHeight + tempH;
				DrawRectangle(x, y, w, ui::UnitHeight / 4, ColorF(75, 75, 75, 255));
				color.update();
				if (fabs(now - 1) <= 0.0001 && draw_loading_circle)color.stp(1);
				else color.stp(0);
				DrawRectangle(x, y, move.gnp()*w, ui::UnitHeight / 4, ColorF(ThemeColor));
				return ui::UnitHeight * 1.25 + tempH * 2 + ui::SpaceSize;
			}
		};
		class Slider : public Element {
		public:
			Animation move;
			realn num = 0;
			realn minn = 0;
			realn maxn = 10;
			realn* ptr = nullptr;
			bool text_visible = false;
			Slider(realn minn_ = 0, realn maxn_ = 10, realn now_ = 0, realn* ptr_ = nullptr) {
				minn = minn_;
				maxn = maxn_;
				num = now_;
				ptr = ptr_;
			}
			Slider& Set(realn x) {
				num = x;
				return *this;
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
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, ColorF(GRAY));
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, ColorF(ThemeColor));
				DrawRectangle(x + k, y, UnitHeight / 5, UnitHeight, ColorF(ThemeColor));
				if (text_visible) {
					Print(x + cw + SpaceSize, y + h, content, TextColor);
					DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, ColorF(TextColor2));
					std::ostringstream out;
					out << num;
					std::string t = out.str();
					if (t.size() > 4)t.resize(4);
					Print(x + w - nw + h, y + h, t, MainColor);
				}
				if (MouseInRect(x, y, cw, UnitHeight) && check) {
					if (IsMousePressed(MOUSE_BUTTON_LEFT)) ChooseSlider = this;
					DrawRectangle(x + k, y, UnitHeight / 5, UnitHeight, ColorF(WHITE));
				}
				if (ChooseSlider == this) {
					realn kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5) + minn;
					num = kx;
					DrawRectangle(x + k, y, UnitHeight / 5, UnitHeight, ColorF(WHITE));
				}
				if (num < minn)num = minn;
				if (num > maxn)num = maxn;
				if (!IsMouseDown(MOUSE_BUTTON_LEFT)) ChooseSlider = nullptr;
				if (ptr)(*ptr) = num;
				return UnitHeight;
			}
		};
		class Slider_Int : public Slider {
		public:
			int num = 0;
			int minn = 0;
			int maxn = 10;
			int* ptr = nullptr;
			bool text_visible = false;
			Slider_Int(int minn_ = 0, int maxn_ = 10, int now_ = 0, int* ptr_ = nullptr) {
				minn = minn_;
				maxn = maxn_;
				num = now_;
				ptr = ptr_;
			}
			Slider_Int& Set(int x) {
				num = x;
				return *this;
			}
			int Draw(int x, int y, int w = 400, bool check = true) {
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
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, cw, h2, ColorF(GRAY));
				DrawRectangle(x, y + UnitHeight / 2 - h2 / 2, k, h2, ColorF(MainColor));
				DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, ColorF(MainColor));
				if (text_visible) {
					Print(x + cw + SpaceSize, y + h, content, TextColor);
					DrawRectangle(x + w - nw, y + h / 2, nw, UnitHeight - h, ColorF(TextColor2));
					std::ostringstream out;
					out << num;
					std::string t = out.str();
					t = t.substr(0, 5);
					Print(x + w - nw + h, y + h, t, MainColor);
				}
				if (MouseInRect(x, y + h / 2, cw, UnitHeight - h) && check) {
					if (IsMousePressed(MOUSE_BUTTON_LEFT))ChooseSlider = this;
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, ColorF(WHITE));
				}
				if (ChooseSlider == this) {
					realn kx = 1.0 * (Mouse.x - x - UnitHeight / 10) * (maxn - minn) / (cw - UnitHeight / 5) + minn;
					num = round(kx);
					DrawRectangle(x + k, y + h / 2, UnitHeight / 5, UnitHeight - h, ColorF(WHITE));
				}
				if (num < minn)num = minn;
				if (num > maxn)num = maxn;
				if (IsMouseReleased(MOUSE_BUTTON_LEFT))ChooseSlider = nullptr;
				if (ptr)(*ptr) = num;
				return UnitHeight;
			}
		};
		class Switch : public Element {
		private:
			Animation move;
			bool* ptr = nullptr;
		public:
			bool on = false;
			Switch(std::string text_ = "Switch", bool on_ = false, bool* ptr_ = nullptr) {
				content = text_;
				on = on_;
				ptr = ptr_;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				move.sd(300);
				move.sms(anif::bounce4);
				int h = (UnitHeight - TextHeight) / 2;
				int nw = UnitHeight * 1.7;
				realn h2 = UnitHeight / 4;
				move.Update();
				Print(x, y + h, content);
				DrawRectangle(x + w - nw, y + UnitHeight / 2 - h2 / 2, nw, h2, ColorF(GRAY));
				DrawRectangle(x + w - nw, y + UnitHeight / 2 - h2 / 2, round(move.gnp()), h2, ColorF(ThemeColor));
				DrawRectangle(x + w - nw + round(move.gnp()), y + h / 2, round(UnitHeight / 3.5), UnitHeight - h, ColorF(ThemeColor));
				if (MouseInRect(x + w - nw, y + h / 2, nw, UnitHeight - h) && check) {
					DrawRectangle(x + w - nw + round(move.gnp()), y + h / 2, round(UnitHeight / 3.5), UnitHeight - h, ColorF(WHITE));
					if (IsMousePressed(MOUSE_BUTTON_LEFT))on = !on;
				}
				if (on) move.stp(nw - UnitHeight / 3.5);
				else move.stp(0.0);
				if (ptr) *ptr = on;
				width = wp::strLen(content) * TextHeight / 2 + SpaceSize + nw;
				return UnitHeight;
			}
		};
		class Choose : public Element {
		private:
			Animation angle;
			Animation move;
			bool open = false;
		public:
			std::vector<std::string> key;
			int choose = -1;
			Choose& Open() {
				open = true;
				angle.stp(acos(-1) / 2);
				move.stp(key.size()*UnitHeight);
				return *this;
			}
			Choose& Close() {
				open = false;
				angle.stp(0);
				move.stp(0);
				return *this;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				angle.sd(300);
				move.sd(300);
				angle.Update();
				move.Update();
				int h = (UnitHeight - TextHeight) / 2;
				int cw = w * 0.6;
				Print(x + SpaceSize + cw, y + h, content, TextColor);
				DrawRectangle(x, y + h / 2, cw, UnitHeight - h, UnitBgColor);
				special_effect::DrawMouseRectangle(x, y + h / 2, cw, UnitHeight - h);
				if (choose != -1)Print(x + SpaceSize, y + h, key[choose], TextColor);
				vector2d k1 = vector2d(-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8);
				vector2d k2 = vector2d(TextHeight / 4 * 0.8, 0);
				vector2d k3 = vector2d(-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8);
				vector2d p1 = k1.Rotate(angle.gnp());
				vector2d p2 = k2.Rotate(angle.gnp());
				vector2d p3 = k3.Rotate(angle.gnp());
				realn TempX = x + cw - UnitHeight / 2.0;
				realn TempY = y + UnitHeight / 2.0;
				DrawLine(p1.x + TempX, p1.y + TempY, p2.x + TempX, p2.y + TempY, LIGHTGRAY);
				DrawLine(p2.x + TempX, p2.y + TempY, p3.x + TempX, p3.y + TempY, LIGHTGRAY);
				if (MouseInRect(x, y + h / 2.0, cw, UnitHeight - h) && check) {
					if (IsMousePressed(MOUSE_BUTTON_LEFT))Open();
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
		class Collapse : public Element {
		private:
			Animation move;
			Animation angle;
			int Height = 0;
			bool swapping = false;
			bool open = false;
			Animation appearAni;				// 淡入动画
			realn GetAniBias(int id) {
				return (1 - appearAni.GetPos(gclock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id >= 0)return appearAni.GetPos(gclock() - id * 50);
				else return appearAni.GetPos((gclock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}

		public:
			bool draw_background = true;
			bool draw_menu_background = false;
			bool insert_ani = false;
			Collapse(std::string text_ = "Collapse") {
				content = text_;
				angle.sd(300);
				move.sd(500);
				angle.sms(anif::bounce5);
			}
			Collapse& Open() {
				open = true;
				angle.stp(acos(-1) / 2);
				move.stp(Height + SpaceSize * 2);
				move.sms(anif::classics);
				appearAni.stp(1);
				appearAni.sms(anif::classics);
				return *this;
			}
			Collapse& Close() {
				open = false;
				angle.stp(0);
				move.stp(0);
				move.sms(anif::classics_d);
				appearAni.stp(0);
				appearAni.sms(anif::classics_d);
				return *this;
			}
			Collapse& SetDrawMenuBackground(bool on) {
				draw_menu_background = on;
				return *this;
			}
			Collapse& SetDrawBackground(bool on) {
				draw_background = on;
				return *this;
			}
			int Draw(int x, int y, int w = 600, bool check = true) {
				appearAni.update();
				Height = 0;
				X = x, Y = y, W = w;
				swapping = false;
				for (int i = 0; i < key.size(); i++)
					Height += key[i]->height;
				TempHeight = Height;
				angle.Update();
				move.Update();
				int h = (UnitHeight - TextHeight) / 2;
				if (open)BeginAlphaMode(GetAniAlpha(0));
				else BeginAlphaMode(GetAniAlpha(-2));
				if (draw_menu_background)DrawRectangle(x, y + UnitHeight - h, w, move.gnp() + h, ColorF(20, 20, 20, 150));
				EndAlphaMode();
				if (draw_background)DrawRectangle(x, y + h / 2, w, UnitHeight - h, ColorF(MainColor));
				if (MouseInRect(x, y + h / 2, w, UnitHeight - h) && check) {
					if (check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
						if (!open)Open();
						else Close();
					}
					DrawRectangle(x, y + h / 2, w, UnitHeight - h, ColorF(ChooseColor));
				}
				special_effect::DrawMouseRectangle(x, y + h / 2, w, UnitHeight - h);
				Print(x + 2 * h + UnitHeight, y + h, content, WHITE);
				vector2d k1 = vector2d(-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8);
				vector2d k2 = vector2d(TextHeight / 4 * 0.8, 0);
				vector2d k3 = vector2d(-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8);
				vector2d p1 = k1.Rotate(angle.gnp());
				vector2d p2 = k2.Rotate(angle.gnp());
				vector2d p3 = k3.Rotate(angle.gnp());
				int TempX = x + h + UnitHeight / 2;
				int TempY = y + UnitHeight / 2;
				DrawLine(p1.x + TempX, p1.y + TempY, p2.x + TempX, p2.y + TempY, ColorF(LIGHTGRAY));
				DrawLine(p2.x + TempX, p2.y + TempY, p3.x + TempX, p3.y + TempY, ColorF(LIGHTGRAY));
				if (move.gnp() != Height && open && !move.is_run())move.gt(Height + SpaceSize * 2);
				if (open)Open();
				if (open) {
					x += GetAniBias(2) / 2;
					w -= GetAniBias(2);
					BeginAlphaMode(GetAniAlpha(-2));
				} else {
					x += GetAniBias(0) / 2;
					w -= GetAniBias(0);
					BeginAlphaMode(GetAniAlpha(0));
				}
				if (move.gsp() == 0 || move.gtp() == 0)BeginScissor(x, y + UnitHeight, w, move.gnp());
				check &= open;
				if (move.gnp() != 0) {
					realn nowh;
					if (move.gsp() == 0 || move.gtp() == 0)nowh = move.gnp() - Height - SpaceSize;
					else nowh = SpaceSize;
					realn nowh2 = 0;
					for (int i = 0; i < key.size(); i++)nowh2 += key[i]->Draw_Auto(x + UnitHeight * 0.7, y + UnitHeight + nowh + nowh2, w - UnitHeight * 1.4, check && !swapping && move.gsp() != 0 && move.gtp() != 0);
				}
				if (move.gsp() == 0 || move.gtp() == 0)EndScissor();
				EndAlphaMode();
				height = move.gnp() + UnitHeight;
				return height;
			}
		};
		class Box : public Element {
		private:
			int Height = 0;
			bool swapping = false;
			int max_width = -1;
		public:
			bool insert_ani = false;
			Box& SetMaxWidth(int max_width_) {
				max_width = max_width_;
				return * this;
			}
			int Draw(int x, int y, int w, bool check = true) {
				Height = 0;
				if (w > max_width && max_width != -1)w = max_width;
				X = x, Y = y, W = w, CHECK = check;
				swapping = false;
				for (int i = 0; i < key.size(); i++)Height += key[i]->height;
				DrawRectangle(x, y, w, Height + SpaceSize * 2, MenuColor);
				ui::special_effect::DrawFrame(x, y, w, Height + SpaceSize * 2);
				realn nowh = SpaceSize;
				for (int i = 0; i < key.size(); i++)nowh += key[i]->Draw_Auto(x + UnitHeight, y + nowh, w - UnitHeight * 2, check && !swapping);
				height = Height + SpaceSize * 2;
				return height;
			}
		};
		Scene* plot;
		Scene3D* plot3;
		class Scene : public Element {
		public:
			vector2d camera = {0, 0};
			bool choose = false;
			bool mouse_move = false;
			bool movable = true;
			bool ctrl_to_move = false;
			realn zoom = 100;
			realn startx, starty, endx, endy;
			realn mesh_startx, mesh_starty, mesh_endx, mesh_endy;
			realn click_time = 0;
			realn mesh_min = -6;
			realn zoom_min = -3;
			realn zoom_max = 7;
			vector2d choose_pos;
			Animation zoom_ani;
			Animation ilenAni, idegAni;
			Animation jlenAni, jdegAni;
			Slider zoom_slider;
			std::map <vector2d*, std::pair<Animation, Animation> > v2ani;
			std::map <vector2d*, bool> v2state;
			std::function<void()> draw_fun;

			bool mesh_visible = true;
			bool axis_visible = true;
			bool zoom_visible = true;
			bool polar_visible = false;
			bool number_visible = true;
			bool mesh_limit = false;
			realn move_threshold_dist = 15 * ui::dpi;
			realn move_threshold_time = 0.2;

			Scene(std::function<void()> DrawFun = nullptr) {
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
				draw_fun = DrawFun;
				content = "Scene";
			}
			inline void set_zoom(realn z = 2) {
				zoom_ani.SetTargetPos(z);
			}
			inline void set_zoomani_goto(realn z = 2) {
				zoom_ani.Goto(z);
			}
			inline realn get_zoom() {
				return zoom_ani.gnp();
			}
			inline void set_position(vector2d pos) {
				camera = pos;
			}
			inline void set_position(realn x, realn y) {
				camera = vector2d{x, y};
			}
			inline void set_mesh(int sx, int sy, int ex, int ey) {
				mesh_limit = true;
				mesh_startx = sx;
				mesh_starty = sy;
				mesh_endx = ex;
				mesh_endy = ey;
			}
			inline void set_mesh(pg::aabb box) {
				mesh_limit = true;
				set_mesh(box.x1, box.y1, box.x2, box.y2);
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
				return w * zoom;
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
			bool MouseRelease(MouseButton mb) {
				if (mb != MOUSE_BUTTON_LEFT || (ctrl_to_move && !IsKeyDown(KEY_LEFT_CONTROL))) return IsMouseReleased(mb) && CHECK && MouseInRect(X, Y, W, H);
				return IsMouseReleased(mb) && !mouse_move && CHECK && MouseInRect(X, Y, W, H);
			}
			bool MousePressed(MouseButton mb) {
				if (mb != MOUSE_BUTTON_LEFT) return IsMousePressed(mb) && CHECK && MouseInRect(X, Y, W, H);
				return IsMousePressed(mb) && !mouse_move && CHECK && MouseInRect(X, Y, W, H);
			}
			bool MouseDown(MouseButton mb) {
				return IsMouseDown(mb) && CHECK && MouseInRect(X, Y, W, H);
			}

			void DrawMesh_(realn sspace, Color color, bool num = false) {
				vector2d O = W2S({0, 0});
				realn x = X, y = Y, w = W, h = H;
				zoom = pow(10, zoom_ani.gnp()) * w / 1080;
				realn startx = -ceil(1.0 * (O.x) / sspace) * sspace + O.x + x;
				realn starty = -ceil(1.0 * (O.y) / sspace) * sspace + O.y + y;
				if (mesh_limit) {
					vector2d ms = W2S(mesh_startx, mesh_endy) + vector2d{X, Y};
					vector2d me = W2S(mesh_endx, mesh_starty) + vector2d{X, Y};
					for (realn i = startx; i <= x + w; i += sspace)if (i >= ms.x && i <= me.x)DrawLine(i, std::max(y, ms.y), i, std::min(y + h, me.y), ColorF(color));
					for (realn i = starty; i <= y + h; i += sspace)if (i >= ms.y && i <= me.y)DrawLine(std::max(x, ms.x), i, std::min(x + w, me.x), i, ColorF(color));
					DrawRectangleLines(round(ms.x), round(ms.y), round(me.x) - round(ms.x), round(me.y) - round(ms.y), ColorF(LIGHTGRAY));
				} else {
					for (realn i = startx; i <= x + w; i += sspace)DrawLine(i, y, i, y + h, ColorF(color));
					for (realn i = starty; i <= y + h; i += sspace)DrawLine(x, i, x + w, i, ColorF(color));
				}
				if (num) {
					if (sspace <= 70 * dpi)sspace = sspace * 5;
					for (realn i = std::max((realn)O.x, O.x + int((x - O.x) / sspace) * sspace); i <= w; i += sspace) {
						realn k = S2W({i, 0}).x;
						std::string s = ts(k);
						if (i == O.x)s = "[0]";
						Print(i + x, y, s.c_str(), GRAY);
					}
					for (realn i = std::min((realn)(O.x - sspace), O.x + int((x + W - O.x) / sspace) * sspace); i >= 0; i -= sspace) {
						realn k = S2W({i, 0}).x;
						std::string s = ts(k);
						Print(i + x, y, s.c_str(), GRAY);
					}
					for (realn i = std::max((realn)O.y, O.y + int((y - O.y) / sspace) * sspace); i <= H; i += sspace) {
						realn k = S2W({0, i}).y;
						std::string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str(), GRAY);
					}
					for (realn i = std::min((realn)(O.y - sspace), O.y + int((y + W - O.y) / sspace) * sspace); i >= 0; i -= sspace) {
						realn k = S2W({0, i}).y;
						std::string s = ts(k);
						if (i == O.y)s = "[0]";
						Print(x, i + y, s.c_str(), GRAY);
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
			inline bool in_sight(vector2d v1, vector2d v2) {
				return in_sight(v1.x, v1.y, v2.x, v2.y);
			}
			void text(realn x, realn y, std::string text_, Color color = LIGHTPINK) {
				if (!in_sight(x, y))return;
				vector2d a = W2S({x, y});
				Print(a.x + X - wp::strLen(text_)*ui::TextHeight / 4, a.y + Y - ui::TextHeight / 2, text_, ColorF(color));
			}
			void text(vector2d pos, std::string text_, Color color = LIGHTPINK) {
				text(pos.x, pos.y, text_, color);
			}
			void raylib_text(vector2d pos, std::string text_, realn size = 1.0, Color color = LIGHTPINK) {
				pos = W2S(pos) + vector2d(X, Y);
				int size2 = W2S(size);
				int len = MeasureText(text_.c_str(), size2);
				DrawText(text_.c_str(), pos.x - len / 2, pos.y - size2 / 2, size2, ColorF(color));
			}
			void raylib_text(realn x, realn y, std::string text_, realn size = 1.0, Color color = LIGHTPINK) {
				raylib_text(vector2d(x, y), text_, size, color);
			}
			void point(realn x, realn y, Color color = LIGHTPINK) {
				if (!in_sight(x, y))return;
				vector2d a = W2S({x, y});
				DrawCircle(a.x + X, a.y + Y, 2.5 * dpi, ColorF(color));
			}
			void point(vector2d v, Color color = LIGHTPINK) {
				point(v.x, v.y, color);
			}
			bool choose_point = false;
			bool float_point = false;
			void point_controlled_rel(vector2d* v, vector2d rfrc = {0, 0}, realn rotate = 0, Color color = LIGHTPINK) {
				vector2d abs_v = v->Rotate(rotate) + rfrc;
				if (!in_sight(abs_v) && !v2state[v])return;
				else {
					vector2d m = _v(Mouse) - vector2d{X, Y};
					vector2d a = W2S(abs_v);
					DrawCircle(a.x + X, a.y + Y, 8 * dpi, ColorF(color, 0.2));
					point(abs_v, color);
					if (Mod2(m - a) < 64 * dpi * dpi || v2state[v]) {
						if (CHECK) {
							if (!float_point)DrawCircleLines(a.x + X, a.y + Y, 8 * dpi, ColorF(color));
							MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
							if (IsMousePressed(MOUSE_BUTTON_LEFT) && !choose_point && ChooseSlider == nullptr) {
								if (!float_point)v2state[v] = true;
								choose_point = true;
							}
							float_point = true;
						}
					}
					if (v2state[v] && ChooseSlider == nullptr) {
						(*v) = (S2W(m) - rfrc).Rotate(-rotate);
						choose = false;
					}
					if (v2state[v] && ChooseSlider == nullptr) {
						(*v) = (S2W(m) - rfrc).Rotate(-rotate);
						MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
						choose = false;
					}
					if (!IsMouseDown(MOUSE_BUTTON_LEFT)) {
						for (auto i = v2state.begin(); i != v2state.end(); i++)i->second = false;
						choose_point = false;
					}
				}
			}
			void point_controlled_rel(vector2d* v, vector2d rfrc = {0, 0}, vector2d dir = {1, 0}, Color color = LIGHTPINK) {
				point_controlled_rel(v, rfrc, atan2(dir.y, dir.x), color);
			}
			void point_controlled(vector2d* v, Color color = LIGHTPINK) {
				point_controlled_rel(v, vector2d{0, 0}, 0, color);
			}
			void line(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				vector2d a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, ColorF(color));
			}
			void line(vector2d v1, vector2d v2, Color color = LIGHTPINK) {
				line(v1.x, v1.y, v2.x, v2.y, color);
			}
			void line_controlled(vector2d *v1, vector2d *v2, Color color = LIGHTPINK) {
				line(*v1, *v2, color);
				point_controlled(v1, color);
				point_controlled(v2, color);
			}
			void ray(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				vector2d a = W2S({x1, y1}), b = W2S(vector2d{x1 + x2 * 10000, y1 + y2 * 10000});
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, ColorF(color));
			}
			void ray(vector2d v1, vector2d v2, Color color = LIGHTPINK) {
				ray(v1.x, v1.y, v2.x, v2.y, color);
			}
			void ray_controlled(vector2d *v1, vector2d *v2, Color color = LIGHTPINK) {
				ray(*v1, *v2, color);
				point_controlled(v1, color);
				point_controlled(v2, color);
			}
			void rectangle_lines(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				if (x1 > endx || x2 < startx || y2 > endy || y1 < starty) return;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangleLines(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, ColorF(color));
			}
			void rectangle(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				if (x1 > endx || x2 < startx || y2 > endy || y1 < starty) return;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				if (b.x - a.x >= 4 * ui::dpi && b.y - a.y >= 4 * ui::dpi) {
					DrawRectangle(a.x + X, a.y + Y, b.x - a.x, b.y - a.y, ColorF(color, 0.2));
					DrawRectangleLines(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), ColorF(color));
				} else {
					if (round(b.x) - round(a.x) < 1 || round(b.y) - round(a.y) < 1)return;
					DrawRectangle(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), ColorF(color, 0.6));
				}
			}
			void rectangle_solid(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				if (x1 > x2)std::swap(x1, x2);
				if (y1 < y2)std::swap(y1, y2);
				if (x1 > endx || x2 < startx || y2 > endy || y1 < starty) return;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				DrawRectangle(round(a.x + X), round(a.y + Y), round(b.x) - round(a.x), round(b.y) - round(a.y), ColorF(color));
			}
			void rectangle(pg::aabb rect, Color color = LIGHTPINK) {
				rectangle_lines(rect.x1, rect.y1, rect.x2, rect.y2, color);
			}
			void rectangle(vector2d v1, vector2d v2, Color color = LIGHTPINK) {
				rectangle(v1.x, v1.y, v2.x, v2.y, color);
			}
			void rectangle_controlled(vector2d *v1, vector2d *v2, Color color = LIGHTPINK) {
				rectangle(*v1, *v2, color);
				point_controlled(v1, color);
				point_controlled(v2, color);
			}
			void rectangle_r(vector2d pos, realn w, realn h, realn rotate, Color color = LIGHTPINK) {
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
				DrawTriangleFan(p2, 4, ColorF(color2));
				line(p[0], p[1], color);
				line(p[1], p[2], color);
				line(p[2], p[3], color);
				line(p[3], p[0], color);
			}
			void rectangle_r_solid(vector2d pos, realn w, realn h, realn rotate, Color color = LIGHTPINK) {
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
				DrawTriangleFan(p2, 4, ColorF(color));
			}
			void triangle(vector2d p1, vector2d p2, vector2d p3, Color color = LIGHTPINK) {
				vector2d t1 = W2S(p1) + vector2d{X, Y};
				vector2d t2 = W2S(p2) + vector2d{X, Y};
				vector2d t3 = W2S(p3) + vector2d{X, Y};
				color2 = ColorF(color, 0.2);
				DrawTriangle(_V(t1), _V(t2), _V(t3), color2);
				DrawTriangle(_V(t1), _V(t3), _V(t2), color2);
				DrawTriangleLines(_V(t1), _V(t2), _V(t3), ColorF(color));
			}
			void triangle_lines(vector2d p1, vector2d p2, vector2d p3, Color color = LIGHTPINK) {
				vector2d t1 = W2S(p1) + vector2d{X, Y};
				vector2d t2 = W2S(p2) + vector2d{X, Y};
				vector2d t3 = W2S(p3) + vector2d{X, Y};
				DrawTriangleLines(_V(t1), _V(t2), _V(t3), ColorF(color));
			}
			void triangle_solid(vector2d p1, vector2d p2, vector2d p3, Color color = LIGHTPINK) {
				vector2d t1 = W2S(p1) + vector2d{X, Y};
				vector2d t2 = W2S(p2) + vector2d{X, Y};
				vector2d t3 = W2S(p3) + vector2d{X, Y};
				DrawTriangle(_V(t1), _V(t2), _V(t3), ColorF(color));
				DrawTriangle(_V(t1), _V(t3), _V(t2), ColorF(color));
			}
			void triangle(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = LIGHTPINK) {
				triangle(vector2d{x1, y1}, vector2d{x2, y2}, vector2d{x3, y3}, color);
			}
			void triangle_solid(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = LIGHTPINK) {
				triangle_solid(vector2d{x1, y1}, vector2d{x2, y2}, vector2d{x3, y3}, color);
			}
			void triangle_controlled(vector2d *p1, vector2d *p2, vector2d *p3, Color color = LIGHTPINK) {
				triangle(*p1, *p2, *p3, color);
				point_controlled(p1, color);
				point_controlled(p2, color);
				point_controlled(p3, color);
			}
			void arc(realn x1, realn y1, realn x2, realn y2, realn x3, realn y3, Color color = LIGHTPINK) {
				realn a = x1 - x2;
				realn b = y1 - y2;
				realn c = x1 - x3;
				realn d = y1 - y3;
				realn e = ((x1 * x1 - x2 * x2) - (y2 * y2 - y1 * y1)) / 2;
				realn f = ((x1 * x1 - x3 * x3) - (y3 * y3 - y1 * y1)) / 2;
				realn x = (e * d - b * f) / (a * d - b * c);
				realn y = (a * f - e * c) / (a * d - b * c);
				realn r = Mod(vector2d{x1, y1} -vector2d{x, y});
				realn a1 = -atan2(y1 - y, x1 - x);
				realn a2 = -atan2(y2 - y, x2 - x);
				realn a3 = -atan2(y3 - y, x3 - x);
				if (a1 < 0)a1 = 2 * PI + a1;
				if (a2 < 0)a2 = 2 * PI + a2;
				if (a3 < 0)a3 = 2 * PI + a3;
				if (a2 < a1)a2 += PI * 2;
				if (a3 < a1)a3 += PI * 2;
				a1 = a1 * 180 / PI;
				a2 = a2 * 180 / PI;
				a3 = a3 * 180 / PI;
				vector2d v = vector2d{x, y};
				v = W2S(v) + vector2d{X, Y};
				if (a2 - a1 < a3 - a1)DrawRingLines(_V(v), r * zoom, r * zoom, a1, a3, 0, ColorF(color));
				if (a2 - a1 > a3 - a1) {
					if (a1 < a3)a1 += 360;
					DrawRingLines(_V(v), r * zoom, r * zoom, a3, a1, 0, ColorF(color));
				}
			}
			void arc(vector2d p1, vector2d p2, vector2d p3, Color color = LIGHTPINK) {
				arc(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
			}
			void arc(vector2d o, realn r, realn start, realn end, Color color = LIGHTPINK) {
				DrawRingLines(_V(W2S(o) + vector2d(X, Y)), r * zoom, r * zoom, start - 90, end - 90, 50, ColorF(color));
			}
			void arc_controlled(vector2d *p1, vector2d *p2, vector2d *p3, Color color = LIGHTPINK) {
				arc(*p1, *p2, *p3, color);
				point_controlled(p1, color);
				point_controlled(p2, color);
				point_controlled(p3, color);
			}
			void circle(realn x1, realn y1, realn r, Color color = LIGHTPINK) {
				a = W2S({x1, y1});
				DrawCircleSector({a.x + X, a.y + Y}, r * zoom, 0, 360, 0, ui::ColorF(color, 0.2));
				DrawRingLines({a.x + X, a.y + Y}, r * zoom, r * zoom, 0, 360, 0, ui::ColorF(color));
			}
			void circle_solid(realn x1, realn y1, realn r, Color color = LIGHTPINK) {
				a = W2S({x1, y1});
				DrawCircleSector({a.x + X, a.y + Y}, r * zoom, 0, 360, 0, ui::ColorF(color));
			}
			void circle_lines(realn x1, realn y1, realn r, Color color = LIGHTPINK) {
				a = W2S({x1, y1});
				DrawRingLines({a.x + X, a.y + Y}, r * zoom, r * zoom, 0, 360, 0, ColorF(color));
			}
			void circle(vector2d pos, realn r, Color color = LIGHTPINK) {
				circle(pos.x, pos.y, r, color);
			}
			void circle_solid(vector2d pos, realn r, Color color = LIGHTPINK) {
				circle_solid(pos.x, pos.y, r, color);
			}
			void circle_lines(vector2d pos, realn r, Color color = LIGHTPINK) {
				circle_lines(pos.x, pos.y, r, color);
			}
			void polygon(std::vector <vector2d> pos, Color color = LIGHTPINK) {
				if (pos.size() <= 1) return;
				std::vector <Vector2> p(pos.size());
				std::vector <Vector2> p2(pos.size());
				for (int i = 0; i < pos.size(); i++) {
					p[i] = _V(W2S(pos[i]) + vector2d(X, Y));
					if (i) DrawLineV(p[i - 1], p[i], ui::ColorF(color));
				}
				std::copy(p2.rbegin(), p2.rend(), p2.begin());
				DrawLineV(p[p.size() - 1], p[0], ColorF(color));
				DrawTriangleFan(p.data(), p.size(), ui::ColorF(color, 0.2));
				DrawTriangleFan(p2.data(), p2.size(), ui::ColorF(color, 0.2));
			}
			void polygon_lines(std::vector <vector2d> pos, Color color = LIGHTPINK) {
				std::vector <Vector2> p(pos.size());
				for (int i = 0; i < pos.size(); i++) {
					p[i] = _V(W2S(pos[i]) + vector2d(X, Y));
					if (i) DrawLineV(p[i - 1], p[i], ColorF(color));
				}
				DrawLineV(p[p.size()], p[0], ColorF(color));
			}
			void polygon_solid(std::vector <vector2d> pos, Color color = LIGHTPINK) {
				std::vector <Vector2> p(pos.size());
				std::vector <Vector2> p2(pos.size());
				for (int i = 0; i < pos.size(); i++) p[i] = _V(W2S(pos[i]) + vector2d(X, Y));
				std::copy(p2.rbegin(), p2.rend(), p2.begin());
				DrawTriangleFan(p.data(), p.size(), ui::ColorF(color, 0.2));
				DrawTriangleFan(p2.data(), p2.size(), ui::ColorF(color, 0.2));
			}
			void round_polygon(std::vector <vector2d> pos, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(pos.size() * 10);
				for (int i = 1; i <= pos.size(); i++) {
					vector2d v1 = pos[i % pos.size()] - pos[(i - 1) % pos.size()];
					vector2d v2 = pos[i % pos.size()] - pos[(i + 1) % pos.size()];
					realn deg = PI - std::fabs(VecAngle(v1, v2));
					vector2d v = VecUnit(VecUnit(v1) + VecUnit(v2)) * r;
					for (int j = 0; j < 10; j++) {
						vector2d tmp = v.Rotate(deg * j / 9 - deg / 2);
						p[(i % pos.size()) * 10 + j] = pos[i % pos.size()] - v / cos(deg / 2) + tmp;
					}
				}
				polygon(p, color);
			}
			void round_polygon_lines(std::vector <vector2d> pos, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(pos.size() * 10);
				for (int i = 1; i <= pos.size(); i++) {
					vector2d v1 = pos[i % pos.size()] - pos[(i - 1) % pos.size()];
					vector2d v2 = pos[i % pos.size()] - pos[(i + 1) % pos.size()];
					realn deg = PI - std::fabs(VecAngle(v1, v2));
					vector2d v = VecUnit(VecUnit(v1) + VecUnit(v2)) * r;
					for (int j = 0; j < 10; j++) {
						vector2d tmp = v.Rotate(deg * j / 9 - deg / 2);
						p[(i % pos.size()) * 10 + j] = pos[i % pos.size()] - v / cos(deg / 2) + tmp;
					}
				}
				polygon_lines(p, color);
			}
			void round_polygon_solid(std::vector <vector2d> pos, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(pos.size() * 10);
				for (int i = 1; i <= pos.size(); i++) {
					vector2d v1 = pos[i % pos.size()] - pos[(i - 1) % pos.size()];
					vector2d v2 = pos[i % pos.size()] - pos[(i + 1) % pos.size()];
					realn deg = PI - std::fabs(VecAngle(v1, v2));
					vector2d v = VecUnit(VecUnit(v1) + VecUnit(v2)) * r;
					for (int j = 0; j < 10; j++) {
						vector2d tmp = v.Rotate(deg * j / 9 - deg / 2);
						p[(i % pos.size()) * 10 + j] = pos[i % pos.size()] - v / cos(deg / 2) + tmp;
					}
				}
				polygon_solid(p, color);
			}
			void capsule(vector2d p1, vector2d p2, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(40);
				vector2d v = VecUnit(p1 - p2);
				for (int i = 0; i < 20; i++) {
					vector2d tmp = v.Rotate(PI * i / 19 - PI / 2) * r;
					p[i] = p1 + tmp, p[i + 20] = p2 - tmp;
				}
				polygon(p, color);
			}
			void capsule_lines(vector2d p1, vector2d p2, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(40);
				vector2d v = VecUnit(p1 - p2);
				for (int i = 0; i < 20; i++) {
					vector2d tmp = v.Rotate(PI * i / 19 - PI / 2) * r;
					p[i] = p1 + tmp, p[i + 20] = p2 - tmp;
				}
				polygon_lines(p, color);
			}
			void capsule_solid(vector2d p1, vector2d p2, realn r, Color color = LIGHTPINK) {
				std::vector <vector2d> p(30);
				vector2d v = VecUnit(p1 - p2);
				for (int i = 0; i < 20; i++) {
					vector2d tmp = v.Rotate(PI * i / 19 - PI / 2) * r;
					p[i] = p1 + tmp, p[i + 20] = p2 - tmp;
				}
				polygon_solid(p, color);
			}
			void ellipse(vector2d pos, realn a, realn b, realn rotate = 0, Color color = LIGHTPINK) {
				std::vector <vector2d> p(30);
				for (int i = 0; i < 30; i++) p[i] = rel2abs(vector2d(cos(PI * i / 15) * a, sin(PI * i / 15.0) * b), pos, rotate);
				polygon(p, color);
			}
			void ellipse_lines(vector2d pos, realn a, realn b, realn rotate = 0, Color color = LIGHTPINK) {
				std::vector <vector2d> p(30);
				for (int i = 0; i < 30; i++) p[i] = rel2abs(vector2d(cos(PI * i / 15) * a, sin(PI * i / 15.0) * b), pos, rotate);
				polygon_lines(p, color);
			}
			void ellipse_solid(vector2d pos, realn a, realn b, realn rotate = 0, Color color = LIGHTPINK) {
				std::vector <vector2d> p(30);
				for (int i = 0; i < 30; i++) p[i] = rel2abs(vector2d(cos(PI * i / 15) * a, sin(PI * i / 15.0) * b), pos, rotate);
				polygon_solid(p, color);
			}
			void vector(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				x2 += x1, y2 += y1;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.5);
				vector2d v2 = (b - a).Rotate(-2.5);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, ColorF(color));
				if (Mod(a - b) > 30 * ui::dpi) {
					v1 = VecUnit(v1) * 10 * ui::dpi;
					v2 = VecUnit(v2) * 10 * ui::dpi;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, ColorF(color));
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, ColorF(color));
				} else {
					v1 = VecUnit(v1) * Mod(a - b) / 3.0;
					v2 = VecUnit(v2) * Mod(a - b) / 3.0;
					DrawLine(b.x + X, b.y + Y, b.x + v1.x + X, b.y + v1.y + Y, ColorF(color));
					DrawLine(b.x + X, b.y + Y, b.x + v2.x + X, b.y + v2.y + Y, ColorF(color));
				}
			}
			void vector_head(realn x1, realn y1, realn x2, realn y2, Color color = LIGHTPINK) {
				x2 += x1, y2 += y1;
				a = W2S({x1, y1}), b = W2S({x2, y2});
				vector2d v1 = (b - a).Rotate(2.75);
				vector2d v2 = (b - a).Rotate(-2.75);
				DrawLine(a.x + X, a.y + Y, b.x + X, b.y + Y, ColorF(color));
				vector2d t = vector2d{X, Y};
				if (Mod(a - b) > 37.5 * ui::dpi) {
					v1 = VecUnit(v1) * 12.5 * ui::dpi;
					v2 = VecUnit(v2) * 12.5 * ui::dpi;
					DrawTriangle(_V(b + t), _V(b + v2 + t), _V(b + v1 + t), ColorF(color));
				} else {
					v1 = VecUnit(v1) * Mod(a - b) / 3.0;
					v2 = VecUnit(v2) * Mod(a - b) / 3.0;
					DrawTriangle(_V(b + t), _V(b + v2 + t), _V(b + v1 + t), ColorF(color));
				}
			}
			void vector(realn x, realn y, Color color = LIGHTPINK) {
				vector(0, 0, x, y, color);
			}
			void vector(vector2d v, Color color = LIGHTPINK) {
				vector(0, 0, v.x, v.y, color);
			}
			void vector(vector2d v1, vector2d v2, Color color = LIGHTPINK) {
				vector(v1.x, v1.y, v2.x, v2.y, color);
			}
			void vector_controlled(vector2d* pos, vector2d* dir, Color color = LIGHTPINK) {
				vector(*pos, *dir);
				point_controlled_rel(dir, *pos, 0, color);
				point_controlled(pos, color);
			}
			void vector_controlled(vector2d* dir, Color color = LIGHTPINK) {
				vector(*dir, color);
				point_controlled_rel(dir, {0, 0}, 0, color);
			}
			void vector_head(vector2d v1, vector2d v2, Color color = LIGHTPINK) {
				vector_head(v1.x, v1.y, v2.x, v2.y, color);
			}
			void vector_head_controlled(vector2d* pos, vector2d* dir, Color color = LIGHTPINK) {
				vector_head(*pos, *dir);
				point_controlled_rel(dir, *pos, 0, color);
				point_controlled(pos, color);
			}
			void arrow(vector2d pos, vector2d dir, Color color = LIGHTPINK) {
				dir.y = -dir.y;
				dir = VecUnit(dir);
				a = W2S(pos);
				a += dir * 7 * ui::dpi;
				vector2d v1 = dir.Rotate(2.75);
				vector2d v2 = dir.Rotate(-2.75);
				vector2d t = vector2d{X, Y};
				v1 = VecUnit(v1) * 12.5 * ui::dpi;
				v2 = VecUnit(v2) * 12.5 * ui::dpi;
				DrawTriangle(_V(a + t), _V(a + v2 + t), _V(a + v1 + t), ColorF(color));
			}
			void arrow(realn x, realn y, realn dx, realn dy, Color color = LIGHTPINK) {
				arrow(vector2d{x, y}, vector2d{dx, dy}, color);
			}
			void vector_withAni(vector2d v1, vector2d* v2, Color color = LIGHTPINK) {
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.stp(v2->x);
				v2ani[v2].second.stp(v2->y);
				v2ani[v2].first.update();
				v2ani[v2].second.update();
				v2ani[v2].first.sms(anif::tanh);
				v2ani[v2].second.sms(anif::tanh);
				vector(0, 0, v2ani[v2].first.gnp(), v2ani[v2].second.gnp(), color);
			}
			void vector_withAni(vector2d* v2, Color color = LIGHTPINK) {
				vector_withAni({0, 0}, v2, color);
			}
			void bezier2(vector2d v1, vector2d v2, vector2d v3, Color color = LIGHTPINK) {
				vector2d l = v1;
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector2d p1 = (v2 - v1) * t + v1;
					vector2d p2 = (v3 - v2) * t + v2;
					vector2d p3 = (p2 - p1) * t + p1;
					line(l, p3, color);
					l = p3;
				}
			}
			void bezier3(vector2d v1, vector2d v2, vector2d v3, vector2d v4, Color color = LIGHTPINK) {
				vector2d l = v1;
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector2d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					line(l, p, color);
					l = p;
				}
			}
			void bezier3_mesh(vector2d v1, vector2d v2, vector2d v3, vector2d v4, realn radius = 1, Color color = LIGHTPINK) {
				vector2d l = v1, l1 = v1, l2 = v1;
				for (realn t = 0, i = 0; t <= 1.01; t += 0.02, i++) {
					vector2d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					vector2d dp = v1 * (-3 * t * t + 6 * t - 3) + v2 * (9 * t * t - 12 * t + 3) + v3 * (-9 * t * t + 6 * t) + v4 * (3 * t * t);
					vector2d temp = dp.Rotate(G_PI / 2);
					temp = VecUnit(temp);
					line(l, p, color);
					line(l1, p + temp * radius, color);
					line(l2, p - temp * radius, color);
					if (int(i) % 5 == 0) {
						line(p, p + temp * radius, color);
						line(p, p - temp * radius, color);
					}
					l = p;
					l1 = p + temp * radius;
					l2 = p - temp * radius;
				}
			}
			void function(std::function<realn(realn)> fun, Color color = LIGHTPINK) {
				for (realn i = startx; i <= endx; i += 1.0 / zoom)line(i, fun(i), i + 1.0 / zoom, fun(i + 1.0 / zoom), color);
			}
			void function(std::string fun, Color color = LIGHTPINK) {
				realn last = INT_MAX;
				for (realn i = startx; i <= endx; i += 1.0 / zoom) {
					if (last == INT_MAX) last = eval(fun, {{"x", i}});
					line(i, last, i + 1.0 / zoom, eval(fun, {{"x", i}}), color);
					last = eval(fun, {{"x", i}});
				}
			}
			void function_polar(realn (*fun)(realn), realn start = 0, realn end = PI * 2, int prec = 100, Color color = LIGHTPINK) {
				for (int i = 0; i < prec; i++) {
					realn t1 = start + 1.0 * i * (end - start) / prec;
					realn t2 = start + 1.0 * (i + 1) * (end - start) / prec;
					vector2d k1 = _polar({fun(t1), t1});
					vector2d k2 = _polar({fun(t2), t2});
					line(k1.x, k1.y, k2.x, k2.y, color);
				}
			}
			void function(vector2d (*fun)(realn), realn start = 0, realn end = 10, int prec = 5, Color color = LIGHTPINK) {
				for (realn i = start; i < end; i += 1.0 / prec)line(fun(i).x, fun(i).y, fun(i + 1.0 / prec).x, fun(i + 1.0 / prec).y, color);
			}
			void mesh(vector2d (*mesh)(realn, realn), realn sx, realn ex, realn sy, realn ey, realn space = 1.0, int prec = 5, Color color = LIGHTPINK) {
				for (realn i = sx; i <= ex; i += space) {
					for (realn j = sy; j < ey; j += space / prec) {
						line(mesh(i, j), mesh(i, j + space / prec), color);
					}
				}
				for (realn j = sy; j <= ey; j += space) {
					for (realn i = sx; i < ex; i += space / prec) {
						line(mesh(i, j), mesh(i + space / prec, j), color);
					}
				}
			}
			void liner_transformation(realn m11, realn m12, realn m21, realn m22, realn r = 10, realn space = 1.0, Color color = LIGHTPINK) {
				realn r2 = ceil(r / space) * space;
				for (realn i = -r2; i <= r2; i += space) {
					line(m11 * i + m12 * (-r), m21 * i + m22 * (-r), m11 * i + m12 * r, m21 * i + m22 * r, color);
					line(m11 * (-r) + m12 * i, m21 * (-r) + m22 * i, m11 * r + m12 * i, m21 * r + m22 * i, color);
				}
			}
			void liner_transformation_withAni(realn m11, realn m12, realn m21, realn m22, realn r = 10, realn space = 1.0, Color color = LIGHTPINK) {
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				ilenAni.stp(sqrt(m11 * m11 + m21 * m21));
				jlenAni.stp(sqrt(m12 * m12 + m22 * m22));
				if (fabs(atan2(m21, m11) - idegAni.gnp()) > fabs(atan2(m21, m11) - idegAni.gnp() + 3.1415926535897932 * 2))idegAni.stp(atan2(m21, m11) + 3.1415926535897932 * 2);
				else if (fabs(atan2(m21, m11) - idegAni.gnp()) > fabs(atan2(m21, m11) - idegAni.gnp() - 3.1415926535897932 * 2))idegAni.stp(atan2(m21, m11) - 3.1415926535897932 * 2);
				else idegAni.stp(atan2(m21, m11));
				if (fabs(atan2(m22, m12) - jdegAni.gnp()) > fabs(atan2(m22, m12) - jdegAni.gnp() + 3.1415926535897932 * 2))jdegAni.stp(atan2(m22, m12) + 3.1415926535897932 * 2);
				else if (fabs(atan2(m22, m12) - jdegAni.gnp()) > fabs(atan2(m22, m12) - jdegAni.gnp() - 3.1415926535897932 * 2))jdegAni.stp(atan2(m22, m12) - 3.1415926535897932 * 2);
				else jdegAni.stp(atan2(m22, m12));
				ilenAni.Update();
				idegAni.Update();
				jlenAni.Update();
				jdegAni.Update();
				realn il = ilenAni.gnp(), jl = jlenAni.gnp();
				realn id = idegAni.gnp(), jd = jdegAni.gnp();
				realn ix = il * cos(id), iy = il * sin(id);
				realn jx = jl * cos(jd), jy = jl * sin(jd);
				liner_transformation(ix, jx, iy, jy, r, space, color);
				vector(ix, iy, RED);
				vector(jx, jy, BLUE);
			}
			void shape(pg::shape& sh, Color color = LIGHTPINK) {
				sh.Draw(Color2Int(color));
				point(sh.pos, color);
				line(sh.pos, sh.pos + vector2d{0.3, 0}.Rotate(sh.rotate), color);
			}
			void shape_withAABB(pg::shape& sh, Color color = LIGHTPINK) {
				shape(sh);
				rectangle(sh.CalcAABB());
			}
			void shape_lines(pg::shape& sh, Color color = LIGHTPINK) {
				Color color2 = ColorF(color);
				sh.DrawLines(Color2Int(color));
				point(sh.pos, color);
				line(sh.pos, sh.pos + vector2d{0, 0.3}.Rotate(sh.rotate), color);
			}
			void shape_controlled(pg::shape& shape, Color color = LIGHTPINK) {
				Color color2 = ColorF(color);
				shape.Draw(Color2Int(color));
				line(shape.pos, shape.pos + vector2d{0, 0.3}.Rotate(shape.rotate), color);
				point_controlled(&shape.pos, color);
			}
			void shape_controlled_withAABB(pg::shape& shape, Color color = LIGHTPINK) {
				rectangle(shape.CalcAABB(), color);
				shape_controlled(shape, color);
			}

			vector2d last_mouse_pos{0, 0};
			Scene& StartSetting(std::function <void()> fun) {
				plot = this;
				fun();
				return *this;
			}
			void CalcStartEnd() {
				startx = S2W({0, 0}).x, endx = S2W({W, 0}).x;
				starty = S2W({0, H}).y, endy = S2W({0, 0}).y;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				X = x, Y = y, W = w, H = h, CHECK = check;
				BeginScissor(x, y, w, h);
				zoom_ani.Update();
				zoom = pow(10, zoom_ani.gnp()) * w / 1080;
				startx = S2W(vector2d(0, 0)).x, endx = S2W(vector2d(w, 0)).x;
				starty = S2W(vector2d(0, h)).y, endy = S2W(vector2d(0, 0)).y;
				realn wspace = pow(10, std::ceil(log10(30 * dpi / zoom)));
				realn sspace = wspace * zoom;
				float_point = false;
				vector2d O = W2S({0, 0});

				if (movable) {
					if (MouseInRect(x, y, w, h) && check) UseSliderX = UseSliderY = true;
					if (IsMousePressed(MOUSE_BUTTON_LEFT) || (IsKeyPressed(KEY_LEFT_CONTROL) && ctrl_to_move)) {
						click_time = GetTime();
						if (!ctrl_to_move || IsKeyDown(KEY_LEFT_CONTROL)) {
							if (MouseInRect(x, y, w, h) && check && !ChooseSlider) {
								choose = true;
								choose_pos = S2W(_v(Mouse) - vector2d(x, y));
							}
						}
					}
					if (!IsMouseDown(MOUSE_BUTTON_LEFT) && check)choose = false;
					vector2d move = S2W(_v(Mouse) - vector2d(x, y)) - choose_pos;
					if (choose && !ChooseSlider && check) {
						if (Mod(_v(Mouse) - last_mouse_pos) > move_threshold_dist || GetTime() - click_time > move_threshold_time) camera -= move;
						startx = S2W(vector2d(0, 0)).x, endx = S2W(vector2d(w, 0)).x;
						starty = S2W(vector2d(0, h)).y, endy = S2W(vector2d(0, 0)).y;
						O = W2S({0, 0});
					}
					if (Mod(_v(Mouse) - last_mouse_pos) > 0 && (Mod(_v(Mouse) - last_mouse_pos) > move_threshold_dist || GetTime() - click_time > move_threshold_time))mouse_move = true;
					else mouse_move = false;
					if (!IsMouseDown(MOUSE_BUTTON_LEFT) && !IsMouseDown(MOUSE_BUTTON_RIGHT)) last_mouse_pos = _v(Mouse);
				} else mouse_move = false;

				if (mesh_visible) {
					if (sspace / 10.0 > 10 * dpi) {
						realn a = (sspace / 10 - 10 * dpi) / (20.0 * dpi);
						if (std::ceil(log10(30 * dpi / zoom)) >= mesh_min + 1) DrawMesh_(sspace / 10, Color{60, 60, 60, (unsigned char)(a * 255)});
						if (std::ceil(log10(30 * dpi / zoom)) >= mesh_min) DrawMesh_(sspace, Color{(unsigned char)(60 + 60 * a), (unsigned char)(60 + 60 * a), (unsigned char)(60 + 60 * a), 255}, number_visible);
						if (std::ceil(log10(30 * dpi / zoom)) >= mesh_min - 1) DrawMesh_(sspace * 10, Color{ (unsigned char)(120 + 60 * a), (unsigned char)(120 + 60 * a), (unsigned char)(120 + 60 * a), 255});
					} else {
						if (std::ceil(log10(30 * dpi / zoom)) >= mesh_min) DrawMesh_(sspace, Color{60, 60, 60, 255}, number_visible);
						if (std::ceil(log10(30 * dpi / zoom)) >= mesh_min - 1) DrawMesh_(sspace * 10, Color{120, 120, 120, 255});
					}
				}
				if (polar_visible) {
				}
				if (axis_visible) {
					DrawRectangle(x + O.x - 3 * dpi, y + O.y - 3 * dpi, 6 * dpi, 6 * dpi, ColorF(LIGHTGRAY));
					DrawLine(x, y + O.y, x + w, y + O.y, ColorF(LIGHTGRAY));
					DrawLine(x + O.x, y, x + O.x, y + h, ColorF(LIGHTGRAY));
				}
				zoom_ani.update();
				if (ChooseSlider == nullptr)zoom_slider.num = zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (draw_fun != nullptr) {
					BeginScissor(X, Y, W, H);
					plot = this;
					draw_fun();
					EndScissor();
				}
				if (zoom_visible) {
					zoom_slider.minn = zoom_min;
					zoom_slider.maxn = zoom_max;
					int tw = std::min(int(300 * dpi), w - ui::SpaceSize * 4);
					DrawRectangleRounded({float(x) + w / 2 - tw / 2, float(y + h - UnitHeight - SpaceSize * 1.5), (float)tw, (float)UnitHeight + SpaceSize}, 1, 10, ColorF(50, 50, 70, 150));
					zoom_slider.Draw_Auto(x + w / 2 - (tw - 80) / 2, y + h - UnitHeight - SpaceSize, (tw - 80));
				}
				zoom_ani.update();
				if (ChooseSlider == nullptr)zoom_slider.num = zoom_ani.gnp();
				else zoom_ani.stp(zoom_slider.num);
				if (MouseInRect(x, y, w, h) && check) {
					if (IsMouseDown(MOUSE_BUTTON_LEFT) && choose && !ChooseSlider) {
						DrawCircle(Mouse.x, Mouse.y, 7 * dpi, ColorF(255, 255, 255, 100));
					}
					zoom_ani.stp(zoom_ani.gtp() + GetMouseWheelMove() / 10.0);
					if (zoom_ani.gtp() < zoom_min)zoom_ani.stp(zoom_min);
					if (zoom_ani.gtp() > zoom_max)zoom_ani.stp(zoom_max);
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
		class Scene3D : public Element {
		private:
			realn f(realn a) {
				return a - floor(a);
			}
			realn window_scale = 1;

		public:
			Camera3D camera = { 0 };
			std::function<void()> draw_fun;

			bool axis_visible = true;
			bool zoom_visible = true;
			bool mesh_visible = true;
			bool movable = true;

			Scene3D(std::function<void()> DrawFun = nullptr) {
				extra = true;
				// 初始化摄像机
				camera.position = Vector3 {2.0f, 2.0f, 2.0f}; //相机所在位置{x,y,z}
				camera.target = Vector3 {0.0f, 0.0f, 0.0f}; //相机朝向位置{x,y,z}
				camera.up = Vector3 {0.0f, 0.0f, 1.0f}; //相机正上方朝向矢量
				camera.fovy = 70;
				camera.projection = CAMERA_PERSPECTIVE;
				// 绘制函数
				draw_fun = DrawFun;
			}
			void set_position(vector3d pos) {
				camera.position = _V(pos);
			}
			void set_target(realn level, realn vertical) {
				camera.target = _V(VecUnit(level, vertical) + _v(camera.position));
			}
			void set_target(vector3d pos) {
				camera.target = _V(pos);
			}
			void point(vector3d pos, Color color = LIGHTPINK) {
				realn dist = Mod(_v(camera.position) - pos);
				DrawSphere(_V(pos), 0.007 * dist * 1000.0 / (window_scale * winH), ColorF(color));
			}
			void vector_rotate(vector3d start, vector3d v, Color color = LIGHTPINK) {
				DrawLine3D(_V(start), _V(v + start), ColorF(color));
				vector3d v2 = Cross(v, {0, 0, 1});
				if (v2 == vector3d{0, 0, 0})v2 = Cross(v, {0, 1, 0});
				vector3d v31 = VecUnit(v.Rotate(v2, PI / 8) * (-1));
				vector3d v32 = VecUnit(v.Rotate(v2, -PI / 8) * (-1));
				v31 = v31.Rotate(v, gclock() / 200.0);
				v32 = v32.Rotate(v, gclock() / 200.0);
				vector3d v41 = v + v31 * Mod(v) / 10;
				vector3d v42 = v + v32 * Mod(v) / 10;
				DrawLine3D(_V(v + start), _V(v41 + start), ColorF(color));
				DrawLine3D(_V(v + start), _V(v42 + start), ColorF(color));
			}
			void line(vector3d v1, vector3d v2, Color color = LIGHTPINK) {
				DrawLine3D(_V(v1), _V(v2), ColorF(color));
			}
			void cube(vector3d pos, realn w = 1, realn h = 1, realn l = 1, Color color = LIGHTPINK) {
				DrawCube(_V(pos), w, h, l, MixColor(ColorF(color), BgColor, 0.2));
				DrawCubeWires(_V(pos), w, h, l, ColorF(color));
			}
			void sphere(vector3d pos, realn r = 0.5, Color color = LIGHTPINK) {
				DrawSphere(_V(pos), r, MixColor(ColorF(color), BgColor, 0.2));
				DrawCircle3D(_V(pos), r * 1.002, {0, 0, 1}, 0, ColorF(color));
				DrawCircle3D(_V(pos), r * 1.002, {0, 1, 0}, 90, ColorF(color));
				DrawCircle3D(_V(pos), r * 1.002, {1, 0, 0}, 90, ColorF(color));
			}
			void cylinder(vector3d v1, realn r = 0.5, realn r2 = 0.5, realn h = 1, int slices = 3, Color color = LIGHTPINK) {
				DrawCylinder(_V(v1), r, r2, h, slices, MixColor(ColorF(color), BgColor, 0.2));
				DrawCylinderWires(_V(v1), r, r2, h, slices, ColorF(color));
			}
			void cylinder(vector3d v1, vector3d v2, realn r = 0.5, realn r2 = 0.5, int slices = 3, Color color = LIGHTPINK) {
				DrawCylinderEx(_V(v1), _V(v2), r, r2, slices, MixColor(ColorF(color), BgColor, 0.2));
				DrawCylinderWiresEx(_V(v1), _V(v2), r, r2, slices, ColorF(color));
			}
			void vector(vector3d start, vector3d v, Color color = LIGHTPINK) {
				DrawLine3D(_V(start), _V(v + start), ColorF(color));
				DrawCylinderEx(_V(start + v * 0.9), _V(start + v), Mod(v * 0.02), 0, 10, MixColor(ColorF(color), BgColor, 0.2));
			}
			void vector(vector3d v, Color color = LIGHTPINK) {
				vector({0, 0, 0}, v, color);
			}
			void vector(realn x, realn y, realn z, Color color = LIGHTPINK) {
				vector({0, 0, 0}, {x, y, z}, color);
			}
			void capsule(vector3d v1, vector3d v2, realn r, Color color = LIGHTPINK) {
				DrawCapsule(_V(v1), _V(v2), r, 15, 10, MixColor(ColorF(color), BgColor, 0.5));
				DrawCapsuleWires(_V(v1), _V(v2), r, 3, 10, ColorF(color));
			}
			void bezier2(vector3d v1, vector3d v2, vector3d v3, Color color = LIGHTPINK) {
				vector3d l = v1;
				line(v1, v2, GRAY);
				line(v2, v3, GRAY);
				point(v1);
				point(v2);
				point(v3);
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector3d p1 = (v2 - v1) * t + v1;
					vector3d p2 = (v3 - v2) * t + v2;
					vector3d p3 = (p2 - p1) * t + p1;
					line(l, p3, color);
					l = p3;
				}
			}
			void bezier3(vector3d v1, vector3d v2, vector3d v3, vector3d v4, Color color = LIGHTPINK) {
				vector3d l = v1;
				line(v1, v2, GRAY);
				line(v3, v4, GRAY);
				point(v1);
				point(v2);
				point(v3);
				point(v4);
				for (realn t = 0.02; t <= 1.01; t += 0.02) {
					vector3d p = v1 * (-t * t * t + 3 * t * t - 3 * t + 1) + v2 * (3 * t * t * t - 6 * t * t + 3 * t) + v3 * (-3 * t * t * t + 3 * t * t) + v4 * (t * t * t);
					line(l, p, color);
					l = p;
				}
			}

			int Draw(int x, int y, int w, int h, bool check = true) {
				plot3 = this;
				BeginMode3D(camera);
				double k = pow(10, round(log10(fabs(camera.position.z)))), k01 = k / 10.0;
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
							int y2 = ceil(j + camera.position.y / k01);
							realn x = x2 * k01, y = y2 * k01;
							realn distance = sqrtf((x - camera.position.x) * (x - camera.position.x) + (y - camera.position.y) * (y - camera.position.y));

							// 根据距离设置线段的颜色
							if (1.0f - distance * 0.03f / fabs(camera.position.z) * 10 < 0)continue;
							Color lineColor = Color {150, 150, 150, (unsigned char)(255 * ((1 - f(log10(fabs(camera.position.z)) - 0.5))) * (1.0f - distance * 0.03f / fabs(camera.position.z) * 10))};

							// 绘制线段
							if (x2 % 10 != 0)DrawLine3D(Vector3{x, y, 0.0f}, Vector3{x, float(y + k01), 0.0f}, lineColor);
							if (y2 % 10 != 0)DrawLine3D(Vector3{x, y, 0.0f}, Vector3{float(x + k01), y, 0.0f}, lineColor);
						}
					}
					for (int i = -60; i <= 60; i ++) {
						for (int j = -60; j <= 60; j ++) {
							// 计算线段的距离
							int x2 = ceil(i + camera.position.x / k);
							int y2 = ceil(j + camera.position.y / k);
							realn x = x2 * k, y = y2 * k;
							float distance = sqrtf((x - camera.position.x) * (x - camera.position.x) + (y - camera.position.y) * (y - camera.position.y));

							// 根据距离设置线段的颜色
							if (1.0f - distance * 0.03f / fabs(camera.position.z) * 9 < 0)continue;
							Color lineColor = Color {150, 150, 150, (unsigned char)(255 * (1.0f - distance * 0.03f / fabs(camera.position.z) * 9))};

							// 绘制线段
							if (x2 != 0)DrawLine3D(Vector3{x, y, 0.0f}, Vector3{x, float(y + k), 0.0f}, lineColor);
							if (y2 != 0)DrawLine3D(Vector3{x, y, 0.0f}, Vector3{float(x + k), y, 0.0f}, lineColor);
						}
					}
				}
				if (axis_visible) {
					DrawLine3D(Vector3{10000, 0, 0}, Vector3{-10000, 0, 0}, Color{231, 162, 154, 255});/*x*/
					DrawLine3D(Vector3{0, 10000, 0}, Vector3{0, -10000, 0}, Color{140, 128, 191, 255});/*y*/
					DrawLine3D(Vector3{0, 0, 10000}, Vector3{0, 0, -10000}, Color{255, 128, 192, 255});/*z*/
				}
				if (draw_fun) draw_fun();

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
		struct InputHistory {
			InputBoxOperation op = operation_insert;
			vector2d pos1;
			vector2d pos2;
			std::string str;
			realn time;
		};
		class InputBox : public Element {
		private:
			int choose_start = 0;
			int choose_end = 0;
			int choose_pos;
			int choose_pos2;
			bool choose_word = false;
			bool choose_word_on = false;
			bool choose_minimap = false;
			std::stack<InputHistory> history;
			std::stack<InputHistory> history2;
			Animation ipa;
			Animation spa;
			Animation move;
			int last_history_len = -1;
			std::string* input_ptr = nullptr;
		public:
			std::string input = "";
			int input_pos = 0;
			int fix_time = 0;
			int start_pos = 0;
			bool choose = false;
			bool chosen = false;

			Color background_color = ui::BgColor;
			bool input_enable = true;
			bool auto_complete = true;
			int box_height = UnitHeight * 1.2;

			InputBox() {
				ipa.sd(100);
				spa.sd(200);
			}
			InputBox(std::string content_, std::string* input_) {
				ipa.sd(100);
				spa.sd(200);
				content = content_;
				input_ptr = input_;
			}
			realn GetPos(realn v) {
				int tempx = X - spa.gnp() + ui::SpaceSize;
				return tempx + ui::TextHeight / 2 * v;
			}
			void SetFocus() {
				ChooseInputBox = this;
				fix_time = gclock() - 500;
			}
			std::string Copy(int pos1, int pos2) {
				if (pos1 < 0)pos1 = 0;
				if (pos1 > input.size())pos1 = input.size();
				if (pos2 < 0)pos2 = 0;
				if (pos2 > input.size())pos2 = input.size();
				if (pos1 > pos2)std::swap(pos1, pos2);
				return input.substr(pos1, pos2 - pos1);
			}
			std::string CopyAll() {
				return Copy(0, input.size());
			}
			int Insert(int pos, std::string str) {
				if (pos < 0)pos = 0;
				if (pos > input.size())pos = input.size();
				std::string str2 = "";
				for (int i = 0; i < str.size(); i++) {
					if (str[i] == '\r' && str[i + 1] == '\n')str2 += "  ", i++;
					else if (str[i] == '\n')str2 += "  ";
					else if (str[i] == '\t')str2 += "    ";
					else str2 += str[i];
				}
				str = str2;
				input.insert(pos, str);

				InputHistory temp_history;
				temp_history.op = operation_insert;
				temp_history.pos1 = vector2d(pos, 0);
				temp_history.pos2 = vector2d(pos + str.size(), 0);
				temp_history.str = str;
				if (history.empty())history.push(temp_history);
				else {
					InputHistory temp2 = history.top();
					if (temp_history.op == temp2.op && temp_history.pos1 == temp2.pos2) {
						history.pop();
						temp2.str += temp_history.str;
						temp2.pos2 = temp_history.pos2;
						history.push(temp2);
					} else history.push(temp_history);
				}

				return pos + str.size();
			}
			int InsertBack(std::string str) {
				return Insert(input.size(), str);
			}
			int Delete(int pos1, int pos2) {
				if (pos1 < 0)pos1 = 0;
				if (pos1 > input.size())pos1 = input.size();
				if (pos2 < 0)pos2 = 0;
				if (pos2 > input.size())pos2 = input.size();
				if (pos1 > pos2)std::swap(pos1, pos2);
				std::string backup = Copy(pos1, pos2);
				input.erase(pos1, pos2 - pos1);

				InputHistory temp_history;
				temp_history.op = operation_delete;
				temp_history.pos1 = vector2d(pos1, 0);
				temp_history.pos2 = vector2d(pos2, 0);
				temp_history.str = backup;
				if (history.empty())history.push(temp_history);
				else {
					InputHistory temp2 = history.top();
					if (temp_history.op == temp2.op && temp_history.pos2 == temp2.pos1) {
						history.pop();
						temp2.str = temp_history.str + temp2.str;
						temp2.pos1 = temp_history.pos1;
						history.push(temp2);
					} else history.push(temp_history);
				}

				return pos1;
			}
			int GetEnd() {
				return input.size();
			}
			int Clear() {
				return Delete(0, GetEnd());
			}
			int Undo() {
				if (last_history_len != history.size()) {
					std::stack<InputHistory>().swap(history2);
					last_history_len = history.size();
				}
				if (history.empty())return input_pos;
				InputHistory temp = history.top();
				int v;
				history.pop();
				if (temp.op == operation_insert) {
					v = Delete(temp.pos1.x, temp.pos2.x);
					history.pop();
				} else if (temp.op == operation_delete) {
					v = Insert(temp.pos1.x, temp.str);
					history.pop();
				}
				history2.push(temp);
				last_history_len = history.size();
				return v;
			}
			int Redo() {
				if (last_history_len != history.size()) {
					std::stack<InputHistory>().swap(history2);
					last_history_len = history.size();
				}
				if (history2.empty())return input_pos;
				InputHistory temp = history2.top();
				int v;
				history2.pop();
				if (temp.op == operation_insert) {
					v = Insert(temp.pos1.y, temp.str);
					history.pop();
				} else if (temp.op == operation_delete) {
					v = Delete(temp.pos1.y, temp.pos2.y);
					history.pop();
				}
				history.push(temp);
				last_history_len = history.size();
				return v;
			}
			int Draw(int x, int y, int w, bool check = true) {
				// 初始化
				ipa.update();
				spa.update();
				move.update();
				int h = ( box_height -  TextHeight) / 2;
				char c =  GetChar;
				ipa.stp(wp::Index2Cursor(input, input_pos));
				spa.stp(start_pos);
				BeginScissor(x, y, w,  box_height);
				// 绘制主体
				DrawRectangle(x, y, w, box_height, ColorF(background_color));
				Print(x +  SpaceSize - spa.gnp()* TextHeight / 2, y + h, input);
				if (input.size() == 0)Print(x +  SpaceSize - spa.gnp() * TextHeight / 2, y + h, content, ColorF(GRAY));
				if (input_ptr) *input_ptr = input;
				// 焦点检查
				if ( MouseInRect(x, y, w,  box_height)) {
					MouseCursorStyle = MOUSE_CURSOR_IBEAM;
					if (IsMousePressed(MOUSE_BUTTON_LEFT)) SetFocus();
				} else if (IsMousePressed(MOUSE_BUTTON_LEFT) && ChooseInputBox == this)ChooseInputBox = nullptr;
				if (!choose && ChooseInputBox == this)choose = true, move.stp(1);
				if (choose && ChooseInputBox != this)choose = false, move.stp(0), start_pos = input_pos = choose_pos = choose_pos2 = 0;;
				if (choose) {
					// 鼠标检查
					if ( MouseInRect(x +  SpaceSize, y + h / 2, w -  SpaceSize,  box_height - h)) {
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							int k =  Mouse.x - x -  SpaceSize;
							int k2 = round(1.0 * k * 2 /  TextHeight) + start_pos;
							k2 = std::min(k2, int(input.size()));
							input_pos = wp::Cursor2Index(input, k2);
							choose_word = true;
							choose_pos = input_pos;
						}
					}
					// 是否取消选择文本
					if (choose_word) {
						if (IsMouseDown(MOUSE_BUTTON_LEFT)) {
							int k =  Mouse.x - x -  SpaceSize;
							int k2 = round(1.0 * k * 2 /  TextHeight) + start_pos;
							k2 = std::min(k2, int(input.size()));
							input_pos = wp::Cursor2Index(input, k2);
						}
					}
					if (!IsMouseDown(MOUSE_BUTTON_LEFT))choose_word = false;
					// 如果选择文本，计算选择起止点
					if (choose_word) {
						int k =  Mouse.x - x -  SpaceSize;
						int k2 = wp::Cursor2Index(input, round(1.0 * k * 2 /  TextHeight) + start_pos);
						if (k2 != choose_pos) {
							choose_word_on = true;
							choose_pos2 = k2;
						} else {
							choose_word_on = false;
						}
					}
					bool delete_choose = false;
					if (choose_word_on) {
						// 绘制起止光标间的阴影
						int x1 = x +  SpaceSize +  TextHeight / 2 * (wp::Index2Cursor(input, choose_pos) - spa.gnp()) -  dpi;
						int x2 = x +  SpaceSize +  TextHeight / 2 * (wp::Index2Cursor(input, choose_pos2) - spa.gnp()) -  dpi;
						if (x1 > x2)std::swap(x1, x2);
						int tx1 = std::max(x1, x);
						int tx2 = std::min(x2, x + w);
						Color color = MainColor;
						color.a = 100;
						DrawRectangle(x1, y + h / 2, x2 - x1, box_height - h, ColorF(color));
						// 绘制起止光标
						DrawRectangle(x1, y, 2 *  dpi,  box_height, ColorF(ThemeColor));
						DrawRectangle(x2, y, 2 *  dpi,  box_height, ColorF(ThemeColor));
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
					// 输入检查
					if (input_enable) {
						// 特殊按键、快捷键输入检查
						if (ui::IsKeyInput(KEY_BACKSPACE) && !delete_choose)input_pos = Delete(input_pos - wp::GetPreCharacter(input, input_pos), input_pos);
						else if (ui::IsKeyInput(KEY_DELETE) && !delete_choose)input_pos = Delete(input_pos + wp::GetNextCharacter(input, input_pos), input_pos);
						else if (ui::IsKeyInput(KEY_LEFT) && input_pos > 0)input_pos -= wp::GetPreCharacter(input, input_pos);
						else if (ui::IsKeyInput(KEY_RIGHT) && input_pos < input.size())input_pos += wp::GetNextCharacter(input, input_pos);
						else if (IsKeyInput(KEY_END))input_pos = input.size();
						else if (IsKeyInput(KEY_HOME))input_pos = 0;
						else if (IsKeyInput(KEY_TAB))input_pos = Insert(input_pos, "    ");
						if (IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT)) {
							if (choose_word_on) {
								if (IsKeyPressed(KEY_C)) {
									SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
									ui::message::Send_Tip("已复制到剪切板");
								} else if (IsKeyPressed(KEY_X)) {
									ui::message::Send_Tip("已复制到剪切板");
									choose_pos2 = input_pos;
									SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
									input_pos = Delete(choose_pos, choose_pos2);
									choose_word_on = false;
								}
							}
							if (IsKeyPressed(KEY_A)) {
								choose_word_on = true;
								choose_pos = 0;
								choose_pos2 = GetEnd();
								input_pos = choose_pos2;
							}
							if (ui::IsKeyInput(KEY_V)) {
								if (choose_word_on) {
									input_pos = Delete(choose_pos, input_pos);
									choose_word_on = false;
								}
								try {
									std::string str = GetClipboardText();
									input_pos = Insert(input_pos, str);
								} catch (...) {
									ui::message::Send_Error("[CRASH #001] ");
								}
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
									if (str == "<" && input[0] == '#')Insert(input_pos, ">");
									if (str == "(")Insert(input_pos, ")");
									if (str == "[")Insert(input_pos, "]");
									if (str == "{")Insert(input_pos, "}");
									if (str == "\'")Insert(input_pos, "\'");
									if (str == "\"")Insert(input_pos, "\"");
								}
							}
						}
					}
					if (!choose_word) {
						while ((ipa.gtp() - start_pos) * TextHeight / 2 > w -  SpaceSize * 2)start_pos += w /  TextHeight;
						while ((ipa.gtp() - start_pos) * TextHeight / 2 < 0)start_pos -= w /  TextHeight;
					} else {
						while ((ipa.gtp() - start_pos) * TextHeight / 2 > w -  SpaceSize * 2)start_pos ++;
						while ((ipa.gtp() - start_pos) * TextHeight / 2 < 0)start_pos --;
					}
					if (start_pos < 0)start_pos = 0;
				} else start_pos = 0;
				// 焦点检查
				if (!check && IsMousePressed(MOUSE_BUTTON_LEFT))start_pos = input_pos = choose_pos = choose_pos2 = 0;
				if (!choose && ChooseInputBox == this)choose = true, move.stp(1).sms(anif::classics);
				if (choose && ChooseInputBox != this)choose = false, move.stp(0).sms(anif::classics_r);
				// 绘制光标
				if (choose && !choose_word_on) {
					int a = (gclock() - fix_time) % 1000;
					if (a < 300)a = 200;
					else if (a < 500)a = 500 - a;
					else if (a < 800)a = 0;
					else a = a - 800;
					a = a * 255 / 200;
					for (int i = 1; i <= 350; i++)if (IsKeyDown(i))a = 200, fix_time = gclock();
					DrawRectangle(x +  SpaceSize +  TextHeight / 2 * (ipa.gnp() - spa.gnp()) -  dpi, y, 2 *  dpi,  box_height, ColorF(232, 192, 114, a));
				}
				DrawRectangle(x + w / 2 - w * move.gnp() / 2, y + box_height - 3 * dpi, w * move.gnp(), 3 * dpi,  ColorF(MainColor, move.gnp()));
				// 结束！
				EndScissor();
				return  box_height;
			}
		};
		class MultiInputBox : public  ui::Element {
		private:
			int choose_start = 0;					// 我也不知道这是干啥的
			int choose_end = 0;						// 我也不知道这是干啥的
			bool choose_word = false;				// 是否准备选择文本awa
			bool choose_word_on = false;			// 是否选择文本
			bool choose_minimap = false;			// 是否选择小地图
			bool change = false;					// 是否出现改动
			int choose_minimap_delta = 0;			// 我也不知道这是干啥的
			vector2d choose_pos = {0, 0};			// 选择起始点
			vector2d choose_pos1 = {0, 0};			// 选择起始点
			vector2d choose_pos2 = {0, 0};			// 选择终止点
			Animation ipx, ipy;						// 光标行、列位置动画
			std::mutex writemtx;					// 写锁

		public:
			std::vector<std::string> input;			// 文本
			vector2d input_pos = {0, 0};			// 光标位置
			vector2d size = {0, 0};					// 代码版面大小
			int fix_time = 0;						// 我也不知道这是干啥的
			bool choose = false;					// 是否选择
			int multi_height = 5;					// 处于普通控件状态时的高度
			bool chosen = false;					// 是否处于焦点
			Color background_color = BgColor;		// 背景色
			std::vector<std::vector<highlight::Type> > color;// 代码高亮
			ui::SliderBar sx, sy;					// 横向、纵向滚动条

			bool label_visible = false;				// 是否显示行号
			bool auto_complete = true;				// 是否使用自动补全
			bool minimap_visible = false;			// 是否显示小地图
			bool highlight_visible = true;			// 是否高亮当前行
			bool input_enable = true;				// 是否可以输入
			bool modify_enable = true;				// 是否可以修改
			bool space_visible = false;				// 是否显示空白字符
			bool tabline_visible = false;			// 是否显示缩进提示线
			bool statebar_visible = false;			// 是否显示状态栏
			bool shadow_visible = false;			// 是否显示小地图、行号栏的阴影
			int minimap_width = 100 * dpi;			// 小地图宽度
			int label_width = 60 * dpi;				// 行号栏宽度

			std::stack<InputHistory> history;		// 操作历史（用于撤销）
			std::stack<InputHistory> history2;		// 撤销历史（用于重做）
			int last_history_len = -1;				// 我也不知道这是干啥的

			MultiInputBox(std::string content_ = "MultiInputBox") {
				ipx.sd(100), ipy.sd(150);
				extra = true;
				sx.SetBlank(0), sy.SetBlank(0);
				input.push_back("");
				content = content_;
			}
			MultiInputBox& SetLabelVisible(bool on) {
				label_visible = on;
				return *this;
			}
			MultiInputBox& SetAutoComplete(bool on) {
				auto_complete = on;
				return *this;
			}
			MultiInputBox& SetMinimapVisible (bool on) {
				minimap_visible = on;
				return *this;
			}
			MultiInputBox& SetHighlightVisible(bool on) {
				highlight_visible = on;
				return *this;
			}
			MultiInputBox& SetInputEnable(bool on) {
				input_enable = on;
				return *this;
			}
			MultiInputBox& SetModifyEnable(bool on) {
				modify_enable = on;
				return *this;
			}
			MultiInputBox& SetSpaceVisible (bool on) {
				space_visible = on;
				return *this;
			}
			MultiInputBox& SetTablineVisible(bool on) {
				tabline_visible = on;
				return *this;
			}
			MultiInputBox& SetStatebarVisible(bool on) {
				statebar_visible = on;
				return *this;
			}
			MultiInputBox& SetShadowVisible(bool on) {
				shadow_visible = on;
				return *this;
			}
			MultiInputBox& SetCodeDefaultMode() {
				label_visible = true;
				auto_complete = true;
				minimap_visible = true;
				highlight_visible = true;
				input_enable = true;
				modify_enable = true;
				space_visible = false;
				tabline_visible = true;
				statebar_visible = true;
				shadow_visible = false;
				return *this;
			}
			MultiInputBox& SetTextDefaultMode() {
				label_visible = false;
				auto_complete = true;
				minimap_visible = false;
				highlight_visible = true;
				input_enable = true;
				modify_enable = true;
				space_visible = false;
				tabline_visible = false;
				statebar_visible = false;
				shadow_visible = false;
				return *this;
			}
			vector2d GetPos(vector2d v) {
				int tempW = 0;
				if (label_visible)tempW = ui::TextHeight * 4 - SpaceSize;
				int tempx = X - sx.Now() + ui::SpaceSize + tempW;
				int tempy = Y - sy.Now() + ui::SpaceSize;
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				return vector2d {
					tempx + ui::TextHeight / 2 * v.x,
					tempy + ui::UnitHeight * v.y
				};
			}
			std::string Copy(vector2d pos1, vector2d pos2) {
				if (pos1.y < 0)pos1.y = 0;
				if (pos1.x < 0)pos1.x = 0;
				if (pos1.y >= input.size())pos1.y = input.size() - 1;
				if (pos1.x >= input[pos1.y].size())pos1.x = input[pos1.y].size();
				if (pos2.y < 0)pos2.y = 0;
				if (pos2.x < 0)pos2.x = 0;
				if (pos2.y >= input.size())pos2.y = input.size() - 1;
				if (pos2.x >= input[pos2.y].size())pos2.x = input[pos2.y].size();
				vector2d v1, v2;
				if (pos1.y < pos2.y)v1 = pos1, v2 = pos2;
				else if (pos1.y > pos2.y)v1 = pos2, v2 = pos1;
				else  {
					if (pos1.x < pos2.x)v1 = pos1, v2 = pos2;
					else v2 = pos1, v1 = pos2;
				}
				std::string temp_str = "";
				if (v1.y != v2.y) {
					temp_str += input[v1.y].substr(v1.x, input[v1.y].size()) + "\r\n";
					for (int i = v1.y + 1; i <= v2.y - 1; i++)temp_str += input[i] + "\r\n";
					temp_str += input[v2.y].substr(0, v2.x);
				} else {
					temp_str = input[v1.y].substr(v1.x, v2.x - v1.x);
				}
				return temp_str;
			}
			std::string CopyAll() {
				return Copy({0, 0}, { 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1});
			}
			std::string GetLine(int line) {
				return Copy(vector2d(0, line), vector2d(input[line].size(), line));
			}
			std::string CopySelect() {
				return Copy(choose_pos1, choose_pos2);
			}
			bool IsSelect() {
				return choose_word_on;
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
					} else str2 += str[i];
				}
				input[pos.y].insert(pos.x, str2), pos.x += str2.size();
				input[pos.y] += temp_str;

				InputHistory temp_history;
				temp_history.op = operation_insert;
				temp_history.pos1 = backup_pos;
				temp_history.pos2 = pos;
				temp_history.str = backup;
				if (history.empty())history.push(temp_history);
				else {
					InputHistory temp2 = history.top();
					if (temp_history.op == temp2.op && temp_history.pos1 == temp2.pos2) {
						history.pop();
						temp2.str += temp_history.str;
						temp2.pos2 = temp_history.pos2;
						history.push(temp2);
					} else history.push(temp_history);
				}
				change = true;
				return pos;
			}
			vector2d Insert_andMove(vector2d pos, std::string str) {
				input_pos = Insert(pos, str);
				return input_pos;
			}
			vector2d InsertBack(std::string str) {
				return Insert({ 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1}, str);
			}
			void InsertBack_andMove(std::string str) {
				input_pos = Insert({ 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1}, str);
			}
			std::string insert_prepare;
			std::mutex prepare_mtx;
			void InsertBack_andMove_Prepare(std::string str) {
				prepare_mtx.lock();
				insert_prepare += str;
				prepare_mtx.unlock();
			}
			vector2d InsertLine(int pos, std::string str) {
				return Insert({ 1.0f * input[pos - 1].size(), 1.0f * pos - 1}, "\n" + str);
			}
			vector2d InsertLine_andMove(int pos, std::string str) {
				input_pos = Insert({ 1.0f * input[pos - 1].size(), 1.0f * pos - 1}, "\n" + str);
				return input_pos;
			}
			vector2d Delete(vector2d pos1, vector2d pos2) {
				if (pos1.y < 0)pos1.y = 0;
				if (pos1.x < 0)pos1.x = 0;
				if (pos1.y >= input.size())pos1.y = input.size() - 1;
				if (pos1.x >= input[pos1.y].size())pos1.x = input[pos1.y].size();
				if (pos2.y < 0)pos2.y = 0;
				if (pos2.x < 0)pos2.x = 0;
				if (pos2.y >= input.size())pos2.y = input.size() - 1;
				if (pos2.x >= input[pos2.y].size())pos2.x = input[pos2.y].size();
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
					input.erase(input.begin() + v1.y + 1, input.begin() + v2.y + 1);
				} else {
					input[v1.y].erase(v1.x, v2.x - v1.x);
				}

				InputHistory temp_history;
				temp_history.op = operation_delete;
				temp_history.pos1 = v1;
				temp_history.pos2 = v2;
				temp_history.str = backup;
				if (history.empty())history.push(temp_history);
				else {
					InputHistory temp2 = history.top();
					if (temp_history.op == temp2.op && temp_history.pos2 == temp2.pos1) {
						history.pop();
						temp2.str = temp_history.str + temp2.str;
						temp2.pos1 = temp_history.pos1;
						history.push(temp2);
					} else history.push(temp_history);
				}
				change = true;
				return v1;
			}
			vector2d Delete(vector2d pos, int n) {
				return pos;
			}
			vector2d DeleteLine(int pos) {
				if (pos < 0)return vector2d{0, 0};
				if (pos >= input.size())return vector2d{ 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1};
				if (pos == 0)return Delete({0, 0}, { 1.0f * input[0].size(), 0});
				else return Delete({ 1.0f * input[pos - 1].size(), 1.0f * pos - 1}, { 1.0f * input[pos].size(), 1.0f * pos});
			}
			vector2d SwapLine(int l1, int l2) {
				if (l1 < 0)return {input_pos.x, 0};
				if (l1 >= input.size())return { 1.0f * input_pos.x, 1.0f * input.size() - 1};
				if (l2 < 0)return {input_pos.x, 0};
				if (l2 >= input.size())return { 1.0f * input_pos.x, 1.0f * input.size() - 1};
				std::swap(input[l1], input[l2]);
				InputHistory temp_history;
				temp_history.op = operation_swap;
				temp_history.pos1.y = l1;
				temp_history.pos2.y = l2;
				history.push(temp_history);
				change = true;
				return {input_pos.x, 1.0f * l2};
			}
			vector2d GetEnd() {
				return { 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1};
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
				if (temp.op == operation_insert) {
					v = Delete(temp.pos1, temp.pos2);
					history.pop();
				} else if (temp.op == operation_delete) {
					v = Insert(temp.pos1, temp.str);
					history.pop();
				} else if (temp.op == operation_swap) {
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
				if (temp.op == operation_insert) {
					v = Insert(temp.pos1, temp.str);
					history.pop();
				} else if (temp.op == operation_delete) {
					v = Delete(temp.pos1, temp.pos2);
					history.pop();
				} else if (temp.op == operation_swap) {
					v = SwapLine(temp.pos1.y, temp.pos2.y);
					history.pop();
				}
				history.push(temp);
				last_history_len = history.size();
				return v;
			}
			bool InText(vector2d pos, vector2d p1, vector2d p2) {
				if (p1.y > p2.y)std::swap(p1, p2);
				else if (p1.y == p2.y && p1.x > p2.x)std::swap(p1, p2);
				if (pos.y < p1.y)return false;
				if (pos.y > p2.y)return false;
				if (pos.y == p1.y && pos.x < p1.x)return false;
				if (pos.y == p2.y && pos.x > p2.x)return false;
				return true;
			}
			void Import(std::string path) {
				Clear();
				std::ifstream fr;
				fr.open(path);
				std::string str;
				while (getline(fr, str))InsertBack(str + "\n");
				DeleteLine(GetEnd().y);
				fr.close();
			}
			void Export(std::string path) {
				std::ofstream fw;
				fw.open(path);
				fw << CopyAll();
				fw.close();
			}
			int GetSize() {
				int s = input.size();
				return s;
			}
			int GetSize(int line) {
				int s = input[line].size();
				return s;
			}
			void SetFocus() {
				ChooseInputBox = this;
				fix_time = gclock() - 500;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				// 开始
				BeginScissor(x, y, w, h);
				// 更新动画
				ipx.stp(wp::Index2Cursor(input, input_pos.y, input_pos.x)), ipy.stp(input_pos.y);
				ipx.update(), ipy.update();
				X = x, Y = y, W = w, H = w;
				vector2d input_pos1 = vector2d(wp::Index2Cursor(input, input_pos.y, input_pos.x), input_pos.y);
				// 处理插入事件
				prepare_mtx.lock();
				if (insert_prepare != "") InsertBack_andMove(insert_prepare);
				insert_prepare = "";
				prepare_mtx.unlock();
				// 如果光标在运动，则通过光标移动视野
				if (ipx.IsRunning() || ipy.IsRunning()) {
					if (ipx.gnp() * TextHeight / 2 < sx.Now())sx.Shift(ipx.gnp() * TextHeight / 2);
					if (ipy.gnp() * UnitHeight < sy.Now()) sy.Shift(ipy.gnp() * UnitHeight);
					if (ipx.gnp() * TextHeight / 2 + SpaceSize * 2 > sx.Now() + w - SliderWidth * !minimap_visible - minimap_width * minimap_visible - label_width * label_visible)
						sx.Shift(ipx.gnp() * TextHeight / 2 + SpaceSize * 2 - (w - SliderWidth * !minimap_visible - minimap_width * minimap_visible - label_width * label_visible));
					if ((ipy.gnp() + 1) * UnitHeight + SpaceSize * 2 > sy.Now() + h - SliderWidth - UnitHeight * statebar_visible)
						sy.Shift((ipy.gnp() + 1) * UnitHeight + SpaceSize * 2 - (h - SliderWidth - UnitHeight * statebar_visible));
				}
				// 计算文本区起止位置
				int start_x = 2 * (sx.Now() - ui::SpaceSize) / ui::TextHeight;
				int start_y = (sy.Now() - ui::SpaceSize) / ui::UnitHeight;
				int end_x = 2 * (sx.Now() - ui::SpaceSize + w - label_visible * ui::TextHeight * 4 - minimap_visible * minimap_width ) / ui::TextHeight + 1;
				int end_y = (sy.Now() - ui::SpaceSize + h) / ui::UnitHeight + 1;
				float tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				float tempx = x - sx.Now() + ui::SpaceSize;
				float tempy = y - sy.Now() + ui::SpaceSize;
				// 绘制背景色
				if (background_color != BgColor)DrawRectangle(x, y, w, h, ColorF(background_color));
				// 绘制行号
				int tempW = 0;
				if (label_visible) {
					tempW = label_width;
					// 绘制高亮行
					if (highlight_visible) {
						if (minimap_visible)DrawRectangle(x + ui::SpaceSize, tempy + ui::UnitHeight * ipy.gnp(), w - ui::SpaceSize - minimap_width, ui::UnitHeight, ColorF(100, 100, 100, 100));
						else DrawRectangle(x + ui::SpaceSize, tempy + ui::UnitHeight * ipy.gnp(), w - ui::SpaceSize, ui::UnitHeight, ColorF(100, 100, 100, 100));
					}
					// 绘制行号数字
					for (int i = start_y; i < std::min((int)GetSize(), end_y); i++) {
						size.x = std::max(size.x, (realn)GetSize(i));
						std::string temp_str = "";
						for (int j = 1; j <= 4 - int(log10(i + 1)); j++)temp_str += ' ';
						temp_str += wp::tostr(i + 1);
						if (i == round(ipy.gnp()))ui::Print(x + ui::TextHeight * 0.5, tempy + tempH + i * ui::UnitHeight, temp_str, highlight::GetColor(highlight::Type_Gutter_AL));
						else ui::Print(x + ui::TextHeight * 0.5, tempy + tempH + i * ui::UnitHeight, temp_str, highlight::GetColor(highlight::Type_Gutter));
					}
					x += tempW, tempx += tempW, w -= tempW;
				} else {
					// 绘制高亮行
					if (highlight_visible) {
						if (minimap_visible)DrawRectangle(x, tempy + ui::UnitHeight * ipy.gnp(), w - minimap_width, ui::UnitHeight, ColorF(100, 100, 100, 100));
						else DrawRectangle(x, tempy + ui::UnitHeight * ipy.gnp(), w, ui::UnitHeight, ColorF(100, 100, 100, 100));
					}
				}
				// 绘制状态栏
				if (statebar_visible) {
					h -= UnitHeight;
					DrawRectangle(x - tempW, y + h, w + tempW - minimap_width, UnitHeight, ColorF(background_color));
					Print(x + SpaceSize - tempW, y + h + (ui::UnitHeight - ui::TextHeight) / 2,
					      "INSERT MODE, Line " + wp::tostr((int)input_pos.y + 1) + ", Column " + wp::tostr((int)input_pos.x),
					      highlight::GetColor(highlight::Type_Default));
				}
				// 计算文本裁剪区
				char c = ui::GetChar;
				if (minimap_visible)ui::BeginScissor(x, y, w - minimap_width, h);
				else ui::BeginScissor(x, y, w, h);
				// 计算文本长度
				size.x = 0;
				for (int i = start_y; i <= end_y; i++)size.x = std::max(size.x, (realn)wp::Index2Cursor(input, i, input[i].size()));
				size.y = input.size();
				// 计算光标透明度
				int a = (gclock() - fix_time) % 1000;
				if (a < 300)a = 200;
				else if (a < 500)a = 500 - a;
				else if (a < 800)a = 0;
				else a = a - 800;
				if (ipx.is_run() || ipy.is_run())a = 200, fix_time = clock();
				// 处理按键事件
				if (true) {
					// 判断焦点
					if (ui::MouseInRect(x - tempW, y, w + tempW - ui::SpaceSize * 3, h - ui::SpaceSize * 3) && InScissor(Mouse.x, Mouse.y) && check) {
						ui::MouseCursorStyle = MOUSE_CURSOR_IBEAM;
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) SetFocus();
					} else if (IsMousePressed(MOUSE_BUTTON_LEFT) && ChooseInputBox == this)ChooseInputBox = nullptr;
					// 处于焦点状态
					if (!choose && ChooseInputBox == this)choose = true;
					if (choose && ChooseInputBox != this)choose = false;
					if (choose) {
						// 判断是否选择文本
						if (!choose_word && IsMousePressed(MOUSE_BUTTON_LEFT))choose_word_on = false;
						// 通过鼠标点击移动光标
						if (ui::MouseInRect(x, y, w - ui::SpaceSize * 3, h - ui::SpaceSize * 3) || choose_word) {
							if (IsMouseDown(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0f * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0f * ky / ui::UnitHeight);
								if (kx2 < 0)kx2 = 0;
								if (ky2 < 0)ky2 = 0;
								ky2 = std::min(ky2, int(input.size() - 1));
								kx2 = wp::Cursor2Index(input, ky2, kx2);
								kx2 = std::min(kx2, int(input[ky2].size()));
								input_pos = vector2d{ 1.0f * kx2, 1.0f * ky2};
								ipx.stp(wp::Index2Cursor(input, input_pos.y, input_pos.x)), ipy.stp(input_pos.y);
								ipx.update(), ipy.update();
							}
							if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
								int kx = ui::Mouse.x - tempx;
								int ky = ui::Mouse.y - tempy;
								int kx2 = round(1.0f * kx * 2 / ui::TextHeight);
								int ky2 = floor(1.0f * ky / ui::UnitHeight);
								if (kx2 < 0)kx2 = 0;
								if (ky2 < 0)ky2 = 0;
								ky2 = std::min(ky2, int(input.size() - 1));
								kx2 = wp::Cursor2Index(input, ky2, kx2);
								kx2 = std::min(kx2, int(input[ky2].size()));
								input_pos = vector2d{ 1.0f * kx2, 1.0f * ky2};
								choose_word = true;
								choose_pos = vector2d{ 1.0f * kx2, 1.0f * ky2};
							}
						}
						// 是否取消选择文本
						if (!IsMouseDown(MOUSE_BUTTON_LEFT))choose_word = false;
						// 如果选择文本，计算选择起止点
						if (choose_word) {
							int kx = ui::Mouse.x - tempx;
							int ky = ui::Mouse.y - tempy;
							int kx2 = round(1.0f * kx * 2 / ui::TextHeight);
							int ky2 = floor(1.0f * ky / ui::UnitHeight);
							if (kx2 < 0)kx2 = 0;
							if (ky2 < 0)ky2 = 0;
							ky2 = std::min(ky2, int(input.size() - 1));
							kx2 = wp::Cursor2Index(input, ky2, kx2);
							kx2 = std::min(kx2, int(input[ky2].size()));
							if (kx2 != choose_pos.x || ky2 != choose_pos.y) {
								choose_word_on = true;
								choose_pos2 = vector2d{ 1.0f * kx2, 1.0f * ky2};
							} else {
								choose_word_on = false;
							}
						}
						bool delete_choose = false;
						// 防止动画过长而做的优化
						if (fabs(input_pos.y - ipy.gnp()) > 20)ipy.ssp(input_pos.y);
						// 选择文本后的事件
						input_pos1 = vector2d(wp::Index2Cursor(input, input_pos.y, input_pos.x), input_pos.y);
						if (choose_word_on) {
							// 绘制起止光标间的阴影
							vector2d v1, v2;
							choose_pos2 = vector2d(ipx.gnp(), ipy.gnp());
							choose_pos1 = vector2d(wp::Index2Cursor(input, choose_pos.y, choose_pos.x), choose_pos.y);
							if (fabs(input_pos1.y - ipy.gnp()) == 0 && fabs(input_pos1.x - ipx.gnp()) > 10)choose_pos2.x = input_pos1.x;
							if (fabs(input_pos1.y - ipy.gnp()) > 5)choose_pos2.y = input_pos1.y, choose_pos2.x = input_pos1.x;
							if (choose_pos1.y < choose_pos2.y)v1 = choose_pos1, v2 = choose_pos2;
							else if (choose_pos1.y > choose_pos2.y)v1 = choose_pos2, v2 = choose_pos1;
							else  {
								if (choose_pos1.x < choose_pos2.x)v1 = choose_pos1, v2 = choose_pos2;
								else v2 = choose_pos1, v1 = choose_pos2;
							}
							vector2d v3 = GetPos(v1), v4 = GetPos(v2);
							Color color = ui::MainColor;
							color.a = 100;
							if (v2.y - v1.y > 1 && v3.y < y + h && v4.y > y)
								DrawRectangle(x, std::max(int(v3.y + ui::UnitHeight), y),
								              w, ceil(std::min(v4.y, realn(y + h)) - std::max(int(v3.y + ui::UnitHeight), y)),
								              ColorF(color)
								             );
							if (v2.y - v1.y < 0.9)DrawRectangle(v3.x, v3.y, v4.x - v3.x, ui::UnitHeight, ColorF(color));
							else {
								DrawRectangle(v3.x, v3.y, x + w - v3.x, ui::UnitHeight, ColorF(color));
								DrawRectangle(x, v4.y, v4.x - x, ui::UnitHeight, ColorF(color));
							}
							// 绘制起止光标
							DrawRectangle(
							    tempx + ui::TextHeight / 2 * choose_pos1.x - ui::dpi,
							    tempy + ui::UnitHeight * choose_pos1.y - tempH,
							    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(ThemeColor)
							);
							DrawRectangle(
							    tempx + ui::TextHeight / 2 * choose_pos2.x - ui::dpi,
							    tempy + ui::UnitHeight * choose_pos2.y - tempH,
							    2 * ui::dpi, ui::TextHeight + tempH * 4, ColorF(ThemeColor)
							);
							// 判断是否通过一些按键取消选择
							if (IsKeyDown(KEY_HOME) || IsKeyDown(KEY_END) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
								choose_word_on = false;
							}
							// 判断是否缩进
							if (IsKeyPressed(KEY_TAB)) {
								if (IsKeyDown(KEY_LEFT_SHIFT)) {
//									bool front = false;
//									for (int i = v1.y; i <= v2.y; i++) {}
								} else {
									for (int i = v1.y; i <= v2.y; i++) Insert(vector2d(0, i), "\t");
									input_pos.x--;
								}
								choose_word_on = false;
							}
							if (input_enable) {
								bool flag = false;
								for (int i = 32; i <= 127; i++)if (c == i) {
										flag = true;
										break;
									}
								if (IsKeyDown(KEY_BACKSPACE) || IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_DELETE))flag = true;
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
								if (input_pos.x > 0)input_pos = Delete(input_pos - vector2d{ 1.0f * wp::GetPreCharacter(input, input_pos.y, input_pos.x), 0}, input_pos);
								else if (input_pos.y > 0)input_pos = Delete({ 1.0f * input[input_pos.y - 1].size(), input_pos.y - 1}, input_pos);
							} else if (ui::IsKeyInput(KEY_DELETE) && !delete_choose) {
								if (input_pos.x < input[input_pos.y].size())input_pos = Delete(input_pos + vector2d{ 1.0f * wp::GetNextCharacter(input, input_pos.y, input_pos.x), 0}, input_pos);
								else if (input_pos.y < input.size() - 1)input_pos = Delete({0, input_pos.y + 1}, input_pos);
							} else if (ui::IsKeyInput(KEY_LEFT)) {
								if (input_pos.x > 0) {
									if (ipy.gnp() == input_pos.y)input_pos.x -= wp::GetPreCharacter(input, input_pos.y, input_pos.x);
								} else if (input_pos.y > 0 && !ipx.is_run())input_pos.y--, input_pos.x = input[input_pos.y].size();
							} else if (ui::IsKeyInput(KEY_RIGHT)) {
								if (input_pos.x < input[input_pos.y].size()) {
									if (ipy.gnp() == input_pos.y)input_pos.x += wp::GetNextCharacter(input, input_pos.y, input_pos.x);
								} else if (input_pos.y < input.size() - 1 && !ipx.is_run())input_pos.y++, input_pos.x = 0;
							} else if (ui::IsKeyInput(KEY_UP) && input_pos.y > 0) {
								if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT)) {
									SwapLine(input_pos.y, input_pos.y - 1);
									input_pos.y--;
								} else {
									input_pos.y--;
									input_pos.x = wp::Cursor2Index(input, input_pos.y, wp::Index2Cursor(input, input_pos.y + 1, input_pos.x));
								}
							} else if (ui::IsKeyInput(KEY_DOWN) && input_pos.y < input.size() - 1) {
								if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT)) {
									SwapLine(input_pos.y, input_pos.y + 1);
									input_pos.y++;
								} else {
									input_pos.y++;
									input_pos.x = wp::Cursor2Index(input, input_pos.y, wp::Index2Cursor(input, input_pos.y - 1, input_pos.x));
								}
							} else if (ui::IsKeyInput(KEY_END)) input_pos.x = input[input_pos.y].size();
							else if (ui::IsKeyInput(KEY_HOME)) input_pos.x = 0;
							else if (ui::IsKeyInput(KEY_TAB)) input_pos = Insert(input_pos, "\t");
							else if (ui::IsKeyInput(KEY_ENTER)) {
								bool flag = true;
								if (input_pos.x <= 0 || input_pos.x >= input[input_pos.y].size()) flag = false;
								if (flag && input[input_pos.y][input_pos.x - 1] == '{' && input[input_pos.y][input_pos.x] == '}') {
									Insert(input_pos, "\n\n");
									input_pos.y++;
									input_pos.x = 0;
									int space_size = 0;
									std::string temp = "";
									for (int i = 0; i < input[input_pos.y - 1].size(); i++) {
										if (input[input_pos.y - 1][i] == ' ') space_size++;
										else if (input[input_pos.y - 1][i] == '\t') space_size += 4;
										else {
											break;
										}
									}
									if (space_size % 4 == 0) {
										for (int i = 0; i < space_size / 4; i++) temp += '\t';
										Insert(input_pos + vector2d{0, 1}, temp);
										input_pos = Insert(input_pos, temp + "\t");
									}
								} else {
									input_pos = Insert(input_pos, "\n");
									int space_size = 0;
									std::string temp = "";
									for (int i = 0; i < input[input_pos.y - 1].size(); i++) {
										if (input[input_pos.y - 1][i] == ' ') space_size++;
										else if (input[input_pos.y - 1][i] == '\t') space_size += 4;
										else {
											break;
										}
									}
									if (space_size % 4 == 0) {
										for (int i = 0; i < space_size / 4; i++) temp += '\t';
										input_pos = Insert(input_pos, temp);
									}
								}
							}
							if (IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT)) {
								if (choose_word_on) {
									if (IsKeyPressed(KEY_C)) {
										choose_pos2 = vector2d{input_pos.x, input_pos.y};
										SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
										ui::message::Send_Tip("已复制到剪切板");
									} else if (IsKeyPressed(KEY_X)) {
										ui::message::Send_Tip("已复制到剪切板");
										choose_pos2 = vector2d{input_pos.x, input_pos.y};
										SetClipboardText(Copy(choose_pos, choose_pos2).c_str());
										input_pos = Delete(choose_pos, choose_pos2);
										choose_word_on = false;
									}
								}
								if (IsKeyPressed(KEY_A)) {
									choose_word_on = true;
									choose_pos = vector2d{0, 0};
									choose_pos2 = vector2d{ 1.0f * input[input.size() - 1].size(), 1.0f * input.size() - 1};
									input_pos = choose_pos2;
								}
								if (ui::IsKeyInput(KEY_V)) {
									if (choose_word_on) {
										input_pos = Delete(choose_pos, input_pos);
										choose_word_on = false;
									}
									try {
										std::string str = GetClipboardText();
										input_pos = Insert(input_pos, str);
									} catch (...) {
										ui::message::Send_Error("[CRASH #001] ", 500000);
									}
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
					}
				} else ChooseInputBox = nullptr;
				// 绘制文本
				color.resize(input.size());
				for (int i = 0; i < color.size(); i++)color[i].resize(input[i].size());
				std::string char2str;
				if (change)highlight::AnalysisColor(input, color);
				for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
					int count = 0;
					for (int j = 0; j < input[i].size();) {
						char2str = "";
						char2str += input[i][j];
						int count2 = count, j2 = j;
						if (input[i][j] == ' ')j++, count++;
						else if (input[i][j] == '\t')j++, count = floor(count / 4.0) * 4 + 4;
						else if ((input[i][j] & 0xF8) == 0xF8)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], char2str += input[i][j + 4], j += 5, count += 2;
						else if ((input[i][j] & 0xF0) == 0xF0)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], j += 4, count += 2;
						else if ((input[i][j] & 0xE0) == 0xE0)char2str += input[i][j + 1], char2str += input[i][j + 2], j += 3, count += 2;
						else if ((input[i][j] & 0xC0) == 0xC0)char2str += input[i][j + 1], j += 2, count += 2;
						else j++, count++;
						Print_All(tempx + count2 * TextHeight / 2, tempy + tempH + i * UnitHeight, char2str, highlight::GetColor(color[i][j2]));
					}
				}
				background_color = highlight::GetBgColor();
				ipx.update(), ipy.update();
				// 输入框为空，则绘制提示文本
				if (input.size() == 1 && input[0].size() == 0) {
					Print(tempx, tempy + tempH, content, GRAY);
				}
				// 初始化下一帧帧未更改
				change = false;
				// 绘制空白字符
				if (space_visible || (choose_word_on && ChooseInputBox == this)) {
					for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
						int count = 0;
						for (int j = 0; j < input[i].size(); j++) {
							int tcount = count;
							if (input[i][j] == '\t')count = floor(count / 4.0) * 4 + 4;
							else if ((input[i][j] & 0xF8) == 0xF8)j += 4, count += 2;
							else if ((input[i][j] & 0xF0) == 0xF0)j += 3, count += 2;
							else if ((input[i][j] & 0xE0) == 0xE0)j += 2, count += 2;
							else if ((input[i][j] & 0xC0) == 0xC0)j += 1, count += 2;
							else count++;
							if (choose_word_on && !InText(vector2d(j, i), choose_pos, choose_pos2))continue;
							if (input[i][j] == '\t')DrawLineEx(
								    Vector2{tempx + tcount * TextHeight / 2, tempy + i * UnitHeight + UnitHeight / 2},
								    Vector2{tempx + count * TextHeight / 2 - dpi, tempy + i * UnitHeight + UnitHeight / 2},
								    dpi, ColorF(DARKGRAY)
								);
							if (input[i][j] == ' ')DrawCircle(tempx + count * TextHeight / 2 - TextHeight / 4, tempy + i * UnitHeight + UnitHeight / 2, dpi, DARKGRAY);
						}
					}
				}
				// 绘制缩进提示线
				if (tabline_visible) {
					for (int i = start_y; i < std::min((int)input.size(), end_y); i++) {
						for (int j = 0; j < input[i].size(); j++) {
							Color tlc;
							if (j % 4 == 3)tlc = highlight::GetColor(highlight::Type_Bracket_L1);
							if (j % 4 == 0)tlc = highlight::GetColor(highlight::Type_Bracket_L2);
							if (j % 4 == 1)tlc = highlight::GetColor(highlight::Type_Bracket_L3);
							if (j % 4 == 2)tlc = highlight::GetColor(highlight::Type_Bracket_L4);
							if (input[i][j] == '\t')
								DrawLineEx(
								    Vector2{tempx + j*TextHeight * 2, tempy + i * UnitHeight},
								    Vector2{tempx + j*TextHeight * 2, tempy + i * UnitHeight + UnitHeight},
								    dpi, ColorF(tlc, 0.3)
								);
							else break;
						}
					}
				}
				// 绘制光标
				if (choose) {
					// 焦点状态，黄色
					a = a * 255 / 200;
					if (!choose_word_on)DrawRectangle(
						    tempx + TextHeight / 2 * ipx.gnp() - ui::dpi,
						    tempy + UnitHeight * ipy.gnp() - tempH,
						    2 * dpi, TextHeight + tempH * 4, ColorF(232, 192, 114, a)
						);
				} else {
					// 非焦点，灰色
					DrawRectangle(
					    tempx + TextHeight / 2 * ipx.gnp() - dpi,
					    tempy + UnitHeight * ipy.gnp() - tempH,
					    2 * dpi, TextHeight + tempH * 4, ColorF(70, 70, 70, 255)
					);
				}
				// 绘制行号栏的阴影
				if (label_visible && shadow_visible) {
					if (sx.Now() > SpaceSize - 1) {
						int delta = sx.Now() - SpaceSize + 1;
						if (delta > UnitHeight * 2)delta = UnitHeight * 2;
						special_effect::DrawShadowLine(x, y + h, x, y, 10 * dpi, 1.0f * delta / UnitHeight / 2);
					}
				}

				EndScissor();
				// 绘制小地图
				if (minimap_visible) {
					int nowy = sy.Now();
					if (choose_minimap)nowy = sy.Target();
					realn temp = 1.0f * nowy / sy.Sum() * (1 - h * 3 * dpi / UnitHeight / h);
					realn start = 1.0f * nowy / ui::UnitHeight - temp * h / dpi / 3;
					int delta_y = start * dpi * 3;
					if (start < 0)start = 0;
					Color tcolor;
					// 绘制内容
					for (int i = start; i < std::min((int)input.size(), int(start + h / 3 / dpi)); i++) {
						int p1 = 0, count = 0;
						// 绘制文本
						for (int j = 0; j < input[i].size(); j++) {
							if (input[i][j] == '\t')count = floor(count / 4.0) * 4 + 4;
							else if ((input[i][j] & 0xF8) == 0xF8)j += 4, count += 2;
							else if ((input[i][j] & 0xF0) == 0xF0)j += 3, count += 2;
							else if ((input[i][j] & 0xE0) == 0xE0)j += 2, count += 2;
							else if ((input[i][j] & 0xC0) == 0xC0)j += 1, count += 2;
							else count++;
							if (input[i][j] != ' ' && input[i][j] != '\t') tcolor = ColorF(MixColor(highlight::GetColor(color[i][j]), background_color, 0.5));
							else tcolor = background_color;
							// 选择的文本得有阴影
							if (choose_word_on) {
								if (InText(vector2d(j, i), choose_pos1, choose_pos2))tcolor = ColorF(MixColor(tcolor, MainColor, 0.5));
								if (vector2d(j, i) == choose_pos1 || vector2d(j, i) == choose_pos2)tcolor = ColorF(ThemeColor);
							}
							if (tcolor != BgColor)DrawRectangle(x + w - minimap_width + count * dpi, y + i * dpi * 3 - delta_y, dpi, dpi * 2, tcolor);
							if (j * dpi > minimap_width) break;
						}
					}
					// 绘制当前行高亮
					if (highlight_visible) {
						DrawRectangle(x + w - minimap_width, y + ipy.gnp() * dpi * 3 - delta_y, minimap_width, dpi * 2, ColorF(LIGHTGRAY, 0.5));
					}
					// 绘制当前位置
					DrawRectangle(x + w - minimap_width, y + nowy * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight, ColorF(ChooseColor));
					// 绘制小地图阴影
					if (size.x * TextHeight / 2 - sx.Now() > w - minimap_width && shadow_visible) {
						int delta = size.x * TextHeight / 2 - sx.Now() - w + minimap_width;
						if (delta > ui::UnitHeight * 2)delta = UnitHeight * 2;
						special_effect::DrawShadowLine(x + w - minimap_width, y, x + w - minimap_width, y + h, 10 * dpi, 1.0f * delta / UnitHeight / 2);
					}
					// 检测按键
					if (check && MouseInRect(x + w - minimap_width, y, minimap_width - SpaceSize * 3, h - SpaceSize * 3)) {
						// 悬浮时加深颜色
						if (MouseInRect(x + w - minimap_width, y + nowy * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight) || choose_minimap) {
							DrawRectangle(x + w - minimap_width, y + nowy * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3 * dpi / UnitHeight, ColorF(ChooseColor));
						}
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							if (MouseInRect(x + w - minimap_width, y + nowy * dpi * 3 / UnitHeight - delta_y, minimap_width, h * 3.0 * dpi / UnitHeight)) {
								// 拖动
								realn k = ((Mouse.y - (y + nowy * dpi * 3.0 / UnitHeight - delta_y + h * 3.0 * dpi / UnitHeight / 2))) / h;
								choose_minimap = true;
								choose_minimap_delta = k * (nowy * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight)));
							} else {
								// 跳转
								realn k = (Mouse.y - h * 3.0 * dpi / UnitHeight / 2 - y) / h;
								sy.Set(k * (nowy * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight))));
								choose_minimap = true;
								choose_minimap_delta = 0;
							}
						}
					}
					// 拖动时加深颜色
					if (choose_minimap) {
						DrawRectangle(x + w - minimap_width, y + nowy * dpi * 3.0 / UnitHeight - delta_y, minimap_width, h * 3.0 * dpi / UnitHeight, ColorF(ChooseColor));
						realn k = (Mouse.y - h * 3.0 * dpi / UnitHeight / 2 - y) / h;
						sy.Set(k * (sy.Sum() * (1 + (h * 3.0 * dpi / UnitHeight) / (h - h * 3.0 * dpi / UnitHeight))) - choose_minimap_delta);
					}
					if (!IsMouseDown(MOUSE_BUTTON_LEFT))choose_minimap = false;
				}

				// 绘制滚动条
				BeginAlphaMode(0.7);
				sx.SetFixed(true);
				sy.SetFixed(true);
				sx.SetControl(x, y, w, h);
				sy.SetControl(x, y, w, h);
				sx.SetDrawBackground(false);
				sy.SetDrawBackground(false);
				sx.SetSum(size.x * TextHeight / 2 + SliderWidth + tempW + minimap_width * minimap_visible);
				sy.SetSum(size.y * UnitHeight + h - UnitHeight - SliderWidth);
				sy.SetDrawCursor(true);
				sy.SetCursorPos(ipy.gnp() * UnitHeight);
				sx.Draw_Auto_Extra(x - tempW, y + h - SliderWidth, w - SliderWidth + tempW, SliderWidth);
				sy.Draw_Auto_Extra(x + w - SliderWidth, y, SliderWidth, h - SliderWidth);
				sx.Update();
				sy.Update();
				EndAlphaMode();

				// 结束
				EndScissor();
				return UnitHeight;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = multi_height * UnitHeight + 2 * SpaceSize;
				x += dpi, y += dpi, w -= dpi * 2, h;
				Draw(x, y, w, h, check);
				special_effect::DrawMouseBox(x, y, w, h);
				return h + dpi;
			}
		};
		class TextBox : public  ui::Element {
		private:
			int choose_start = 0;					// 我也不知道这是干啥的
			int choose_end = 0;						// 我也不知道这是干啥的
			bool choose_word = false;				// 是否准备选择文本awa
			bool choose_word_on = false;			// 是否选择文本
			vector2d choose_pos = {0, 0};			// 选择起始点
			vector2d choose_pos1 = {0, 0};			// 选择起始点
			vector2d choose_pos2 = {0, 0};			// 选择终止点
			Animation ipx, ipy;						// 光标行、列位置动画
			Button copybtn;							// 复制按钮

		public:
			std::vector<std::string> input;			// 文本
			vector2d size = {0, 0};					// 代码版面大小
			bool choose = false;					// 是否选择
			Color background_color = BgColor;		// 背景色
			std::vector<std::vector<highlight::Type> > color;// 代码高亮
			ui::SliderBar sx;						// 横向滚动条

			bool label_visible = false;				// 是否显示行号
			bool space_visible = false;				// 是否显示空白字符
			bool tabline_visible = false;			// 是否显示缩进提示线
			int label_width = 60 * dpi;				// 行号栏宽度

			TextBox& SetLabelVisible(bool on) {
				label_visible = on;
				return *this;
			}
			TextBox& SetSpaceVisible (bool on) {
				space_visible = on;
				return *this;
			}
			TextBox& SetTablineVisible(bool on) {
				tabline_visible = on;
				return *this;
			}
			TextBox& SetCodeDefaultMode() {
				label_visible = true;
				space_visible = false;
				tabline_visible = true;
				return *this;
			}
			TextBox& SetTextDefaultMode() {
				label_visible = false;
				space_visible = false;
				tabline_visible = false;
				return *this;
			}

			TextBox() {
				copybtn = Button(u8"[]Copy").withCallback([&] {
					std::string str;
					for (int i = 0; i < input.size(); i++) {
						if (i != 0) str += "\r\n";
						str += input[i];
					}
					message::Send_Tip("已复制到剪切板");
					SetClipboardText(str.c_str());
				});
			}
			TextBox(std::string content_, std::string text) {
				SetText(text);
				content = content_;
				copybtn = Button(u8"[]Copy").withCallback([&] {
					std::string str;
					for (int i = 0; i < input.size(); i++) {
						if (i != 0) str += "\r\n";
						str += input[i];
					}
					message::Send_Tip("已复制到剪切板");
					SetClipboardText(str.c_str());
				});
			}
			int GetSize() {
				int s = input.size();
				return s;
			}
			int GetSize(int line) {
				int s = input[line].size();
				return s;
			}
			vector2d GetPos(vector2d v) {
				int tempW = 0;
				if (label_visible)tempW = ui::TextHeight * 4;
				int tempx = X - sx.Now() + ui::SpaceSize + tempW;
				int tempy = Y + ui::SpaceSize;
				int tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				return vector2d {
					tempx + ui::TextHeight / 2 * v.x,
					tempy + ui::UnitHeight * v.y
				};
			}
			void SetText(std::string str) {
				std::string str2 = "";
				input.clear();
				for (int i = 0; i < str.size(); i++) {
					if (str[i] == '\r' && str[i + 1] == '\n') {
						input.push_back(str2);
						str2 = "";
					} else if (str[i] == '\n') {
						input.push_back(str2);
						str2 = "";
					} else str2 += str[i];
				}
				if (str2 != "") input.push_back(str2);
				color.resize(input.size());
				for (int i = 0; i < input.size(); i++) color[i].resize(input[i].size());
				highlight::AnalysisColor(input, color);
			}
			bool InText(vector2d pos, vector2d p1, vector2d p2) {
				if (p1.y > p2.y)std::swap(p1, p2);
				else if (p1.y == p2.y && p1.x > p2.x)std::swap(p1, p2);
				if (pos.y < p1.y)return false;
				if (pos.y > p2.y)return false;
				if (pos.y == p1.y && pos.x < p1.x)return false;
				if (pos.y == p2.y && pos.x > p2.x)return false;
				return true;
			}
			int Draw(int x, int y, int w, bool check = true) {
				// 计算文本区起止位置
				float h = input.size() * UnitHeight + SpaceSize * 3 + UnitHeight + SliderWidth;
				float tempy = y + SpaceSize * 2 + UnitHeight;
				float tempH = (ui::UnitHeight - ui::TextHeight) / 2;
				float tempx = x - sx.Now() + ui::SpaceSize;
				// 绘制背景色
				if (background_color != BgColor) DrawRectangle(x, y, w, h, ColorF(background_color));
				// 绘制标题
				DrawCircle(x + SpaceSize * 2 + TextHeight / 2, y + SpaceSize * 2 + TextHeight / 2, TextHeight * 0.3, ColorF(RED));
				DrawCircle(x + SpaceSize * 2 + TextHeight * 1.5, y + SpaceSize * 2 + TextHeight / 2, TextHeight * 0.3, ColorF(YELLOW));
				DrawCircle(x + SpaceSize * 2 + TextHeight * 2.5, y + SpaceSize * 2 + TextHeight / 2, TextHeight * 0.3, ColorF(GREEN));
				Print(x + SpaceSize * 2 + TextHeight * 3.5, y + SpaceSize * 2, content);
				copybtn.Draw_Auto(x + w - copybtn.GetWidth() - ui::SpaceSize, y, copybtn.GetWidth());
				// 绘制行号
				int tempW = 0;
				if (label_visible) {
					tempW = label_width;
					// 绘制行号数字
					for (int i = 0; i < input.size(); i++) {
						size.x = std::max(size.x, (realn)GetSize(i));
						std::string temp_str = "";
						for (int j = 1; j <= 4 - int(log10(i + 1)); j++)temp_str += ' ';
						temp_str += wp::tostr(i + 1);
						ui::Print(x + ui::TextHeight * 0.5, tempy + tempH + i * ui::UnitHeight, temp_str, highlight::GetColor(highlight::Type_Gutter));
					}
					x += tempW, tempx += tempW, w -= tempW;
				}
				// 计算文本长度
				size.x = 0;
				for (int i = 0; i < input.size(); i++) size.x = std::max(size.x, (realn)wp::Index2Cursor(input, i, input[i].size()));
				size.y = input.size();
				BeginScissor(x, tempy, w, h);
				// 绘制文本
				std::string char2str;
				for (int i = 0; i < input.size(); i++) {
					int count = 0;
					for (int j = 0; j < input[i].size();) {
						char2str = "";
						char2str += input[i][j];
						int count2 = count, j2 = j;
						if (input[i][j] == ' ')j++, count++;
						else if (input[i][j] == '\t')j++, count = floor(count / 4.0) * 4 + 4;
						else if ((input[i][j] & 0xF8) == 0xF8)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], char2str += input[i][j + 4], j += 5, count += 2;
						else if ((input[i][j] & 0xF0) == 0xF0)char2str += input[i][j + 1], char2str += input[i][j + 2], char2str += input[i][j + 3], j += 4, count += 2;
						else if ((input[i][j] & 0xE0) == 0xE0)char2str += input[i][j + 1], char2str += input[i][j + 2], j += 3, count += 2;
						else if ((input[i][j] & 0xC0) == 0xC0)char2str += input[i][j + 1], j += 2, count += 2;
						else j++, count++;
						Print_All(tempx + count2 * TextHeight / 2, tempy + tempH + i * UnitHeight, char2str, highlight::GetColor(color[i][j2]));
					}
				}
				background_color = highlight::GetBgColor();
				// 绘制空白字符
				if (space_visible || (choose_word_on && ChooseInputBox == this)) {
					for (int i = 0; i < input.size(); i++) {
						int count = 0;
						for (int j = 0; j < input[i].size(); j++) {
							int tcount = count;
							if (input[i][j] == '\t')count = floor(count / 4.0) * 4 + 4;
							else if ((input[i][j] & 0xF8) == 0xF8)j += 4, count += 2;
							else if ((input[i][j] & 0xF0) == 0xF0)j += 3, count += 2;
							else if ((input[i][j] & 0xE0) == 0xE0)j += 2, count += 2;
							else if ((input[i][j] & 0xC0) == 0xC0)j += 1, count += 2;
							else count++;
							if (choose_word_on && !InText(vector2d(j, i), choose_pos, choose_pos2))continue;
							if (input[i][j] == '\t')DrawLineEx(
								    Vector2{tempx + tcount * TextHeight / 2, tempy + i * UnitHeight + UnitHeight / 2},
								    Vector2{tempx + count * TextHeight / 2 - dpi, tempy + i * UnitHeight + UnitHeight / 2},
								    dpi, ColorF(DARKGRAY)
								);
							if (input[i][j] == ' ')DrawCircle(tempx + count * TextHeight / 2 - TextHeight / 4, tempy + i * UnitHeight + UnitHeight / 2, dpi, DARKGRAY);
						}
					}
				}
				// 绘制缩进提示线
				if (tabline_visible) {
					for (int i = 0; i < input.size(); i++) {
						for (int j = 0; j < input[i].size(); j++) {
							Color tlc;
							if (j % 4 == 3)tlc = highlight::GetColor(highlight::Type_Bracket_L1);
							if (j % 4 == 0)tlc = highlight::GetColor(highlight::Type_Bracket_L2);
							if (j % 4 == 1)tlc = highlight::GetColor(highlight::Type_Bracket_L3);
							if (j % 4 == 2)tlc = highlight::GetColor(highlight::Type_Bracket_L4);
							if (input[i][j] == '\t')
								DrawLineEx(
								    Vector2{tempx + j*TextHeight * 2, tempy + i * UnitHeight},
								    Vector2{tempx + j*TextHeight * 2, tempy + i * UnitHeight + UnitHeight},
								    dpi, ColorF(tlc, 0.3)
								);
							else break;
						}
					}
				}
				EndScissor();
				// 绘制滚动条
				BeginAlphaMode(0.7);
				sx.SetControl(x, y, w, h);
				sx.SetDrawBackground(false);
				sx.SetSum(size.x * TextHeight / 2 + SliderWidth + tempW);
				sx.SetBlank(0);
				sx.Draw_Auto_Extra(x - tempW, y + h - SliderWidth, w - SliderWidth + tempW, SliderWidth);
				sx.Update();
				EndAlphaMode();

				// 结束
				return h;
			}
		};
		class Table : public Element {
		private:
			ui::SliderBar sx;						// 横向滚动条
			ui::SliderBar sy;						// 纵向滚动条
			std::vector <int> colwidth;				// 列宽度
			std::vector <int> colstartx;			// 列起始位置
			std::vector <int> rowheight;			// 行高度
			std::vector <int> rowstarty;			// 行起始位置
			int cols = 0, rows = 0;					// 行数、列数
			int max_width = UnitHeight * 15;		// 最大宽度
			int interval = UnitHeight;				// 间隔大小
			vector2d size{0, 0};					// 表格大小
			void DrawTable(int x, int y, bool check = true) {
				// 计算裁剪区
				float six, siy, siw, sih;
				GetScissor(&six, &siy, &siw, &sih);
				// 找到绘制起始终止位置
				auto xit1 = std::lower_bound(colstartx.begin(), colstartx.end(), six - x + sx.Now());
				auto xit2 = std::lower_bound(colstartx.begin(), colstartx.end(), six - x + siw + sx.Now());
				int xid1 = std::distance(colstartx.begin(), xit1);
				int xid2 = std::distance(colstartx.begin(), xit2);
				if (xid1 > 0) xid1--;
				auto yit1 = std::lower_bound(rowstarty.begin(), rowstarty.end(), siy - y + sy.Now());
				auto yit2 = std::lower_bound(rowstarty.begin(), rowstarty.end(), siy - y + sih + sy.Now());
				int yid1 = std::distance(rowstarty.begin(), yit1);
				int yid2 = std::distance(rowstarty.begin(), yit2);
				if (yid1 > 0) yid1--;
				// 绘制表格
				for (int i = yid1; i < yid2; i++) {
					int tmpx = x - sx.Now();
					int tmpy = rowstarty[i] + y - sy.Now();
					for (int j = xid1; j < xid2; j++) {
						DrawRectangleLines(tmpx + colstartx[j], tmpy, colwidth[j], rowheight[i], ColorF(LineColor));
						vector2d rect = GetPrintRectSize(0, 0, colwidth[j] - TextHeight * 2, items[i][j]);
						PrintRect(
							tmpx + colstartx[j] + (colwidth[j] - rect.x) / 2, 
							tmpy + (rowheight[i] - rect.y) / 2, 
							colwidth[j] - TextHeight * 2, 
							items[i][j]
							);
					}
				}
				// 绘制边框
				DrawRectangleLines(x - sx.Now(), y - sy.Now(), size.x, size.y, ColorF(WHITE));
			}

		public:
			std::vector <std::vector <std::string> > items;
			Table() {
				items.resize(1);
				CalcInfo();
				extra = true;
			}
			Table(std::vector <std::vector <std::string> > items_) {
				items = items_;
				extra = true;
				CalcInfo();
			}
			Table& SetItems(std::vector <std::vector <std::string> > items_) {
				items = items_;
				CalcInfo();
				return *this;
			}
			Table& AddRow(std::vector <std::string> items_) {
				items.push_back(items_);
				return *this;
			}
			Table& SetExtra(bool on) {
				extra = on;
				return *this;
			}
			void CalcInfo() {
				rows = items.size();
				cols = items[0].size();
				for (int i = 0; i < rows; i++) items[i].resize(cols);
				if (colwidth.size()  != cols) colwidth .resize(cols);
				if (colstartx.size() != cols) colstartx.resize(cols);
				if (rowheight.size() != rows) rowheight.resize(rows);
				if (rowstarty.size() != rows) rowstarty.resize(rows);
				size.x = size.y = 0;
				for (int i = 0; i < cols; i++) {
					colwidth[i] = 0;
					colstartx[i] = size.x;
					for (int j = 0; j < rows; j++) {
						int tmpw = wp::strLen(items[j][i]) * TextHeight / 2 + TextHeight * 2;
						if (tmpw > max_width) tmpw = max_width;
						colwidth[i] = std::max(colwidth[i], tmpw);
					}
					size.x += colwidth[i];
				}
				for (int i = 0; i < rows; i++) {
					rowheight[i] = 0;
					rowstarty[i] = size.y;
					for (int j = 0; j < cols; j++) {
						int tmph = GetPrintRectSize(0, 0, colwidth[j] - TextHeight * 2, items[i][j]).y;
						rowheight[i] = std::max(rowheight[i], tmph);
					}
					rowheight[i] += SpaceSize;
					size.y += rowheight[i];
				}
				height = size.y + SliderWidth;
			}
			int Draw(int x, int y, int w, bool check = true) {
				// 表格无内容，舍去
				if (cols == 0 || rows == 0) return 1;
				// 绘制表格
				DrawTable(x, y, check);
				// 绘制滚动条
				BeginAlphaMode(0.7);
				sy.GotoTop();
				sx.SetControl(x, y, w, size.y);
				sx.SetDrawBackground(false);
				sx.SetSum(size.x);
				sx.SetBlank(0);
				sx.Draw_Auto_Extra(x, y + size.y, w, SliderWidth);
				sx.Update();
				EndAlphaMode();
				return height;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				// 表格无内容，舍去
				if (cols == 0 || rows == 0) return 1;
				// 绘制表格
				BeginScissor(x, y, w, h);
				DrawTable(x + interval, y + interval, check);
				EndScissor();
				// 绘制滚动条
				BeginAlphaMode(0.7);
				sx.SetControl(x, y, w, h);
				sx.SetDrawBackground(false);
				sx.SetSum(size.x + interval + SliderWidth);
				sx.SetBlank(0);
				sx.Draw_Auto_Extra(x, y + h - SliderWidth, w - SliderWidth, SliderWidth);
				sx.Update();
				sy.SetControl(x, y, w, h);
				sy.SetDrawBackground(false);
				sy.SetSum(size.y + interval + SliderWidth);
				sy.SetBlank(0);
				sy.Draw_Auto_Extra(x + w - SliderWidth, y, SliderWidth, h - SliderWidth);
				sy.Update();
				EndAlphaMode();
				return height;
			}
		};
		class Console : public Element {
		private:
			MultiInputBox box;
			std::function <void()> stream_fun = nullptr;

		public:
			Console() {
				extra = true;
				box.input_enable = false;
				box.background_color = BLACK;
			}
			void Main(std::function <void()> fun) {
				stream_fun = fun;
				std::thread([&] {
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					fun();
				}).detach();
			}
			template <class T>
			void println(T var) {
				box.InsertBack_andMove_Prepare(wp::tostr(var) + "\n");
			}
			template <class T>
			void print(T var) {
				box.InsertBack_andMove_Prepare(wp::tostr(var));
			}
			template <class T>
			void inputln(T& var) {
				int line = box.input_pos.y;
				int x = box.input_pos.x;
				box.input_enable = true;
				while (box.input_pos.y == line);
				box.input_enable = false;
				std::stringstream ss;
				ss << box.Copy(vector2d(x, line), vector2d(box.input[line].size(), line));
				ss >> var;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				box.Draw_Auto_Extra(x, y, w, h, check);
				return 0;
			}

		};
		class CheckBox : public Element {
		private:
			bool* ptr = nullptr;
			Animation tickAni, aAni;
		public:
			bool choose = false;
			bool draw_box_background = true;
			CheckBox(std::string text_ = "Check Box", bool choose_ = false, bool* ptr_ = nullptr) {
				content = text_;
				choose = choose_;
				ptr = ptr_;
				if (choose)tickAni.gt(1).sms(anif::bounce3).sd(400);
				else tickAni.gt(0).sms(anif::bounce3).sd(400);
			}
			int Draw(int x, int y, int w, bool check = true) {
				int h = (UnitHeight - TextHeight) / 2;
				tickAni.update();
				aAni.update();
				if (choose) {
					tickAni.stp(1);
					aAni.stp(1);
				} else {
					tickAni.stp(0);
					aAni.stp(0);
				}
				if (draw_box_background) {
					if (aAni.gnp() != 1) DrawRectangle(x + UnitHeight / 4, y + UnitHeight / 4, UnitHeight / 2, UnitHeight / 2, ColorF(MainColor));
					if (aAni.gnp() != 0) DrawRectangle(x, y, UnitHeight, UnitHeight, ColorF(ThemeColor, aAni.gnp()));
					special_effect::DrawMouseRectangle(x, y, UnitHeight, UnitHeight);
				}
				Print(x + UnitHeight + SpaceSize * 2, y + h, content);
				if (tickAni.gnp() > 0) {
					realn t1 = std::min(tickAni.gnp(), (realn)0.4) / 0.4;
					realn t2 = std::max(tickAni.gnp() - (realn)0.4, (realn)0) / 0.6;
					int k = UnitHeight;
					vector2d p1 = vector2d(x + k * 0.2, y + k * 0.5);
					vector2d p2 = vector2d(x + k * 0.4, y + k * 0.8);
					vector2d p3 = vector2d(x + k * 0.8, y + k * 0.2);
					DrawLineEx(_V(p1), _V(p1 + (p2 - p1)*t1), dpi, ColorF(WHITE));
					DrawLineEx(_V(p2), _V(p2 + (p3 - p2)*t2), dpi, ColorF(WHITE));
				}
				if (draw_box_background) {
					if (check && MouseInRect(x, y, width, UnitHeight)) {
						DrawRectangle(x, y, UnitHeight, UnitHeight, ColorF(ChooseColor));
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							choose = !choose;
						}
					}
				} else {
					if (check && MouseInRect(x, y, w, UnitHeight)) {
						DrawRectangle(x, y, UnitHeight, UnitHeight, ColorF(ChooseColor));
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							choose = !choose;
						}
					}
				}
				if (ptr) *ptr = choose;
				width = wp::strLen(content) * TextHeight / 2 + UnitHeight + SpaceSize * 2;
				return UnitHeight;
			}
		};
		class Hyperlink : public Element {
		private:
			std::string link = "";				// 链接网址
			Animation move;						// 底部划线动画
			std::string icon = u8"";			// 图标
			bool click = false;					// 是否点击
			std::function <void()> callback = nullptr; // 回调函数
		public:
			Hyperlink() {}
			Hyperlink(std::string text_, std::string link_) {
				if (text_.find('[') == 0 && text_.find(']') != -1) {
					icon = text_.substr(1, text_.find(']') - 1);
					content = text_.substr(text_.find(']') + 1);
				} else {
					content = text_;
					icon = u8"";
				}
				link = link_;
				move.sd(300);
			}
			Hyperlink& withCallback(std::function <void()> callback_) {
				callback = callback_;
				return *this;
			}
			int Draw(int _x, int _y, int _w, bool check = true) {
				float x = float(_x);
				float y = float(_y);
				float w = float(_w);
				float h = (UnitHeight - TextHeight) / 2;
				move.update();
				click = false;
				PrintIcon(x, y + h, icon, ColorF(177, 164, 246, 255));
				Print(x + TextHeight + SpaceSize, y + h, content, ColorF(177, 164, 246, 255));
				DrawLineEx(
				    Vector2{x + width / 2 - move.gnp() * width / 2, y + UnitHeight},
				    Vector2{x + width / 2 + move.gnp() * width / 2, y + UnitHeight},
				    dpi, ColorF(177, 164, 246, 255)
				);
				if (MouseInRect(x, y, width, UnitHeight)) {
					move.stp(1);
					MouseCursorStyle = MOUSE_CURSOR_POINTING_HAND;
					if (IsMouseDown(MOUSE_BUTTON_LEFT)) {
						DrawRectangle(x, y, width, UnitHeight, ColorF(ChooseColor));
					}
					if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
						if (link != "") OpenURL(link.c_str());
						click = true;
						if (callback) callback();
					}
				} else move.stp(0);
				width = wp::strLen(content) * TextHeight / 2 + TextHeight + SpaceSize;
				return UnitHeight;
			}
		};
		class RadioBox : public Element {
		private:
			std::vector<Animation> choose_ani;
			std::vector<std::string> rtext;
			int* ptr = nullptr;
			int DrawOne(int id, int _x, int _y, int _w, bool check = true) {
				float x = float(_x), y = float(_y), w = float(_w);
				int h = (UnitHeight - TextHeight) / 2;
				if (draw_box_background) {
					if (choose != id) DrawCircle(x + UnitHeight / 2, y + UnitHeight / 2, UnitHeight / 4, ColorF(MainColor));
					DrawRing({x + UnitHeight / 2, y + UnitHeight / 2}, std::min(UnitHeight / 2 - int(choose_ani[id].gnp()*UnitHeight / 3.0), UnitHeight / 2), UnitHeight / 2, 0, 360, 30,  ColorF(ThemeColor));
					ui::special_effect::DrawMouseCircle(x + UnitHeight / 2, y + UnitHeight / 2, UnitHeight / 2);
				} else {
					BeginAlphaMode(choose_ani[id].gnp());
					DrawCircle(x + UnitHeight / 2, y + UnitHeight / 2, UnitHeight / 6, ColorF(WHITE));
					EndAlphaMode();
				}
				Print(x + UnitHeight + SpaceSize * 2, y + h, rtext[id]);
				if (draw_box_background) {
					if (check && MouseInRect(x, y, width, UnitHeight)) {
						DrawCircle(x + UnitHeight / 2, y + UnitHeight / 2, UnitHeight / 2, ColorF(ChooseColor));
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							choose_ani[id].stp(1);
							choose = id;
						}
					}
				} else {
					if (check && MouseInRect(x, y, w, UnitHeight)) {
						DrawCircle(x + UnitHeight / 2, y + UnitHeight / 2, UnitHeight / 2, ColorF(ChooseColor));
						if (IsMousePressed(MOUSE_BUTTON_LEFT)) {
							choose_ani[id].stp(1);
							choose = id;
						}
					}
				}
				return UnitHeight;
			}
		public:
			int choose = -1;
			bool draw_box_background = true;
			RadioBox(std::vector<std::string> rtext_, int choose_ = -1, int* ptr_ = nullptr) {
				for (int i = 0; i < rtext_.size(); i++)AddOption(rtext_[i]);
				choose = choose_;
				ptr = ptr_;
			}
			RadioBox() {}
			RadioBox& AddOption(std::string text_) {
				rtext.push_back(text_);
				Animation ani;
				ani.sd(300).sms(anif::bounce5);
				choose_ani.push_back(ani);
				return *this;
			}
			int Draw(int x, int y, int w, bool check = true) {
				int maxn = 0;
				for (int i = 0; i < rtext.size(); i++) {
					choose_ani[i].update();
					DrawOne(i, x, y + (UnitHeight + SpaceSize) * i, w, check);
					if (choose != i)choose_ani[i].stp(0);
					maxn = std::max(maxn, wp::strLen(rtext[i]));
				}
				if (ptr)(*ptr) = choose;
				width = maxn * TextHeight / 2 + UnitHeight + SpaceSize * 2;
				return (UnitHeight + SpaceSize) * rtext.size() - SpaceSize;
			}
		};
		class Pulldown : public Priority {
		private:
			Animation wani, hani;				// 长、宽动画
			int Height = 0;						// 控件总高度
			int Width = 0;						// 控件总宽度
			std::vector<char> type; 			// 控件类型
			std::vector<Pulldown*> menu;		// 指向菜单
			std::vector<std::function<void()> > callback;// 回调函数
			Vector2 pos;						// 位置
			bool open = false;					// 是否展开
			RenderTexture texture;				// texture
			int texture_inited = 0;				// 是否初始化texture
			int unit_interval = SpaceSize;		// 控件间距

			realn GetAniBias(int id) {
				return (1 - appearAni.GetPos(gclock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id >= 0)return appearAni.GetPos(gclock() - id * 50);
				else return appearAni.GetPos((gclock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}

		public:
			Animation appearAni;				// 淡入动画
			std::string click = "";				// 点击的按钮
			Pulldown(std::string text_ = "", ReleaseFunc fun = nullptr) {
				extra = true;
				content = text_;
				SetReleaseFunc(fun);
				wani.ssp(0);
				hani.ssp(0);
				Width = UnitHeight * 2;
				Height = UnitHeight;
			}
			Pulldown& AddButton(std::string content) {
				ColorText* temp = new ColorText(content);
				Add(temp, auto_release);
				type.resize(Size());
				type[type.size() - 1] = 1;
				return *this;
			}
			Pulldown& AddCheckBox(std::string content, bool on = false, bool* ptr = nullptr) {
				CheckBox* temp = new CheckBox(content, on, ptr);
				temp->draw_box_background = false;
				Add(temp, auto_release);
				return *this;
			}
			Pulldown& AddRadioBox(std::vector<std::string> content, int choose = -1, int* ptr = nullptr) {
				RadioBox* temp = new RadioBox(content, choose, ptr);
				temp->draw_box_background = false;
				Add(temp, auto_release);
				type.resize(Size());
				type[type.size() - 1] = 4;
				return *this;
			}
			Pulldown& AddLine() {
				Line* temp = new Line();
				Add(temp, auto_release);
				type.resize(Size());
				type[type.size() - 1] = 3;
				return *this;
			}
			Pulldown& withCallback(std::function <void()> callback_) {
				callback.resize(Size());
				callback[Size() - 1] = callback_;
				return *this;
			}
			Pulldown& AddMenu(std::string content, Pulldown* temp = nullptr, ReleaseFunc fun = nullptr) {
				if (temp) {
					Add(temp, fun);
					temp->content = content;
					type.resize(Size());
					type[type.size() - 1] = 2;
					menu.resize(type.size());
					menu[menu.size() - 1] = temp;
				} else {
					temp = new Pulldown;
					Add(temp, auto_release);
					temp->content = content;
					type.resize(Size());
					type[type.size() - 1] = 2;
					menu.resize(type.size());
					menu[menu.size() - 1] = temp;
				}
				return *this;
			}
			Pulldown& Open(Vector2 pos_) {
				pos = pos_;
				wani.stp(Width).sd(500).sms(anif::bounce);
				hani.stp(Height).sd(500).sms(anif::bounce);
				appearAni.sd(500).sms(anif::sine);
				open = true;
				pop = true;
				SetTopPriority();
				return *this;
			}
			Pulldown& Open(int x, int y) {
				Open(Vector2{float(x), float(y)});
				return *this;
			}
			Pulldown& Close() {
				wani.stp(0).sd(300).sms(anif::classics_r);
				hani.stp(0).sd(300).sms(anif::classics_r);
				appearAni.sd(300).sms(anif::classics);
				open = false;
				return *this;
			}
			Pulldown& ChangeState(Vector2 pos_) {
				if (pop)return Close();
				return Open(pos_);
				return *this;
			}
			Pulldown& ChangeState(int x, int y) {
				return ChangeState(Vector2{float(x), float(y)});
				return *this;
			}
			Pulldown& SetPos(Vector2 pos_) {
				pos = pos_;
				return *this;
			}
			Pulldown& SetPos(int x, int y) {
				pos.x = x;
				pos.y = y;
				return *this;
			}
			int Draw(int x, int y, int w, int h, bool check) {
				// 判断是否收起
				if (!open && wani.gnp() == 0) {
					texture_inited = 0;
					UnloadRenderTexture(texture);
					pop = false;
					width = wp::strLen(content) * TextHeight / 2 + TextHeight + SpaceSize * 3 + TextHeight / 2;
					return h;
				}
				x = pos.x, y = pos.y;
				if (priority != GetTopPriority() || (!MouseInRect(x, y, wani.gnp(), hani.gnp()) && IsMousePressed(MOUSE_BUTTON_LEFT))) {
					bool flag = false;
					for (int i = 0; i < menu.size(); i++) {
						if (!menu[i])continue;
						if (menu[i]->appearAni.gnp() > 0.7 || menu[i]->open) {
							flag = true;
							break;
						}
					}
					if (!flag)Close();
				}
				// 计算控件总高度和总高度
				type.resize(Size());
				menu.resize(Size());
				callback.resize(Size());
				Height = 0;
				Width = 0;
				for (int i = 0; i < key.size(); i++) {
					if (!key[i])continue;
					if (type[i] == 2) {
						Height += UnitHeight;
						Width = std::max(Width, key[i]->width);
						continue;
					}
					Height += key[i]->GetHeight() + unit_interval;
					Width = std::max(Width, key[i]->width);
				}
				// 更新
				Width += SpaceSize * 2 + UnitHeight * 2;
				Height += unit_interval * 3;
				w = Width;
				h = Height;
				if (open) {
					wani.stp(w);
					hani.stp(h);
					appearAni.stp(1);
				} else {
					wani.stp(0);
					hani.stp(0);
					appearAni.stp(0);
				}
				wani.update();
				hani.update();
				appearAni.update();
				click = "";
				// 边界检查
				if (x + wani.gnp() > ui::winW) x = ui::winW - wani.gnp();
				if (y + hani.gnp() > ui::winH) y = ui::winH - hani.gnp();
				X = x, Y = y, W = w, H = h;
				// 绘制控件
				if (texture_inited <= 2 && wani.is_run()) {
					texture_inited++;
					if (texture_inited == 1) {
						texture = LoadRenderTexture(w, h);
					}
					BeginTextureMode(texture);
					DrawRectangle(0, 0, w, h, MenuColor);
					int nowh = unit_interval * 1.5;
					for (int i = 0; i < key.size(); i++) {
						if (type[i] == 0 || type[i] == 3) {
							nowh += key[i]->Draw_Auto(SpaceSize * 2, nowh, w - SpaceSize * 4, check);
						} else if (type[i] == 1) {
							nowh += key[i]->Draw_Auto(SpaceSize * 2, nowh, w - SpaceSize * 4, check);
						} else if (type[i] == 2) {
							if (!menu[i]) continue;
							Print(SpaceSize * 3 + TextHeight, nowh + (UnitHeight - TextHeight) / 2, menu[i]->content);
							Print(w - SpaceSize * 2 - TextHeight / 2, nowh + (UnitHeight - TextHeight) / 2, ">", LineColor);
							nowh += UnitHeight;
						} else if (type[i] == 4) {
							nowh += key[i]->Draw_Auto(SpaceSize * 2, nowh, w - SpaceSize * 4, check);
						}
						nowh += unit_interval;
					}
					EndTextureMode();
				}
				if (wani.is_run()) {
					BeginAlphaMode(GetAniAlpha(0));
					special_effect::DrawFrame(x - dpi, y - dpi, wani.gnp() + dpi * 2, hani.gnp() + dpi * 2);
					DrawTexturePro(texture.texture, {0, 0, (float)w, (float) - h}, {(float)x, (float)y, wani.gnp(), hani.gnp()}, {0, 0}, 0, ui::ColorF(WHITE));
					EndAlphaMode();
					int nowh = SpaceSize;
					for (int i = 0; i < key.size(); i++) {
						if (menu[i]) menu[i]->SetPos(x + wani.gnp() + SpaceSize, y + nowh * hani.gnp() / h);
						if (type[i] == 0 || type[i] == 3) nowh += key[i]->GetHeight();
						else if (type[i] == 1) nowh += key[i]->GetHeight();
						else if (type[i] == 2) nowh += UnitHeight;
						else if (type[i] == 4) nowh += key[i]->GetHeight();
					}
				} else {
					BeginScissor(x - dpi, y - dpi, wani.gnp() + dpi * 2, hani.gnp() + dpi * 2);
					BeginAlphaMode(GetAniAlpha(0));
					special_effect::DrawFrame(x - dpi, y - dpi, wani.gnp() + dpi * 2, hani.gnp() + dpi * 2);
					DrawRectangle(x, y, wani.gnp(), hani.gnp(), ColorF(MenuColor));
					x -= w - wani.gnp();
					y -= h - hani.gnp();
					y += unit_interval * 1.5;
					int nowh = 0;
					for (int i = 0; i < key.size(); i++) {
						bool next_check = (check && MouseInRect(x, y, wani.gnp(), hani.gnp()));
						if (type[i] == 0 || type[i] == 3) {
							if (!wani.is_run() && MouseInRect(x, y + nowh, w, key[i]->height) && type[i] != 3) {
								DrawRectangle(x, y + nowh - unit_interval / 2, w, UnitHeight + unit_interval, ColorF(ChooseColor));
							}
							nowh += key[i]->Draw_Auto(x + SpaceSize * 2, y + nowh, w - SpaceSize * 4, next_check);
						} else if (type[i] == 1) {
							if (!wani.is_run() && MouseInRect(x, y + nowh, w, UnitHeight)) {
								DrawRectangle(x, y + nowh - unit_interval / 2, w, UnitHeight + unit_interval, ColorF(ChooseColor));
								if (next_check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
									click = key[i]->content;
									if (callback[i]) callback[i]();
								}
								if (next_check && IsMouseDown(MOUSE_BUTTON_LEFT)) {
									DrawRectangle(x, y + nowh - unit_interval / 2, w, UnitHeight + unit_interval, ColorF(ChooseColor));
								}
							}
							nowh += key[i]->Draw_Auto(x + SpaceSize * 2, y + nowh, w - SpaceSize * 4, next_check);
						} else if (type[i] == 2) {
							if (!menu[i])continue;
							Print(x + SpaceSize * 3 + TextHeight, y + nowh + (UnitHeight - TextHeight) / 2, menu[i]->content);
							Print(x + w - SpaceSize * 2 - TextHeight / 2, y + nowh + (UnitHeight - TextHeight) / 2, ">", LineColor);
							menu[i]->SetPos(x + wani.gnp() + SpaceSize, y + nowh);
							if (!wani.is_run() && MouseInRect(x, y + nowh, w, UnitHeight)) {
								DrawRectangle(x, y + nowh - unit_interval / 2, w, UnitHeight + unit_interval, ColorF(ChooseColor));
								if (next_check && IsMousePressed(MOUSE_BUTTON_LEFT)) menu[i]->ChangeState(x + wani.gnp() + SpaceSize, y + nowh);
								if (next_check && IsMouseDown(MOUSE_BUTTON_LEFT)) {
									DrawRectangle(x, y + nowh - unit_interval / 2, w, UnitHeight + unit_interval, ColorF(ChooseColor));
								}
							}
							nowh += UnitHeight;
						} else if (type[i] == 4) {
							if (!wani.is_run() && MouseInRect(x, y + nowh - unit_interval / 2, w, key[i]->height + unit_interval / 2) && type[i] != 3) {
								DrawRectangle(
								    x, y + nowh + int((Mouse.y - y - nowh) / (UnitHeight + SpaceSize)) * (UnitHeight + SpaceSize) - unit_interval / 2,
								    w, UnitHeight + SpaceSize, ColorF(ChooseColor)
								);
							}
							nowh += key[i]->Draw_Auto(x + SpaceSize * 2, y + nowh, w - SpaceSize * 4, next_check);
						}
						nowh += unit_interval;
					}
					EndAlphaMode();
					EndScissor();
				}
				if (check && DebugMode) {
					DrawRectangleLines(x, y - unit_interval * 1.5, w, h, ORANGE);
				}
				// 结束
				width = wp::strLen(content) * TextHeight / 2 + TextHeight + SpaceSize * 3 + TextHeight / 2;
				return UnitHeight;
			}

		};
		class TopMenu : public Element {
		private:
			std::vector<std::string> mtext;
			std::vector<std::string> icon;
			std::vector<Pulldown*> menu;
			std::vector<std::function<void() >> callback;
			int Height = UnitHeight * 2;
			bool opened = false;
		public:
			int click = -1;
			TopMenu() {
				extra = true;
				content = "TopMenu";
			}
			TopMenu& AddButton(std::string text_) {
				if (text_.find('[') == 0 && text_.find(']') != -1) {
					icon.push_back(text_.substr(1, text_.find(']') - 1));
					mtext.push_back(text_.substr(text_.find(']') + 1));
				}
				else {
					icon.push_back("");
					mtext.push_back(text_);
				}
				menu.push_back(nullptr);
				callback.push_back(nullptr);
				return *this;
			}
			TopMenu& withMenu(Pulldown* temp) {
				menu[menu.size() - 1] = temp;
				return *this;
			}
			TopMenu& withCallback(std::function<void()> callback_) {
				callback[callback.size() - 1] = callback_;
				return *this;
			}
			TopMenu& SetHeight(int h) {
				Height = h;
				return *this;
			}
			void DrawOne(int id, int x, int y, int w, int h, bool check = true) {
				int t = (h - TextHeight) / 2;
				special_effect::DrawMouseRectangle(x, y + SpaceSize / 2, w, h - SpaceSize);
				PrintIcon(x + SpaceSize * 2, y + t, icon[id], ThemeColor);
				if (icon[id] == "") Print(x + SpaceSize * 2 + wp::strLen(icon[id]) * ui::TextHeight / 2, y + t, mtext[id], MenuFtColor);
				else Print(x + SpaceSize * 4 + wp::strLen(icon[id])*ui::TextHeight / 2, y + t, mtext[id], MenuFtColor);
				if (MouseInRect(x, y + SpaceSize / 2, w, h - SpaceSize)) {
					DrawRectangle(x, y + SpaceSize / 2, w, h - SpaceSize, ColorF(ChooseColor));
					if (opened) {
						for (int i = 0; i < menu.size(); i++) if (menu[i] && i != id) menu[i]->Close();
						menu[id]->Open(x, y + h + SpaceSize);
					}
					if (IsMouseDown(MOUSE_BUTTON_LEFT) && check) DrawRectangle(x, y + SpaceSize / 2, w, h - SpaceSize, ColorF(ChooseColor));
					if (IsMousePressed(MOUSE_BUTTON_LEFT) && check) {
						click = id;
						if (menu[id]) {
							menu[id]->Open(x, y + h + SpaceSize);
							opened = true;
						}
						if (callback[id]) callback[id]();
					}
				}
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (check) opened = false;
				DrawRectangle(x, y, w, h, ColorF(MenuColor));
				int w2 = dpi;
				click = -1;
				for (int i = 0; i < mtext.size(); i++) {
					int s = (wp::strLen(mtext[i]) + wp::strLen(icon[i])) * TextHeight / 2;
					if (icon[i] == "" || mtext[i] == "") s -= ui::SpaceSize * 2;
					DrawOne(i, x + w2, y, s + SpaceSize * 6, h, check);
					w2 += s + SpaceSize * 6 + dpi;
				}
				return Height;
			}
		};
		class BottomMenu : public Element {
		private:
			std::vector<Button> button;
			std::vector<std::function<void() >> callback;
			int Height = UnitHeight * 2.5;
		public:
			int click = -1;
			BottomMenu() {}
			BottomMenu& AddButton(std::string icon, std::string content, Color color = DARKGRAY) {
				Button but;
				but.content = content;
				but.SetColor(color);
				but.icon = icon;
				button.push_back(but);
				callback.push_back(nullptr);
				return *this;
			}
			BottomMenu& AddButton(std::string content, Color color = DARKGRAY) {
				return AddButton("", content, color);
			}
			BottomMenu& withCallback(std::function<void()> callback_) {
				callback[callback.size() - 1] = callback_;
				return *this;
			}
			BottomMenu& SetHeight(int h) {
				Height = h;
				return *this;
			}
			int Draw(int _x, int _y, int _w, int _h, bool check = true) {
				float x = _x, y = _y, w = _w, h = _h;
				click = -1;
				DrawRectangle(_x, _y, _w, _h, ColorF(35, 35, 35, 255));
				DrawLineEx({x, y + dpi / 2}, {x + w, y + dpi / 2}, dpi, ColorF(255, 255, 255, 30));
				int t = (Height - UnitHeight * 1.3) / 2;
				int width = t;
				for (int i = 0; i < button.size(); i++) {
					int k = std::max(button[i].GetWidth(), UnitHeight * 4);
					button[i].Draw_Auto_Extra(x + w - width - k, y + t, k, UnitHeight * 1.3, check);
					if (button[i].Click()) {
						click = i;
						if (callback[i])callback[i]();
					}
					width += k + SpaceSize;
				}
				return Height;
			}
		};
		class NavigationItem {
		public:
			std::string icon = "";
			std::string content = "content";
			Animation angle;
			Animation move;
			bool open = false;
			int dfs_order = 0;
			int size = 0;
			void Open() {
				open = true;
				angle.stp(acos(-1) / 2).sd(300).sms(anif::bounce5);
				move.stp(1).sd(500).sms(anif::classics_d);
			}
			void Close() {
				open = false;
				angle.stp(0).sd(300).sms(anif::bounce5);
				move.stp(0).sd(500).sms(anif::classics_d);
			}
		};
		Navigation* this_navigation = nullptr;
		class Navigation : public Element {
		private:
			tree_node <NavigationItem> tree;
			tree_node <NavigationItem>* click_node = nullptr;
			bool click = false;
			bool top_or_bottom = true;
			SliderBar sbar;
			std::function <void()> callback = nullptr;
			int order = 0;
			int DFSDraw(tree_node<NavigationItem>& node, int x, int y, bool check) {
				int NodeHeight = UnitHeight + SpaceSize;
				if (&node == &tree) {
					int h = 0;
					BeginScissor(X, y, W, node.value().size);
					for (auto i : node.children()) {
						h += DFSDraw(*i, x, y + h, check);
					}
					EndScissor();
					node.value().size = h;
					return h;
				}
				node.value().dfs_order = order, order++;
				int tempH = (NodeHeight - TextHeight) / 2;
				node.value().angle.update();
				node.value().move.update();
				if (&node == click_node) DrawRectangle(X, y, W, NodeHeight, ColorF(MainColor));
				if (node.value().icon == "") Print(x + NodeHeight + SpaceSize * 2, y + tempH, node.value().content);
				else {
					PrintIcon(x + NodeHeight + SpaceSize * 2, y + tempH, node.value().icon, ThemeColor);
					Print(x + NodeHeight + SpaceSize * 2 + NodeHeight, y + tempH, node.value().content);
				}
				int width = wp::strLen(node.value().content) * TextHeight / 2 + NodeHeight + SpaceSize * 4;
				if (node.size() > 0) {
					vector2d k1 = vector2d(-TextHeight / 4 * 0.8, -TextHeight / 2 * 0.8);
					vector2d k2 = vector2d(TextHeight / 4 * 0.8, 0);
					vector2d k3 = vector2d(-TextHeight / 4 * 0.8, TextHeight / 2 * 0.8);
					vector2d p1 = k1.Rotate(node.value().angle.gnp());
					vector2d p2 = k2.Rotate(node.value().angle.gnp());
					vector2d p3 = k3.Rotate(node.value().angle.gnp());
					int TempX = x + NodeHeight / 2;
					int TempY = y + NodeHeight / 2;
					DrawLine(p1.x + SpaceSize + TempX, p1.y + TempY, p2.x + SpaceSize + TempX, p2.y + TempY, ColorF(LIGHTGRAY));
					DrawLine(p2.x + SpaceSize + TempX, p2.y + TempY, p3.x + SpaceSize + TempX, p3.y + TempY, ColorF(LIGHTGRAY));
				}
				if (MouseInRect(X, y, W, NodeHeight)) {
					if (check) DrawRectangle(X, y, W, NodeHeight, ChooseColor);
					if (IsMouseDown(MOUSE_BUTTON_LEFT) && check) DrawRectangle(X, y, W, NodeHeight, ChooseColor);
					if (IsMousePressed(MOUSE_BUTTON_LEFT) && check) {
						if (click_node != &node) click = true;
						if (click_node) {
							if (click_node->value().dfs_order > node.value().dfs_order) top_or_bottom = false;
							else top_or_bottom = true;
						}
						click_node = &node;
						if (node.size() > 0) {
							if (node.value().open) node.value().Close();
							else node.value().Open();
						}
					}
				}
				int h = NodeHeight;
				int dh = (1.0 - node.value().move.gnp()) * node.value().size;
				bool run = node.value().move.is_run();
				BeginScissor(X, y + NodeHeight, W, node.value().move.gnp() * node.value().size);
				for (auto i : node.children()) {
					h += DFSDraw(*i, x + SpaceSize * 2, y + h - dh, check && !node.value().move.is_run() && node.value().open);
				}
				EndScissor();
				node.value().size = h - NodeHeight;
				return h - dh;
			};
			void DFSSet(tree_node<std::string>& tr, tree_node<NavigationItem>& node) {
				NavigationItem temp;
				if (tr.value().find('[') == 0 && tr.value().find(']') != -1) {
					temp.icon = tr.value().substr(1, tr.value().find(']') - 1);
					temp.content = tr.value().substr(tr.value().find(']') + 1);
				} else temp.content = tr.value();
				for (int i = 0; i < tr.size(); i++) {
					DFSSet(tr.child(i), node.child(i));
				}
				node.set(temp);
			};
		public:
			Navigation(std::string content_, tree_node <std::string>& tr) {
				content = content_;
				width = 180 * ui::dpi;
				SetContentTree(tr);
			}
			Navigation() {
				content = "Navigation";
				width = 180 * ui::dpi;
			}
			Navigation& SetContentTree(tree_node <std::string>& tr) {
				DFSSet(tr, tree);
				return *this;
			}
			Navigation& withCallback(std::function <void()> callback_) {
				callback = callback_;
				return *this;
			}
			Navigation& SetWidth(int width_) {
				width = width_;
				return *this;
			}
			bool Click() {
				return click;
			}
			std::string GetClickNode() {
				if (click_node->value().icon == "") return click_node->value().content;
				return "[" + click_node->value().icon + "]" + click_node->value().content;
			}
			SiderPosition GetShiftPos() {
				if (top_or_bottom) return spos_bottom;
				else return spos_top;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				click = false;
				if (click_node == nullptr) {
					click_node = &tree.child(0);
					click = true;
				}
				tree.value().Open();
				DrawRectangle(x, y, w, h, ColorF(MenuColor));
				static ui::Head head;
				head.content = content;
				head.SetSize(4);
				head.Draw_Auto(x + ui::UnitHeight, y - sbar.Now() + ui::SpaceSize * 3, w, check);
				order = 0;
				DFSDraw(tree, x, y - sbar.Now() + UnitHeight * 3, check && MouseInRect(x, y, w - SliderWidth, h));
				if (click) {
					this_navigation = this;
					if (callback) callback();
				}
				sbar.SetBlank(0);
				sbar.SetControl(x, y, w, h);
				sbar.SetSum(tree.value().size + UnitHeight * 5);
				sbar.SetBgColor(BLANK);
				sbar.Draw_Auto_Extra(x + w - SliderWidth, y, SliderWidth, h, true);
				sbar.Update();
				return width;
			}
		};
		class Tip : public Priority {
		public:
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
			void Set(int x, int y, int w, int h) {
				flag = 0;
				cx = x, cy = y, cw = w, ch = h;
			}
			void Set(Element* Ele) {
				flag = 1;
				ele = Ele;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				if (flag == 0)x = cx, y = cy, w = cw, h = ch;
				else x = ele->X, y = ele->Y, w = ele->W, h = ele->height;
				if (MouseInRect(x, y, w, h)) {
					if (!float_) {
						float_ = true;
						float_time = gclock();
					}
				} else if (float_) {
					float_ = false;
				}
				if (float_ && gclock() - float_time > delay && !pop) {
					pop = true;
					pop_time = gclock();
					priority = ++TopPriority;
				}
				if (!float_ && pop) {
					pop = false;
					pop_time = gclock();
				}
				if (pop || gclock() - pop_time <= 200) {
					int tx, ty, tw, th;
					th = UnitHeight;
					tw = content.size() * TextHeight / 2 + SpaceSize * 2;
					tx = x + w / 2 - tw / 2;
					ty = y - th - SpaceSize;
					int h = (UnitHeight - TextHeight) / 2;
					double a;
					if (pop)a = (gclock() - pop_time) / 200.0;
					else a = 1 - (gclock() - pop_time) / 200.0;
					if (a > 1)a = 1;

					special_effect::DrawShadowRectangle(tx, ty, tw, th, a * 15 * dpi);
					DrawRectangleRounded(Rectangle{(float)tx, (float)ty, (float)tw, (float)th}, 0.4, 10, Fade(BgColor, a * 0.7));
					DrawRectangleRoundedLines(Rectangle{(float)tx, (float)ty, (float)tw, (float)th}, 0.4, 10, Fade(MainColor, a * 0.7));
					Print(tx + SpaceSize, ty + h, content, Fade(TextColor, a * 0.7));
				} else priority = -1;
				return 0;
			}
		};
		Free* this_free = nullptr;
		class Free : public Element {
		private:
			SliderBar sx, sy;						// 横向、纵向滚动条
			int maxw = 100 * dpi, maxh = 100 * dpi;	// 最大宽度、高度
			Animation appearAni;					// 淡入动画
			realn GetAniBias(int id) {
				return (1 - appearAni.GetPos(gclock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id >= 0)return appearAni.GetPos(gclock() - id * 50);
				else return appearAni.GetPos((gclock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}

		public:
			bool slider_visible = false;			// 是否显示滚动条
			std::function <void()> draw_fun; 		// 绘制函数
			Free(std::function <void()> fun = nullptr) {
				extra = true;
				draw_fun = fun;
			}
			Free& SetSize(int w, int h) {
				maxw = w;
				maxh = h;
				return *this;
			}
			int GetX() {
				return sider.X - sx.Now();
			}
			int GetY() {
				return sider.Y - sy.Now();
			}
			int GetWidth() {
				return std::max(sider.W, sx.GetHeight());
			}
			int GetHeight() {
				return std::max(sider.H, sy.GetHeight());
			}
			void print(int x, int y, std::string text, Color color = ui::TextColor) {
				int tw = wp::strLen(text) * ui::TextHeight / 2;
				if (x + tw - sx.Now() < 0 || x - sx.Now() > W || y + ui::UnitHeight - sy.Now() < 0 || y - sy.Now() > H) return;
				Print(x + X - sx.Now(), y + Y - sy.Now(), text, color);
			}
			void print_rect(int x, int y, int w, std::string text, Color color = ui::TextColor) {
				vector2d box = GetPrintRectSize(x, y, w, text);
				if (x + box.x - sx.Now() < 0 || x - sx.Now() > W || y + box.y - sy.Now() < 0 || y - sy.Now() > H) return;
				PrintRect(x + X - sx.Now(), y + Y - sy.Now(), w, text, color);
			}
			void rectangle(int x, int y, int w, int h, Color color) {
				if (x + w - sx.Now() < 0 || x - sx.Now() > W || y + h - sy.Now() < 0 || y - sy.Now() > H) return;
				DrawRectangle(x + X - sx.Now(), y + Y - sy.Now(), w, h, ui::ColorF(color));
			}
			void GotoBottom() {
				sy.GotoBottom();
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				this_free = this;
				// 界面可见，检查是否启动淡入动画
				appearAni.update();
				if (GetTick() - update_tick > 10)appearAni.ssp(0);
				appearAni.stp(1);
				x += GetAniBias(2) / 2;
				y += GetAniBias(2) / 2;
				w -= GetAniBias(2);
				h -= GetAniBias(2);
				// 绘制侧边栏
				BeginAlphaMode(GetAniAlpha(0));
				sider.Draw(x, y, w, h, check);
				EndAlphaMode();
				// 绘制内容
				BeginAlphaMode(GetAniAlpha(-2));
				BeginScissor(sider.X, sider.Y, sider.W, sider.H);
				if (slider_visible) {
					if (draw_fun) draw_fun();
					sx.SetBlank(0);
					sy.SetBlank(0);
					sx.SetSum(maxw);
					sy.SetSum(maxh);
					sx.SetControl(sider.X, sider.Y, sider.W, sider.H);
					sy.SetControl(sider.X, sider.Y, sider.W, sider.H);
					sx.Draw_Auto_Extra(sider.X, sider.Y + sider.H - SliderWidth, sider.W - SliderWidth, SliderWidth, check);
					sy.Draw_Auto_Extra(sider.X + sider.W - SliderWidth, sider.Y, SliderWidth, sider.H - SliderWidth, check);
					sx.Update();
					sy.Update();
					DrawRectangle(sider.X + sider.W - SliderWidth, sider.Y + sider.H - SliderWidth, SliderWidth, SliderWidth, ColorF(DARKGRAY));
				} else {
					if (draw_fun) draw_fun();
					sx.SetBlank(0);
					sy.SetBlank(0);
					sx.SetSum(sider.W);
					sy.SetSum(sider.H);
					sx.SetControl(sider.X, sider.Y, sider.W, sider.H);
					sy.SetControl(sider.X, sider.Y, sider.W, sider.H);
				}
				// 结束
				EndScissor();
				EndAlphaMode();
				return maxh;
			}
		};
		Page* this_page = nullptr;
		class Page : public Element {
		private:
			int Height = 0;						// 控件高度
			bool swapping = false;				// 是否正在执行交换动画
			SliderBar sbar;						// 滚动条
			Animation appearAni;				// 淡入动画
			std::function <void()> callback;	// 回调函数
			bool enable_bias_animation = true;	// 是否启用偏移动画
			int max_width = 500;				// 最大宽度
			int unit_interval = ui::SpaceSize;	// 控件间距
			int interval = SpaceSize * 4;		// 控件与界面左右间隔
			realn blank = 0;					// 滚动条空白
			Animation shiftAni;					// 界面切换动画
			int keyid = 0;						// 当前页面
			SiderPosition shiftpos = spos_right;// 页面推出位置
			realn GetAniBias(int id) {
				if (!enable_bias_animation) return 0;
				return (1 - appearAni.GetPos(gclock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id >= 0)return appearAni.GetPos(gclock() - id * 50);
				else return appearAni.GetPos((gclock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}

		public:
			bool visible = true;				// 是否可见
			bool insert_ani = false;			// 是否启用插入动画
			bool appear_ani = true;				// 是否启用淡入动画
			bool sbar_visible = true;			// 是否启用滚动条
			Position pos = pos_full;			// 控件位置
			Page() {
				content = "Page";
				extra = true;
			}
			Page& SetBiasAnimation(bool on) {
				enable_bias_animation = on;
				return *this;
			}
			Page& SetMaxWidth(int w) {
				max_width = w;
				return *this;
			}
			Page& SetPosition(Position pos_) {
				pos = pos_;
				return *this;
			}
			Page& SetInterval(int itv) {
				interval = itv;
				return *this;
			}
			Page& SetUnitInterval(int itv) {
				unit_interval = itv;
				return *this;
			}
			Page& SetBlank(int blk) {
				blank = blk;
				return *this;
			}
			Page& withCallback(std::function<void()> callback_) {
				callback = callback_;
				return *this;
			}
			int GetX() {
				return sider.X + GetAniBias(2) / 2;
			}
			int GetY() {
				return sider.Y + GetAniBias(2) / 2;
			}
			int GetW() {
				return sider.W - GetAniBias(2);
			}
			int GetH() {
				return sider.H - GetAniBias(2);
			}
			Page& ShiftTo(Element* ele, SiderPosition pos = spos_right) {
				shiftpos = pos;
				if (keyid >= key.size()) keyid = key.size() - 1;
				if (keyid >= 0 && ele == key[keyid]) return *this;
				while (Size() > keyid + 1) Erase(keyid + 1);
				Add(ele);
				keyid++;
				shiftAni.ssp(0).stp(1).sms(anif::classics).sd(400);
				return *this;
			}
			Page& ShiftBack() {
				if (keyid <= 0) {
					keyid = 0;
					return *this;
				}
				keyid--;
				shiftAni.ssp(1).stp(0).sms(anif::classics).sd(400);
				return *this;
			}
			int Draw(int x, int y, int w = 600, int h = 600, bool check = true) {
				this_page = this;
				// 界面不可见，直接退出
				if (!visible) return 0;
				// 界面可见，检查是否启动淡入动画
				appearAni.update();
				if (restart_animation) {
					appearAni.ssp(0), restart_animation = false;
				}
				appearAni.stp(1);
				// 初始化
				swapping = false;
				X = x, Y = y, W = w, H = h;
				BeginScissor(x, y, w, h);
				// 计算控件总高度
				Height = 0;
				for (int i = 0; i < key.size(); i++) if (!key[i]->extra) Height += key[i]->height + unit_interval;
				// 绘制侧边栏
				BeginAlphaMode(GetAniAlpha(0));
				sider.Draw(x, y, w, h, check);
				// 绘制控件
				bool flag = false;
				for (int i = 0; i < key.size(); i++) if (key[i]->extra) flag = true;
				// 绘制空页面
				if (Size() == 0) ui::PrintMiddle(sider.X, sider.Y, sider.W, sider.H, "EMPTY PAGE");
				// 绘制扩展控件
				if (flag) {
					shiftAni.update();
					int b = GetAniBias(0);
					if (shiftAni.is_run()) {
						int keyid2 = keyid;
						if (shiftAni.gtp() == 0) keyid2++;
						int dx, dy, sx, sy;
						if (shiftpos == spos_left)   sx = -sider.W * 0.3, sy = 0, dx = sider.W * 0.3 * shiftAni.gnp(), dy = 0;
						if (shiftpos == spos_right)  sx = sider.W * 0.3, sy = 0, dx = -sider.W * 0.3 * shiftAni.gnp(), dy = 0;
						if (shiftpos == spos_top)    sy = -sider.H * 0.3, sx = 0, dy = sider.H * 0.3 * shiftAni.gnp(), dx = 0;
						if (shiftpos == spos_bottom) sy = sider.H * 0.3, sx = 0, dy = -sider.H * 0.3 * shiftAni.gnp(), dx = 0;
						if (!key.empty() && key[keyid2]) {
							BeginAlphaMode(shiftAni.gnp());
							key[keyid2]->Draw_Auto_Extra(sider.X + b + dx + sx, sider.Y + b + dy + sy, sider.W - b * 2, sider.H - b * 2, check);
							EndAlphaMode();
						}
						if (key.size() >= 2 && key[keyid2 - 1]) {
							BeginAlphaMode(1 - shiftAni.gnp());
							key[keyid2 - 1]->Draw_Auto_Extra(sider.X + b + dx, sider.Y + b + dy, sider.W - b * 2, sider.H - b * 2, check);
							EndAlphaMode();
						}
					} else {
						if (!key.empty() && key[keyid]) {
							key[keyid]->Draw_Auto_Extra(sider.X + b, sider.Y + b, sider.W - b * 2, sider.H - b * 2, check);
						}
					}
				}
				EndAlphaMode();
				// 绘制普通控件
				if (!flag) {
					BeginScissor(sider.X, sider.Y, sider.W, sider.H);
					if (DebugMode) {
						DrawRectangleLines(sider.X, sider.Y, sider.W, sider.H, RED);
						DrawRectangleLines(sider.X + interval, sider.Y, sider.W - interval * 2 - SliderWidth, sider.H, ORANGE);
					}
					realn nowh = -sbar.Now();
					for (int i = 0; i < key.size(); i++) {
						if (!key[i]->extra) {
							bool next_check = (check && !swapping && MouseInRect(sider.X, sider.Y, sider.W - SliderWidth, sider.H));
							int w2 = std::min(max_width, sider.W - interval * 2 - SliderWidth);
							BeginAlphaMode(GetAniAlpha(i));
							if (pos == pos_full)		nowh += key[i]->Draw_Auto(sider.X + interval, sider.Y + interval + nowh + GetAniBias(i), sider.W - interval * 2 - SliderWidth, next_check);
							else if (pos == pos_left)	nowh += key[i]->Draw_Auto(sider.X + interval, sider.Y + interval + nowh + GetAniBias(i), w2, next_check);
							else if (pos == pos_right)	nowh += key[i]->Draw_Auto(sider.X + sider.W - interval - w2 - SliderWidth, sider.Y + interval + nowh + GetAniBias(i), w2, next_check);
							else if (pos == pos_mid)	nowh += key[i]->Draw_Auto(sider.X + sider.W / 2 - w2 / 2 - SliderWidth / 2, sider.Y + interval + nowh + GetAniBias(i), w2, next_check);
							nowh += unit_interval;
							EndAlphaMode();
						}
					}
				}
				// 回调函数
				if (callback) {
					BeginAlphaMode(GetAniAlpha(0));
					callback();
					EndAlphaMode();
				}
				EndScissor();
				// 绘制滚动条
				BeginAlphaMode(GetAniAlpha(-2));
				sbar.SetControl(sider.X, sider.Y, sider.W, sider.H);
				sbar.SetSum(Height + interval * 2 + SpaceSize);
				sbar.SetBlank(blank);
				sbar.Draw_Auto_Extra(sider.X + sider.W - ui::SpaceSize * 3, sider.Y, ui::SpaceSize * 3, sider.H, check);
				sbar.Update();
				EndAlphaMode();
				// 结束
				EndScissor();
				return Height;
			}
		};
		class MultiTab : public Element {
		private:
			std::vector<std::string> ttext;		// 标签名称
			std::vector<std::string> icon;		// 标签图标
			std::vector<Element*> ele;			// 标签页指向的控件
			std::vector<int> width;				// 标签宽度
			std::vector<ReleaseFunc> tabrlf;	// 释放函数
			std::function <void()> callback;	// 回调函数
			Animation tabAni;					// 当前标签标记移动动画
			Animation widthAni;					// 当前标签标记宽度动画
			Animation moveAni;					// 标签绘制起始点动画
			Animation appearAni;				// 淡入动画
			bool move_enable = false;			// 是否可以左右移动
			int tab = 0;						// 当前标签页

			bool DrawLeft(int _x, int _y, int _w, int _h, bool check = true) {
				float x = _x, y = _y, w = _w, h = _h;
				DrawRectangle(_x, _y, _w, _h, ColorF(255, 255, 255, 150));
				DrawLineEx(Vector2{x + w * 0.3f, y + h * 0.5f}, Vector2{x + w * 0.7f, y + h * 0.3f}, dpi, ColorF(BLACK));
				DrawLineEx(Vector2{x + w * 0.3f, y + h * 0.5f}, Vector2{x + w * 0.7f, y + h * 0.7f}, dpi, ColorF(BLACK));
				if (MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ColorF(255, 255, 255, 150));
					if (check && IsMouseInput(MOUSE_BUTTON_LEFT))return true;
				}
				return false;
			}
			bool DrawRight(int x, int y, int w, int h, bool check = true) {
				DrawRectangle(x, y, w, h, ColorF(255, 255, 255, 150));
				DrawLineEx(Vector2{x + w * 0.7f, y + h * 0.5f}, Vector2{x + w * 0.3f, y + h * 0.3f}, dpi, ColorF(BLACK));
				DrawLineEx(Vector2{x + w * 0.7f, y + h * 0.5f}, Vector2{x + w * 0.3f, y + h * 0.7f}, dpi, ColorF(BLACK));
				if (MouseInRect(x, y, w, h)) {
					DrawRectangle(x, y, w, h, ColorF(255, 255, 255, 150));
					if (check && IsMouseInput(MOUSE_BUTTON_LEFT))return true;
				}
				return false;
			}
			realn GetAniBias(int id) {
				return (1 - appearAni.GetPos(gclock() - id * 50)) * 100 * dpi;
			}
			realn GetAniAlpha(int id) {
				if (id > 0)return appearAni.GetPos(gclock() - id * 50);
				else return appearAni.GetPos((gclock() - appearAni.gst()) / 2 + appearAni.gst() + id * 50);
			}
			int DrawOne(int id, int x, int y, int w, int h, bool check = true) {
				int t = (UnitHeight * 1.5 - TextHeight) / 2;
				PrintIcon(x + SpaceSize * 2, y + t, icon[id], WHITE);
				if (icon[id] == "")Print(x + SpaceSize * 2 + wp::strLen(icon[id]) * TextHeight / 2, y + t, ttext[id], WHITE);
				else Print(x + SpaceSize * 3 + wp::strLen(icon[id])*TextHeight / 2, y + t, ttext[id], WHITE);
				Color color = GRAY;
				if (tab == id) {
					tabAni.stp(x + int(moveAni.gnp()) - X);
					if (tabAni.gnp() - tabAni.gtp() > W * 1.2)tabAni.ssp(tabAni.gtp() + W);
					if (tabAni.gnp() - tabAni.gtp() < -W * 1.2)tabAni.ssp(tabAni.gtp() - W);
					widthAni.stp(w);
				}
				if (MouseInRect(x, y + SpaceSize / 2, w, h - SpaceSize)) {
					if (!move_enable || !(Mouse.x <= X + UnitHeight * 0.8 || Mouse.x >= X + W - UnitHeight * 0.8)) {
						if (!tabAni.is_run() || moveAni.is_run())DrawRectangle(x, y, w, h, ColorF(ChooseColor));
						if (close_enable && MouseInCircle(x + w - SpaceSize * 2 - TextHeight / 2, y + t + TextHeight / 2, TextHeight / 2)) {
							color = WHITE;
							if (check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
								EraseTab(id);
								return 0;
							}
						} else if (check && IsMousePressed(MOUSE_BUTTON_LEFT) && check)SetTab(id);
					}
				}
				if (close_enable) {
					DrawLineEx(
					    Vector2{x + w - SpaceSize * 2 - TextHeight * 0.25f, y + t + TextHeight * 0.25f},
					    Vector2{x + w - SpaceSize * 2 - TextHeight * 0.75f, y + t + TextHeight * 0.75f},
					    dpi * 2, ColorF(color)
					);
					DrawLineEx(
					    Vector2{x + w - SpaceSize * 2 - TextHeight * 0.75f, y + t + TextHeight * 0.25f},
					    Vector2{x + w - SpaceSize * 2 - TextHeight * 0.25f, y + t + TextHeight * 0.75f},
					    dpi * 2, ColorF(color)
					);
				}
				return 0;
			}

		public:
			SiderPosition position = spos_top;	// 标签栏的位置
			SiderPosition fposition = spos_top;	// 标签栏选择标记的位置
			bool close_enable = false;			// 是否允许关闭标签页

			MultiTab() {
				tabAni.sd(400);
				widthAni.sd(200);
				moveAni.sd(250);
				tabAni.sms(anif::bounce);
				extra = true;
			}
			~MultiTab() {
				for (int i = 0; i < tabrlf.size(); i++) {
					if (tabrlf[i])tabrlf[i](ele[i]);
				}
			}
			inline int TabSize() {
				return ttext.size();
			}
			MultiTab& AddTab(std::string text_, Element* ele_ = nullptr, ReleaseFunc fun_ = nullptr) {
				icon.push_back("");
				ttext.push_back(text_);
				ele.push_back(ele_);
				tabrlf.push_back(fun_);
				return *this;
			}
			MultiTab& AddTab(std::string icon_, std::string text_, Element* ele_ = nullptr, ReleaseFunc fun_ = nullptr) {
				icon.push_back(icon_);
				ttext.push_back(text_);
				ele.push_back(ele_);
				tabrlf.push_back(fun_);
				return *this;
			}
			MultiTab& EraseTab(int id) {
				if (tabrlf[id])tabrlf[id](ele[id]);
				ttext.erase(ttext.begin() + id);
				icon.erase(icon.begin() + id);
				ele.erase(ele.begin() + id);
				tabrlf.erase(tabrlf.begin() + id);
				return *this;
			}
			MultiTab& EraseTab(Element* ele_) {
				for (int i = 0; i < content.size(); i++)
					if (ele[i] == ele_) {
						if (tabrlf[i])tabrlf[i](ele[i]);
						ttext.erase(ttext.begin() + i);
						icon.erase(icon.begin() + i);
						ele.erase(ele.begin() + i);
						tabrlf.erase(tabrlf.begin() + i);
					}
				return *this;
			}
			MultiTab& InsertTab(int id, std::string text_, Element* ele_ = nullptr, ReleaseFunc fun_ = nullptr) {
				if (id <= tab)tab++;
				icon.insert(icon.begin() + id, "");
				ttext.insert(ttext.begin() + id, text_);
				ele.insert(ele.begin() + id, ele_);
				tabrlf.insert(tabrlf.begin() + id, fun_);
				return *this;
			}
			MultiTab& InsertTab(int id, std::string icon_, std::string text_, Element* ele_ = nullptr, ReleaseFunc fun_ = nullptr) {
				if (id <= tab)tab++;
				icon.insert(icon.begin() + id, icon_);
				ttext.insert(ttext.begin() + id, text_);
				tabrlf.insert(tabrlf.begin() + id, fun_);
				return *this;
			}
			bool FindTabText(std::string text_) {
				for (int i = 0; i < ttext.size(); i++)if (ttext[i] == text_)return true;
				return false;
			}
			bool FindTabIcon(std::string icon_) {
				for (int i = 0; i < icon.size(); i++)if (icon[i] == icon_)return true;
				return false;
			}
			bool FindTabElement(Element* ele_) {
				for (int i = 0; i < ele.size(); i++)if (ele[i] == ele_)return true;
				return false;
			}
			int Tab() {
				return tab;
			}
			Element* GetTab(int id = -1) {
				if (id == -1)return ele[tab];
				else return ele[id];
			}
			MultiTab& SetTab(int id) {
				tab = id;
				int w = 0;
				width.resize(id + 1);
				for (int i = 0; i <= id; i++) {
					width[i] = (wp::strLen(ttext[i]) + wp::strLen(icon[i])) * TextHeight / 2 + SpaceSize * 4;
					if (icon[i] != "")width[i] += ui::SpaceSize;
					if (close_enable)width[i] += ui::TextHeight + ui::SpaceSize;
					w += width[i];
				}
				if (w - width[id] < moveAni.gnp())moveAni.stp(w - width[id]);
				if (w > moveAni.gnp() + W)moveAni.stp(w - W);

				return *this;
			}
			MultiTab& withCallback(std::function<void()> callback_) {
				callback = callback_;
				return *this;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {
				// 界面可见，检查是否启动淡入动画
				appearAni.update();
				if (GetTick() - update_tick > 10)appearAni.ssp(0);
				appearAni.stp(1);
				update_tick = GetTick();
				x += GetAniBias(2) / 2;
				y += GetAniBias(2) / 2;
				w -= GetAniBias(2);
				h -= GetAniBias(2);
				X = x, Y = y, W = w, H = h;
				BeginAlphaMode(GetAniAlpha(-2));
				// 绘制侧边栏
				sider.Draw(x, y, w, h, check);
				x = sider.X, y = sider.Y, w = sider.W, h = sider.H;
				// 绘制选择标签的标记
				moveAni.update();
				tabAni.update();
				widthAni.update();
				width.resize(ttext.size());
				if (position == spos_top) {
					DrawRectangle(x, y, w, UnitHeight * 1.5, ColorF(MenuColor));
					if (TabSize() > 0) {
						DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y, widthAni.gnp(), UnitHeight * 1.5, ColorF(ChooseColor));
						if (fposition == spos_top)DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y, widthAni.gnp(), dpi * 3, ColorF(ThemeColor));
						if (fposition == spos_bottom)DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y + UnitHeight * 1.5 - 3 * dpi, widthAni.gnp(), dpi * 3, ColorF(ThemeColor));
					}
				}
				if (position == spos_bottom) {
					DrawRectangle(x, y + h - UnitHeight * 1.5, w, UnitHeight * 1.5, ColorF(MenuColor));
					if (TabSize() > 0) {
						DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y + h - UnitHeight * 1.5, widthAni.gnp(), UnitHeight * 1.5, ColorF(ChooseColor));
						if (fposition == spos_top)DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y + h - dpi * 3, widthAni.gnp(), dpi * 3, ColorF(ThemeColor));
						if (fposition == spos_bottom)DrawRectangle(X + tabAni.gnp() - moveAni.gnp(), y + h - UnitHeight * 1.5, widthAni.gnp(), dpi * 3, ColorF(ThemeColor));
					}
				}
				// 绘制标签
				int w2 = dpi;
				for (int i = 0; i < ttext.size(); i++) {
					width[i] = (wp::strLen(ttext[i]) + wp::strLen(icon[i])) * TextHeight / 2 + SpaceSize * 4;
					if (icon[i] != "")width[i] += ui::SpaceSize;
					if (close_enable)width[i] += ui::TextHeight + ui::SpaceSize;
					if (position == spos_top)DrawOne(i, x + w2 - moveAni.gnp(), y, width[i], UnitHeight * 1.5, check);
					if (position == spos_bottom)DrawOne(i, x + w2 - moveAni.gnp(), y + h - UnitHeight * 1.5, width[i], UnitHeight * 1.5, check);
					w2 += width[i] + dpi;
				}
				if (tab < 0)tab = 0;
				if (tab >= TabSize())tab = TabSize() - 1;
				moveAni.update();
				// 绘制左右移动按钮
				if (w2 > w) {
					move_enable = true;
					if (position == spos_top) {
						if (MouseInRect(x, y, w, UnitHeight * 1.5)) {
							if (DrawLeft(x, y, UnitHeight * 0.8, UnitHeight * 1.5, check))moveAni.stp(moveAni.gtp() - w / 2);
							if (DrawRight(x + w - UnitHeight * 0.8, y, UnitHeight * 0.8, UnitHeight * 1.5, check))moveAni.stp(moveAni.gtp() + w / 2);
							moveAni.update();
							moveAni.stp(moveAni.gtp() - GetMouseWheelMove() * 70 * dpi);
						}
					}
					if (position == spos_bottom) {
						if (MouseInRect(x, y + h - UnitHeight * 1.5, w, UnitHeight * 1.5)) {
							if (DrawLeft(x, y + h - UnitHeight * 1.5, UnitHeight * 0.8, UnitHeight * 1.5, check))moveAni.stp(moveAni.gtp() - w / 2);
							if (DrawRight(x + w - UnitHeight * 0.8, y + h - UnitHeight * 1.5, UnitHeight * 0.8, UnitHeight * 1.5, check))moveAni.stp(moveAni.gtp() + w / 2);
							moveAni.update();
							moveAni.stp(moveAni.gtp() - GetMouseWheelMove() * 70 * dpi);
						}
					}
				} else move_enable = false;
				moveAni.update();
				if (moveAni.gtp() < 0)moveAni.stp(0);
				if (w2 - moveAni.gtp() < w)moveAni.stp(std::max(0, w2 - w));
				// 绘制页面
				if (TabSize() > 0) {
					if (ele[tab]) {
						if (position == spos_top)ele[tab]->Draw_Auto_Extra(x, y + UnitHeight * 1.5, w, h - UnitHeight * 1.5, check);
						if (position == spos_bottom)ele[tab]->Draw_Auto_Extra(x, y, w, h - UnitHeight * 1.5, check);
					}
				}
				// 回调函数
				if (callback) callback();
				// 结束
				EndAlphaMode();
				return UnitHeight * 1.5;
			}
			int Draw(int x, int y, int w, bool check = true) {
				Draw(x, y, w, ele[tab]->height, check);
				return 100;
			}
		};
		Window* this_win;
		class Window : public Priority {
		private:
			bool rx = false, ry = false, rw = false, rh = false;// 各条边框是否正在被拖动
			Vector2 move_start, pos_start;						// 鼠标拖动相关参数
			Animation xani, yani, wani, hani, darkani;			// 动画
			int rel_x, rel_y;									// 位置
			bool open = true;									// 是否打开窗口
			std::function<void()> callback;						// 绘制回调函数
			Animation shiftAni;									// 界面切换动画
			int keyid = 0;										// 当前页面
			SiderPosition shiftpos = spos_right;				// 页面推出位置

		public:
			std::string title = "Window";						// 窗口名称
			std::string icon = u8"";							// 窗口图标
			bool moving = false;								// 是否正在移动
			bool draw_title = true;								// 是否绘制标题
			bool draw_body = true;								// 是否绘制主体
			bool draw_dark = false;								// 是否绘制深色背景
			bool draw_shadow = false;							// 是否绘制阴影
			bool close_enable = true;							// 是否可关闭
			int title_height = 25 * dpi;						// 标题高度

			Window(std::string title_ = "Window", ReleaseFunc fun = nullptr) {
				title = title_;
				extra = true;
				SetReleaseFunc(fun);
				xani.ssp(WindowPos.x), yani.ssp(WindowPos.y);
				pop = true;
				content = "Window";
			}
			Window& Set(Element* ele) {
				ClearKey();
				Add(ele);
				return *this;
			}
			Window& ShiftTo(Element* ele, SiderPosition pos = spos_right) {
				if (!ele) ui::message::Send_Error("[CRASH #002]", 500000);
				shiftpos = pos;
				if (keyid >= key.size()) keyid = key.size() - 1;
				while (Size() > keyid + 1) Erase(keyid + 1);
				if (keyid >= 0 && ele == key[keyid]) return *this;
				Add(ele);
				keyid++;
				shiftAni.ssp(0).stp(1).sms(anif::classics_d).sd(400);
				return *this;
			}
			Window& ShiftBack() {
				if (keyid <= 0) {
					keyid = 0;
					return *this;
				}
				keyid--;
				shiftAni.ssp(1).stp(0).sms(anif::classics_d).sd(400);
				return *this;
			}
			Window& Pop(int tx, int ty, int tw, int th, int fx = INT_MAX, int fy = INT_MAX, int fw = INT_MAX, int fh = INT_MAX) {
				if (fx == INT_MAX)fx = tx + tw / 4;
				if (fy == INT_MAX)fy = winH * 1.2;
				if (fw == INT_MAX)fw = tw / 2;
				if (fh == INT_MAX)fh = th;
				xani.ssp(fx + WindowPos.x), xani.stp(tx + WindowPos.x), xani.sd(300);
				yani.ssp(fy + WindowPos.y), yani.stp(ty + WindowPos.y), yani.sd(300);
				wani.ssp(fw), wani.stp(tw), wani.sd(300);
				hani.ssp(fh), hani.stp(th), hani.sd(300);
				priority = ++TopPriority;
				pop = true;
				open = true;
				darkani.stp(0.7);
				return *this;
			}
			Window& Pop() {
				if (!pop) priority = ++TopPriority;
				pop = true, open = true;
				darkani.stp(0.7);
				return *this;
			}
			Window& PopFromMid() {
				xani.Goto(winW / 2 + WindowPos.x);
				yani.Goto(winH / 2 + WindowPos.y);
				wani.ssp(0);
				hani.ssp(0);
				if (!pop) priority = ++TopPriority;
				pop = true, open = true;
				darkani.stp(0.7);
				return *this;
			}
			Window& Close() {
				if (open == false) return *this;
				yani.stp(winH * 1.2 + WindowPos.y);
				hani.stp(H);
				open = false;
				darkani.stp(0);
				return *this;
			}
			Window& Hide() {
				yani.ssp(winH * 1.2 + WindowPos.y);
				hani.ssp(H);
				pop = false;
				darkani.ssp(0);
				darkani.stp(0);
				return *this;
			}
			Window& SetPos(int x, int y, int w, int h) {
				if (!open) return *this;
				if (w < 100 * dpi) w = 100 * dpi;
				if (h < title_height) h = title_height;
				if (w > winW) w = winW;
				if (h > winH) h = winH;
				if (y < 0)y = 0;
				if (x < 0)x = 0;
				if (x + w > winW) x = winW - w;
				if (y + h > winH) y = winH - h;
				rel_x = x, rel_y = y;
				xani.stp(x + WindowPos.x), yani.stp(y + WindowPos.y), wani.stp(w), hani.stp(h);
				return *this;
			}
			Window &SetSize(int w, int h) {
				if (!open) return *this;
				if (w < 100 * dpi) w = 100 * dpi;
				if (h < title_height) h = title_height;
				if (w > winW) w = winW;
				if (h > winH) h = winH;
				wani.stp(w), hani.stp(h);
				return *this;
			}
			Window& GotoMid() {
				if (!open) return *this;
				rel_x = (winW - wani.gtp()) / 2;
				rel_y = (winH - hani.gtp()) / 2;
				xani.stp(rel_x + WindowPos.x);
				yani.stp(rel_y + WindowPos.y);
				return *this;
			}
			Window& withCallback(std::function<void()> callback_) {
				callback = callback_;
				return *this;
			}
			int GetSizeW() {
				return sider.W;
			}
			int GetSizeH() {
				return sider.H;
			}
			int GetX() {
				return sider.X;
			}
			int GetY() {
				return sider.Y;
			}
			bool IsOpen() {
				return !wani.is_run() && !yani.is_run() && !xani.is_run() && open;
			}
			int Draw(int x, int y, int w, int h, bool check = true) {

				this_win = this;
				// 更新动画
				if (!pop) return 0;
				if (open) {
					if (WindowState == state_moving) {
						xani.gt(rel_x + WindowPos.x);
						yani.gt(rel_y + WindowPos.y);
					}
				} else {
					if (!yani.is_run()) pop = false;
				}
				xani.update(), yani.update(), wani.update(), hani.update();
				darkani.update();
				rel_x = x = xani.gnp() - WindowPos.x;
				rel_y = y = yani.gnp() - WindowPos.y;
				w = wani.gnp();
				h = hani.gnp();

				// 绘制背景
				if (draw_dark && !is_mainwin) {
					DrawRectangle(0, 0, winW, winH, Fade(BLACK, darkani.gnp()));
				}

				// 绘制主体
				if (!is_mainwin) BeginAlphaMode(darkani.gnp() / 0.7);
				if (draw_body) {
					if (draw_shadow) {
						special_effect::DrawShadowRectangle(x, y, w, h, 15 * dpi);
					}
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
						int tw = TextHeight + SpaceSize * 2 + wp::strLen(title) * TextHeight / 2;
						PrintIcon(x + (w - tw) / 2, y + t, icon, TextColor2);
						Print(x + (w - tw) / 2 + TextHeight + SpaceSize * 2, y + t, title, TextColor2);
						// 绘制关闭按钮
						if (close_enable) {
							if (MouseInRect(x + w - title_height, y, title_height, title_height)) {
								DrawRectangle(x + w - title_height, y, title_height, title_height, RED);
								if (check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
									Close();
								}
							}
							DrawLineEx(
							    Vector2{x + w - title_height * 0.3f, y + title_height * 0.3f},
							    Vector2{x + w - title_height * 0.7f, y + title_height * 0.7f},
							    dpi, ColorF(TextColor2)
							);
							DrawLineEx(
							    Vector2{x + w - title_height * 0.7f, y + title_height * 0.3f},
							    Vector2{x + w - title_height * 0.3f, y + title_height * 0.7f},
							    dpi, ColorF(TextColor2)
							);
						}
					}
					if (priority == WindowTopPriority) {
						if (draw_title) {
							if ( MouseInRect(x, y, w, title_height) && !rx && !ry && !rw && !rh) {
								if (IsMousePressed(MOUSE_BUTTON_LEFT))moving = true, move_start = Mouse, pos_start = {x * 1.0f, y * 1.0f};
							}
						}
						if (!IsMouseDown(MOUSE_BUTTON_LEFT))moving = false;
						if (moving && pop) {
							x = Mouse.x - move_start.x + pos_start.x;
							y = Mouse.y - move_start.y + pos_start.y;
							xani.stp(x + WindowPos.x);
							yani.stp(y + WindowPos.y);
						}
					}
					if (draw_title) {
						y += title_height;
						h -= title_height;
					}
				}

				// 绘制侧边栏
				if (!is_mainwin) BeginScissor(x, y, w, h);
				sider.Draw(x, y, w, h, check);
				int tx = x, ty = y, tw = w, th = h;

				// 绘制空页面
				if (Size() == 0) ui::PrintMiddle(sider.X, sider.Y, sider.W, sider.H, "EMPTY WINDOW");

				// 绘制界面
				shiftAni.update();
				if (shiftAni.is_run()) {
					int keyid2 = keyid;
					if (shiftAni.gtp() == 0) keyid2++;
					int dx, dy, sx, sy;
					if (shiftpos == spos_left)   sx = -sider.W * 0.3, sy = 0, dx = sider.W * 0.3 * shiftAni.gnp(), dy = 0;
					if (shiftpos == spos_right)  sx = sider.W * 0.3, sy = 0, dx = -sider.W * 0.3 * shiftAni.gnp(), dy = 0;
					if (shiftpos == spos_top)    sy = -sider.H * 0.3, sx = 0, dy = sider.H * 0.3 * shiftAni.gnp(), dx = 0;
					if (shiftpos == spos_bottom) sy = sider.H * 0.3, sx = 0, dy = -sider.H * 0.3 * shiftAni.gnp(), dx = 0;
					if (!key.empty() && key[keyid2]) {
						BeginAlphaMode(shiftAni.gnp());
						key[keyid2]->Draw_Auto_Extra(
						    sider.X + sx + dx, sider.Y + sy + dy, sider.W, sider.H,
						    check && (!(rx || ry || rw || rh) | !IsMouseDown(MOUSE_BUTTON_LEFT))
						);
						EndAlphaMode();
					}
					if (key.size() >= 2 && key[keyid2 - 1]) {
						BeginAlphaMode(1 - shiftAni.gnp());
						key[keyid2 - 1]->Draw_Auto_Extra(
						    sider.X + dx, sider.Y + dy, sider.W, sider.H,
						    check && (!(rx || ry || rw || rh) | !IsMouseDown(MOUSE_BUTTON_LEFT))
						);
						EndAlphaMode();
					}
				} else {
					if (!key.empty() && key[keyid]) {
						key[keyid]->Draw_Auto_Extra(
						    sider.X, sider.Y, sider.W, sider.H,
						    check && (!(rx || ry || rw || rh) | !IsMouseDown(MOUSE_BUTTON_LEFT))
						);
					}
				}
				if (!is_mainwin) EndScissor();

				// 绘制标题
				if (draw_title) {
					if (priority == WindowTopPriority || check) {
						if (!IsMouseDown(MOUSE_BUTTON_LEFT) || IsMousePressed(MOUSE_BUTTON_LEFT)) {
							if (!is_mainwin) {
								bool cx = false, cy = false, cw = false, ch = false;
								int k = 5 * dpi;
								if ( Mouse.y >= y - k && Mouse.y <= y + h + k) {
									if ( Mouse.x >= x - k && Mouse.x < x)cx = true;
									if ( Mouse.x > x + w && Mouse.x <= x + w + k)cw = true;
								}
								if ( Mouse.x >= x - k && Mouse.x <= x + w + k) {
									if ( Mouse.y >= y - k && Mouse.y < y)cy = true;
									if ( Mouse.y > y + h && Mouse.y <= y + h + k)ch = true;
								}
								if ((cx && cy) || (cw && ch)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NWSE;
								else if ((cx && ch) || (cy && cw)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NESW;
								else if (cx || cw) MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								else if (cy || ch) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
								rx = cx, ry = cy, rw = cw, rh = ch;
							}
						}
						if (IsMouseDown(MOUSE_BUTTON_LEFT)) {
							if (!is_mainwin) {
								int tx = Mouse.x, ty = Mouse.y;
								if (tx < 0)tx = 0;
								if (ty < 0)ty = 0;
								if (tx > winW)tx = winW;
								if (ty > winH)ty = winH;
								if (rx)w = x + w - tx, x = tx, printf("rx");
								if (ry)h = y + h - ty, y = ty, printf("ry");
								if (rw)w = tx - x, printf("rw");
								if (rh)h = ty - y, printf("rh");
//								xani.stp(x + WindowPos.x),yani.stp(y + WindowPos.y),wani.stp(w),hani.stp(h + title_height);
								if ((rx && ry) || (rw && rh)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NWSE;
								else if ((rx && rh) || (ry && rw)) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NESW;
								else if (rx || rw) MouseCursorStyle = MOUSE_CURSOR_RESIZE_EW;
								else if (ry || rh) MouseCursorStyle = MOUSE_CURSOR_RESIZE_NS;
							}
						}
					}
				}

				// 自定义绘制函数
				if (callback) callback();

				// 边界检查
				if (wani.gtp() < 100 * dpi) wani.stp(100 * ui::dpi);
				if (hani.gtp() < title_height) hani.stp(title_height);
				if (wani.gtp() > winW) wani.stp(winW);
				if (hani.gtp() > winH) hani.stp(winH);
//				if (!IsMouseDown(MOUSE_BUTTON_LEFT)) {
//					if (Y < 0)Y = 0;
//					if (X < 0)X = 0;
//					if (X + W > winW)X = winW - W;
//					if (Y + H > winH)Y = winH - H;
//				}

				// 更新动画
				// if (pop) {
				// 	xani.stp(X + WindowPos.x);
				// 	yani.stp(Y + WindowPos.y);
				// 	wani.stp(W);
				// 	hani.stp(H);
				// }

				// 结束
				if (!is_mainwin) EndAlphaMode();
				return 0;
			}
		} mainwin;

		System::~System() {
			for (int i = 0; i < win.size(); i++) {
				if (win[i].second)win[i].second(win[i].first);
			}
			TraceLog(LOG_INFO, "__________________________________");
			TraceLog(LOG_INFO, "GGCCUI: UI system has been shut down.");
			TraceLog(LOG_INFO, "__________________________________");
		}
		bool System::CMP_Window(std::pair<Priority*, ReleaseFunc> w1, std::pair<Priority*, ReleaseFunc> w2) {
			return w1.first->priority > w2.first->priority;
		}
		void System::Update() {
			sort(win.begin(), win.end(), CMP_Window);
			TopPriority = win[0].first->priority;
			bool c[1005], flag = false;
			int k = 5 * dpi;
			for (int i = 0; i < win.size(); i++) {
				if (win[i].first->deleted && !win[i].first->pop) Erase(win[i].first), TraceLog(LOG_INFO, "GGCCUI: OP: Deleted finished\n");
			}
			for (int i = 0; i < win.size(); i++) {
				if ( MouseInRect(win[i].first->X - k, win[i].first->Y - k, win[i].first->W + k * 2, win[i].first->H + k * 2)) {
					if (IsMousePressed(MOUSE_BUTTON_LEFT) && win[i].first->pop && (!win[i].first->is_mainwin || !flag)) {
						if (win[i].first->priority != TopPriority)win[i].first->priority = ++TopPriority;
						break;
					}
				}
				if (win[i].first->pop)flag = true;
				win[i].second = win[i].first->rlf;
			}
			sort(win.begin(), win.end(), CMP_Window);
			for (int i = 0; i < win.size(); i++) {
				if (win[i].first->prio_flag == "Window" && win[i].first->pop) {
					WindowTopPriority = win[i].first->priority;
					break;
				}
			}
			memset(c, 0, sizeof(c));
			for (int i = 0; i < win.size(); i++) {
				c[i] = false;
				if (!win[i].first->pop)continue;
				if ( (MouseInRect(win[i].first->X - k, win[i].first->Y - k, win[i].first->W + k * 2, win[i].first->H + k * 2) || win[i].first->is_mainwin )
				&& (win[i].first->priority == WindowTopPriority || !win[i].first->is_mainwin)) {
					c[i] = true;
					break;
				}
			}
			for (int i = win.size() - 1; i >= 0; i--) {
				if (win[i].first->pop) win[i].first->Draw_Auto_Extra(0, 0, winW, winH, c[i]);
			}
		}
		void System::Erase(Priority* w) {
			for (int i = 0; i < win.size(); i++)
				if (win[i].first == w) {
					if (win[i].second)win[i].second(win[i].first);
					win.erase(win.begin() + i);
				}
		}

		class LeftMenu : public Element {
		public:
			int n = 5;
			std::string mtext[32];
			std::string icon[32];
			int last_choose = -1;
			int choose = 0;
			bool draw_full = false;
			bool full_alltime = false;
			Page* page[32];
			Window* target = nullptr;
			Animation move;
			bool move_inited = false;
			int choise = -1;
			int choose_time = 0;
			int menu_width = 250;
			LeftMenu() {
				mtext[0] = "Page #1";
				mtext[1] = "Page #2";
				mtext[2] = "Page #3";
				mtext[3] = "Page #4";
				mtext[4] = "Page #5";
				icon[0] = u8"";
				icon[1] = u8"";
				icon[2] = u8"";
				icon[3] = u8"";
				icon[4] = u8"";
				move.sd(300);
			}
			int DrawOne(int id, int x, int y, int w, bool check = true) {
				int t = (2 * UnitHeight - TextHeight) / 2;
				special_effect::DrawMouseRectangle_onlyLight(x, y, w, UnitHeight * 2);
				if (id == -1) {
					PrintIcon(x + SpaceSize * 3, y + t, u8"", WHITE);
					return 0;
				}
				if (id == choose)PrintIcon(x + SpaceSize * 3, y + t, icon[id].c_str(), ThemeColor);
				else PrintIcon(x + SpaceSize * 3, y + t, icon[id].c_str(), WHITE);
				if (draw_full || full_alltime)Print(x + SpaceSize * 6 + TextHeight, y + t, mtext[id], WHITE);
				if (MouseInRect(x, y, w, UnitHeight * 2)) {
					DrawRectangle(x, y, w, UnitHeight * 2, ChooseColor);
					if (check && IsMousePressed(MOUSE_BUTTON_LEFT)) {
						choise = id;
						choose_time = gclock();
					}
				}
				if (choise == id) {
					DrawRectangle(x, y, w, UnitHeight * 2, ChooseColor);
				}
				if (choise != -1 && gclock() - choose_time > 200) {
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
						target->key[0] = page[choose];
//						page[choose]->sbar.Set(0);
						last_choose = choose;
					}
				}
				if (target->W > 700 * dpi)draw_full = true;
				else draw_full = false;
				return move.gnp();
			}
		};

		void SetFullScreen(bool on) {
			static int origin_w = 860, origin_h = 640;
			if (on && !IsWindowState(FLAG_FULLSCREEN_MODE)) {
				int w = GetMonitorWidth(0);
				int h = GetMonitorHeight(0);
				origin_w = winW, origin_h = winH;
				SetWindowSize(w, h);
				SetWindowState(FLAG_FULLSCREEN_MODE);
			}
			if (!on && IsWindowState(FLAG_FULLSCREEN_MODE)) {
				ClearWindowState(FLAG_FULLSCREEN_MODE);
				SetWindowSize(origin_w, origin_h);
			}
		}
		void SetWindowTitle(std::string title) {
			SetWindowTitle(title.c_str());
		}
		int Init(int winw = 960, int winh = 640, std::string title = "Untitled", double zoom = 1) {
			// 窗口
			if (!IsWindowReady()) {
				SetConfigFlags(FLAG_MSAA_4X_HINT);
				SetConfigFlags(FLAG_WINDOW_RESIZABLE);
				if (EnableRaylibLog) SetTraceLogLevel(LOG_ALL);
				else SetTraceLogLevel(LOG_ERROR);
				InitWindow(winw, winh, title.c_str());
				Vector2 v = GetWindowPosition();
				realn k = GetWindowScaleDPI().x;
				winW = winw * k, winH = winh * k;
				if (k != 1.0) {
					SetWindowPosition(v.x - winW * (k - 1) / 2 / k, v.y - winH * (k - 1) / 2 / k);
					SetWindowSize(winW, winH);
				}
			}
			winW = GetScreenWidth();
			winH = GetScreenHeight();
			DPI = GetWindowScaleDPI();
			if (InitFinished) SetWindowSize(winw, winH);
			if (!InitFinished) {
				TextHeight = 16;
				UnitHeight = 20;
				SpaceSize = 5;
				DPI.x *= zoom * Scale;
				TextHeight *= DPI.x;
				UnitHeight *= DPI.x;
				SpaceSize *= DPI.x;
				SliderWidth *= DPI.x;
				dpi = DPI.x;
				InitFinished = true;
				// 虚拟窗口
				mainwin.draw_body = false;
				mainwin.is_mainwin = true;
				// 鼠标动画
				MouseXAni.sd(300);
				MouseYAni.sd(300);
				// 启动动画
				SetTargetFPS(70);
				if (StartAni) {
					int _time = gclock() + 2100;
					Animation logo_ani, cir_ani, a_ani;
					logo_ani.ssp(0);
					logo_ani.sd(500);
					logo_ani.sms(anif::classics_r);
					logo_ani.stp(1, 2100);
					cir_ani.ssp(0);
					cir_ani.sd(500);
					cir_ani.sms(anif::classics_r);
					cir_ani.stp(1, 2000);
					a_ani.ssp(1);
					a_ani.stp(0);
					a_ani.sms(anif::linear);
					a_ani.sd(1000);
					Logo logo;
					while (gclock() - _time < 300 && !WindowShouldClose()) {
						logo_ani.update();
						a_ani.update();
						cir_ani.update();
						winW = GetScreenWidth();
						winH = GetScreenHeight();
						update_gclock();
						int k = std::min(int(winW * 0.1), int(80 * dpi));
						BeginAlphaMode(1 - a_ani.gnp());
						if (gclock() - _time < 0) {
							BeginDrawing();
							ClearBackground(BgColor);
							logo.Draw(winW / 2 - k, winH / 2 - k, k * 2, k * 2);
							special_effect::DrawLoadingCircle(winW / 2, winH * 4 / 5 + cir_ani.gnp() * (winH * 0.5 + winW * 0.1), k / 5);
						} else {
							realn a = (300 - (gclock() - _time)) / 300.0;
							BeginDrawing();
							ClearBackground(BgColor);
							BeginAlphaMode(a);
							logo.Draw(winW / 2 - k, winH / 2 - k + logo_ani.gnp() * (winH * 0.5 + winW * 0.1), k * 2, k * 2);
							special_effect::DrawLoadingCircle(winW / 2, winH * 4 / 5 + cir_ani.gnp() * (winH * 0.5 + winW * 0.1), k / 5);
							EndAlphaMode();
						}
						EndAlphaMode();
						EndDrawing();
						if (WindowShouldClose()) {
							CloseWindow();
							exit(0);
						}
					}
				}
				BeginDrawing();
				ClearBackground(BgColor);
				EndDrawing();
				// 字幕
				TraceLog(LOG_INFO, "__________________________________");
				TraceLog(LOG_INFO, "GGCCUI: UI started successfully!");
				TraceLog(LOG_INFO, (std::string("GGCCUI: UI Version: ") + UIVer).c_str());
				TraceLog(LOG_INFO, "__________________________________");
			}

			return 0;
		}
		void Update() {
			// 更新内容
			special_effect::Draw();
			LastWindowSize = Vector2{1.0f * winW, 1.0f * winH};
			LastWindowPos = WindowPos;
			winW = GetScreenWidth();
			winH = GetScreenHeight();
			Mouse = GetMousePosition();
			WindowPos = GetWindowPosition();
			WindowSize = Vector2{ 1.0f * winW, 1.0f * winH};
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
			update_gclock();
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
				if (key <= 128) GetChar = key;
				else if (key) GetChar = ' ';
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
				int fileSize;
				unsigned char *fontFileData = new unsigned char;
				if (FontName == "仿宋")fontFileData = LoadFileData("C:/windows/fonts/simfang.ttf", &fileSize);
				if (FontName == "宋体")fontFileData = LoadFileData("C:/windows/fonts/SIMSUN.ttf", &fileSize);
				if (FontName == "微软雅黑")fontFileData = LoadFileData("C:/windows/fonts/simhei.ttf", &fileSize);
				if (FontName == "隶书")fontFileData = LoadFileData("C:/windows/fonts/simli.ttf", &fileSize);
				if (FontName == "楷体")fontFileData = LoadFileData("C:/windows/fonts/simkai.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints((UseCharacter.Text()).c_str(), &codepointsCount);
				font = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
				UnloadFileData(fontFileData);
				UnloadCodepoints(codepoints);
			}
			if (UseIcon.Change()) {
				int fileSize;
				unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\segmdl2.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints((UseIcon.Text() + u8"").c_str(), &codepointsCount);
				IconFont = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
				UnloadCodepoints(codepoints);
				UnloadFileData(fontFileData);
			}
			if (UseEmoji.Change()) {
				int fileSize;
				unsigned char *fontFileData = LoadFileData("c:\\windows\\fonts\\seguiemj.ttf", &fileSize);
				int codepointsCount;
				int *codepoints = LoadCodepoints((UseEmoji.Text() + u8"!\"#$%").c_str(), &codepointsCount);
				IconFont = LoadFontFromMemory(".ttf", fontFileData, fileSize, TextHeight, codepoints, codepointsCount);
				UnloadCodepoints(codepoints);
				UnloadFileData(fontFileData);
			}
			UseCharacter.SetMaximum(CharactorLoadMaximum);
			UseCharacter.Update();
			// 绘制
			UseSliderX = false;
			UseSliderY = false;
			MainSystem.Update();
			mainwin.SetPos(0, 0, winW, winH);
			mainwin.priority = 0;
			if (MouseEventLock) MouseCursorStyle = MOUSE_CURSOR_ARROW;
			if (MouseCursorStyle >= 0) {
				ShowCursor();
				SetMouseCursor(MouseCursorStyle);
			} else HideCursor();
			MouseCursorStyle = MOUSE_CURSOR_ARROW;
			// 调试
			if (DebugMode) {
				DrawRectangle(winW / 2 - 100 * dpi, 50 * dpi, 200 * dpi, 40 * dpi, Fade(BLACK, 0.6));
				PrintMiddle(winW / 2 - 100 * dpi, 50 * dpi, 200 * dpi, 40 * dpi, "调试模式: 开启", RED);
			}
		}
		void Run(std::function<void()> script = nullptr) {
			while (1) {
				BeginDrawing();
				ClearBackground(ui::BgColor);
				ui::Update();
				if (script)script();
				if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) MouseEventLock = false;
				message::Draw();
				EndDrawing();
				if (WindowShouldClose()) {
					if (IsKeyPressed(KEY_ESCAPE)) continue;
					else {
						CloseWindow();
						break;
					}
				}
				if (!IsWindowFocused() && DocumentMode) {
					while (1) {
						if (IsWindowFocused()) break;
						WaitTime(0.01);
						PollInputEvents();
					}
				}
			}
			Running = true;
		}

	}

	// 实验功能============================
	namespace create {

		int FatherElementDeep = 1;
		int FatherLayoutDeep = 0;
		ui::Element* FatherElement = nullptr;
		ui::Layout* FatherLayout = nullptr;
		std::stack<ui::Element*> FatherElementStack;
		std::stack<ui::Layout*> FatherLayoutStack;
		void BeginAddElement(ui::Element* ele) {
			if (FatherElementStack.empty() && FatherElementDeep == 1) {
				FatherElementDeep = 0;
				BeginAddElement(&ui::mainwin);
			}
			FatherElementStack.push(ele);
			FatherElement = ele;
			FatherElementDeep++;
		}
		void EndAddElement() {
			if (FatherElementStack.empty() && FatherElementDeep == 1) {
				FatherElementDeep = 0;
				return;
			}
			if (FatherElementDeep > 0) {
				FatherElementDeep--;
				FatherElementStack.pop();
			}
			if (FatherElementDeep == 0) FatherElement = nullptr;
			else FatherElement = FatherElementStack.top();
		}
		ui::Element* GetFatherElement() {
			if (!IsWindowReady()) ui::Init();
			if (FatherElementStack.empty() && FatherElementDeep == 1) {
				FatherElementDeep = 0;
				BeginAddElement(&ui::mainwin);
			}
			return FatherElement;
		}
		void AddElement(ui::Element* ele) {
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(ele);
		}
		void AddElement_autoRelease(ui::Element* ele) {
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(ele, ui::auto_release);
		}
		ui::Layout* GetFatherLayout() {
			if (FatherLayoutStack.empty())return nullptr;
			return FatherLayout;
		}
		void Begin(ui::Element* a, std::function<void()> func = nullptr) {
			BeginAddElement(a);
			func();
			EndAddElement();
		}
		ui::Window& Window(std::string title, std::function<void()> func = nullptr) {
			ui::Window* win = new ui::Window(title, ui::auto_release);
			BeginAddElement(win);
			if (func)func();
			EndAddElement();
			return *win;
		}
		ui::Layout &Layout(std::function<void()> func) {
			ui::Layout* temp = new ui::Layout();
			ui::Layout* temp2 = ui::this_layout;
			ui::this_layout = temp;
			temp->ClearKey();
			BeginAddElement(temp);
			if (func)func();
			EndAddElement();
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			ui::this_layout = temp2;
			return *temp;
		}
		ui::Text &Text(std::string content) {
			ui::Text* temp = new ui::Text(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::OrderedText &OrderedText(std::string number, std::string content) {
			ui::OrderedText* temp = new ui::OrderedText(number, content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::OrderedText &OrderedText(std::string content) {
			ui::OrderedText* temp = new ui::OrderedText(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::ColorText &ColorText(std::string content, Color color = ui::TextColor2, Color bgcolor = BLANK) {
			ui::ColorText* temp = new ui::ColorText(content, color, bgcolor);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Head& Head(std::string content) {
			ui::Head* temp = new ui::Head(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Head& Head(int head, std::string content) {
			ui::Head* temp = new ui::Head(head, content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Warning& Warning(std::string content) {
			ui::Warning* temp = new ui::Warning(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Error& Error(std::string content) {
			ui::Error* temp = new ui::Error(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Hyperlink& Hyperlink(std::string content, std::string link = "") {
			ui::Hyperlink* temp = new ui::Hyperlink(content, link);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Switch &Switch(std::string content, bool on = false, bool* on_ptr = nullptr) {
			ui::Switch* temp = new ui::Switch(content, on, on_ptr);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Button &Button(std::string content) {
			ui::Button* temp = new ui::Button(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::CheckBox &CheckBox(std::string content, bool on = false, bool* ptr = nullptr) {
			ui::CheckBox* temp = new ui::CheckBox(content, on, ptr);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::RadioBox &RadioBox(std::vector<std::string> content, int choose = -1, int* ptr = nullptr) {
			ui::RadioBox* temp = new ui::RadioBox(content, choose, ptr);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Space &Space(int space = 1) {
			ui::Space* temp = new ui::Space(space);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Line &Line() {
			ui::Line* temp = new ui::Line();
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Slider &Slider(realn minn, realn maxn, realn now, realn* num) {
			ui::Slider* temp = new ui::Slider(minn, maxn, now, num);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Slider_Int &Slider_Int(int minn, int maxn, int now, int* num) {
			ui::Slider_Int* temp = new ui::Slider_Int(minn, maxn, now, num);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Collapse &Collapse(std::string content = "Collapse", std::function<void()> fun = nullptr) {
			ui::Collapse* temp = new ui::Collapse(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			BeginAddElement(temp);
			if (fun)fun();
			EndAddElement();
			return *temp;
		}
		ui::Scene &Scene(std::function<void()> draw_fun = nullptr) {
			ui::Scene* temp = new ui::Scene(draw_fun);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Scene3D &Scene3D(std::function<void()> draw_fun = nullptr) {
			ui::Scene3D* temp = new ui::Scene3D(draw_fun);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::InputBox& InputBox(std::string content = "", std::string* input = nullptr) {
			ui::InputBox* temp = new ui::InputBox(content, input);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::MultiInputBox& MultiInputBox(std::string content = "") {
			ui::MultiInputBox* temp = new ui::MultiInputBox(content);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::TextBox& TextBox(std::string content = "Text", std::string str = "") {
			ui::TextBox* temp = new ui::TextBox(content, str);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Table& Table(std::vector <std::vector <std::string> > items) {
			ui::Table* temp = new ui::Table(items);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Table& Table() {
			ui::Table* temp = new ui::Table();
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::Page &Page(std::function<void()> fun = nullptr) {
			ui::Page* temp = new ui::Page;
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			temp->ClearKey();
			ui::this_page = temp;
			BeginAddElement(temp);
			if (fun)fun();
			EndAddElement();
			return *temp;
		}
		ui::Page &Prepare_Page(std::function<void()> fun = nullptr) {
			ui::Page* temp = new ui::Page;
			temp->ClearKey();
			ui::this_page = temp;
			BeginAddElement(temp);
			if (fun)fun();
			EndAddElement();
			return *temp;
		}
		ui::Box &Box() {
			ui::Box* temp = new ui::Box;
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::MultiTab &MultiTab(std::function<void()> fun = nullptr) {
			Vector2 DPI = GetWindowScaleDPI();
			ui::dpi = DPI.x;
			ui::MultiTab* temp = new ui::MultiTab;
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			BeginAddElement(temp);
			if (fun)fun();
			EndAddElement();
			return *temp;
		}
		ui::Free &Free(std::function <void()> draw_fun = nullptr) {
			ui::Free* temp = new ui::Free(draw_fun);
			ui::this_free = temp;
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}
		ui::LoadingBar &LoadingBar(std::string icon = "", std::string text = "进度", std::function <realn()> fun_ = nullptr) {
			ui::LoadingBar* temp = new ui::LoadingBar(icon, text, fun_);
			if (GetFatherElement() != nullptr)GetFatherElement()->Add(temp, ui::auto_release);
			return *temp;
		}

		namespace sider {

			ui::TopMenu& TopMenu() {
				ui::TopMenu* temp = new ui::TopMenu();
				if (GetFatherElement() != nullptr)GetFatherElement()->sider.AddSider(temp, ui::spos_top, ui::auto_release);
				return *temp;
			}
			ui::BottomMenu& BottomMenu() {
				ui::BottomMenu* temp = new ui::BottomMenu();
				if (GetFatherElement() != nullptr)GetFatherElement()->sider.AddSider(temp, ui::spos_bottom, ui::auto_release);
				return *temp;
			}
			ui::Navigation& Navigation(std::string content, tree_node<std::string>& tree) {
				ui::Navigation* temp = new ui::Navigation(content, tree);
				if (GetFatherElement() != nullptr)GetFatherElement()->sider.AddSider(temp, ui::spos_left, ui::auto_release);
				return *temp;
			}

		}

	}

	// 更多功能============================
	namespace ui {
		Window* this_msgbox = nullptr;
		BottomMenu& MessageBox(int w, int h, std::function <void()> fun) {
			Window* win = new Window;
			TraceLog(LOG_INFO, ("GGCCUI: Created MsgBox #" + wp::tostr(win)).c_str());
			if (!win) throw "MessageBox created failed!";
			win->draw_dark = true;
			win->draw_title = false;
			ui::BottomMenu* menu;
			create::Begin(win, [&] {
				create::Page(fun);
				menu = &create::sider::BottomMenu();
			});
			win->Hide();
			win->PopFromMid();
			win->SetReleaseFunc(ui::auto_release);
			win->withCallback([menu, win, w, h] {
				this_msgbox = win;
				if (!win) throw "MessageBox failed!";
				win->draw_dark = true;
				win->SetSize(w, h);
				win->GotoMid();
				if (menu->click != -1) {
					TraceLog(LOG_INFO, ("GGCCUI: Close MsgBox #" + wp::tostr(win)).c_str());
					win->Close();
					win->DeleteThis();
				}
			});
			return *menu;
		};
		TopMenu& MessageBox_TopMenu(int w, int h, std::function <void()> fun) {
			Window* win = new Window;
			TraceLog(LOG_INFO, ("GGCCUI: Created MsgBox (TopMenu) #" + wp::tostr(win)).c_str());
			if (!win) throw "MessageBox created failed!";
			win->draw_dark = true;
			win->draw_title = false;
			ui::TopMenu* menu;
			create::Begin(win, [&] {
				create::Page(fun);
				menu = &create::sider::TopMenu();
			});
			win->Hide();
			win->PopFromMid();
			win->SetReleaseFunc(ui::auto_release);
			win->withCallback([menu, win, w, h] {
				this_msgbox = win;
				if (!win) throw "MessageBox failed!";
				win->draw_dark = true;
				win->SetSize(w, h);
				win->GotoMid();
				if (menu->click != -1) {
					TraceLog(LOG_INFO, ("GGCCUI: Close MsgBox (TopMenu) #" + wp::tostr(win)).c_str());
					win->Close();
					win->DeleteThis();
				}
			});
			return *menu;
		};
		BottomMenu& MessageBox(std::string text) {
			return MessageBox(ui::UnitHeight * 20, 10 * UnitHeight, [&] {create::Text(text);});
		};
		BottomMenu& MessageBox(std::function <void()> fun) {
			return MessageBox(ui::UnitHeight * 20, 10 * UnitHeight, fun);
		};
		BottomMenu& MessageBox(int h, std::function <void()> fun) {
			return MessageBox(ui::UnitHeight * 20, h, fun);
		};

		namespace loading {
			std::atomic<bool> done(false); // 用于线程间通信的原子标志

			// 执行后台工作的函数
			void doWork(std::function<void()> work) {
				work(); // 执行传入的函数
				done = true; // 设置标志，表示工作完成
			}

			// 启动加载框的函数
			void StartLoading(std::string text, std::function<void()> work) {
				done = false;
				std::thread workerThread(doWork, work); // 创建工作线程
				while (!done) {
					BeginDrawing();
					ClearBackground(ui::BgColor);
					ui::Update();
					DrawRectangle(0, 0, ui::winW, ui::winH, ui::ColorF(BLACK, 0.6));
					ui::special_effect::DrawLoadingCircle(ui::winW / 2, ui::winH / 2, 50 * ui::dpi, text);
					EndDrawing();
					if (WindowShouldClose()) {
						if (IsKeyPressed(KEY_ESCAPE)) continue;
						else {
							CloseWindow();
							exit(0);
						}
					}
				}
				// 等待工作线程结束
				workerThread.join();
			}
		}
	}

	// ====================================

	// 平面几何绘制函数
	namespace pg {
		void segment::Draw(unsigned color) {
			ui::plot->line(Abs(p1), Abs(p2), ui::ColorF(color));
		}
		void segment::DrawLines(unsigned color) {
			ui::plot->line(Abs(p1), Abs(p2), ui::ColorF(color));
		}
		void circle::Draw(unsigned color) {
			ui::plot->circle(pos, r, ui::ColorF(color));
		}
		void circle::DrawLines(unsigned color) {
			ui::plot->circle_lines(pos, r, ui::ColorF(color));
		}
		void ellipse::Draw(unsigned color) {
			ui::plot->ellipse(pos, a, b, rotate, ui::ColorF(color));
		}
		void ellipse::DrawLines(unsigned color) {
			ui::plot->ellipse_lines(pos, a, b, rotate, ui::ColorF(color));
		}
		void polygon::Draw(unsigned color) {
			auto p2 = p;
			for (auto& i : p2) i = Abs(i);
			ui::plot->polygon(p2, ui::ColorF(color));
		}
		void polygon::DrawLines(unsigned color) {
			auto p2 = p;
			for (auto& i : p2) i = Abs(i);
			ui::plot->polygon_lines(p2, ui::ColorF(color));
		}
		void roundpoly::Draw(unsigned color) {
			auto p2 = p;
			for (auto& i : p2) i = Abs(i);
			ui::plot->round_polygon(p2, roundness, ui::ColorF(color));
		}
		void roundpoly::DrawLines(unsigned color) {
			auto p2 = p;
			for (auto& i : p2) i = Abs(i);
			ui::plot->round_polygon_lines(p2, roundness, ui::ColorF(color));
		}
		void capsule::Draw(unsigned color) {
			ui::plot->capsule(Abs(p1), Abs(p2), r, ui::ColorF(color));
		}
		void capsule::DrawLines(unsigned color) {
			ui::plot->capsule_lines(Abs(p1), Abs(p2), r, ui::ColorF(color));
		}
		void shape::Draw(unsigned color) {}
		void shape::DrawLines(unsigned color) {}
	}

}
