// ui.h
// ggcc用户交互界面库（基础库）

#ifndef __GGCCUI_H__
#define __GGCCUI_H__

#include <bits/stdc++.h>
#include <ggcc/animation.h>
using namespace std;

namespace ggcc {

	// 声明
	struct Point;
	struct ButtonState;
	class Button;
	struct MenuText;
	struct MenuState;
	class Menu;
	class MenuList;

	struct Point {
		double x;
		double y;
	};

	// 编号
	int ButtonSum=0;		// 按钮数量
	int MenuSum=0;			// 下拉菜单数量
	int MenuListSum=0;		// 下拉菜单组数量
	int TextboxSum=0;		// 文本框数量

	// 鼠标
	Point MousePos;			// 位置
	bool LDOWN=false;		// 左键按下
	bool RDOWN=false;		// 右键按下
	bool Scissor=true;		// 是否使用裁剪模式自动变换

	bool InRect(Point p1,Point p2) {
		return MousePos.x>=p1.x&&MousePos.y>=p1.y&&
		       MousePos.x<p2.x&&MousePos.y<p2.y;
	}
	bool InRect(double x1,double y1,double x2,double y2) {
		return MousePos.x>=x1&&MousePos.y>=y1&&
		       MousePos.x<x2&&MousePos.y<y2;
	}
	bool InCircle(Point p,double r) {
		return (MousePos.x-p.x)*(MousePos.x-p.x)+
		       (MousePos.y-p.y)*(MousePos.y-p.y)<=
		       r*r;
	}

	void ScissorMode(bool mode) {
		Scissor=mode;
	}

	void SetMouse(Point k,bool lDown=false,bool rDown=false) {
		MousePos=k;
	}
	void SetMouse(double x,double y,bool lDown=false,bool rDown=false) {
		MousePos= {x,y};
		LDOWN=lDown;
		RDOWN=rDown;
	}

	// 名称与id映射
	map <string,int> Name2ID;

	// 按钮
	struct ButtonState {
		Point pos;							// 位置
		double w=100,h=30;					// 宽、高
		double l=0;							// 放大率 (0-1)
		double a=1;							// 透明度 (0-1)
		double ani=100;						// 动画 (0-100)
		double highlight=0;					// 高亮 (0-100)
		bool mfloat=false;					// 鼠标悬浮
		bool mldown=false,mrdown=false;		// 鼠标按下
		bool mlclick=false,mrclick=false;	// 鼠标点击
		int mlclicks=0,mrclicks=0;			// 鼠标点击次数
		int id=0;							// 编号
		string name;						// 名称
		string text;						// 内容

		// 高级成员
		int FloatTime=0;					// 悬浮起始时间
		int UnFloatTime=0;					// 不悬浮起始时间
		int LClickTime=0;					// 鼠标左键点击时间
		int RClickTime=0;					// 鼠标右键点击时间
		int LDownTime=0;					// 鼠标左键按下时间
		int RDownTime=0;					// 鼠标右键按下时间
		void (*DrawMode)(ButtonState);		// 绘制方式
		bool Visible=true;					// 可见
		bool Clickable=true;				// 可点击

	};

	class Button {
		private:
			Animation Enlarge;				// 放大率（或者认为是缩小率 ）动画
			Animation AppearAni;			// 出现/消失的动画
			ButtonState k;					// 按钮状态

		public:
			Button(Point Pos,double w,double h,string Name,string Text);		// 构造函数
			void Init(Point Pos,double w,double h,string Name,string Text);		// 初始化
			void Draw(void (*draw)(ButtonState));								// 绘制
			void Update();														// 更新
			void SetDrawMode(void (*draw)(ButtonState));						// 设置绘制方式
			void SetA(double a);												// 设置透明度(0-1)
			void SetVisible(bool t);											// 设置是否可见
			void SetPos(Point pos);												// 设置位置
			void SetPos(double x,double y);										// 设置位置
			void SetClickable(bool t);											// 设置是否可点击
			string GetID();														// 获取按钮编号
			ButtonState GetState();												// 获取按钮状态

			bool Click();														// 是否左键点击
			bool LClick();														// 是否左键点击
			bool RClick();														// 是否右键点击
			bool Float();														// 是否鼠标悬停

