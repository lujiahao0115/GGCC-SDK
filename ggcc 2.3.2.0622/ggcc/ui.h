// ui.h
// ggcc�û���������⣨�����⣩

#ifndef __GGCCUI_H__
#define __GGCCUI_H__

#include <bits/stdc++.h>
#include <ggcc/animation.h>
using namespace std;

namespace ggcc {

	// ����
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

	// ���
	int ButtonSum=0;		// ��ť����
	int MenuSum=0;			// �����˵�����
	int MenuListSum=0;		// �����˵�������
	int TextboxSum=0;		// �ı�������

	// ���
	Point MousePos;			// λ��
	bool LDOWN=false;		// �������
	bool RDOWN=false;		// �Ҽ�����
	bool Scissor=true;		// �Ƿ�ʹ�òü�ģʽ�Զ��任

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

	// ������idӳ��
	map <string,int> Name2ID;

	// ��ť
	struct ButtonState {
		Point pos;							// λ��
		double w=100,h=30;					// ����
		double l=0;							// �Ŵ��� (0-1)
		double a=1;							// ͸���� (0-1)
		double ani=100;						// ���� (0-100)
		double highlight=0;					// ���� (0-100)
		bool mfloat=false;					// �������
		bool mldown=false,mrdown=false;		// ��갴��
		bool mlclick=false,mrclick=false;	// �����
		int mlclicks=0,mrclicks=0;			// ���������
		int id=0;							// ���
		string name;						// ����
		string text;						// ����

		// �߼���Ա
		int FloatTime=0;					// ������ʼʱ��
		int UnFloatTime=0;					// ��������ʼʱ��
		int LClickTime=0;					// ���������ʱ��
		int RClickTime=0;					// ����Ҽ����ʱ��
		int LDownTime=0;					// ����������ʱ��
		int RDownTime=0;					// ����Ҽ�����ʱ��
		void (*DrawMode)(ButtonState);		// ���Ʒ�ʽ
		bool Visible=true;					// �ɼ�
		bool Clickable=true;				// �ɵ��

	};

	class Button {
		private:
			Animation Enlarge;				// �Ŵ��ʣ�������Ϊ����С�� ������
			Animation AppearAni;			// ����/��ʧ�Ķ���
			ButtonState k;					// ��ť״̬

		public:
			Button(Point Pos,double w,double h,string Name,string Text);		// ���캯��
			void Init(Point Pos,double w,double h,string Name,string Text);		// ��ʼ��
			void Draw(void (*draw)(ButtonState));								// ����
			void Update();														// ����
			void SetDrawMode(void (*draw)(ButtonState));						// ���û��Ʒ�ʽ
			void SetA(double a);												// ����͸����(0-1)
			void SetVisible(bool t);											// �����Ƿ�ɼ�
			void SetPos(Point pos);												// ����λ��
			void SetPos(double x,double y);										// ����λ��
			void SetClickable(bool t);											// �����Ƿ�ɵ��
			string GetID();														// ��ȡ��ť���
			ButtonState GetState();												// ��ȡ��ť״̬

			bool Click();														// �Ƿ�������
			bool LClick();														// �Ƿ�������
			bool RClick();														// �Ƿ��Ҽ����
			bool Float();														// �Ƿ������ͣ

			void Appear();														// �������ֶ�������
			void Disappear();													// ������ʧ��������

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

	// ����
	class Pull {
		private:

		public:

	};

	// ѡ��
	class Choose {
		private:

		public:
	};

	// �ı���
	struct TextboxState {
		Point pos;							// λ��
		string text="This is a text";		// �ı�
		double w,h;							// ����
		double TopBlank,ButtomBlank;		// ��������
		double LeftBlank,RightBlank;		// ��������
		double a=1;							// ͸����(0-1)
		int id=0;							// ���
		int ani=0;							// ���ֶ���(0-100)
		bool mfloat=false;					// �������
		bool mldown=false,mrdown=false;		// ��갴��
		bool mlclick=false,mrclick=false;	// �����

		// �߼���Ա
		int FloatTime=0;					// ������ʼʱ��
		int UnFloatTime=0;					// ��������ʼʱ��
		int LClickTime=0;					// ���������ʱ��
		int RClickTime=0;					// ����Ҽ����ʱ��
		int LDownTime=0;					// ����������ʱ��
		int RDownTime=0;					// ����Ҽ�����ʱ��
		bool Visible=true;					// �ɼ�
		bool CopyAllowed=true;				// ������
		Button CopyButton;					// ���ư�ť
		void (*DrawMode)(ButtonState);		// ���Ʒ�ʽ
	};
	class Textbox {
		private:
			TextboxState k;																	// �ı���״̬
			Animation AppearAni;															// ���ֶ���
			bool ClickCopy=false;															// �Ƿ�ʹ�ø���

		public:
			bool IsAppear=false;															// �Ƿ����

			Textbox(Point Pos,double w,double h,double tb,double bb,double lb,double rb);	// ���캯��
			void Init(Point Pos,double w,double h,double tb,double bb,double lb,double rb);	// ��ʼ��
			void Draw(void (*draw)(TextboxState));											// ����
			void Update();																	// ����

			bool Copy();																	// �Ƿ���
			bool Float();																	// �Ƿ�����
			bool Click();																	// �Ƿ�������
			bool LClick();																	// �Ƿ�������
			bool RClick();																	// �Ƿ��Ҽ����

