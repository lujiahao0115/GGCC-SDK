// PhysicsDebugger.h
// ggcc物理调试器

#ifndef GGCCPHYSICSDEBUGGER_H
#define GGCCPHYSICSDEBUGGER_H

#include <bits/stdc++.h>
#include <raylib.h>
#include <ggcc/physics.h>
#include <ggcc/animation.h>
using namespace std;

namespace ggcc {

	// 声明一下
	PhysicsWorld* DebuggerWorldList[64];		// 世界列表
	int DebuggerWorldSum=0;						// 世界数量
	PhysicsWorld* DebuggerWorld;				// 世界
	vector2d DebuggerCamera;					// 摄像机位置
	vector2d* DebuggerCameraP;					// 摄像机位置
	bool DebuggerCameraType=0;					// 摄像机类型
	Animation DebuggerZoom(100,100);			// 缩放比例
	PhysicsBody* LClickBody=NULL;				// 左键点击物体
	PhysicsBody* RClickBody=NULL;				// 右键点击物体
	PhysicsBody* ShowBody=NULL;					// 演示物体
	vector2d ClickSPos;							// 点击位置(屏幕位置)
	vector2d ClickBodyPos;						// 点击物体位置
    vector2d LastMousePos;                      // 上一次鼠标位置
    vector2d MousePos;                          // 鼠标位置
    vector2d MPpos;                             // 鼠标在世界中的位置
    PhysicsJointSpring MouseSpring;             // 鼠标约束
    PhysicsJointSpring FixedSpring[1005];       // 固定约束
	int GetMouseWheelMoveTime;					// 鼠标滚动时间
	int DebuggerCostTime;						// 花费时间
	Vector2 DebuggerWindowsDPI= {1,1};			// DPI
	bool DebuggerDrawPhysicsJoint=true;			// 是否绘制关节
	bool DebuggerAutoDrawing=true;				// 是否自动绘图
	bool DebuggerAutoUpdate=true;				// 是否自动更新世界
	bool DebuggerDrawAABB=false;				// 是否绘制AABB碰撞包围盒
	bool DebuggerDrawBody=true;					// 是否绘制物体
	bool DebuggerDrawCore=true;					// 是否绘制重心
	bool DebuggerDrawAxis=true;					// 是否绘制坐标轴
	bool DebuggerDrawMesh=false;				// 是否绘制网格
	bool DebuggerDrawCollision=true;			// 是否绘制碰撞
	bool DebuggerCollideEnabled=true;			// 是否允许碰撞
	string DebuggerBroadphaseAlgorithm;			// 碰撞粗检算法
	string DebuggerNarrowphaseAlgorithm;		// 碰撞粗检算法
	struct GPEUI_ListText;						// 列表字幕
	struct GPEUI_List;							// 列表
	int KeyHeight=20;							// 按钮高度
	int TextHeight=16;							// 文本高度
	int SpaceHeight=10;							// 空行高度
	int ListWidth=350;							// 列表宽度
	int ChooseWidth=200;						// 选择框宽度
	int NumberBoxWidth=35;						// 数字显示框宽度
	int SidebarHeight=25;						// 底侧栏高度
	int AddBodyBarWeigth=300;					// 添加物体栏宽度
	int BodyRadius=35;							// 物体半径
	int SpaceSize=5;							// 间隔大小
	Animation AddBodyBarSiderBar;				// 添加物体栏滚动栏动画
	bool AddBodyBarOpened=false;				// 是否打开添加物体栏
	bool ListChooseOpened=false;				// 是否打开设置的选择框
	Font font;									// 字体
	string ChooseWorldName;						// 选择世界的名称
	Animation AddBodyBarHeight;					// 添加物体框高度
	PhysicsBody SampleBody[30];					// 示例物体
	PhysicsBody DebuggerAddBody[512];			// 添加的物体
	int DebuggerAddBodySum=0;					// 添加物体数量
	double DebuggerGravity=0;					// 重力
	double DebuggerResistance=0;				// 空气阻力
	double* ChooseListNumberBar;				// 选择的数字滚动条

	void InitDebugger(string,int,int);			// 初始化调试器
	void CloseDebugger();						// 关闭调试器
	void DebugWorld(PhysicsWorld* world);		// 调试世界
	void UpdateDebugger();						// 更新调试器
	void DrawBody(PhysicsBody*);				// 绘制物体
	void SetDebuggerZoom(double zoom);			// 设置缩放比例
	void SetCameraPos(vector2d pos);			// 设置相机位置
	void SetCameraPos(vector2d* pos);			// 设置相机位置
	vector2d GetCameraPos();					// 获取相机位置
	bool MouseInRect(double,double,double,double);// 鼠标是否在矩形内
	void outtextxy(double,double,string,Color);	// 输出

	vector2d World2Screen(vector2d pos);		// 世界坐标转屏幕坐标
	vector2d Screen2World(vector2d pos);		// 屏幕坐标转世界坐标
    #define W2S World2Screen
    #define S2W Screen2World

	// 实现一下
	struct GPEUI_ListText {
		int Type=0;					// 类型
		string Text="It's a text";	// 文本
		double* Key1;				// 实数
		double Key1_max=10;			// 最大实数
		double Key1_min=0;			// 最小实数
		int* Key2;					// 整数
		bool* Key3;					// 开关
		Animation Key3_MoveAni;		// 开关移动动画
		string* Key4;				// 选择
		vector<string> Str;			// 选择内容
		Animation Key4_Angle;		// 选择的旋转动画
		Animation Key4_OpenAni;		// 选择的展开动画
		int Key4_Height;			// 选择的展开高度
		int Key4_N;					// 选择内容数量
		bool Key4_Open;				// 选择是否展开
		bool* Key5;					// 是否展开
		GPEUI_List* To;				// 展开内容
		GPEUI_List* From;			// 属于的列表

		GPEUI_ListText() {
			Key4_Angle.SetStartPos(0);
			Key4_Angle.SetTargetPos(0);
			Key3_MoveAni.SetStartPos(0);
			Key3_MoveAni.SetTargetPos(0);
			Key4_OpenAni.SetStartPos(0);
			Key4_OpenAni.SetTargetPos(0);
		}

	};
	class GPEUI_List {
		public:
			GPEUI_ListText Text[10005];	// 文本内容	
			int N=0;					// 文本数量
			bool Open=false;			// 是否展开
			int Height=0;				// 高度
			Animation HeightAni;		// 高度动画
			Animation Angle;			// 旋转动画