			void Appear();														// 启动出现动画计算
			void Disappear();													// 启动消失动画计算

	};

	Button::Button(Point Pos= {0,0},double w=300,double h=100,string Name="Button",
	               string Text="This is a button") {
		k.id=++ButtonSum;
		k.pos.x=Pos.x;
		k.pos.y=Pos.y;
		k.w=w;
		k.h=h;
		k.name=Name;
		k.text=Text;
		AppearAni.SetStartPos(100);
		AppearAni.SetTargetPos(100);
	}
	void Button::Init(Point Pos= {0,0},double w=300,double h=100,string Name="Button",
	                  string Text="This is a button") {
		k.pos.x=Pos.x;
		k.pos.y=Pos.y;
		k.w=w;
		k.h=h;
		k.name=Name;
		k.text=Text;
		AppearAni.SetStartPos(100);
		AppearAni.SetTargetPos(100);
	}
	void Button::Draw(void (*draw)(ButtonState)) {
		if(k.Visible)draw(k);
	}
	void Button::SetDrawMode(void (*draw)(ButtonState)) {
		k.DrawMode=draw;
	}
	void Button::SetA(double a) {
		k.a=a;
	}
	void Button::SetVisible(bool t) {
		k.Visible=t;
	}
	void Button::SetPos(Point pos) {
		k.pos=pos;
	}
	void Button::SetPos(double x,double y) {
		k.pos= {x,y};
	}
	void Button::SetClickable(bool t) {
		k.Clickable=t;
	}
	void Button::Update() {
		Enlarge.Update();
		Enlarge.GetNowPos(k.l);
		AppearAni.Update();
		AppearAni.GetNowPos(k.ani);

		if(k.mlclick)k.mlclick=false;
		if(k.mrclick)k.mrclick=false;

		if(InRect(k.pos.x,k.pos.y,k.pos.x+k.w,k.pos.y+k.h)) {
			if(!k.mfloat) {
				k.FloatTime=clock();
				Enlarge.SetTargetPos(1);
			}
			k.highlight=min((int)clock()-k.FloatTime,100);
			k.mfloat=true;
			if(LDOWN) {
				if(!k.mldown) {
					k.LDownTime=clock();
					k.mldown=true;
				}
			} else if(RDOWN) {
				if(!k.mrdown) {
					k.RDownTime=clock();
					k.mrdown=true;
				}
			} else {
				if(k.mldown) {
					k.mldown=false;
					k.mlclick=true;
					k.mlclicks++;
					k.LClickTime=clock();
				} else if(k.mrdown) {
					k.mrdown=false;
					k.mrclick=true;
					k.mrclicks++;
					k.RClickTime=clock();
				}
			}
		} else {
			if(k.mfloat) {
				k.UnFloatTime=clock();
				Enlarge.SetTargetPos(0);
			}
			if(k.mldown) {
				k.mldown=false;
			} else if(k.mrdown) {
				k.mrdown=false;
			}
			k.mfloat=false;
			k.highlight=100-min((int)clock()-k.UnFloatTime,100);
		}
	}
	string Button::GetID() {
		return "Button"+to_string(k.id);
	}
	ButtonState Button::GetState() {
		return k;
	}
	bool Button::Click() {
		return k.mlclick&&k.Clickable;
	}
	bool Button::LClick() {
		return k.mlclick&&k.Clickable;
	}
	bool Button::RClick() {
		return k.mrclick&&k.Clickable;
	}
	bool Button::Float() {
		return k.mfloat;
	}
	void Button::Appear() {
		AppearAni.SetTargetPos(0);
	}
	void Button::Disappear() {
		AppearAni.SetTargetPos(100);
	}

	// 拉杆
	class Pull {
		private:

		public:

	};

	// 选择
	class Choose {
		private:

		public:
	};

	// 文本框
	struct TextboxState {
		Point pos;							// 位置
		string text="This is a text";		// 文本
		double w,h;							// 宽、高
		double TopBlank,ButtomBlank;		// 上下留白
		double LeftBlank,RightBlank;		// 左右留白
		double a=1;							// 透明度(0-1)
		int id=0;							// 编号
		int ani=0;							// 出现动画(0-100)
		bool mfloat=false;					// 鼠标悬浮
		bool mldown=false,mrdown=false;		// 鼠标按下
		bool mlclick=false,mrclick=false;	// 鼠标点击