			void SetCopyButton(bool able,double w,double h,Point d/*��������Ͻǵ�ƫ��λ��*/,string t);// ���ø��ư�ť
			void SetText(string Text);														// �����ı�����
			void SetVisible(bool visible);													// ���ÿɼ�
			void SetA(double a);															// ����͸����
			TextboxState GetState();														// ��ȡ״̬
			string GetID();																	// ��ȡ���
			string GetText();																// ��ȡ�ı�����

			void Appear();																	// �������ֶ�������
			void Disappear();																// ������ʧ��������

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

	// ��ʾ�ı�
	struct TiptextState {
		Point pos;							// λ��
		double w=50,h=20;					// ����
		string text="This is a tip";		// �ı�
		int dir=1;							// ����1��2��3��4��
		int wait=1000;						// �ȴ�ʱ�䣨��һ����Ҫ���̵�����ʾ��
		bool visible=false;					// �Ƿ�ɼ�
	};
	class Tiptext {
		private:
			TiptextState k;									// ��ʾ�ı�״̬

		public:
			Tiptext(Point pos,double w,int h,string text,int dir,int wait,bool visible);	// ���캯��
			void Init(Point pos,double w,int h,string text,int dir,int wait,bool visible);	// ��ʼ��
			void Update();																	// ����
			void Draw(void (*draw)(TiptextState));											// ����
			void SetVisible(bool visible);													// �����Ƿ�ɼ�

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

	// �Ի���
	class Messagebox {
		private:

		public:

	};

	// �����˵�
	struct MenuText {
		int type=1; 			// 1��ť 2�ָ��� 3�ı� 4�����˵�
		Button button;			// ��ť
		string text;			// �ı�
		Menu *menu;				// �����˵�
		int height;				// ��ǰ���Ƶ���λ��
	};
	struct MenuState {
		vector <MenuText> text;	// ����
		int ButtonHeight=30;	// ��ť�߶�
		int LineHeight=10;		// �ָ��߸߶�
		int TextHeight=30;		// �ı��߶�
		int Teams[64];			// ÿ������Ĵ�С
		int id=0;				// ���
		bool IsAppear=false;	// �Ƿ����
		bool IsFixed=false;		// �Ƿ�̶�
		bool Clicked=false;		// �Ƿ񼤻�

		Point pos;				// λ��
		double w=0,h=0;			// ��ȡ��߶�
		double drawh=0;			// ���Ƹ߶�

		// �߼���Ա
		int LastClickButton=-1;	// �ϴε����ť
		int LastClickButtonInTeam[64];// �������ϴε����ť
		void (*DrawButtonMode)(ButtonState);
		void (*DrawMenuButtonMode)(ButtonState);
		void (*DrawTextMode)(int x,int y,string text);
		void (*DrawLineMode)(int x,int y,int w);

	};

	class Menu {
		private:
			Animation DrawH;	// ���Ƹ߶�
			bool ClickDisappear=0;// ���Ե�������ʧ
			bool IsFloat=false;	// �Ƿ������ͣ
			MenuState k;		// �˵�״̬

		public:
			bool IsAppear=false;
			Menu(Point Pos,int w,int bh,int lh,int th);						// ���캯��
			void Init(Point Pos,int w,int bh,int lh,int th);				// ��ʼ��
			void Update(bool deep);											// ����
			void AddButton(string Text);									// ��Ӱ�ť
			void AddText(string Text);										// ����ı�
			void AddLine();													// ��ӷָ���
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
			};						// ��Ӹ����˵���ť
			void AddTeam();													// �����
			MenuState GetState();											// ��ȡ��ǰ״̬

			void SetDrawButtonMode(void (*draw)(ButtonState));				// ���ð�ť����ģʽ
			void SetDrawMenuButtonMode(void (*draw)(ButtonState));			// ���ò˵���ť����ģʽ
			void SetDrawTextMode(void (*draw)(int x,int y,string text));	// �����ı�����ģʽ
			void SetDrawLineMode(void (*draw)(int x,int y,int w));			// ���÷ָ��߻���ģʽ
			void SetPos(Point Pos);											// ����λ��
			void SetPos(double x,double y);									// ����λ��
			void Fix(bool fix);												// �����Ƿ�̶�
			void Draw(void (*draw)(MenuState));								// ����
			bool Float();													// ����Ƿ���ͣ
			string GetID();													// ��ȡ���

			void Appear();													// �������ֶ�������
			void Disappear();												// ������ʧ��������

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

	// �����˵���
	struct MenuListState {
		Point pos;							// λ��
		vector <Menu*> menu;				// �˵�
		vector <string> name;				// ����
		vector <int> nowx;					// ��ǰX
		vector <Button> button;				// ��ť
		map <string,Menu*> Name2Menu;		// ������ת����ť
		int ButtonWidth=50;					// ��ť���
		int Height=20;						// �߶�
		int id=0;							// ���
		int menus=0;						// �˵����������ö��߳�size()�����⣩ 
		int w=0;							// ��� 
		bool Clicked=false;					// �Ƿ��Ѽ���
	};
	class MenuList {
		private:
			MenuListState k;				// �����˵���

		public:
			MenuList(Point Pos,int buttonwidth,int height);							// ���캯��
			void Init(Point Pos,int buttonwidth,int height);						// ��ʼ��
			void AddMenu(string name,Menu* id);										// ��������˵�
			void Update();															// ����
			void Draw(void (*drawmenu)(MenuState),void (*drawbutton)(ButtonState));	// ����
			string GetID();															// ��ȡ���
			MenuListState GetState();												// ��ȡ״̬

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

	// ����
	struct InterfaceState {
		vector <Menu*> menu;
	};
	class Interface {
		private:

		public:

	};


}

#endif