			GPEUI_List() {
				HeightAni.SetStartPos(0);
				Angle.SetStartPos(0);
			}
			void open() {
				Open=true;
				HeightAni.SetTargetPos(Height);
				Angle.SetTargetPos(GPE_PI/2);
			}
			void close() {
				Open=false;
				HeightAni.SetTargetPos(0);
				Angle.SetTargetPos(0);
			}
			void addText(string text) {
				Text[N].Type=0;
				Text[N].Text=text;
				N++;
				Height+=KeyHeight;
			}
			void addTitle(string text) {
				Text[N].Type=-1;
				Text[N].Text=text;
				N++;
				Height+=KeyHeight;
			}
			void addLine() {
				Text[N].Type=-2;
				N++;
				Height+=SpaceHeight;
			}
			void addSpace() {
				Text[N].Type=-3;
				N++;
				Height+=SpaceHeight;
			}
			void addChooseNumber(string text,double* num,double minn=0,double maxn=10) {
				Text[N].Type=1;
				Text[N].Text=text;
				Text[N].Key1=num;
				Text[N].Key1_max=maxn;
				Text[N].Key1_min=minn;
				N++;
				Height+=KeyHeight;
			}
			void addSwitch(string text,bool* init) {
				Text[N].Type=3;
				Text[N].Text=text;
				Text[N].Key3=init;
				N++;
				Height+=KeyHeight;
			}
			void addChoose(string text,string* t,int n,string* now) {
				Text[N].Type=4;
				Text[N].Text=text;
				for(int i=0;i<n;i++)Text[N].Str.push_back(t[i]);
				Text[N].Key4=now;
				*now=Text[N].Str[0];
				Text[N].Key4_Height=n*KeyHeight;
				Text[N].Key4_N=n;
				Text[N].Key4_Open=false;
				N++;
				Height+=KeyHeight;
			}
			void addButton(string text) {
				Text[N].Type=6;
				Text[N].Text=text;
				Height+=KeyHeight;
				N++;
			}
			void Update() {
				if(Open)HeightAni.SetTargetPos(Height);
				HeightAni.Update();
				Angle.Update();
				for(int i=0;i<N;i++)Text[i].Key4_Angle.Update();
			}

	} Settings;
	vector2d World2Screen(vector2d pos) {
		vector2d CP=GetCameraPos();
		int Ox=GetScreenWidth()/2-CP.x*DebuggerZoom.GetNowPos();
		int Oy=GetScreenHeight()/2+CP.y*DebuggerZoom.GetNowPos();
		return {Ox+pos.x*DebuggerZoom.GetNowPos(),Oy-pos.y*DebuggerZoom.GetNowPos()};
	}
	vector2d Screen2World(vector2d pos) {
		vector2d CP=GetCameraPos();
		int Ox=GetScreenWidth()/2-CP.x*DebuggerZoom.GetNowPos();
		int Oy=GetScreenHeight()/2+CP.y*DebuggerZoom.GetNowPos();
		return {(pos.x-Ox)/DebuggerZoom.GetNowPos(),-(pos.y-Oy)/DebuggerZoom.GetNowPos()};
	}
	double World2Screen(double len) {
		return len*DebuggerZoom.GetNowPos();
	}
	double Screen2World(double len) {
		return len/DebuggerZoom.GetNowPos();
	}
	bool MouseInRect(double x1,double y1,double w,double h) {
		double x2=x1+w,y2=y1+h;
		if(MousePos.x>=x1&&MousePos.x<=x2&&MousePos.y>=y1&&MousePos.y<=y2)return true;
		return false;
	}
	void outtextxy(double x,double y,string str,Color color) {
		DrawTextEx(font,str.c_str(),Vector2{x,y},TextHeight,0,color);
	}
	void SetCameraPos(vector2d pos) {
		DebuggerCameraType=0;
		DebuggerCamera=pos;
	}
	void SetCameraPos(vector2d* pos) {
		DebuggerCameraType=1;
		DebuggerCameraP=pos;
	}
	vector2d GetCameraPos() {
		if(DebuggerCameraType)return *DebuggerCameraP;
		return DebuggerCamera;
	}
	void InitDebugger(int W=860,int H=640) {
		SetConfigFlags(FLAG_MSAA_4X_HINT);
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		SetTraceLogLevel(LOG_WARNING);
		InitWindow(W,H,"GPE Debugger 1.0");
		cout<<"Successfully start GPE Debugger V1.0 by George Wang"<<endl;
		cout<<"Physics Engine : "<<GetGPEVer()<<endl;
		DebuggerWindowsDPI=GetWindowScaleDPI();
		KeyHeight*=DebuggerWindowsDPI.x;
		TextHeight*=DebuggerWindowsDPI.x;
		SpaceHeight*=DebuggerWindowsDPI.x;
		ListWidth*=DebuggerWindowsDPI.x;
		ChooseWidth*=DebuggerWindowsDPI.x;
		SidebarHeight*=DebuggerWindowsDPI.x;
		AddBodyBarWeigth*=DebuggerWindowsDPI.x;
		BodyRadius*=DebuggerWindowsDPI.x;
		NumberBoxWidth*=DebuggerWindowsDPI.x;
		SpaceSize*=DebuggerWindowsDPI.x;
		SetTargetFPS(60);
		// 动画
		AddBodyBarHeight.SetStartPos(0);
		AddBodyBarHeight.SetTargetPos(0);
		AddBodyBarSiderBar.SetStartPos(0);
		AddBodyBarSiderBar.SetTargetPos(0);
		// 字体	
		unsigned int fileSize;
		unsigned char *fontFileData = LoadFileData("C:/windows/fonts/simhei.ttf", &fileSize);
		char text[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]\\{}|;\':\",./<>?＋⊙◢〓▼◆→";
		int codepointsCount;
		int *codepoints=LoadCodepoints(text,&codepointsCount);
		font = LoadFontFromMemory(".ttf",fontFileData,fileSize,TextHeight,codepoints,codepointsCount);
		UnloadCodepoints(codepoints);
		UnloadFileData(fontFileData);
		// 示例物体
		SampleBody[0]=physicsbody::CreateCircle({0,0},1,1);
		SampleBody[1]=physicsbody::CreateBox({0,0},2.4,2.4,1);
		SampleBody[2]=physicsbody::CreatePolygon({0,0},1,3,1);
		SampleBody[3]=physicsbody::CreatePolygon({0,0},1,5,1);
		SampleBody[4]=physicsbody::CreatePolygon({0,0},1,5,1);
		SampleBody[5]=physicsbody::CreateCapsule({0,0},1,0.618,1);
		SampleBody[6]=physicsbody::CreateEdge({0,0},{1,1},1);
		SampleBody[7]=physicsbody::CreateEdgeCircle({0,0},1,1);
		SampleBody[8]=physicsbody::CreateEdgeBox({0,0},2.4,2.4,1);
		SampleBody[9]=physicsbody::CreateEdgePolygon({0,0},1,3,1);
		SampleBody[10]=physicsbody::CreateEdgePolygon({0,0},1,5,1);
		SampleBody[11]=physicsbody::CreateEdgePolygon({0,0},1,5,1);
		SampleBody[12]=physicsbody::CreateEdgeCapsule({0,0},1,0.618,1);
	}
	void CloseDebugger() {
		CloseWindow();
	}
	void DebugWorld(PhysicsWorld* world) {
		DebuggerWorldList[DebuggerWorldSum++]=world;
		DebuggerWorld=world;
		SetWindowTitle((world->Name+" - GPE Debugger 1.0").c_str());
        for(int i=0;i<=1000;i++) {
            FixedSpring[i].Remove();
        }
		// 设置
		GPEUI_ListText k;
		for(int i=0;i<Settings.N;i++)Settings.Text[i]=k;
		Settings.N=0;
		Settings.Height=0;
		Settings.addTitle("◢ Scenes");
		string t[64];
		for(int i=0;i<DebuggerWorldSum;i++)t[i]=DebuggerWorldList[i]->Name;
		Settings.addChoose("World",t,DebuggerWorldSum,&ChooseWorldName);
		Settings.addLine();
		Settings.addTitle("〓 Parameters");
		DebuggerGravity=DebuggerWorld->GetGravity();
		DebuggerResistance=DebuggerWorld->GetResistance();
		DebuggerCollideEnabled=DebuggerWorld->CollideEnabled;
		DebuggerBroadphaseAlgorithm=DebuggerWorld->BroadphaseAlgorithm;
		DebuggerNarrowphaseAlgorithm=DebuggerWorld->NarrowphaseAlgorithm;
		DebuggerWorld->Restart();
		Settings.addChooseNumber("Gravity",&DebuggerGravity,0,30);
		Settings.addChooseNumber("Resistance",&DebuggerResistance,0,30);
		Settings.addLine();
		Settings.addTitle("▼ Debug");
		Settings.addSwitch("Collide enabled",&DebuggerCollideEnabled);
		string t2[10]= {"DSAP","SAP","Violence"};
		string t3[10]= {"SAT","Minkowski"};
		Settings.addText("Collision algorithm");
		Settings.addChoose("Broad phase",t2,3,&DebuggerBroadphaseAlgorithm);
		Settings.addChoose("Narrow phase",t3,2,&DebuggerNarrowphaseAlgorithm);
		Settings.addLine();
		Settings.addTitle("◆ View");
		Settings.addSwitch("Body visable",&DebuggerDrawBody);
		Settings.addSwitch("Joint visable",&DebuggerDrawPhysicsJoint);
		Settings.addSwitch("Core visable",&DebuggerDrawCore);
		Settings.addSwitch("AABB visable",&DebuggerDrawAABB);
		Settings.addSwitch("Collision visable",&DebuggerDrawCollision);
		Settings.addSwitch("Axis visable",&DebuggerDrawAxis);
		Settings.addSwitch("Mesh visable",&DebuggerDrawMesh);
		Settings.addLine();
		Settings.addTitle("→ Timestep");
		Settings.addButton("Pause");
		Settings.addButton("Continue");
		Settings.addButton("Restart");
		Settings.addSpace();
		SetWindowMinSize((Settings.Height+SidebarHeight+SpaceHeight*3)*1.414,(Settings.Height+SidebarHeight+SpaceHeight*3));
	}
	void DrawBody(PhysicsBody* Body,vector2d pos,double R,bool choose=false,bool collided=false) {
		Color bcolors,bcolor;
		if(!Body->enabled) {
			bcolors={47,193,225,200};
			bcolor={47,193,225,50};
			if(choose)bcolor={8, 131, 216,50};
			if(collided&&DebuggerDrawCollision)bcolor={255,0,0,50},bcolors={255,0,0,200};
		} else {
			bcolors={0,255,0,200};
			bcolor={0,255,0,50};
			if(choose)bcolor={100,255,100,50};
			if(collided&&DebuggerDrawCollision)bcolor={255,0,0,50},bcolors={255,0,0,200};
		}
		PhysicsBody body=*Body;
		double zoom=R/Body->r;
		double Px=pos.x,Py=pos.y;
		if(DebuggerDrawCore) {
			// 方向
			int Rx=sin(body.Rotation)*20;
			int Ry=cos(body.Rotation)*20;
			DrawRectangle(Px-3,Py-3,6,6,bcolors);
			DrawLine(Px,Py,Px-Rx,Py+Ry,WHITE);
			DrawLine(Px,Py,Px-Ry,Py-Rx,YELLOW);
		}
		// 物体
		if(body.Shape.Flag==PHYSICSSHAPE_CIRCLE) {
			DrawCircle(Px,Py,R,bcolor);
			DrawCircleLines(Px,Py,R,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_BOX) {
			vector2d k1=vector2d {body.Shape.ShapeBox.a/2,body.Shape.ShapeBox.b/2};
			vector2d k2=vector2d {body.Shape.ShapeBox.a/2,-body.Shape.ShapeBox.b/2};
			vector2d k3=vector2d {-body.Shape.ShapeBox.a/2,-body.Shape.ShapeBox.b/2};
			vector2d k4=vector2d {-body.Shape.ShapeBox.a/2,body.Shape.ShapeBox.b/2};
			k1*=zoom,k2*=zoom,k3*=zoom,k4*=zoom;
			k1=k1.Rotate(body.Rotation);
			k2=k2.Rotate(body.Rotation);
			k3=k3.Rotate(body.Rotation);
			k4=k4.Rotate(body.Rotation);
			k1+=pos,k2+=pos,k3+=pos,k4+=pos;
			Vector2 ks[5]= {
				{(float)k1.x,(float)k1.y},
				{(float)k2.x,(float)k2.y},
				{(float)k3.x,(float)k3.y},
				{(float)k4.x,(float)k4.y},
				{(float)k1.x,(float)k1.y}
			};
			DrawTriangleFan(ks,4,bcolor);
			DrawLineStrip(ks,5,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_POLYGON) {
			Vector2 ks[64];
			for(int i=0;i<body.Shape.ShapePolygon.N;i++) {
				vector2d k;
				k=body.Shape.ShapePolygon.Point[i]*zoom;
				k=k.Rotate(-body.Rotation);
				k.y=-k.y;
				k+=pos;
				ks[i]=Vector2 {(float)k.x,(float)k.y};
			}
			ks[body.Shape.ShapePolygon.N]=ks[0];
			DrawTriangleFan(ks,body.Shape.ShapePolygon.N,bcolor);
			DrawLineStrip(ks,body.Shape.ShapePolygon.N+1,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_CAPSULE) {
			double a=Body->Shape.ShapeCapsule.a;
			double b=Body->Shape.ShapeCapsule.b;
			double len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(Body->Rotation);
			vector2d k2=vector2d{len/2,0}.Rotate(Body->Rotation);
			k1*=zoom,k2*=zoom;
			k1+=pos,k2+=pos;
			if(!choose)DrawLine(k1.x,k1.y,k2.x,k2.y,bcolors);
			else DrawLine(k1.x,k1.y,k2.x,k2.y,bcolor);
			DrawRectangle(k1.x-3,k1.y-3,6,6,bcolors);
			DrawRectangle(k2.x-3,k2.y-3,6,6,bcolors);
			DrawCircleSector(Vector2{(float)k1.x,(float)k1.y},a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A-180,0,bcolor);
			DrawCircleSector(Vector2{(float)k2.x,(float)k2.y},a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A+180,0,bcolor);
			DrawRingLines(Vector2{(float)k1.x,(float)k1.y},a/2*zoom,a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A-180,0,bcolors); 
			DrawRingLines(Vector2{(float)k2.x,(float)k2.y},a/2*zoom,a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A+180,0,bcolors); 
			vector2d temp=axisY.Rotate(Body->Rotation)*a/2*zoom;
			vector2d p1=k1+temp,p2=k2+temp,p3=k1-temp,p4=k2-temp;
			DrawLine(p1.x,p1.y,p2.x,p2.y,bcolors);
			DrawLine(p3.x,p3.y,p4.x,p4.y,bcolors);
			Vector2 ks[5]= {
				{(float)p1.x,(float)p1.y},
				{(float)p2.x,(float)p2.y},
				{(float)p4.x,(float)p4.y},
				{(float)p3.x,(float)p3.y},
				{(float)p1.x,(float)p1.y}
			};
			DrawTriangleFan(ks,4,bcolor);
		} else if(body.Shape.Flag==PHYSICSSHAPE_EDGE) {
			vector2d k1=vector2d{-body.Shape.ShapeEdge.Length/2,0}.Rotate(body.Rotation);
			vector2d k2=vector2d{body.Shape.ShapeEdge.Length/2,0}.Rotate(body.Rotation);
			k1*=zoom,k2*=zoom;
			k1+=pos,k2+=pos;
			if(!choose)DrawLine(k1.x,k1.y,k2.x,k2.y,bcolors);
			else DrawLine(k1.x,k1.y,k2.x,k2.y,bcolor);
			DrawRectangle(k1.x-3,k1.y-3,6,6,bcolors);
			DrawRectangle(k2.x-3,k2.y-3,6,6,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_EDGECIRCLE) {
			DrawCircleLines(Px,Py,R,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_EDGEBOX) {
			vector2d k1=vector2d {body.Shape.ShapeEdgeBox.a/2,body.Shape.ShapeEdgeBox.b/2};
			vector2d k2=vector2d {body.Shape.ShapeEdgeBox.a/2,-body.Shape.ShapeEdgeBox.b/2};
			vector2d k3=vector2d {-body.Shape.ShapeEdgeBox.a/2,-body.Shape.ShapeEdgeBox.b/2};
			vector2d k4=vector2d {-body.Shape.ShapeEdgeBox.a/2,body.Shape.ShapeEdgeBox.b/2};
			k1*=zoom,k2*=zoom,k3*=zoom,k4*=zoom;
			k1=k1.Rotate(body.Rotation);
			k2=k2.Rotate(body.Rotation);
			k3=k3.Rotate(body.Rotation);
			k4=k4.Rotate(body.Rotation);
			k1+=pos,k2+=pos,k3+=pos,k4+=pos;
			Vector2 ks[5]= {
				{(float)k1.x,(float)k1.y},
				{(float)k2.x,(float)k2.y},
				{(float)k3.x,(float)k3.y},
				{(float)k4.x,(float)k4.y},
				{(float)k1.x,(float)k1.y}
			};
			DrawLineStrip(ks,5,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_EDGEPOLYGON) {
			Vector2 ks[64];
			for(int i=0;i<body.Shape.ShapeEdgePolygon.N;i++) {
				vector2d k;
				k=body.Shape.ShapeEdgePolygon.Point[i]*zoom;
				k=k.Rotate(-body.Rotation);
				k.y=-k.y;
				k+=pos;
				ks[i]=Vector2 {(float)k.x,(float)k.y};
			}
			ks[body.Shape.ShapeEdgePolygon.N]=ks[0];
			DrawLineStrip(ks,body.Shape.ShapeEdgePolygon.N+1,bcolors);
		} else if(body.Shape.Flag==PHYSICSSHAPE_EDGECAPSULE) {
			double a=Body->Shape.ShapeEdgeCapsule.a;
			double b=Body->Shape.ShapeEdgeCapsule.b;
			double len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(Body->Rotation);
			vector2d k2=vector2d{len/2,0}.Rotate(Body->Rotation);
			k1*=zoom,k2*=zoom;
			k1+=pos,k2+=pos;
			if(!choose)DrawLine(k1.x,k1.y,k2.x,k2.y,bcolors);
			else DrawLine(k1.x,k1.y,k2.x,k2.y,bcolor);
			DrawRectangle(k1.x-3,k1.y-3,6,6,bcolors);
			DrawRectangle(k2.x-3,k2.y-3,6,6,bcolors);
			DrawRingLines(Vector2{(float)k1.x,(float)k1.y},a/2*zoom,a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A-180,0,bcolors); 
			DrawRingLines(Vector2{(float)k2.x,(float)k2.y},a/2*zoom,a/2*zoom,-Body->Rotation*R2A,-Body->Rotation*R2A+180,0,bcolors); 
			vector2d temp=axisY.Rotate(Body->Rotation)*a/2*zoom;
			vector2d p1=k1+temp,p2=k2+temp,p3=k1-temp,p4=k2-temp;
			DrawLine(p1.x,p1.y,p2.x,p2.y,bcolors);
			DrawLine(p3.x,p3.y,p4.x,p4.y,bcolors);
		}  else if(body.Shape.Flag==PHYSICSSHAPE_EDGECHAIN) {
			Vector2 ks[64];
			for(int i=0;i<body.Shape.ShapeEdgeChain.N;i++) {
				vector2d k;
				k=body.Shape.ShapeEdgeChain.Point[i]*zoom;
				k=k.Rotate(-body.Rotation);
				k.y=-k.y;
				k+=pos;
				ks[i]=Vector2 {(float)k.x,(float)k.y};
			}
			DrawLineStrip(ks,body.Shape.ShapeEdgeChain.N,bcolors);
		}
	}
	void UpdateDebugger() {
		// 更新调试器
		if(!WindowShouldClose()) {
			// 更新世界
			if(DebuggerAutoUpdate)DebuggerWorld->Update();
			// 更新窗口
			int winW=GetScreenWidth();
			int winH=GetScreenHeight();
			if(DebuggerAutoDrawing) {
				BeginDrawing();
				ClearBackground(Color {39, 39, 39});
			}
			// 初始化
			PhysicsBody* ChooseBody=NULL;
			int Clock=clock();
			Vector2 d=DebuggerWindowsDPI;
			DebuggerZoom.Update();
			double fps=GetFPS();
			// 坐标系
			vector2d CP=GetCameraPos();
			double Ox=GetScreenWidth()/2-CP.x*DebuggerZoom.GetNowPos();
			double Oy=GetScreenHeight()/2+CP.y*DebuggerZoom.GetNowPos();
			MousePos=vector2d {(double)GetMouseX(),(double)GetMouseY()};
			MPpos=S2W(MousePos);
			double MPx=MPpos.x;
			double MPy=MPpos.y;
			if(DebuggerDrawAxis) {
				DrawRectangle(Ox-5,Oy-5,10,10,Color {200,200,200,200});
				DrawRectangle(MousePos.x-3,MousePos.y-3,6,6,YELLOW);
				DrawLine(Ox,0,Ox,GetScreenHeight(),Color {170,170,170,200});
				DrawLine(0,Oy,GetScreenWidth(),Oy,Color {170,170,170,200});
			}
			// 绘制物体
			if(DebuggerDrawBody) {
				for(int i=0; i<DebuggerWorld->GetBodyCount(); i++) {
					PhysicsBody* body=DebuggerWorld->Body[i];
					int Px=Ox+body->Core.x*DebuggerZoom.GetNowPos();
					int Py=Oy-body->Core.y*DebuggerZoom.GetNowPos();
					int R=body->r*DebuggerZoom.GetNowPos();
					vector2d p1={0,(double)winH},p2={(double)winW,0};
					p1=S2W(p1),p2=S2W(p2);
					aabb AABB;
					AABB.Minp=p1;
					AABB.Maxp=p2;
					body->AABB.CalcAABB(body);
					if(!collision::broadphase::AABB_Collide(AABB,body->AABB).IsCollided)continue;
					bool c=false;
					if(DebuggerWorld->BroadCollidePara.IsCollided[body])c=true;
					if(body->PointInBody(vector2d {MPx,MPy},S2W(15))) {
						ChooseBody=body;
						DrawBody(body,W2S(body->Core),body->r*DebuggerZoom.GetNowPos(),true,c);
					} else {
						DrawBody(body,W2S(body->Core),body->r*DebuggerZoom.GetNowPos(),false,c);
					}
					// AABB碰撞盒
					if(DebuggerDrawAABB) {
						vector2d p1=W2S(body->AABB.Minp);
						vector2d p2=W2S(body->AABB.Maxp);
						DrawRectangleLines(p1.x,p2.y,p2.x-p1.x,p1.y-p2.y,Color {47,193,225,200});
					}
				}
			}
			// 绘制关节
			if(DebuggerDrawPhysicsJoint==true) {
				for(int i=0; i<DebuggerWorld->SpringSum; i++) {
					vector2d P1=W2S(DebuggerWorld->Spring[i]->GetP1Pos());
					vector2d P2=W2S(DebuggerWorld->Spring[i]->GetP2Pos());
					DrawRectangle(P1.x-3,P1.y-3,6,6,RED);
					DrawRectangle(P2.x-3,P2.y-3,6,6,RED);
					DrawLine(P1.x,P1.y,P2.x,P2.y,Color {150,150,150,150});
				}
				for(int i=0; i<DebuggerWorld->LimitSum; i++) {
					vector2d P1=W2S(DebuggerWorld->Limit[i]->GetP1Pos());
					vector2d P2=W2S(DebuggerWorld->Limit[i]->GetP2Pos());
					DrawRectangle(P1.x-3,P1.y-3,6,6,BROWN);
					DrawRectangle(P2.x-3,P2.y-3,6,6,BROWN);
					DrawLine(P1.x,P1.y,P2.x,P2.y,Color {150,150,150,150});
				}
				for(int i=0; i<DebuggerWorld->LimitBSum; i++) {
					vector2d P1=W2S(DebuggerWorld->LimitB[i]->GetP1Pos());
					vector2d P2=W2S(DebuggerWorld->LimitB[i]->GetP2Pos());
					DrawRectangle(P1.x-3,P1.y-3,6,6,BROWN);
					DrawRectangle(P2.x-3,P2.y-3,6,6,BROWN);
					DrawLine(P1.x,P1.y,P2.x,P2.y,Color {150,150,150,150});
				}
				for(int i=0; i<DebuggerWorld->DistanceSum; i++) {
					vector2d P1=W2S(DebuggerWorld->Distance[i]->GetP1Pos());
					vector2d P2=W2S(DebuggerWorld->Distance[i]->GetP2Pos());
					DrawRectangle(P1.x-3,P1.y-3,6,6,BROWN);
					DrawRectangle(P2.x-3,P2.y-3,6,6,BROWN);
					DrawLine(P1.x,P1.y,P2.x,P2.y,Color {150,150,150,150});
					vector2d mid=((P1+P2)/2.0);
					DrawCircleLines(mid.x,mid.y,Mod(P1-P2)/2,Color {150,150,150,150});
				}
				for(int i=0; i<DebuggerWorld->AttractSum; i++) {
					vector2d P1=W2S(DebuggerWorld->Attract[i]->GetP1Pos());
					vector2d P2=W2S(DebuggerWorld->Attract[i]->GetP2Pos());
					DrawRectangle(P1.x-3,P1.y-3,6,6,BLUE);
					DrawRectangle(P2.x-3,P2.y-3,6,6,BLUE);
					DrawLine(P1.x,P1.y,P2.x,P2.y,Color {150,150,150,150});
				}
			}
			// 鼠标约束
			PhysicsBody* body=NULL;
			if(ChooseBody!=NULL)body=ChooseBody;
			if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    if(ChooseBody!=NULL) {
						if(body->enabled) {
							ClickBodyPos=body->GetPosAbs2Rel(MPpos);
							MouseSpring.SetPoint1(body,ClickBodyPos);
							MouseSpring.SetPoint2(&MPpos);
							MouseSpring.SetRestitution(body->Mass*10);
							DebuggerWorld->AddBody(&MouseSpring);
							RClickBody=ChooseBody;
						}
					}
				}
				if(RClickBody!=NULL) {
					body=RClickBody;
					// double转string
					std::ostringstream out;
					out.precision(2);
					out<<Mod(MouseSpring.GetF1().dir);
					string text=out.str();
					DrawText(("F="+text+'N').c_str(),MousePos.x+3,MousePos.y-23,20,YELLOW);
					if(IsKeyPressed(KEY_LEFT_SHIFT)) {
                        for(int i=0;i<=1000;i++) {
                            if(FixedSpring[i].IsRemove()) {
                                FixedSpring[i].SetPoint1(body,ClickBodyPos);
                                FixedSpring[i].SetPoint2(MPpos);
                                FixedSpring[i].SetRestitution(body->Mass*10);
                                DebuggerWorld->AddBody(&FixedSpring[i]);
                                break;
                            }
                        }
					}
				}
			} else {
				RClickBody=NULL;
                if(!MouseSpring.IsRemove()) {
                    MouseSpring.Remove();
                    DebuggerWorld->Update();
                }
			}
			// 鼠标拖动摄像机/拖动物体
			if((!AddBodyBarOpened||!MouseInRect(0,0,AddBodyBarWeigth+SpaceSize,AddBodyBarHeight.GetNowPos()+SpaceSize))&&
				(!Settings.Open||!MouseInRect(0,0,ListWidth+SpaceSize,Settings.HeightAni.GetNowPos()+KeyHeight+SpaceSize))&&
				!MouseInRect(SpaceSize,SpaceSize,ListWidth,KeyHeight)&&ChooseListNumberBar==NULL) {
				if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)||IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						if(ChooseBody!=NULL) {
							ShowBody=ChooseBody;
							ClickBodyPos=body->GetPosAbs2Rel(MPpos);
							LClickBody=ChooseBody;
						}
						ClickSPos=vector2d {(double)MPx,(double)MPy};
					}
					if(LClickBody!=NULL) {
						vector2d k=LClickBody->GetPosRel2Abs(ClickBodyPos);
						LClickBody->MoveToRel(ClickBodyPos,MPpos);
						LClickBody->V={0,0};
						LClickBody->W=0;
						if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
							vector2d v2=(S2W(MousePos)-S2W(LastMousePos))/(1.0/fps);
							Impulse I;
							I.SetPointR(LClickBody,ClickBodyPos);
							I.dir=v2*LClickBody->Mass;
							LClickBody->AddImpulse(I);
						}
					} else if(DebuggerCameraType==0) {
						DebuggerCamera-= {MPx-ClickSPos.x,MPy-ClickSPos.y};
					}
				} else {
					LClickBody=NULL;
				}
			}
			// 缩放
			if((!AddBodyBarOpened||!MouseInRect(SpaceSize,SpaceSize,AddBodyBarWeigth,AddBodyBarHeight.GetNowPos()))) {
				if(GetMouseWheelMove()>0)DebuggerZoom.SetTargetPos(DebuggerZoom.GetTargetPos()*(1+GetMouseWheelMove()*GetMouseWheelMove()/5.0));
				else DebuggerZoom.SetTargetPos(DebuggerZoom.GetTargetPos()*(1-GetMouseWheelMove()*GetMouseWheelMove()/5.0));
				if(DebuggerZoom.GetTargetPos()>10000)DebuggerZoom.SetTargetPos(10000);
				else if(DebuggerZoom.GetTargetPos()<0.1)DebuggerZoom.SetTargetPos(0.1);
				if(GetMouseWheelMove())GetMouseWheelMoveTime=clock();
			}
			if(clock()-GetMouseWheelMoveTime<700) {
				int a=128;
				if(clock()-GetMouseWheelMoveTime>500)a=a*(700-clock()+GetMouseWheelMoveTime)/200.0;
				int sw=GetScreenWidth();
				int sh=GetScreenHeight();
				DrawRectangleRounded(
				    Rectangle {float(sw/2-100),float(sh/3-20),float(200),float(40)},
				    0.5,0,
				    Color {32,32,32,(unsigned char)(a*1.5)}
				);
				DrawRectangleRoundedLines(
				    Rectangle {float(sw/2-100),float(sh/3-20),float(200),float(40)},
				    0.5,0,0,
				    Color {29,29,29,(unsigned char)(a*1.9)}
				);
				std::ostringstream out;
				out<<int(int(DebuggerZoom.GetNowPos()));
				string text=out.str()+"%";
				DrawTextEx(font,text.c_str(),{sw/2-MeasureText(text.c_str(),TextHeight)/2,sh/3-TextHeight/2},TextHeight,0,Color {255,255,255,(unsigned char)(a*1.9)});
			}
			// 时间
			// std::ostringstream out,out2,out3;
			// out<<int(DebuggerWorld->GetTime()/1000);
			// string text=out.str();
			// DrawText(("Time "+text+" s").c_str(),0,0,20,WHITE);
			// out2<<int(DebuggerWorld->CostTime);
			// text=out2.str();
			// DrawText(("Physics Cost "+text+" ms").c_str(),0,20,20,WHITE);
			// out3<<int(DebuggerCostTime);
			// text=out3.str();
			// DrawText(("Debugger Cost "+text+" ms").c_str(),0,40,20,WHITE);
			// 帧速
			// DrawFPS(0,GetScreenHeight()-20);
			// 鼠标
			// DrawText(("Mouse "+to_string(MPpos)).c_str(),0,GetScreenHeight()-40,20,Color {255,255,255,100});
			// 方向键移动摄像机
			if(DebuggerCameraType==0) {
				if(IsKeyDown(KEY_UP))DebuggerCamera.y+=10.0/DebuggerZoom.GetNowPos();
				if(IsKeyDown(KEY_DOWN))DebuggerCamera.y-=10.0/DebuggerZoom.GetNowPos();
				if(IsKeyDown(KEY_LEFT))DebuggerCamera.x-=10.0/DebuggerZoom.GetNowPos();
				if(IsKeyDown(KEY_RIGHT))DebuggerCamera.x+=10.0/DebuggerZoom.GetNowPos();
			}
			// 绘制物体详细信息
			if(ShowBody!=NULL) {
				body=ShowBody;
				int sw=GetScreenWidth();
				int sh=GetScreenHeight();
				int px=sw-120,py=120,zoom=100/body->r;
				DrawBody(body,vector2d{(double)px,(double)py},body->r*zoom);
				DrawText(("Pos    "+to_string(body->Core)).c_str(),sw-240,260,20,Color {255,255,255,100});
				DrawText(("Speed  "+to_string(body->GetV())).c_str(),sw-240,280,20,Color {255,255,255,100});
				DrawText(("SpeedA "+to_string(body->VA)).c_str(),sw-240,300,20,Color {255,255,255,100});
				DrawText(("AABB1  "+to_string(body->AABB.Minp)).c_str(),sw-240,320,20,Color {255,255,255,100});
				DrawText(("AABB2  "+to_string(body->AABB.Maxp)).c_str(),sw-240,340,20,Color {255,255,255,100});
			}
			// 绘制设置
			Settings.Update();
			int DrawY=SpaceSize;
			int DrawX=SpaceSize;
			int TempH=(KeyHeight-TextHeight)/2;
			DrawRectangle(DrawX,DrawY,ListWidth,KeyHeight,Color {43, 74, 121,255});
			outtextxy(DrawX+TempH,DrawY+TempH,"⊙ Settings",WHITE);
			vector2d k1=vector2d{-TextHeight/4*0.8,-TextHeight/2*0.8};
			vector2d k2=vector2d{TextHeight/4*0.8,0};
			vector2d k3=vector2d{-TextHeight/4*0.8,TextHeight/2*0.8};
			vector2d p1=k1.Rotate(Settings.Angle.GetNowPos());
			vector2d p2=k2.Rotate(Settings.Angle.GetNowPos());
			vector2d p3=k3.Rotate(Settings.Angle.GetNowPos());
			int TempX=DrawX+ListWidth-KeyHeight/2;
			int TempY=DrawY+KeyHeight/2;
			DrawLine(p1.x+TempX,p1.y+TempY,p2.x+TempX,p2.y+TempY,LIGHTGRAY);
			DrawLine(p2.x+TempX,p2.y+TempY,p3.x+TempX,p3.y+TempY,LIGHTGRAY);
			if(MouseInRect(DrawX,DrawY,ListWidth,KeyHeight)) {
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!AddBodyBarOpened) {
					if(!Settings.Open)Settings.open();
					else Settings.close();
				}
				DrawRectangle(TempX-KeyHeight/2,TempY-KeyHeight/2,KeyHeight,KeyHeight,Color {32,32,32,50});
			}
			if(Settings.HeightAni.GetNowPos()>1) {
				BeginScissorMode(DrawX,DrawY+KeyHeight,ListWidth,Settings.HeightAni.GetNowPos());
				DrawY=Settings.HeightAni.GetNowPos()-Settings.Height+SpaceSize;
				DrawY+=KeyHeight;
				DrawRectangle(SpaceSize,SpaceSize+KeyHeight,ListWidth,Settings.HeightAni.GetNowPos(),Color {32,32,32,170});
				for(int i=0;i<Settings.N;i++) {
					if(Settings.Text[i].Type==0) {
						outtextxy(DrawX+TempH*3,DrawY+TempH,Settings.Text[i].Text,WHITE);
						DrawY+=KeyHeight;
					} else if(Settings.Text[i].Type==-1) {
						outtextxy(DrawX+TempH,DrawY+TempH,Settings.Text[i].Text,GRAY);
						DrawY+=KeyHeight;
					} else if(Settings.Text[i].Type==-2) {
						DrawLine(DrawX,DrawY+SpaceHeight/2,DrawX+ListWidth,DrawY+SpaceHeight/2,GRAY);
						DrawY+=SpaceHeight;
					} else if(Settings.Text[i].Type==1) {
						outtextxy(DrawX+TempH*6+ChooseWidth,DrawY+TempH,Settings.Text[i].Text,WHITE);
						DrawRectangle(DrawX+TempH*3,DrawY+KeyHeight/2-3,ChooseWidth,6,GRAY);
						DrawRectangle(DrawX+TempH*3,DrawY+KeyHeight/2-3,ChooseWidth*(*Settings.Text[i].Key1)/(Settings.Text[i].Key1_max-Settings.Text[i].Key1_min),6,Color {43,74,121,255});
						DrawRectangle(DrawX+TempH*3+ChooseWidth*(*Settings.Text[i].Key1)/(Settings.Text[i].Key1_max-Settings.Text[i].Key1_min)-TempH,DrawY+TempH,TempH*2,KeyHeight-2*TempH,Color {43,74,121,255});
						DrawRectangle(DrawX+ListWidth-TempH*3-NumberBoxWidth,DrawY+TempH/2,NumberBoxWidth,KeyHeight-TempH,LIGHTGRAY);
						std::ostringstream out;
						out<<*Settings.Text[i].Key1;
						string text=out.str();
						if(text.size()>4)text.resize(4);
						outtextxy(DrawX+ListWidth-NumberBoxWidth-TempH*2,DrawY+TempH,text,Color {43,74,121,255});
						if(MouseInRect(DrawX+TempH*3,DrawY+TempH/2,ChooseWidth,KeyHeight-TempH)&&!MouseInRect(SpaceHeight,SpaceHeight,ListWidth,KeyHeight)) {
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!ListChooseOpened&&!AddBodyBarOpened)ChooseListNumberBar=Settings.Text[i].Key1;
							DrawRectangle(DrawX+TempH*3+ChooseWidth*(*Settings.Text[i].Key1)/(Settings.Text[i].Key1_max-Settings.Text[i].Key1_min)-TempH,DrawY+TempH,TempH*2,KeyHeight-2*TempH,WHITE);
						}
						if(ChooseListNumberBar==Settings.Text[i].Key1) {
							double kx=1.0*(MousePos.x-DrawX-TempH*3)*(Settings.Text[i].Key1_max-Settings.Text[i].Key1_min)/ChooseWidth;
							if(kx<Settings.Text[i].Key1_min)kx=Settings.Text[i].Key1_min;
							if(kx>Settings.Text[i].Key1_max)kx=Settings.Text[i].Key1_max;
							(*Settings.Text[i].Key1)=kx;
							DrawRectangle(DrawX+TempH*3+ChooseWidth*(*Settings.Text[i].Key1)/(Settings.Text[i].Key1_max-Settings.Text[i].Key1_min)-TempH,DrawY+TempH,TempH*2,KeyHeight-2*TempH,WHITE);
						}
						if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))ChooseListNumberBar=NULL;
						DrawY+=KeyHeight;
					} else if(Settings.Text[i].Type==3) {
						Settings.Text[i].Key3_MoveAni.Update();
						outtextxy(DrawX+TempH*3,DrawY+TempH,Settings.Text[i].Text,WHITE);
						DrawRectangle(DrawX+ListWidth-TempH*3-NumberBoxWidth,DrawY+round(TempH*3.5),NumberBoxWidth,KeyHeight-TempH*7,GRAY);
						DrawRectangle(DrawX+ListWidth-TempH*3-NumberBoxWidth,DrawY+round(TempH*3.5),round(Settings.Text[i].Key3_MoveAni.GetNowPos()),KeyHeight-TempH*7,Color {43,74,121,255});
						DrawRectangle(DrawX+ListWidth-TempH*3-NumberBoxWidth+round(Settings.Text[i].Key3_MoveAni.GetNowPos()),DrawY+TempH,round(KeyHeight/3.5),KeyHeight-TempH*2,Color {43,74,121,255});
						if(MouseInRect(DrawX+ListWidth-TempH*3-NumberBoxWidth,DrawY+TempH,NumberBoxWidth,KeyHeight-TempH*2)&&!MouseInRect(SpaceHeight,SpaceHeight,ListWidth,KeyHeight)) {
							DrawRectangle(DrawX+ListWidth-TempH*3-NumberBoxWidth+round(Settings.Text[i].Key3_MoveAni.GetNowPos()),DrawY+TempH,round(KeyHeight/3.5),KeyHeight-TempH*2,WHITE);
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!ListChooseOpened&&!AddBodyBarOpened)*Settings.Text[i].Key3=!(*Settings.Text[i].Key3);
						}
						if(*Settings.Text[i].Key3)Settings.Text[i].Key3_MoveAni.SetTargetPos(NumberBoxWidth-KeyHeight/3.5);
						else Settings.Text[i].Key3_MoveAni.SetTargetPos(0);
						DrawY+=KeyHeight;
					} else if(Settings.Text[i].Type==4) {
						outtextxy(DrawX+TempH*6+ChooseWidth,DrawY+TempH,Settings.Text[i].Text,WHITE);
						DrawRectangle(DrawX+TempH*3,DrawY+TempH/2,ChooseWidth,KeyHeight-TempH,Color {43,74,121,255});
						outtextxy(DrawX+TempH*6,DrawY+TempH,*Settings.Text[i].Key4,WHITE);
						p1=k1.Rotate(Settings.Text[i].Key4_Angle.GetNowPos());
						p2=k2.Rotate(Settings.Text[i].Key4_Angle.GetNowPos());
						p3=k3.Rotate(Settings.Text[i].Key4_Angle.GetNowPos());
						TempX=DrawX+TempH*3+ChooseWidth-KeyHeight/2;
						TempY=DrawY+KeyHeight/2;
						DrawLine(p1.x+TempX,p1.y+TempY,p2.x+TempX,p2.y+TempY,LIGHTGRAY);
						DrawLine(p2.x+TempX,p2.y+TempY,p3.x+TempX,p3.y+TempY,LIGHTGRAY);
						if(MouseInRect(DrawX+TempH*3,DrawY+TempH/2,ChooseWidth,KeyHeight-TempH)&&!MouseInRect(SpaceHeight,SpaceHeight,ListWidth,KeyHeight)) {
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!ListChooseOpened&&!AddBodyBarOpened)Settings.Text[i].Key4_Open=true;
							DrawRectangle(TempX-KeyHeight/2,TempY-KeyHeight/2,KeyHeight,KeyHeight,Color {32,32,32,50});
						}
						if(!MouseInRect(DrawX+TempH*3,DrawY+TempH/2,ChooseWidth,KeyHeight-TempH+SpaceHeight+Settings.Text[i].Key4_Height)) {
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))Settings.Text[i].Key4_Open=false;
						}
						DrawY+=KeyHeight;
					} else if(Settings.Text[i].Type==6) {
						DrawRectangle(DrawX+TempH*4,DrawY+TempH/2,ListWidth-TempH*8,KeyHeight-TempH,Color {43, 74, 121,255});
						outtextxy(DrawX+(ListWidth-MeasureText(Settings.Text[i].Text.c_str(),TextHeight))/2,DrawY+TempH,Settings.Text[i].Text,WHITE);
						if(MouseInRect(DrawX+TempH*4,DrawY+TempH/2,ListWidth-TempH*8,KeyHeight-TempH)&&!MouseInRect(SpaceHeight,SpaceHeight,ListWidth,KeyHeight)) {
							if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!ListChooseOpened&&!AddBodyBarOpened) {
								if(Settings.Text[i].Text=="Pause")DebuggerWorld->Pause();
								if(Settings.Text[i].Text=="Continue")DebuggerWorld->Continue();
								if(Settings.Text[i].Text=="Restart") {
									for(int i=0;i<=1000;i++) {
										FixedSpring[i].Remove();
									}
									DebuggerWorld->Restart();
								}
							}
							DrawRectangle(DrawX+TempH*4,DrawY+TempH/2,ListWidth-TempH*8,KeyHeight-TempH,Color {32,32,32,50});
						}
						DrawY+=KeyHeight;
					}
				}
				EndScissorMode();
				DrawY=Settings.HeightAni.GetNowPos()-Settings.Height+SpaceSize;
				DrawY+=KeyHeight;
				ListChooseOpened=false;
				for(int i=0;i<Settings.N;i++) {
					if(Settings.Text[i].Type==4) {
						Settings.Text[i].Key4_OpenAni.Update();
						Settings.Text[i].Key4_Angle.Update();
						if(Settings.Text[i].Key4_Open) {
							ListChooseOpened=true;
							Settings.Text[i].Key4_Angle.SetTargetPos(GPE_PI/2);
							Settings.Text[i].Key4_OpenAni.SetTargetPos(Settings.Text[i].Key4_Height);
							Settings.Text[i].Key4_Open=true;
						} else {
							Settings.Text[i].Key4_Angle.SetTargetPos(0);
							Settings.Text[i].Key4_OpenAni.SetTargetPos(0);
							Settings.Text[i].Key4_Open=false;
						}
						if(Settings.Text[i].Key4_OpenAni.GetNowPos()>1) {
							int TDrawX=DrawX+TempH*3,TDrawY=DrawY+KeyHeight;
							BeginScissorMode(TDrawX,TDrawY,ChooseWidth,Settings.Text[i].Key4_OpenAni.GetNowPos());
							DrawRectangle(TDrawX,TDrawY,ChooseWidth,Settings.Text[i].Key4_OpenAni.GetNowPos(),Color {43, 74, 121,230});
							for(int j=0;j<Settings.Text[i].Key4_N;j++) {
								outtextxy(TDrawX+TempH*3,TDrawY+TempH,Settings.Text[i].Str[j],WHITE);
								if(MouseInRect(TDrawX,TDrawY,ChooseWidth,KeyHeight)) {
									if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!AddBodyBarOpened) {
										*Settings.Text[i].Key4=Settings.Text[i].Str[j];
										Settings.Text[i].Key4_Angle.SetTargetPos(0);
										Settings.Text[i].Key4_OpenAni.SetTargetPos(0);
										Settings.Text[i].Key4_Open=false;
									}
									DrawRectangle(TDrawX,TDrawY,ChooseWidth,KeyHeight,Color {32,32,32,50});
								}
								TDrawY+=KeyHeight;
							}
							EndScissorMode();
						}
					}
					if(Settings.Text[i].Type==-2)DrawY+=SpaceHeight;
					else DrawY+=KeyHeight;
				}
			}
			DebuggerWorld->SetGravity(DebuggerGravity);
			DebuggerWorld->SetResistance(DebuggerResistance);
			DebuggerWorld->CollideEnabled=DebuggerCollideEnabled;
			DebuggerWorld->BroadphaseAlgorithm=DebuggerBroadphaseAlgorithm;
			DebuggerWorld->NarrowphaseAlgorithm=DebuggerNarrowphaseAlgorithm;
			// 底侧栏
			AddBodyBarHeight.Update();
			AddBodyBarSiderBar.Update();
			DrawRectangle(0,winH-SidebarHeight,winW,winH,Color {32,32,32,255});
			DrawY=winH-SidebarHeight-SpaceSize;
			DrawX=SpaceSize;
			DrawRectangle(DrawX,DrawY-AddBodyBarHeight.GetNowPos(),AddBodyBarWeigth,AddBodyBarHeight.GetNowPos(),Color {32,32,32,230});
			DrawLine(0,winH-SidebarHeight,winW,winH-SidebarHeight,Color {29, 29, 29,255});
			TempH=(SidebarHeight-TextHeight)/2;
			outtextxy(TextHeight/2,winH-SidebarHeight+TempH,"＋ Add body",WHITE);
			if(MouseInRect(0,winH-SidebarHeight,TextHeight*6,SidebarHeight)) {
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					AddBodyBarHeight.SetTargetPos(winH-SidebarHeight-SpaceSize*2);
					AddBodyBarOpened=true;
					AddBodyBarSiderBar.SetStartPos(-winH*SpaceSize);
					AddBodyBarSiderBar.SetTargetPos(0);
				}
				DrawRectangle(0,winH-SidebarHeight,TextHeight*7,SidebarHeight,Color {43, 74, 121,50});
			} else {
				if(MouseInRect(DrawX,DrawY-AddBodyBarHeight.GetNowPos(),AddBodyBarWeigth,AddBodyBarHeight.GetNowPos())) {
					AddBodyBarSiderBar.SetTargetPos(AddBodyBarSiderBar.GetTargetPos()-GetMouseWheelMove()*150);
					if(AddBodyBarSiderBar.GetTargetPos()<-winH/3)AddBodyBarSiderBar.SetTargetPos(-winH/3);
					if(AddBodyBarSiderBar.GetTargetPos()>13*BodyRadius*2.4-winH*2/3)AddBodyBarSiderBar.SetTargetPos(13*BodyRadius*2.4-winH*2/3);
				}
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					if(!MouseInRect(DrawX,DrawY-AddBodyBarHeight.GetNowPos(),AddBodyBarWeigth,AddBodyBarHeight.GetNowPos())) {
						AddBodyBarHeight.SetTargetPos(0);
						AddBodyBarOpened=false;
						AddBodyBarSiderBar.SetTargetPos(AddBodyBarSiderBar.GetTargetPos()-winH);
					}
				}
			}
			if(AddBodyBarHeight.GetNowPos()>1) {
				if(AddBodyBarOpened)AddBodyBarHeight.SetTargetPos(winH-SidebarHeight-SpaceSize*2);
				string text[30] {
					"Circle",
					"Rectangle",
					"Triangle",
					"Polygon (regular)",
					"Polygon (common)",
					"Capsule",
					"Edge",
					"Edge Circle",
					"Edge Rectangle",
					"Edge Triangle",
					"Edge Polygon (regular)",
					"Edge Polygon (common)",
					"Edge Capsule",
					"Edge Chain",
					"Bezier (2 points)",
					"Bezier (3 points)",
					"Bezier (n points)",
				};
				BeginScissorMode(DrawX,DrawY-AddBodyBarHeight.GetNowPos(),AddBodyBarWeigth,AddBodyBarHeight.GetNowPos());
				int SiderBarY=AddBodyBarSiderBar.GetNowPos();
				int ChooseShape=(MousePos.y+SiderBarY)/BodyRadius/2.4;
				for(int i=0;i<=12;i++) {
					DrawBody(&SampleBody[i],{DrawX+BodyRadius*1.2,SpaceSize+i*BodyRadius*2.4+BodyRadius*1.2-SiderBarY},BodyRadius);
					outtextxy(DrawX+BodyRadius*2.4,SpaceSize+i*BodyRadius*2.4+BodyRadius*0.6-SiderBarY,text[i],WHITE);
					outtextxy(DrawX+BodyRadius*2.4,SpaceSize+i*BodyRadius*2.4+BodyRadius*0.6+KeyHeight-SiderBarY,"Create body : "+text[i],GRAY);
					if(i==ChooseShape&&MousePos.x>=DrawX&&MousePos.x<=DrawX+AddBodyBarWeigth) {
						DrawRectangle(DrawX,SpaceSize+i*BodyRadius*2.4-SiderBarY,AddBodyBarWeigth,BodyRadius*2.4,Color {43, 74, 121,50});
						if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
							DebuggerAddBody[DebuggerAddBodySum]=SampleBody[i];
							DebuggerWorld->AddBody(&DebuggerAddBody[DebuggerAddBodySum]);
							DebuggerAddBodySum++;
						}
					}
				}
				EndScissorMode();
			}
			// 更新选择世界
			if(ChooseWorldName!=DebuggerWorld->Name) {
				for(int i=0;i<DebuggerWorldSum;i++)if(ChooseWorldName==DebuggerWorldList[i]->Name) {
					DebuggerWorld=DebuggerWorldList[i];
					DebuggerGravity=DebuggerWorld->GetGravity();
					DebuggerResistance=DebuggerWorld->GetResistance();
					DebuggerCollideEnabled=DebuggerWorld->CollideEnabled;
					DebuggerBroadphaseAlgorithm=DebuggerWorld->BroadphaseAlgorithm;
					DebuggerNarrowphaseAlgorithm=DebuggerWorld->NarrowphaseAlgorithm;
					DebuggerWorld->Restart();
				}
			}
			// 更新时间
			DebuggerCostTime=clock()-Clock;
			LastMousePos=MousePos;

			if(DebuggerAutoDrawing)EndDrawing();
		} else {
			CloseDebugger();
		}
	}
	void SetDebuggerZoom(double zoom) {
		DebuggerZoom.SetTargetPos(zoom);
	}

}

#endif