		// 高级成员
		int FloatTime=0;					// 悬浮起始时间
		int UnFloatTime=0;					// 不悬浮起始时间
		int LClickTime=0;					// 鼠标左键点击时间
		int RClickTime=0;					// 鼠标右键点击时间
		int LDownTime=0;					// 鼠标左键按下时间
		int RDownTime=0;					// 鼠标右键按下时间
		bool Visible=true;					// 可见
		bool CopyAllowed=true;				// 允许复制
		Button CopyButton;					// 复制按钮
		void (*DrawMode)(ButtonState);		// 绘制方式
	};
	class Textbox {
		private:
			TextboxState k;																	// 文本框状态
			Animation AppearAni;															// 出现动画
			bool ClickCopy=false;															// 是否使用复制

		public:
			bool IsAppear=false;															// 是否出现

			Textbox(Point Pos,double w,double h,double tb,double bb,double lb,double rb);	// 构造函数
			void Init(Point Pos,double w,double h,double tb,double bb,double lb,double rb);	// 初始化
			void Draw(void (*draw)(TextboxState));											// 绘制
			void Update();																	// 更新

			bool Copy();																	// 是否复制
			bool Float();																	// 是否悬浮
			bool Click();																	// 是否左键点击
			bool LClick();																	// 是否左键点击
			bool RClick();																	// 是否右键点击

			void SetCopyButton(bool able,double w,double h,Point d/*相对与右上角的偏离位置*/,string t);// 设置复制按钮
			void SetText(string Text);														// 设置文本内容
			void SetVisible(bool visible);													// 设置可见
			void SetA(double a);															// 设置透明度
			TextboxState GetState();														// 获取状态
			string GetID();																	// 获取编号
			string GetText();																// 获取文本内容

			void Appear();																	// 启动出现动画计算
			void Disappear();																// 启动消失动画计算

	};

	Textbox::Textbox(Point Pos= {0,0},
	                 double w=200,double h=100,
	                 double tb=10,double bb=10,double lb=10,double rb=10) {
		k.pos=Pos;
		k.w=w,k.h=h;
		k.TopBlank=tb;
		k.ButtomBlank=bb;
		k.LeftBlank=lb;
		k.RightBlank=rb;
		k.id=++TextboxSum;
		AppearAni.SetStartPos(100);
		AppearAni.SetTargetPos(0);
	}
	void Textbox::Init(Point Pos= {0,0},
	                   double w=200,double h=100,
	                   double tb=10,double bb=10,double lb=10,double rb=10) {
		k.pos=Pos;
		k.w=w,k.h=h;
		k.TopBlank=tb;
		k.ButtomBlank=bb;
		k.LeftBlank=lb;
		k.RightBlank=rb;
		AppearAni.SetStartPos(100);
		AppearAni.SetTargetPos(0);
	}
	void Textbox::Update() {
		if(InRect(k.pos.x,k.pos.y,k.pos.x+k.w,k.pos.y+k.h)) {
			k.CopyButton.Appear();
			k.FloatTime=clock();
			k.mfloat=true;
			k.mlclick=k.mrclick=false;
			if(LDOWN)k.mldown=true;
			else {
				if(k.mldown)k.mlclick=true;
				k.mldown=false;
			}
			if(RDOWN)k.mrdown=true;
			else {
				if(k.mrdown)k.mrclick=true;
				k.mrdown=false;
			}
		} else {
			k.mlclick=k.mrclick=false;
			k.mldown=k.mrdown=false;
			k.CopyButton.Disappear();
			k.UnFloatTime=clock();
			k.mfloat=false;
		}
		k.CopyButton.Update();
		ClickCopy=false;
		if(k.CopyButton.Click())ClickCopy=true;
	}
	void Textbox::Draw(void (*draw)(TextboxState)) {
		if(k.Visible)draw(k);
	}
	bool Textbox::Copy() {
		return ClickCopy;
	}
	bool Textbox::Float() {
		return k.mfloat;
	}
	bool Textbox::Click() {
		return k.mlclick;
	}
	bool Textbox::LClick() {
		return k.mlclick;
	}
	bool Textbox::RClick() {
		return k.mrclick;
	}
	string Textbox::GetText() {
		return k.text;
	}
	void Textbox::SetCopyButton(bool able=true,double w=50,double h=10,Point d= {-5,5},string t="copy") {
		k.CopyAllowed=able;
		if(!able)return;
		k.CopyButton.Init({k.pos.x+k.w-w+d.x,k.pos.y+d.y},w,h,"CopyButton",t);
	}
	void Textbox::SetText(string Text="This is a text") {
		k.text=Text;
	}
	void Textbox::SetVisible(bool visible) {
		k.Visible=visible;
	}
	void Textbox::SetA(double a) {
		k.a=a;
	}
	TextboxState Textbox::GetState() {
		return k;
	}
	string Textbox::GetID() {
		return "Textbox"+to_string(k.id);
	}
	void Textbox::Appear() {
		IsAppear=true;
		AppearAni.SetTargetPos(0);
	}
	void Textbox::Disappear() {
		IsAppear=false;
		AppearAni.SetTargetPos(100);
	}

	// 提示文本
	struct TiptextState {
		Point pos;							// 位置
		double w=50,h=20;					// 宽、高
		string text="This is a tip";		// 文本
		int dir=1;							// 方向：1上2下3左4右
		int wait=1000;						// 等待时间（不一定需要立刻弹出提示）
		bool visible=false;					// 是否可见
	};
	class Tiptext {
		private:
			TiptextState k;									// 提示文本状态

		public:
			Tiptext(Point pos,double w,int h,string text,int dir,int wait,bool visible);	// 构造函数
			void Init(Point pos,double w,int h,string text,int dir,int wait,bool visible);	// 初始化
			void Update();																	// 更新
			void Draw(void (*draw)(TiptextState));											// 绘制
			void SetVisible(bool visible);													// 设置是否可见

	};
	Tiptext::Tiptext(
	    Point pos= {0,0},double w=50,int h=20,string text="This is a tip",
	    int dir=1,int wait=1000,bool visible=false
	) {
		k.pos=pos;
		k.w=w,k.h=h;
		k.text=text;
		k.dir=dir;
		k.wait=wait;
		k.visible=visible;
	}
	void Tiptext::Init(
	    Point pos= {0,0},double w=50,int h=20,string text="This is a tip",
	    int dir=1,int wait=1000,bool visible=false
	) {
		k.pos=pos;
		k.w=w,k.h=h;
		k.text=text;
		k.dir=dir;
		k.wait=wait;
		k.visible=visible;
	}

	// 对话框
	class Messagebox {
		private:

		public:

	};

	// 下拉菜单
	struct MenuText {
		int type=1; 			// 1按钮 2分割线 3文本 4附属菜单
		Button button;			// 按钮
		string text;			// 文本
		Menu *menu;				// 附属菜单
		int height;				// 当前绘制到的位置
	};
	struct MenuState {
		vector <MenuText> text;	// 内容
		int ButtonHeight=30;	// 按钮高度
		int LineHeight=10;		// 分割线高度
		int TextHeight=30;		// 文本高度
		int Teams[64];			// 每个分组的大小
		int id=0;				// 编号
		bool IsAppear=false;	// 是否出现
		bool IsFixed=false;		// 是否固定
		bool Clicked=false;		// 是否激活

		Point pos;				// 位置
		double w=0,h=0;			// 宽度、高度
		double drawh=0;			// 绘制高度

		// 高级成员
		int LastClickButton=-1;	// 上次点击按钮
		int LastClickButtonInTeam[64];// 各分组上次点击按钮
		void (*DrawButtonMode)(ButtonState);
		void (*DrawMenuButtonMode)(ButtonState);
		void (*DrawTextMode)(int x,int y,string text);
		void (*DrawLineMode)(int x,int y,int w);

	};

	class Menu {
		private:
			Animation DrawH;	// 绘制高度
			bool ClickDisappear=0;// 可以点起以消失
			bool IsFloat=false;	// 是否鼠标悬停
			MenuState k;		// 菜单状态

		public:
			bool IsAppear=false;
			Menu(Point Pos,int w,int bh,int lh,int th);						// 构造函数
			void Init(Point Pos,int w,int bh,int lh,int th);				// 初始化
			void Update(bool deep);											// 更新
			void AddButton(string Text);									// 添加按钮
			void AddText(string Text);										// 添加文本
			void AddLine();													// 添加分割线
			void AddMenuButton(string Text,Menu *menu) {
				if(Scissor) {
					Button button(Point {0,0+k.h},k.w,k.ButtonHeight,Text,Text);
					MenuText text;
					text.type=4;
					text.button=button;
					text.height=k.h;
					text.menu=menu;
					menu->SetPos(k.pos.x+k.w+menu->GetState().pos.x,
					             k.pos.y+k.h+menu->GetState().pos.y);
					k.text.push_back(text);
					k.h+=k.ButtonHeight;
				} else {
					Button button(Point {k.pos.x,k.pos.y+k.h},k.w,k.ButtonHeight,Text,Text);
					MenuText text;
					text.type=4;
					text.button=button;
					text.height=k.h;
					text.menu=menu;
					menu->SetPos(k.pos.x+k.w+menu->GetState().pos.x,
					             k.pos.y+k.h+menu->GetState().pos.y);
					k.text.push_back(text);
					k.h+=k.ButtonHeight;
				}
			};						// 添加附属菜单按钮
			void AddTeam();													// 添加组
			MenuState GetState();											// 获取当前状态

			void SetDrawButtonMode(void (*draw)(ButtonState));				// 设置按钮绘制模式
			void SetDrawMenuButtonMode(void (*draw)(ButtonState));			// 设置菜单按钮绘制模式
			void SetDrawTextMode(void (*draw)(int x,int y,string text));	// 设置文本绘制模式
			void SetDrawLineMode(void (*draw)(int x,int y,int w));			// 设置分割线绘制模式
			void SetPos(Point Pos);											// 设置位置
			void SetPos(double x,double y);									// 设置位置
			void Fix(bool fix);												// 设置是否固定
			void Draw(void (*draw)(MenuState));								// 绘制
			bool Float();													// 鼠标是否悬停
			string GetID();													// 获取编号

			void Appear();													// 启动出现动画计算
			void Disappear();												// 启动消失动画计算

	};

	Menu::Menu(Point Pos= {0,0},int w=150,int bh=30,int lh=10,int th=30) {
		k.id=++MenuSum;
		k.pos=Pos;
		k.w=w;
		k.ButtonHeight=bh;
		k.LineHeight=lh;
		k.TextHeight=th;
	}
	void Menu::Init(Point Pos= {0,0},int w=150,int bh=30,int lh=10,int th=30) {
		k.pos=Pos;
		k.w=w;
		k.ButtonHeight=bh;
		k.LineHeight=lh;
		k.TextHeight=th;
	}
	void Menu::Update(bool deep=true) {
		DrawH.Update();
		DrawH.GetNowPos(k.drawh);
		Point mp=MousePos;
		k.IsAppear=IsAppear;
		int temp[1000],ts=0;
		IsFloat=false;
		if(InRect(k.pos.x,k.pos.y,k.pos.x+k.w,k.pos.y+k.h)&&IsAppear)IsFloat=true;
		if(Scissor)SetMouse(mp.x-k.pos.x,mp.y-k.pos.y,LDOWN,RDOWN);
		for(int i=0; i<k.text.size(); i++) {
			k.text[i].button.Update();
			if(k.text[i].button.Click()) {
				k.LastClickButton=i;
			}
			if(k.text[i].type==4)temp[++ts]=i;
		}
		if(Scissor)SetMouse(mp,LDOWN,RDOWN);
		if(!deep)return;
		for(int i=1; i<=ts; i++) {
			if(k.text[temp[i]].menu->GetState().IsAppear||k.text[temp[i]].menu->GetState().drawh!=0) {
				k.text[temp[i]].menu->Update();
			} else k.text[temp[i]].menu->Update(false);
			if(k.text[temp[i]].button.Click()) {
				k.text[temp[i]].menu->Appear();
				k.Clicked=true;
			} else if(k.text[temp[i]].button.Float()&&k.Clicked) {
				k.text[temp[i]].menu->Appear();
				for(int j=1; j<=ts; j++) {
					if(i==j)continue;
					k.text[temp[j]].menu->Disappear();
				}
			} else {
				bool flag=false;
				for(int j=1; j<=ts; j++)
					if(k.text[temp[j]].menu->IsAppear)
						flag=true;
				if(!flag)k.Clicked=false;
			}
			if(k.text[temp[i]].menu->Float())IsFloat=true;
		}
		if(!LDOWN&&!RDOWN)ClickDisappear=true;
		if(!InRect(k.pos.x,k.pos.y,k.pos.x+k.w,k.pos.y+k.h)&&ClickDisappear&&!IsFloat) {
			if(LDOWN||RDOWN)Disappear();
		}
	}
	void Menu::AddButton(string Text="This is a button") {
		if(Scissor) {
			Button button(Point {0,0+k.h},k.w,k.ButtonHeight,Text,Text);
			MenuText text;
			text.type=1;
			text.button=button;
			text.height=k.h;
			k.text.push_back(text);
			k.h+=k.ButtonHeight;
		} else {
			Button button(Point {k.pos.x,k.pos.y+k.h},k.w,k.ButtonHeight,Text,Text);
			MenuText text;
			text.type=1;
			text.button=button;
			text.height=k.h;
			k.text.push_back(text);
			k.h+=k.ButtonHeight;
		}
	}
	void Menu::AddText(string Text="This is a button") {
		MenuText text;
		text.type=2;
		text.text=Text;
		text.height=k.h;
		k.text.push_back(text);
		k.h+=k.TextHeight;
	}
	void Menu::AddLine() {
		MenuText text;
		text.type=3;
		text.height=k.h;
		k.text.push_back(text);
		k.h+=k.LineHeight;
	}
	MenuState Menu::GetState() {
		return k;
	}
	void Menu::SetDrawButtonMode(void (*draw)(ButtonState)) {
		k.DrawButtonMode=draw;
	}
	void Menu::SetDrawMenuButtonMode(void (*draw)(ButtonState)) {
		k.DrawMenuButtonMode=draw;
	}
	void Menu::SetDrawTextMode(void (*draw)(int x,int y,string text)) {
		k.DrawTextMode=draw;
	}
	void Menu::SetDrawLineMode(void (*draw)(int x,int y,int w)) {
		k.DrawLineMode=draw;
	}
	void Menu::SetPos(Point Pos) {
		for(int i=0; i<=k.text.size(); i++) {
			if(!Scissor)k.text[i].button.SetPos(Pos.x,Pos.y+k.text[i].height);
			if(k.text[i].type==4) {
				k.text[i].menu->SetPos(Pos.x+k.w+k.text[i].menu->GetState().pos.x-k.pos.x-k.w,
				                       Pos.y+k.text[i].height+k.text[i].menu->GetState().pos.y-k.pos.y-k.text[i].height);
			}
		}
		k.pos=Pos;
	}
	void Menu::SetPos(double x,double y) {
		SetPos({x,y});
	}
	void Menu::Fix(bool fix) {
		k.IsFixed=fix;
		if(fix) {
			DrawH.SetStartPos(k.h);
			Appear();
		}
	}
	void Menu::Draw(void (*draw)(MenuState)) {
		if(k.drawh>0.001)draw(k);
		for(int i=0; i<k.text.size(); i++) {
			if(k.text[i].type==4&&
			        (k.text[i].menu->GetState().IsAppear
			         ||!k.text[i].menu->GetState().drawh==0)) {
				k.text[i].menu->Draw(draw);
			}
		}
	}
	bool Menu::Float() {
		return IsFloat;
	}
	string Menu::GetID() {
		return "Menu"+to_string(k.id);
	}
	void Menu::Appear() {
		DrawH.SetTargetPos(k.h);
		if(LDOWN||RDOWN)ClickDisappear=false;
		IsAppear=true;
		for(int i=0; i<=k.text.size(); i++) {
			k.text[i].button.SetClickable(true);
		}
	}
	void Menu::Disappear() {
		if(k.IsFixed)return;
		DrawH.SetTargetPos(0);
		IsAppear=false;
		for(int i=0; i<=k.text.size(); i++) {
			k.text[i].button.SetClickable(false);
		}
		for(int i=0; i<=k.text.size(); i++) {
			if(k.text[i].type==4) {
				k.text[i].menu->Disappear();
			}
		}
	}

	// 下拉菜单组
	struct MenuListState {
		Point pos;							// 位置
		vector <Menu*> menu;				// 菜单
		vector <string> name;				// 名称
		vector <int> nowx;					// 当前X
		vector <Button> button;				// 按钮
		map <string,Menu*> Name2Menu;		// 由名称转到按钮
		int ButtonWidth=50;					// 按钮宽度
		int Height=20;						// 高度
		int id=0;							// 编号
		int menus=0;						// 菜单数量（放置多线程size()出问题） 
		int w=0;							// 宽度 
		bool Clicked=false;					// 是否已激活
	};
	class MenuList {
		private:
			MenuListState k;				// 下拉菜单组

		public:
			MenuList(Point Pos,int buttonwidth,int height);							// 构造函数
			void Init(Point Pos,int buttonwidth,int height);						// 初始化
			void AddMenu(string name,Menu* id);										// 添加下拉菜单
			void Update();															// 更新
			void Draw(void (*drawmenu)(MenuState),void (*drawbutton)(ButtonState));	// 绘制
			string GetID();															// 获取编号
			MenuListState GetState();												// 获取状态

	};
	MenuList::MenuList(Point Pos= {0,0},int buttonwidth=50,int height=20) {
		k.id=++MenuListSum;
		k.pos=Pos;
		k.ButtonWidth=buttonwidth;
		k.Height=height;
		k.menu.clear();
		k.name.clear();
		k.nowx.clear();
		k.button.clear();
	}
	void MenuList::Init(Point Pos= {0,0},int buttonwidth=50,int height=20) {
		k.pos=Pos;
		k.ButtonWidth=buttonwidth;
		k.Height=height;
		k.menu.clear();
		k.name.clear();
		k.nowx.clear();
		k.button.clear();
	}
	void MenuList::AddMenu(string name,Menu* id) {
		k.name.push_back(name);
		k.menu.push_back(id);
		if(!k.nowx.empty())k.nowx.push_back(k.nowx[k.nowx.size()-1]+k.ButtonWidth);
		else k.nowx.push_back(0);
		k.button.push_back({Point{k.pos.x+k.nowx[k.nowx.size()-1],k.pos.y},(double)k.ButtonWidth,(double)k.Height,name,name});
		id->SetPos(k.pos.x+k.nowx[k.nowx.size()-1],k.pos.y+k.Height);
		k.Name2Menu[name]=id;
	}
	void MenuList::Update() {
		for(int i=0; i<k.menu.size(); i++) {
//			cout<<GetID()<<" - "<<k.button[i].GetID()<<':'<<k.button[i].GetState().pos.x<<"->";
			k.button[i].Update();
//			cout<<k.button[i].GetState().pos.x<<"->";
			if(k.button[i].Click()) {
				k.menu[i]->SetPos(k.pos.x+k.nowx[i],k.pos.y+k.Height);
				k.menu[i]->Appear();
				k.Clicked=true;
			} else if(k.button[i].Float()&&k.Clicked) {
				k.menu[i]->SetPos(k.pos.x+k.nowx[i],k.pos.y+k.Height);
				k.menu[i]->Appear();
				for(int j=0; j<k.menu.size(); j++) {
					if(i==j)continue;
					k.menu[j]->Disappear();
				}
			} else {
				bool flag=false;
				for(int j=0; j<k.menu.size(); j++)if(k.menu[j]->IsAppear)flag=true;
				if(!flag)k.Clicked=false;
			}
//			cout<<k.button[i].GetState().pos.x<<"->";
			k.menu[i]->Update();
//			cout<<k.button[i].GetState().pos.x<<"->"<<endl;;
		}
	}
	void MenuList::Draw(void (*drawmenu)(MenuState),void (*drawbutton)(ButtonState)) {
		for(int i=0; i<k.menu.size(); i++)k.button[i].Draw(drawbutton);
		for(int i=0; i<k.menu.size(); i++)k.menu[i]->Draw(drawmenu);
	}
	string MenuList::GetID() {
		return "MenuList"+to_string(k.id);
	}
	MenuListState MenuList::GetState() {
		return k;
	}

	// 界面
	struct InterfaceState {
		vector <Menu*> menu;
	};
	class Interface {
		private:

		public:

	};


}

#endif
