// physics.h
// ggcc二维刚体物理引擎

#ifndef GGCCPHYSICS_H
#define GGCCPHYSICS_H

#include <bits/stdc++.h>
#include <ggcc/math/point.h>

// 以下是当前版本:
#define GPE_VER "GPE 0.1.4 [2023.1.17]"

using namespace std;

#ifndef __GGCCMATHPOINT_H__
#define __GGCCMATHPOINT_H__

//#define real long double

#endif

namespace ggcc {

	// 宏定义
	#define PHYSICSSHAPE_CIRCLE			1	// 圆 
	#define PHYSICSSHAPE_BOX			2	// 矩形 
	#define PHYSICSSHAPE_POLYGON		3	// 多边形 
	#define PHYSICSSHAPE_CAPSULE		4	// 胶囊形
	#define PHYSICSSHAPE_EDGE			5	// 线段 
	#define PHYSICSSHAPE_EDGECIRCLE		6	// 空心圆 
	#define PHYSICSSHAPE_EDGEBOX		7	// 空心矩形 
	#define PHYSICSSHAPE_EDGEPOLYGON	8	// 空心多边形 
	#define PHYSICSSHAPE_EDGECAPSULE	9	// 胶囊形
	#define PHYSICSSHAPE_EDGECHAIN		10	// 线段组 
	#define PHYSICSSHAPE_PARTICLE		11	// 粒子 

	#define GPE_PI		3.1415926535897932	// 圆周率
	#define BODY_MAXN				 10005	// 最大物体数量
	#define FORCE_MAXN				  1024	// 最大受力数量
	#define POLYGON_EDGE_MAXN			64	// 多边形最大边数
	#define EDGECHAIN_EDGE_MAXN		  1024	// 线段组最大边数
	
	#define R2A 57.295779513082320876798154814105
	#define A2R 0.01745329251994329576923690768489
	#define GPE_EPT 1e-10

	// 声明一下
	class PhysicsBody;				// 物理物体
	class PhysicsWorld; 			// 物理世界
	class Force;					// 力
	class Impulse;					// 冲量

	class PhysicsJoint;				// 关节
	class PhysicsJointSpring;		// 弹簧关节
	class PhysicsJointLimit;		// 限制关节
	class PhysicsJointLimitB;		// 反向限制关节
	class PhysicsJointDistance;		// 固定距离关节
	class PhysicsJointPin;			// 固定关节
	class PhysicsJointAttract;		// 吸引关节
	class PhysicsJointRepel;		// 排斥关节

	class PhysicsShape;				// 形状
	class PhysicsShapeCircle;		// 圆
	class PhysicsShapeBox;			// 矩形
	class PhysicsShapePolygon;		// 多边形
	class PhysicsShapeCapsule;		// 胶囊形
	class PhysicsShapeEdge;			// 线段
	class PhysicsShapeEdgeCircle;	// 空心圆
	class PhysicsShapeEdgeBox;		// 空心矩形
	class PhysicsShapeEdgePolygon;	// 空心多边形
	class PhysicsShapeEdgeCapsule;	// 空心胶囊形
	class PhysicsShapeEdgeChain;	// 线段组
	class PhysicsShapeParticle;		// 粒子

	class PhysicsMaterial;			// 材质
	class PathRecorder;				// 路径记录器

	class aabb;						// AABB碰撞盒

	int IDS=0;						// 物体数量

	// 再声明一下
	class Impulse {						// 冲量
		public:
			vector2d epoint;			// 作用点
			vector2d* epointP;			// 作用点指针
			PhysicsBody* epointBody;	// 作用物体
			short epointType=0;			// 作用点类型
			vector2d dir;				// 方向
			bool IsDel=false;			// 是否被删除

			Impulse(vector2d,vector2d); // 构造函数
			Impulse(vector2d*,vector2d); // 构造函数
			void Del(bool);				// 删除
			// 设置作用点
			void SetPoint(vector2d);
			void SetPoint(PhysicsBody*,vector2d);
			void SetPoint(vector2d*,vector2d);
			void SetPoint(PhysicsBody*,vector2d*,vector2d);
			void SetPointR(PhysicsBody*,vector2d);
			vector2d GetPoint();		// 获取作用点
			void operator =(const Impulse &a);
			void operator +=(const Impulse &a);
			void operator -=(const Impulse&a);
			void operator *=(const real &a);
			void operator /=(const real &a);
	};
	class Force {						// 力
		public:
			vector2d epoint;			// 作用点
			vector2d* epointP;			// 作用点指针
			PhysicsBody* epointBody;	// 作用物体
			short epointType=0;			// 作用点类型
			vector2d dir;				// 方向
			bool IsDel=false;			// 是否被删除

			Force(vector2d,vector2d); 	// 构造函数
			Force(vector2d*,vector2d); 	// 构造函数
			void Del(bool);				// 删除
			// 设置作用点
			void SetPoint(vector2d);
			void SetPoint(PhysicsBody*,vector2d);
			void SetPoint(vector2d*,vector2d);
			void SetPoint(PhysicsBody*,vector2d*,vector2d);
			void SetPointR(PhysicsBody*,vector2d);
			vector2d GetPoint();		// 获取作用点
			void operator =(const Force &a);
			void operator +=(const Force &a);
			void operator -=(const Force &a);
			void operator *=(const real &a);
			void operator /=(const real &a);
	};
	// 图形
	class PhysicsShapeCircle {			// 圆
		public:
			real Radius;				// 半径
			PhysicsShapeCircle(real);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径

	};
	class PhysicsShapeBox {				// 矩形
		public:
			real a,b;					// 长、宽
			PhysicsShapeBox(real,real);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
	};
	class PhysicsShapePolygon {			// 多边形
		public:
			int N=0;					// 顶点数
			vector2d Point[POLYGON_EDGE_MAXN];// 顶点
			PhysicsShapePolygon(int);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
			vector2d ToOrigin();		// 移动到原点

	};
	class PhysicsShapeCapsule {			// 胶囊形
		public:
			real a,b;					// 外接矩形的长、宽
			PhysicsShapeCapsule(real,real);// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径

	};
	class PhysicsShapeEdge {			// 线段
		public:
			real Length;				// 长度
			PhysicsShapeEdge(real);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
	};
	class PhysicsShapeEdgeCircle {		// 空心圆
		public:
			real Radius;				// 半径
			PhysicsShapeEdgeCircle(real);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径

	};
	class PhysicsShapeEdgeBox {			// 空心矩形
		public:
			real a,b;					// 长、宽
			PhysicsShapeEdgeBox(real,real);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
	};
	class PhysicsShapeEdgePolygon {		// 多边形
		public:
			int N=0;					// 顶点数
			vector2d Point[POLYGON_EDGE_MAXN];// 顶点
			PhysicsShapeEdgePolygon(int);// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
			vector2d ToOrigin();		// 移动到原点

	};
	class PhysicsShapeEdgeCapsule {		// 空心胶囊形
		public:
			real a,b;					// 外接矩形的长、宽
			PhysicsShapeEdgeCapsule(real,real);// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径

	};
	class PhysicsShapeEdgeChain {		// 线段组
		public:
			int N=0;					// 顶点数
			vector2d Point[EDGECHAIN_EDGE_MAXN];// 顶点
			PhysicsShapeEdgeChain(int);	// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径
			vector2d ToOrigin();		// 移动到原点

	};
	class PhysicsShapeParticle {		// 粒子
		public:
			PhysicsShapeParticle();		// 构造函数
			vector2d GetCore();			// 获取重心
			real GetArea();			// 获取面积
			real GetRadius();			// 获取半径

	};
	class aabb {						// AABB碰撞盒
		public:
			vector2d Minp;				// 最小点
			vector2d Maxp;				// 最大点
			void CalcAABB(PhysicsBody*);// 计算碰撞盒	

	};
	class PhysicsJoint {				// 物理关节
	};
	class PhysicsShape {								// 物理形状
		public:
			short Flag=0;								// 形状标记
			PhysicsShapeCircle ShapeCircle;				// 圆
			PhysicsShapeBox ShapeBox;					// 矩形
			PhysicsShapePolygon ShapePolygon;			// 多边形
			PhysicsShapeCapsule ShapeCapsule;			// 胶囊形
			PhysicsShapeEdge ShapeEdge;					// 线段
			PhysicsShapeEdgeCircle ShapeEdgeCircle;		// 空心圆
			PhysicsShapeEdgeBox ShapeEdgeBox;			// 空心矩形
			PhysicsShapeEdgePolygon ShapeEdgePolygon;	// 空心多边形
			PhysicsShapeEdgeCapsule ShapeEdgeCapsule;	// 胶囊形
			PhysicsShapeEdgeChain ShapeEdgeChain;		// 线段组
			PhysicsShapeParticle ShapeParticle;			// 粒子

			PhysicsShape();								// 构造函数
			vector2d GetCore();							// 获取重心
			real GetArea();							// 获取面积
			real GetRadius();							// 获取半径

	};
	class PhysicsMaterial {				// 物理材质
		public:
			real Density;				// 密度，用于计算物体的质量
			real Friction;			// 摩擦，用于模拟物体间的接触滑动
			real Restitution;			// 恢复系数
	};
	class PathRecorder {				// 路径记录器
		private:

		public:

	};
	class DistanceParameters;															// 距离参数
	namespace distance {
		DistanceParameters Point_Point(vector2d,vector2d);								// 两点之间的距离
		DistanceParameters Point_Line(vector2d,vector2d,vector2d);						// 点到直线的距离
		DistanceParameters Point_Ray(vector2d,vector2d,vector2d);						// 点到射线的距离
		DistanceParameters Point_Edge(vector2d,vector2d,vector2d);						// 点到线段的距离
		DistanceParameters Edge_Edge(vector2d,vector2d,vector2d,vector2d);				// 线段到线段的距离
		DistanceParameters Edge_Line(vector2d,vector2d,vector2d,vector2d);				// 线段到直线的距离
		DistanceParameters Edge_Ray(vector2d,vector2d,vector2d,vector2d);				// 线段到射线的距离
		DistanceParameters Ray_Line(vector2d,vector2d,vector2d,vector2d);				// 线段到直线的距离
		DistanceParameters Line_Line(vector2d,vector2d,vector2d,vector2d);				// 直线到直线的距离
		DistanceParameters Point_Circle(vector2d,vector2d,vector2d,vector2d);			// 点到圆的距离
		DistanceParameters Point_Box(vector2d,vector2d,vector2d);						// 点到矩形的距离
		DistanceParameters Point_Polgon(vector2d,vector2d,vector2d,vector2d);			// 点到多边形的距离
		DistanceParameters Point_Capsule(vector2d,vector2d,vector2d,vector2d);			// 点到胶囊形的距离
		DistanceParameters Edge_Circle(vector2d,vector2d,vector2d,vector2d);			// 线段到圆的距离
		DistanceParameters Edge_Box(vector2d,vector2d,vector2d,vector2d);				// 线段到矩形的距离
		DistanceParameters Edge_Polygon(vector2d,vector2d,vector2d,vector2d);			// 线段到多边形的距离
		DistanceParameters Edge_Capsule(vector2d,vector2d,vector2d,vector2d);			// 线段到胶囊形的距离
		DistanceParameters Circle_Circle(vector2d,vector2d,vector2d,vector2d);			// 圆到圆的距离
		DistanceParameters Circle_Box(vector2d,vector2d,vector2d,vector2d);				// 圆到矩形的距离
		DistanceParameters Circle_Polygon(vector2d,vector2d,vector2d,vector2d);			// 圆到多边形的距离
		DistanceParameters Circle_Capsule(vector2d,vector2d,vector2d,vector2d);			// 圆到胶囊形的距离
		DistanceParameters Box_Box(vector2d,vector2d,vector2d,vector2d);				// 矩形到矩形的距离
		DistanceParameters Box_Polygon(vector2d,vector2d,vector2d,vector2d);			// 矩形到多边形的距离
		DistanceParameters Box_Capsule(vector2d,vector2d,vector2d,vector2d);			// 矩形到胶囊形的距离
	}
	namespace collision {				// 碰撞检测
		// 声明一下
		class CollisionParameters;		// 碰撞参数
		// 粗略碰撞检测
		namespace broadphase {
			// 粗略碰撞检测参数
			class BroadphaseParameters {				
				public:
					int CollideBodySum=0;						// 碰撞物体数量
					map<PhysicsBody*,bool> IsCollided;			// 是否出现碰撞
					vector<PhysicsBody*> CollideBody;			// 出现碰撞的物体 
					vector<CollisionParameters> CollideBodyPair;// 碰撞物体对
			};
			void AddBodyPair(BroadphaseParameters* para,PhysicsBody* body1,PhysicsBody* body2);
			// AABB碰撞盒碰撞
			class AABB_Parameters;
			AABB_Parameters AABB_Collide(aabb A,aabb B);	// AABB碰撞
			// 暴力算法 O(N^2)	10000物体：1300ms
			void Violence(PhysicsWorld* world,BroadphaseParameters* para);
			// SAP算法 O(NlogN)~O(N^2) 10000物体：100ms
			bool SAP_cmp_X(PhysicsBody* Body1,PhysicsBody* Body2);
			bool SAP_cmp_Y(PhysicsBody* Body1,PhysicsBody* Body2);
			void SAP(PhysicsWorld* world,BroadphaseParameters* para);
			// 动态SAP O(N)~O(N^2)	10000物体：25ms
			class DSAP {
				private:
					PhysicsWorld* World;						// 目标世界
					int CollideBodySum=0;						// 碰撞物体数量
					PhysicsBody* Body[BODY_MAXN];				// 物体
					bool Direction=0;							// 计算方向

				public:
					void Init(PhysicsWorld*);					// 初始化
					void Update(BroadphaseParameters*);			// 更新
			};
			// BVH动态层次包围盒算法 O(NlogN)
			class DBVH;
		}
		// 精确碰撞检测
		namespace narrowphase {
			// 精确碰撞检测参数
			class NarrowphaseParameters {
				public:
					int CollideBodySum=0;						// 碰撞物体数量
					map<PhysicsBody*,bool> IsCollided;			// 是否出现碰撞
					vector<PhysicsBody*> CollideBody;			// 出现碰撞的物体 
					vector<CollisionParameters> CollideBodyPair;// 碰撞物体对
			};
			// 检测
			void AddBodyPair(NarrowphaseParameters* para,PhysicsBody* body1,PhysicsBody* body2,vector2d p1,vector2d p2);
			void Detect(broadphase::BroadphaseParameters* para,NarrowphaseParameters* ans);
		}
		// 碰撞约束
		namespace constraint {
			void Constraint(narrowphase::NarrowphaseParameters*);// 约束
		}
	}
	namespace query {					// 查询
		class QueryParameters;								// 查询参数
		QueryParameters QueryPoint(vector2d);				// 点查询
		QueryParameters QueryRay(vector2d,real);			// 射线查询
		QueryParameters QueryEdge(vector2d,vector2d);		// 射线查询
	}
	class PhysicsBody {					// 物理物体
		private:

		public:
			unsigned int id;            // id
			bool IsDel=false;			// 是否已经删除
			PhysicsShape Shape;			// 形状
			vector2d Core= {0,0};		// 重心
			vector2d LastCore= {0,0};	// 上一次重心位置
			bool enabled=true;    	    // 是否可动
			int PointSum=0;				// 顶点数量
			real r=1;					// 半径
			real Mass=1;				// 质量
			Force* F[FORCE_MAXN];		// 受力
			Impulse* Im[FORCE_MAXN];	// 冲量
			int ISum=0;					// 冲量数量
			Force AddF;					// 添加的力
			Impulse AddI;				// 添加的冲量
			int FSum=0;					// 受力数量
			Force sumF;					// 合力
			vector2d V= {0,0};			// 速度
			vector2d ImV= {0,0};		// 冲量提供的速度
			vector2d VA= {0,0};			// 加速度
			real Rotation=0;			// 转动弧度
			real W=0;					// 角速度
			real A=0;					// 角加速度
			real I=1;					// 转动惯量
			int LastUpdateTime=0;		// 上次更新时间
			bool ShouldMoveTo=false;	// 是否需要移动
			vector2d MoveToPos;			// 移动目标点
			PhysicsMaterial Material;	// 材质
			aabb AABB;					// AABB碰撞盒
			int ResP,GP;				// 阻力、重力下标
			void (*Script)(PhysicsBody*);// 物体脚本
			bool ScriptSet=false;		// 是否已设置脚本

			PhysicsBody();				// 构造函数
			void Update(int Clock);		// 更新
			void SetEnabled(bool);		// 设置可动性
			void LoadForce(Force* f);	// 加载力
			void DelForce(Force* f);	// 卸载力
			void LoadImpulse(Impulse *);// 加载冲量
			void AddImpulse(Impulse);	// 加冲量
			void AddImpulse(vector2d);	// 加冲量
			void DelImpulse(Impulse *);	// 卸载冲量
			void ClearForce();			// 清除添加的力
			void ClearImpulse();		// 清除添加的冲量
			void MoveTo(vector2d);		// 位移
			void MoveToAbs(vector2d,vector2d);// 位移（作用点为绝对位置）
			void MoveToRel(vector2d,vector2d);// 位移（作用点为相对位置）
			void SetScript(void (*script)(PhysicsBody*));// 设置脚本
			vector2d GetLastPos();		// 获取上一次重心位置
			vector2d GetPos();			// 获取重心位置
			vector2d GetPosRel2Abs(vector2d);// 获取位置（从相对位置转到绝对位置）
			vector2d GetPosAbs2Rel(vector2d);// 获取位置（从绝对位置转到相对位置）
			bool PointInBody(vector2d,real);// 点是否在物体上
			real GetWindwardArea();	// 获取迎风面积
			vector2d GetV(vector2d);	// 获取速度

	};
	class PhysicsWorld {				// 物理世界
		private:
			vector2d Gravity;			// 重力常数
			int BodySum=0;				// 物体数量
			int StartPauseTime=0;		// 开始暂停时间刻
			int PauseTime=0;			// 暂停时长
			bool IsPaused=true;			// 是否暂停
			bool IsStarted=false;			// 是否开始
			real Resistance=2;		// 阻尼器
			real Friction=0;			// 摩擦
			collision::broadphase::DSAP sap;// 碰撞检测

			vector<PhysicsBody> MBody;	// 记忆物体
			vector<PhysicsBody*> MBodyP;// 记忆物体地址
			int MBodySum=0;				// 物体数量
			vector<PhysicsJointSpring> MSpring;// 记忆弹簧
			vector<PhysicsJointLimit> MLimit;// 记忆限制关节
			vector<PhysicsJointLimitB> MLimitB;// 记忆反向限制关节
			vector<PhysicsJointDistance> MDistance;// 记忆固定距离关节
			vector<PhysicsJointAttract> MAttract;// 记忆吸引关节
			vector<PhysicsJointSpring*> MSpringP;// 记忆弹簧地址
			vector<PhysicsJointLimit*> MLimitP;// 记忆限制关节地址
			vector<PhysicsJointLimitB*> MLimitBP;// 记忆反向限制关节地址
			vector<PhysicsJointDistance*> MDistanceP;// 记忆固定距离关节地址
			vector<PhysicsJointAttract*> MAttractP;// 记忆吸引关节地址
			int MSpringSum=0;			// 记忆弹簧数量
			int MLimitSum=0;			// 记忆限制关节数量
			int MLimitBSum=0;			// 记忆反向限制关节数量
			int MDistanceSum=0;			// 记忆固定距离关节数量
			int MAttractSum=0;			// 记忆吸引关节数量
			Force MG[BODY_MAXN];		// 记忆物体重力
			Force MRes[BODY_MAXN];		// 记忆阻力

		public:
			vector<PhysicsBody*> Body;	// 物体
			vector<PhysicsJointSpring*> Spring;// 弹簧
			vector<PhysicsJointLimit*> Limit;// 限制关节
			vector<PhysicsJointLimitB*> LimitB;// 反向限制关节
			vector<PhysicsJointDistance*> Distance;// 固定距离关节
			vector<PhysicsJointAttract*> Attract;// 吸引关节
			int SpringSum=0;			// 弹簧数量
			int LimitSum=0;				// 限制关节数量
			int LimitBSum=0;			// 反向限制关节数量
			int DistanceSum=0;			// 固定距离关节数量
			int AttractSum=0;			// 吸引关节数量
			string BroadphaseAlgorithm="DSAP";// 碰撞粗检算法
			string NarrowphaseAlgorithm="SAT";// 碰撞精检算法
			bool CollideEnabled=true;	// 是否启动碰撞
			real CostTime;			// 模拟耗时
			Force G[BODY_MAXN];			// 物体重力
			Force Res[BODY_MAXN];		// 阻力
			string Name="Untitled";		// 世界名称
			collision::broadphase::BroadphaseParameters BroadCollidePara;	// 粗略碰撞参数
			collision::narrowphase::NarrowphaseParameters NarrowCollidePara;// 精确碰撞参数

			PhysicsWorld();				// 构造函数
			void Update();				// 更新
			void AddBody(PhysicsBody*);	// 添加物体
			void AddBody(PhysicsJointSpring*);// 添加弹簧
			void AddBody(PhysicsJointLimit*);// 添加限制关节
			void AddBody(PhysicsJointLimitB*);// 添加限制关节
			void AddBody(PhysicsJointDistance*);// 添加限制关节
			void AddBody(PhysicsJointAttract*);// 添加吸引关节
			void SetGravity(real g);	// 设置重力常数
			real GetGravity();		// 获取重力常数
			int GetBodyCount();			// 获取物体数量
			void Pause();				// 暂停
			void Continue();			// 继续
			void ChangeState();			// 更改状态
			int GetTime();				// 获取时间
			void SetResistance(real);	// 设置阻尼器
			real GetResistance();		// 获取阻尼器
			void Restart();				// 重置世界

	};
	class PhysicsJointSpring {			// 弹簧关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			vector2d* p1p;				// 作用点1指针
			vector2d* p2p;				// 作用点2指针
			short p1Type=0;				// 作用点1类型
			short p2Type=0;				// 作用点2类型
			real Length=0;			// 原长
			real Restitution1=0;		// 弹性系数（小于原长）
			real Restitution2=0;		// 弹性系数（大于原长）
			Force F1;					// 弹力1
			Force F2;					// 弹力2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointSpring();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint1(vector2d*);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetPoint2(vector2d*);	// 设置作用点2 （绝对位置）
			void SetLength(real); 	// 设置弹簧原长
			void SetRestitution(real);// 设置弹性系数
			void SetRestitution(real,real);// 设置弹性系数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			Force GetF1();				// 获取力1
			Force GetF2();				// 获取力2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointLimit {			// 限制关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Length=0;			// 原长
			real Restitution1=0;		// 弹性系数（小于原长）
			real Restitution2=0;		// 弹性系数（大于原长）
			Impulse I1;					// 冲量1
			Impulse I2;					// 冲量2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointLimit();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetLength(real); 	// 设置弹簧原长
			void SetRestitution(real);// 设置弹性系数
			void SetRestitution(real,real);// 设置弹性系数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointLimitB {			// 反向限制关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Length=0;			// 原长
			real Restitution1=0;		// 弹性系数（小于原长）
			real Restitution2=0;		// 弹性系数（大于原长）
			Impulse I1;					// 冲量1
			Impulse I2;					// 冲量2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointLimitB();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetLength(real); 	// 设置弹簧原长
			void SetRestitution(real);// 设置弹性系数
			void SetRestitution(real,real);// 设置弹性系数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointDistance {			// 反向限制关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Length=0;			// 原长
			real Restitution1=0;		// 弹性系数（小于原长）
			real Restitution2=0;		// 弹性系数（大于原长）
			Impulse I1;					// 冲量1
			Impulse I2;					// 冲量2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointDistance();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetLength(real); 	// 设置弹簧原长
			void SetRestitution(real);// 设置弹性系数
			void SetRestitution(real,real);// 设置弹性系数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointPin {				// 固定关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Length=0;			// 原长
			real Restitution1=0;		// 弹性系数（小于原长）
			real Restitution2=0;		// 弹性系数（大于原长）
			Impulse I1;					// 冲量1
			Impulse I2;					// 冲量2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointPin();			// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetLength(real); 	// 设置弹簧原长
			void SetRestitution(real);// 设置弹性系数
			void SetRestitution(real,real);// 设置弹性系数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointAttract {			// 吸引关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Gravity=1;			// 引力系数
			Force F1;					// 引力1
			Force F2;					// 引力2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointAttract();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetGravity(real);	// 设置引力常数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};
	class PhysicsJointRepel {			// 排斥关节
		private:
			PhysicsBody* body1;			// 作用物体1
			PhysicsBody* body2;			// 作用物体2
			vector2d p1;				// 作用点1
			vector2d p2;				// 作用点2
			bool p1Type=0;				// 作用点1类型
			bool p2Type=0;				// 作用点2类型
			real Gravity=1;			// 引力系数
			Force F1;					// 引力1
			Force F2;					// 引力2
			bool IsDel=false;			// 是否删除

		public:
			PhysicsJointRepel();		// 构造函数
			void Update();				// 更新
			void SetPoint1(PhysicsBody*,vector2d);// 设置作用点1 （相对位置）
			void SetPoint1(vector2d);	// 设置作用点1 （绝对位置）
			void SetPoint2(PhysicsBody*,vector2d);// 设置作用点2 （相对位置）
			void SetPoint2(vector2d);	// 设置作用点2 （绝对位置）
			void SetGravity(real);	// 设置引力常数
			vector2d GetP1Pos();		// 获取作用点1位置
			vector2d GetP2Pos();		// 获取作用点2位置
			PhysicsBody* GetP1Body();	// 获取作用物体1
			PhysicsBody* GetP2Body();	// 获取作用物体2
			void Remove(bool);			// 删除
			bool IsRemove();			// 是否删除

	};

	// 继续声明一下
	void InitPhysics();																	// 初始化二维刚体物理引擎
	void ClosePhysics();																// 关闭二维刚体物理引擎
	PhysicsBody CreatePhysicsBodyCircle(vector2d pos,real r,real mass);				// 创建物理物体（圆）
	PhysicsBody CreatePhysicsBodyBox(vector2d pos,real w,real h,real mass);		// 创建物理物体（矩形)）
	PhysicsBody CreatePhysicsBodyPolygon(vector2d pos,real r,int sides,real mass);	// 创建物理物体（正多边形）
	void DelPhysicsBody(PhysicsBody* body);												// 删除物理物体
	string GetGPEVer();																	// 获取GPE版本

	//==========实现一下============

	// 求交
	class Intersection;																// 交点参数
	Intersection SegmentsIntr(vector2d,vector2d,vector2d,vector2d);					// 求线段与线段的焦点

	class Intersection {
		public:
			bool find=false;
			vector2d point=vector2d {0,0};
	};
	namespace intersection {
		// 声明
		Intersection Edge_Edge(vector2d a,vector2d b,vector2d c,vector2d d);
		Intersection Edge_Line(vector2d a,vector2d b,vector2d c,vector2d d);
		Intersection Line_Line(vector2d a,vector2d b,vector2d c,vector2d d);
		// 实现
		Intersection Edge_Edge(vector2d a,vector2d b,vector2d c,vector2d d) {
			Intersection ans;
			// 三角形abc 面积的2倍
			real area_abc=(a.x-c.x)*(b.y-c.y)-(a.y-c.y)*(b.x-c.x);
			// 三角形abd 面积的2倍
			real area_abd=(a.x-d.x)*(b.y-d.y)-(a.y-d.y)*(b.x-d.x);
			// 面积符号相同则两点在线段同侧,不相交 (对点在线段上的情况,本例当作不相交处理);
			if(area_abc*area_abd>=0) {
				ans.find=false;
				return ans;
			}
			// 三角形cda 面积的2倍
			real area_cda=(c.x-a.x)*(d.y-a.y)-(c.y-a.y)*(d.x-a.x);
			// 三角形cdb 面积的2倍
			// 注意: 这里有一个小优化.不需要再用公式计算面积,而是通过已知的三个面积加减得出.
			real area_cdb=area_cda+area_abc-area_abd;
			if(area_cda*area_cdb>=0) {
				ans.find=false;
				return ans;
			}
			//计算交点坐标
			real t=area_cda/(area_abd-area_abc);
			real dx=t*(b.x-a.x);
			real dy=t*(b.y-a.y);
			ans.find=true;
			ans.point=vector2d {a.x+dx,a.y+dy};
			return ans;
		}
		Intersection Edge_Line(vector2d a,vector2d b,vector2d c,vector2d d) {
			Intersection ans;
			return ans;
		}
		Intersection Line_Line(vector2d a,vector2d b,vector2d c,vector2d d) {
			Intersection ans;
			return ans;
		}
	}

	// 距离求解
	class DistanceParameters {// 距离参数
		public:
			real dis;						// 距离
			vector2d p1;					// 物体1的最近点（绝对）
			vector2d p2;					// 物体2的最近点（绝对）
			vector2d p1R;					// 物体1的最近点（相对）
			vector2d p2R;					// 物体2的最近点（相对）
			void operator =(const DistanceParameters&);// 复制
	};
	// 重载输出流
	ostream& operator <<(ostream& out,const DistanceParameters& a) {
		out<<"距离参数 DistanceParameters = {"<<endl;
		out<<"    dis = "<<a.dis<<" ,"<<endl;
		out<<"    p1 = "<<a.p1<<" ,"<<endl;
		out<<"    p2 = "<<a.p2<<" ,"<<endl;
		out<<"    p1R = "<<a.p1R<<" ,"<<endl;
		out<<"    p2R = "<<a.p2R<<endl;
		out<<"}";
		return out;
	}
	// 复制
	void DistanceParameters::operator =(const DistanceParameters& b) {
		this->dis=b.dis;
		this->p1=b.p1;
		this->p2=b.p2;
		this->p1R=b.p1R;
		this->p2R=b.p2R;
	}
	namespace distance {
		// 声明
		DistanceParameters Point_Point(vector2d,vector2d);								// 两点之间的距离
		DistanceParameters Point_Line(vector2d,vector2d,vector2d);						// 点到直线的距离
		DistanceParameters Point_Ray(vector2d,vector2d,vector2d);						// 点到射线的距离
		DistanceParameters Point_Edge(vector2d,vector2d,vector2d);						// 点到线段的距离
		DistanceParameters Edge_Edge(vector2d,vector2d,vector2d,vector2d);				// 线段到线段的距离
		DistanceParameters Edge_Line(vector2d,vector2d,vector2d,vector2d);				// 线段到直线的距离
		DistanceParameters Edge_Ray(vector2d,vector2d,vector2d,vector2d);				// 线段到射线的距离
		DistanceParameters Ray_Line(vector2d,vector2d,vector2d,vector2d);				// 线段到直线的距离
		DistanceParameters Line_Line(vector2d,vector2d,vector2d,vector2d);				// 直线到直线的距离
		DistanceParameters Point_Circle(vector2d,vector2d,vector2d,vector2d);			// 点到圆的距离
		DistanceParameters Point_Box(vector2d,vector2d,vector2d);						// 点到矩形的距离
		DistanceParameters Point_Polgon(vector2d,vector2d,vector2d,vector2d);			// 点到多边形的距离
		DistanceParameters Point_Capsule(vector2d,vector2d,vector2d,vector2d);			// 点到胶囊形的距离
		DistanceParameters Edge_Circle(vector2d,vector2d,vector2d,vector2d);			// 线段到圆的距离
		DistanceParameters Edge_Box(vector2d,vector2d,vector2d,vector2d);				// 线段到矩形的距离
		DistanceParameters Edge_Polygon(vector2d,vector2d,vector2d,vector2d);			// 线段到多边形的距离
		DistanceParameters Edge_Capsule(vector2d,vector2d,vector2d,vector2d);			// 线段到胶囊形的距离
		DistanceParameters Circle_Circle(vector2d,vector2d,vector2d,vector2d);			// 圆到圆的距离
		DistanceParameters Circle_Box(vector2d,vector2d,vector2d,vector2d);				// 圆到矩形的距离
		DistanceParameters Circle_Polygon(vector2d,vector2d,vector2d,vector2d);			// 圆到多边形的距离
		DistanceParameters Circle_Capsule(vector2d,vector2d,vector2d,vector2d);			// 圆到胶囊形的距离
		DistanceParameters Box_Box(vector2d,vector2d,vector2d,vector2d);				// 矩形到矩形的距离
		DistanceParameters Box_Polygon(vector2d,vector2d,vector2d,vector2d);			// 矩形到多边形的距离
		DistanceParameters Box_Capsule(vector2d,vector2d,vector2d,vector2d);			// 矩形到胶囊形的距离

		// 实现
		DistanceParameters Point_Point(vector2d p1,vector2d p2) {
			DistanceParameters ans;
			ans.dis=Mod(p1-p2);
			ans.p1=p1;
			ans.p2=p2;
			ans.p1R=vector2d {0,0};
			ans.p2R=vector2d {0,0};
			return ans;
		}
		DistanceParameters Point_Line(vector2d p,vector2d p1,vector2d p2) {
			DistanceParameters ans;
			vector2d v1=p-p1;
			vector2d v2=p2-p1;
			real area=Cross(v2,v1);
			ans.dis=abs(area/Mod(v2));
			real Ta=ans.dis*ans.dis;
			real Tc=Mod2(v1);
			real Tb=Tc-Ta;
			ans.p1=p;
			ans.p2=p1+VecUnit(v2)*sqrt(Tb);
			ans.p1R=vector2d {0,0};
			ans.p2R=VecUnit(v2)*sqrt(Tb);
			return ans;
		}
		DistanceParameters Point_Ray(vector2d p,vector2d p1,vector2d p2) {
			DistanceParameters ans;
			vector2d v1=p-p1;
			vector2d v2=p2-p1;
			real v3=(v1>>=v2);
			if(v3>=0)ans=Point_Line(p,p1,p2);
			else ans=Point_Point(p,p1);
			return ans;
		}
		DistanceParameters Point_Edge(vector2d p,vector2d p1,vector2d p2) {
			DistanceParameters ans;
			vector2d v1=p-p1;
			vector2d v2=p-p2;
			vector2d v3=p2-p1;
			vector2d v4=p1-p2;
			real t1=(v1>>=v3);
			real t2=(v2>>=v4);
			if(t1<0)ans=Point_Point(p,p1);
			else if(t2<0) {
				ans=Point_Point(p,p2);
				ans.p2R=ans.p2-p1;
			} else ans=Point_Line(p,p1,p2);
			return ans;
		}
		DistanceParameters Edge_Edge(vector2d p11,vector2d p12,vector2d p21,vector2d p22) {
			DistanceParameters ans;
			// 相交判断
			Intersection intr=intersection::Edge_Edge(p11,p12,p21,p22);
			if(intr.find) {
				ans.dis=0;
				ans.p1=intr.point;
				ans.p2=intr.point;
				ans.p1R=intr.point-p11;
				ans.p2R=intr.point-p21;
				return ans;
			}
			DistanceParameters ans1=Point_Edge(p11,p21,p22);
			DistanceParameters ans2=Point_Edge(p12,p21,p22);
			DistanceParameters ans3=Point_Edge(p21,p11,p12);
			DistanceParameters ans4=Point_Edge(p22,p11,p12);
			ans2.p2R=ans2.p2-p21;
			DistanceParameters t=ans3;
			ans3.p1=t.p2;
			ans3.p2=t.p1;
			ans3.p1R=t.p2R;
			ans3.p2R=t.p1R;
			t=ans4;
			ans4.p1=t.p2;
			ans4.p2=t.p1;
			ans4.p1R=t.p2R;
			ans4.p2R=t.p1R;
			ans4.p2R=ans4.p2-p21;
			ans=ans1;
			if(ans2.dis<ans.dis)ans=ans2;
			if(ans3.dis<ans.dis)ans=ans3;
			if(ans4.dis<ans.dis)ans=ans4;
			return ans;
		}
		DistanceParameters Edge_Line(vector2d p11,vector2d p12,vector2d p21,vector2d p22) {
			DistanceParameters ans;
			DistanceParameters ans1=Point_Line(p11,p21,p22);
			DistanceParameters ans2=Point_Line(p12,p21,p22);
			if(ans1.dis>ans2.dis)ans=ans1;
			else ans=ans2;
			return ans;
		}
		DistanceParameters Edge_Ray(vector2d,vector2d,vector2d,vector2d) {
			DistanceParameters ans;
			return ans;
		}
		DistanceParameters Ray_Line(vector2d,vector2d,vector2d,vector2d) {
			DistanceParameters ans;
			return ans;
		}
		DistanceParameters Line_Line(vector2d,vector2d,vector2d,vector2d) {
			DistanceParameters ans;
			return ans;
		}
		DistanceParameters Point_Box(vector2d p,vector2d p1,vector2d p2) {
			DistanceParameters ans;
			real x1=p1.x,x2=p2.x,y1=p1.y,y2=p2.y;
			p1=vector2d {min(x1,x2),min(y1,y2)};
			p2=vector2d {max(x1,x2),max(y1,y2)};
			ans.p1=p;
			if(p.x>=p1.x&&p.x<=p2.x&&p.y<=p1.y) {
				ans.dis=p1.y-p.y;
				ans.p2=vector2d {p.x,p1.y};
			} else if(p.x>=p1.x&&p.x<=p2.x&&p.y>=p2.y) {
				ans.dis=p.y-p2.y;
				ans.p2=vector2d {p.x,p2.y};
			} else if(p.y>=p1.y&&p.y<=p2.y&&p.x<=p1.x) {
				ans.dis=p1.x-p.x;
				ans.p2=vector2d {p1.x,p.y};
			} else if(p.y>=p1.y&&p.y<=p2.y&&p.x>=p2.x) {
				ans.dis=p.x-p2.x;
				ans.p2=vector2d {p2.x,p.y};
			} else if(p.x<=p1.x&&p.y<=p1.y)ans=Point_Point(p,p1);
			else if(p.x<=p1.x&&p.y>=p2.y)ans=Point_Point(p,vector2d {p1.x,p2.y});
			else if(p.x>=p2.x&&p.y<=p1.y)ans=Point_Point(p,vector2d {p2.x,p1.y});
			else if(p.x>=p2.x&&p.y>=p2.y)ans=Point_Point(p,p2);
			else {
				real dis1,dis2,dis3,dis4,dis;
				dis1=abs(p.y-p1.y);
				dis2=abs(p.y-p2.y);
				dis3=abs(p.x-p1.x);
				dis4=abs(p.x-p2.x);
				dis=min(min(dis1,dis2),min(dis3,dis4));
				ans.dis=-dis;
				if(dis==dis1)ans.p2=vector2d {p.x,p1.y};
				else if(dis==dis2)ans.p2=vector2d {p.x,p2.y};
				else if(dis==dis3)ans.p2=vector2d {p1.x,p.y};
				else if(dis==dis4)ans.p2=vector2d {p2.x,p.y};
			}
			return ans;
		}

	}

	// 凸包计算
	namespace convexHull {

		// Andrew算法
		int Andrew_cmp(vector2d p1,vector2d p2) {
			return p1.x<p2.x;
		}
		int CalcAndrew(vector2d* point,int n,vector2d* h) {
			// stk[] 是整型，存的是下标
			// p[] 存储向量或点
			int tp = 0;                       // 初始化栈
			int stk[POLYGON_EDGE_MAXN*POLYGON_EDGE_MAXN];
			bool used[POLYGON_EDGE_MAXN*POLYGON_EDGE_MAXN];
			std::sort(point, point+ n,Andrew_cmp);  // 对点进行排序
			stk[++tp] = 1;
			// 栈内添加第一个元素，且不更新 used，使得 1 在最后封闭凸包时也对单调栈更新
			for (int i = 2; i <= n; ++i) {
			while (tp >= 2  // 下一行 * 操作符被重载为叉积
					&& Cross((point[stk[tp]-1] - point[stk[tp - 1]-1]) , (point[i-1] - point[stk[tp]-1])) <= 0)
				used[stk[tp--]-1] = 0;
			used[i-1] = 1;  // used 表示在凸壳上
			stk[++tp] = i;
			}
			int tmp = tp;  // tmp 表示下凸壳大小
			for (int i = n - 1; i > 0; --i)
			if (!used[i-1]) {
				// ↓求上凸壳时不影响下凸壳
				while (tp > tmp && Cross((point[stk[tp]-1] - point[stk[tp - 1]-1]) , (point[i-1] - point[stk[tp]-1])) <= 0)
				used[stk[tp--]-1] = 0;
				used[i-1] = 1;
				stk[++tp] = i;
			}
			for (int i = 1; i <= tp; ++i)  // 复制到新数组中去
			h[i-1] = point[stk[i]-1];
			int ans = tp - 1;
			return ans;
		}

		// Melkman算法
		inline float isLeft(vector2d P0,vector2d P1,vector2d P2) {
			return (P1.x-P0.x)*(P2.y-P0.y)-(P2.x-P0.x)*(P1.y-P0.y);
		}
		int CalcMelkman(vector2d* P,int n,vector2d* H) {
			vector2d* D=new vector2d[2*n+1];
			int bot=n-2,top=bot+3;
			D[bot]=D[top]=P[2]; 
			if(isLeft(P[0],P[1],P[2])>0) {
				D[bot+1]=P[0];
				D[bot+2]=P[1]; 
			}
			else {
				D[bot+1]=P[1];
				D[bot+2]=P[0];
			}
			for(int i=3; i<n; i++) {
				if((isLeft(D[bot],D[bot+1],P[i])>0)&&(isLeft(D[top-1],D[top],P[i])>0))continue;
				while(isLeft(D[bot],D[bot+1],P[i])<=0)++bot;
				D[--bot]=P[i]; 
				while(isLeft(D[top-1],D[top],P[i])<=0)--top;
				D[++top]=P[i];
			}
			int h; 
			for (h=0;h<=(top-bot);h++)H[h]=D[bot+h];
			delete D;
			return h-1;
		}

	}

	// 碰撞检测
	namespace collision {

		// 碰撞参数
		class CollisionParameters {
			public:
				bool IsCollide;					// 是否碰撞
				PhysicsBody* Body1;				// 碰撞物体1
				PhysicsBody* Body2;				// 碰撞物体2
				vector2d SeparationP1;			// 碰撞分离轴点1
				vector2d SeparationP2;			// 碰撞分离轴点2

		};

		// 粗略碰撞检测
		namespace broadphase {
			void AddBodyPair(BroadphaseParameters* para,PhysicsBody* body1,PhysicsBody* body2) {
				if(!para->IsCollided[body1]) {
					para->IsCollided[body1]=true;
					para->CollideBody.push_back(body1);
					para->CollideBodySum++;
				}
				if(!para->IsCollided[body2]) {
					para->IsCollided[body2]=true;
					para->CollideBody.push_back(body2);
					para->CollideBodySum++;
				}
				CollisionParameters temp;
				temp.Body1=body1;
				temp.Body2=body2;
				temp.IsCollide=true;
				para->CollideBodyPair.push_back(temp);
				para->CollideBodySum++;
			}
			// AABB碰撞盒碰撞
			class AABB_Parameters {				// AABB碰撞参数
				public:
					bool IsCollided=false;		// 是否碰撞
			};
			AABB_Parameters AABB_Collide(aabb A,aabb B) {	// AABB碰撞
				AABB_Parameters ans;
				ans.IsCollided=false;
				if(A.Maxp.x<=B.Minp.x)return ans;
				if(A.Minp.x>=B.Maxp.x)return ans;
				if(A.Maxp.y<=B.Minp.y)return ans;
				if(A.Minp.y>=B.Maxp.y)return ans;
				ans.IsCollided=true;
				return ans;
			}
			// 暴力算法 O(N^2)	10000物体：1300ms
			void Violence(PhysicsWorld* world,BroadphaseParameters* para) {
				for(int i=0;i<world->GetBodyCount();i++)
					for(int j=i+1;j<world->GetBodyCount();j++)
						if(AABB_Collide(world->Body[i]->AABB,world->Body[j]->AABB).IsCollided)
							AddBodyPair(para,world->Body[i],world->Body[j]);
			}
			// SAP扫掠剪除算法 O(NlogN)~O(N^2) 10000物体：100ms
			bool SAP_cmp_X(PhysicsBody* Body1,PhysicsBody* Body2) {
				return Body1->AABB.Minp.x<Body2->AABB.Minp.x;
			}
			bool SAP_cmp_Y(PhysicsBody* Body1,PhysicsBody* Body2) {
				return Body1->AABB.Minp.y<Body2->AABB.Minp.y;
			}
			void SAP(PhysicsWorld* world,BroadphaseParameters* para) {
				PhysicsBody* Body[BODY_MAXN];
				real BodyX[BODY_MAXN],BodyY[BODY_MAXN];
				for(int i=0;i<world->GetBodyCount();i++) {
					Body[i]=world->Body[i];
					BodyX[i]=world->Body[i]->Core.x;
					BodyY[i]=world->Body[i]->Core.y;
				}
				// 利用方差判断物体在X方向还是Y方向上更分散，如果物体在计算的方向上聚集，算法会退化为O(N^2)
				sort(BodyX,BodyX+world->GetBodyCount());
				sort(BodyY,BodyY+world->GetBodyCount());
				long real SumX=0,SumY=0;
				for(int i=0;i<world->GetBodyCount();i++)SumX+=BodyX[i];
				for(int i=0;i<world->GetBodyCount();i++)SumY+=BodyY[i];
				long real AverageX=SumX/world->GetBodyCount(),AverageY=SumY/world->GetBodyCount();
				long real SX=0,SY=0;
				for(int i=0;i<world->GetBodyCount();i++)SX+=(BodyX[i]-AverageX)*(BodyX[i]-AverageX);
				for(int i=0;i<world->GetBodyCount();i++)SY+=(BodyY[i]-AverageY)*(BodyY[i]-AverageY);
				// 在X方向上更分散
				if(SX>SY) {
					vector<pair<int,int> > Pair; 
					sort(Body,Body+world->GetBodyCount(),SAP_cmp_X);
					for(int i=0;i<world->GetBodyCount()-1;i++) {
						int k=i+1;
						while(Body[i]->AABB.Maxp.x>Body[k]->AABB.Minp.x) {
							Pair.push_back(make_pair(i,k)),k++;
							if(k>=world->GetBodyCount())break;
						}
					}
					for(int i=0;i<Pair.size();i++)
						if(Body[Pair[i].first]->AABB.Maxp.y>Body[Pair[i].second]->AABB.Minp.y&&
							Body[Pair[i].first]->AABB.Minp.y<Body[Pair[i].second]->AABB.Maxp.y)
								AddBodyPair(para,world->Body[Pair[i].first],world->Body[Pair[i].second]);
				}
				// 在Y轴上更分散
				else {
					vector<pair<int,int> > Pair; 
					sort(Body,Body+world->GetBodyCount(),SAP_cmp_Y);
					for(int i=0;i<world->GetBodyCount()-1;i++) {
						int k=i+1;
						while(Body[i]->AABB.Maxp.y>Body[k]->AABB.Minp.y) {
							Pair.push_back(make_pair(i,k)),k++;
							if(k>=world->GetBodyCount())break;
						}
					}
					for(int i=0;i<Pair.size();i++)
						if(Body[Pair[i].first]->AABB.Maxp.x>Body[Pair[i].second]->AABB.Minp.x&&
							Body[Pair[i].first]->AABB.Minp.x<Body[Pair[i].second]->AABB.Maxp.x)
								AddBodyPair(para,world->Body[Pair[i].first],world->Body[Pair[i].second]);
				}
			}
			// 动态SAP扫掠剪除法 O(N)~O(N^2)	10000物体：25ms
			void DSAP::Init(PhysicsWorld* world) {			// 初始化
				World=world;
				real BodyX[BODY_MAXN],BodyY[BODY_MAXN];
				for(int i=0;i<world->GetBodyCount();i++) {
					BodyX[i]=world->Body[i]->Core.x;
					BodyY[i]=world->Body[i]->Core.y;
				}
				// 利用方差判断物体在X方向还是Y方向上更分散，如果物体在计算的方向上聚集，算法会退化为O(N^2)
				sort(BodyX,BodyX+world->GetBodyCount());
				sort(BodyY,BodyY+world->GetBodyCount());
				long real SumX=0,SumY=0;
				for(int i=0;i<world->GetBodyCount();i++)SumX+=BodyX[i];
				for(int i=0;i<world->GetBodyCount();i++)SumY+=BodyY[i];
				long real AverageX=SumX/world->GetBodyCount(),AverageY=SumY/world->GetBodyCount();
				long real SX=0,SY=0;
				for(int i=0;i<world->GetBodyCount();i++)SX+=(BodyX[i]-AverageX)*(BodyX[i]-AverageX);
				for(int i=0;i<world->GetBodyCount();i++)SY+=(BodyY[i]-AverageY)*(BodyY[i]-AverageY);
				if(SX>SY)Direction=0;
				else Direction=1;
			}
			void DSAP::Update(BroadphaseParameters* para) {		// 更新
				// 在X轴上更分散
				if(Direction==0) {
					vector<pair<int,int> > Pair; 
					// 插入排序
					for(int i=1; i<World->GetBodyCount(); i++)for(int j=i-1; j>=0; j--) {
							if(SAP_cmp_X(World->Body[j+1],World->Body[j])) {
								swap(World->Body[j+1],World->Body[j]);
								swap(World->Res[j+1],World->Res[j]);
								swap(World->Body[j+1]->F[World->Body[j+1]->ResP],World->Body[j]->F[World->Body[j]->ResP]);
								swap(World->G[j+1],World->G[j]);
								swap(World->Body[j+1]->F[World->Body[j+1]->GP],World->Body[j]->F[World->Body[j]->GP]);
							} else break;	
						}
					for(int i=0;i<World->GetBodyCount()-1;i++) {
						int k=i+1;
						while(World->Body[i]->AABB.Maxp.x>World->Body[k]->AABB.Minp.x) {
							Pair.push_back(make_pair(i,k)),k++;
							if(k>=World->GetBodyCount())break;
						}
					}
					for(int i=0;i<Pair.size();i++)
						if(World->Body[Pair[i].first]->AABB.Maxp.y>World->Body[Pair[i].second]->AABB.Minp.y&&
							World->Body[Pair[i].first]->AABB.Minp.y<World->Body[Pair[i].second]->AABB.Maxp.y)
								AddBodyPair(para,World->Body[Pair[i].first],World->Body[Pair[i].second]);
				}
				// 在Y轴上更分散
				else {
					vector<pair<int,int> > Pair; 
					// 插入排序
					for(int i=1; i<World->GetBodyCount(); i++)for(int j=i-1; j>=0; j--) {
							if(SAP_cmp_Y(World->Body[j+1],World->Body[j])) {
								swap(World->Body[j+1],World->Body[j]);
								swap(World->Res[j+1],World->Res[j]);
								swap(World->Body[j+1]->F[World->Body[j+1]->ResP],World->Body[j]->F[World->Body[j]->ResP]);
								swap(World->G[j+1],World->G[j]);
								swap(World->Body[j+1]->F[World->Body[j+1]->GP],World->Body[j]->F[World->Body[j]->GP]);
							} else break;	
						}
					for(int i=0;i<World->GetBodyCount()-1;i++) {
						int k=i+1;
						while(World->Body[i]->AABB.Maxp.y>World->Body[k]->AABB.Minp.y) {
							Pair.push_back(make_pair(i,k)),k++;
							if(k>=World->GetBodyCount())break;
						}
					}
					for(int i=0;i<Pair.size();i++)
						if(World->Body[Pair[i].first]->AABB.Maxp.x>World->Body[Pair[i].second]->AABB.Minp.x&&
							World->Body[Pair[i].first]->AABB.Minp.x<World->Body[Pair[i].second]->AABB.Maxp.x)
								AddBodyPair(para,World->Body[Pair[i].first],World->Body[Pair[i].second]);
				}
			}
			// BVH动态层次包围盒算法 O(NlogN)~O(N^2)
			class DBVH {
				private:
					struct data {
						int l,r,v,w,rnd,size;
					} tr[10005];
					int size,root,n,ans;

					void update(int k) {
						tr[k].size=tr[tr[k].l].size+tr[tr[k].r].size+tr[k].w;
					}
					void rturn(int &k) {
						int t=tr[k].l;
						tr[k].l=tr[t].r;
						tr[t].r=k;
						tr[t].size=tr[k].size;
						update(k);
						k=t;
					}
					void lturn(int &k) {
						int t=tr[k].r;
						tr[k].r=tr[t].l;
						tr[t].l=k;
						tr[t].size=tr[k].size;
						update(k);
						k=t;
					}
					void insert(int &k,int x) {
						if(k==0) {
							k=++size;
							tr[k].size=tr[k].w=1;
							tr[k].v=x;
							tr[k].rnd=rand();
							return;
						}
						tr[k].size++;
						if(x==tr[k].v)tr[k].w++;
						else if(x<tr[k].v) {
							insert(tr[k].l,x);
							if(tr[tr[k].l].rnd<tr[k].rnd)rturn(k);
						} else {
							insert(tr[k].r,x);
							if(tr[tr[k].r].rnd<tr[k].rnd)lturn(k);
						}
					}
					void del(int &k,int x) {
						if(k==0)return;
						if(x==tr[k].v) {
							if(tr[k].w>1) {
								tr[k].size--,tr[k].w--;
								return;
							}
							if(tr[k].l*tr[k].r==0)k=tr[k].l+tr[k].r;
							else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd)rturn(k),del(k,x);
							else lturn(k),del(k,x);
						} else if(x<tr[k].v)tr[k].size--,del(tr[k].l,x);
						else tr[k].size--,del(tr[k].r,x);
					}
					int query_rank(int k,int x) {
						if(k==0)return 0;
						if(x==tr[k].v)return tr[tr[k].l].size+1;
						else if(x<tr[k].v)return query_rank(tr[k].l,x);
						else return tr[tr[k].l].size+tr[k].w+query_rank(tr[k].r,x);
					}
					int query_num(int k,int x) {
						if(k==0)return 0;
						if(x<=tr[tr[k].l].size)return query_num(tr[k].l,x);
						else if(x>tr[tr[k].l].size+tr[k].w)return query_num(tr[k].r,x-tr[tr[k].l].size-tr[k].w);
						else return tr[k].v;
					}
					void query_pro(int k,int x) {
						if(k==0)return;
						if(x>tr[k].v)ans=k,query_pro(tr[k].r,x);
						else query_pro(tr[k].l,x);
					}
					void query_sub(int k,int x) {
						if(k==0)return;
						if(x<tr[k].v)ans=k,query_sub(tr[k].l,x);
						else query_sub(tr[k].r,x);
					}
				public:
					void init() {
					}
					void Update() {
					}
			};

		}

		// 精确碰撞检测
		namespace narrowphase {
			// 二维凸多边形碰撞检测-SAT算法 O(M^2)
			bool PolygonCollisionSAT(vector2d* A,int sa,vector2d* B,int sb) {
				bool flag=false;
				for(int i=1;i<=sa+sb;i++) {
					// 计算边的中垂线
					vector2d p1,p2;
					if(i<=sa) {
						p1=A[i%sa];
						p2=A[i-1];
					} else {
						p1=B[(i-sa)%sb];
						p2=B[i-1-sa];
					}
					vector2d vex=(p2-p1).Rotate(GPE_PI/2.0);
					// 计算投影
					real min1,max1,min2,max2;
					for(int j=0;j<sa;j++) {
						vector2d p=(A[j]);
						real k=p>>=vex;
						if(j==0)min1=max1=k;
						min1=min(min1,k);
						max1=max(max1,k);
					}
					for(int j=0;j<sb;j++) {
						vector2d p=(B[j]);
						real k=p>>=vex;
						if(j==0)min2=max2=k;
						min2=min(min2,k);
						max2=max(max2,k);
					}
					// 相交测试
					if(max1<min2||max2<min1) {
						flag=true;
						break;
					}
				}
				if(!flag)return true;
				else return false;
			}
			bool PolygonCollisionSAT(PhysicsBody* body1,PhysicsBody* body2) {
				bool flag=false;
				for(int i=1;i<=body1->Shape.ShapePolygon.N+body2->Shape.ShapePolygon.N;i++) {
					// 计算边的中垂线
					vector2d p1,p2;
					if(i<=body1->Shape.ShapePolygon.N) {
						p1=body1->Shape.ShapePolygon.Point[i%body1->Shape.ShapePolygon.N];
						p2=body1->Shape.ShapePolygon.Point[i-1];
						p1=p1.Rotate(-body1->Rotation)+body1->Core;
						p2=p2.Rotate(-body1->Rotation)+body1->Core;
					} else {
						p1=body2->Shape.ShapePolygon.Point[(i-body1->Shape.ShapePolygon.N)%body2->Shape.ShapePolygon.N];
						p2=body2->Shape.ShapePolygon.Point[i-1-body1->Shape.ShapePolygon.N];
						p1=p1.Rotate(-body2->Rotation)+body2->Core;
						p2=p2.Rotate(-body2->Rotation)+body2->Core;
					}
					vector2d vex=(p2-p1).Rotate(GPE_PI/2.0);
					// 计算投影
					real min1,max1,min2,max2;
					for(int j=0;j<body1->Shape.ShapePolygon.N;j++) {
						vector2d p=(body1->Shape.ShapePolygon.Point[j]).Rotate(-body1->Rotation)+body1->Core;
						real k=p>>=vex;
						if(j==0)min1=max1=k;
						min1=min(min1,k);
						max1=max(max1,k);
					}
					for(int j=0;j<body2->Shape.ShapePolygon.N;j++) {
						vector2d p=(body2->Shape.ShapePolygon.Point[j]).Rotate(-body2->Rotation)+body2->Core;
						real k=p>>=vex;
						if(j==0)min2=max2=k;
						min2=min(min2,k);
						max2=max(max2,k);
					}
					// 相交测试
					if(max1<min2||max2<min1) {
						flag=true;
						break;
					}
				}
				if(!flag)return true;
				else return false;
			}
			// 二维凸多边形碰撞检测-闵可夫斯基差&凸包 O(N^2)
			int CalcMinkowskiDifference(vector2d* A,int sa,vector2d* B,int sb,vector2d* Ans) {
				vector2d C[sa*sb];
				int ps=0;
				for(int i=0;i<sa;i++)for(int j=0;j<sb;j++)C[ps++]=A[i]-B[j];
				return convexHull::CalcAndrew(C,ps,Ans);
			}
			bool PolygonCollisionMinkowski(vector2d* A,int sa,vector2d* B,int sb) {
				vector2d C[sa*sb];
				int s=CalcMinkowskiDifference(A,sa,B,sb,C);
				real area=0;
				real areas=0;
				for(int i=2;i<s;i++)areas+=abs(Cross(C[i-1]-C[0],C[i]-C[0])/2.0);
				for(int i=1; i<=s; i++) {
					vector2d p1=C[i%s];
					vector2d p2=C[i-1];
					area+=abs(Cross(p1,p2))/2;
				}
				if(abs(area-areas)>GPE_EPT)return false;
				return true;
			}
			bool PolygonCollisionMinkowski(PhysicsBody* body1,PhysicsBody* body2) {
				vector2d A[POLYGON_EDGE_MAXN];
				vector2d B[POLYGON_EDGE_MAXN];
				for(int i=0;i<body1->Shape.ShapePolygon.N;i++)
					A[i]=body1->Shape.ShapePolygon.Point[i].Rotate(-body1->Rotation)+body1->Core;
				for(int i=0;i<body2->Shape.ShapePolygon.N;i++)
					B[i]=body2->Shape.ShapePolygon.Point[i].Rotate(-body2->Rotation)+body2->Core;
				return PolygonCollisionMinkowski(A,body1->Shape.ShapePolygon.N,B,body2->Shape.ShapePolygon.N);
			}
			// 二维凸多边形碰撞检测-GJK算法 
			bool PolygonCollisionGJK_Support(vector2d* A,int sa,vector2d* B,int sb,vector2d dir) {
				// 计算投影
				for(int i=0;i<sa;i++) {
				}
				for(int i=0;i<sb;i++) {
				}
			}
			bool PolygonCollisionGJK(PhysicsBody* body1,PhysicsBody* body2) {
				return false;
			}
			// 检测
			void AddBodyPair(NarrowphaseParameters* para,PhysicsBody* body1,PhysicsBody* body2,vector2d p1,vector2d p2) {
				if(!para->IsCollided[body1]) {
					para->IsCollided[body1]=true;
					para->CollideBody.push_back(body1);
					para->CollideBodySum++;
				}
				if(!para->IsCollided[body2]) {
					para->IsCollided[body2]=true;
					para->CollideBody.push_back(body2);
					para->CollideBodySum++;
				}
				CollisionParameters temp;
				temp.Body1=body1;
				temp.Body2=body2;
				temp.IsCollide=true;
				temp.SeparationP1=p1;
				temp.SeparationP2=p2;
				para->CollideBodyPair.push_back(temp);
			}
			bool IsCollided(PhysicsBody* body1,PhysicsBody* body2) {
				if(body1->Shape.Flag==PHYSICSSHAPE_CIRCLE) {
					if(body2->Shape.Flag==PHYSICSSHAPE_CIRCLE) {
						if(distance::Point_Point(body1->LastCore,body2->LastCore).dis<body1->r+body2->r) {
							return true;
						}
						return false;
					}
				}
				if(body1->Shape.Flag==PHYSICSSHAPE_BOX) {
				}
				if(body1->Shape.Flag==PHYSICSSHAPE_POLYGON) {
					if(body2->Shape.Flag==PHYSICSSHAPE_POLYGON) {
						if(PolygonCollisionSAT(body1,body2)) {
							return true;
						}
						return false;
					}
				}
				return false;
			}
			void Detect(broadphase::BroadphaseParameters* para,NarrowphaseParameters* ans) {
				for(int i=0;i<para->CollideBodyPair.size();i++) {
					if(para->CollideBodyPair[i].Body1->Shape.Flag>para->CollideBodyPair[i].Body2->Shape.Flag) {
						swap(para->CollideBodyPair[i].Body1,para->CollideBodyPair[i].Body2);
						swap(para->CollideBodyPair[i].SeparationP1,para->CollideBodyPair[i].SeparationP2);
					}
					PhysicsBody* body1=para->CollideBodyPair[i].Body1;
					PhysicsBody* body2=para->CollideBodyPair[i].Body2;
					if(IsCollided(body1,body2)) {
						if(!ans->IsCollided[body1]) {
							ans->IsCollided[body1]=true;
							ans->CollideBody.push_back(body1);
							ans->CollideBodySum++;
						}
						if(!ans->IsCollided[body2]) {
							ans->IsCollided[body2]=true;
							ans->CollideBody.push_back(body2);
							ans->CollideBodySum++;
						}
						CollisionParameters temp;
						temp.Body1=body1;
						temp.Body2=body2;
						temp.IsCollide=true;
						ans->CollideBodyPair.push_back(temp);
					}
				}
			}
		}

		// 碰撞约束
		namespace constraint {
			void Constraint(narrowphase::NarrowphaseParameters* para) {
				// for(int i=0;i<world.BroadCollidePara.CollideBodyPair.size();i++) {
				// 	PhysicsBody* body1=world.BroadCollidePara.CollideBodyPair[i].Body1;
				// 	PhysicsBody* body2=world.BroadCollidePara.CollideBodyPair[i].Body2;
				// 	if(distance::Point_Point(body1->LastCore,body2->LastCore).dis<2*r) {
				// 		if(body1->LastCore==body2->LastCore)body1->LastCore+={0.001,0.001};
				// 		vector2d d1=body1->LastCore-body2->LastCore;
				// 		vector2d d2=body2->LastCore-body1->LastCore;
				// 		vector2d v1=body1->V>>d1;
				// 		vector2d v2=body2->V>>d2;
				// 		real k=distance::Point_Point(body1->LastCore,body2->LastCore).dis;
				// 		body1->MoveTo(body1->LastCore+VecUnit(d1)*(r-k/2));
				// 		body2->MoveTo(body2->LastCore+VecUnit(d2)*(r-k/2));
				// 		body1->V=body1->V-v1+v2;
				// 		body2->V=body2->V-v2+v1;
				// 	}
				// }
				for(int i=0;i<para->CollideBodyPair.size();i++) {
					PhysicsBody* body1=para->CollideBodyPair[i].Body1;
					PhysicsBody* body2=para->CollideBodyPair[i].Body2;
					if(distance::Point_Point(body1->LastCore,body2->LastCore).dis>body1->r+body2->r)cout<<distance::Point_Point(body1->LastCore,body2->LastCore).dis<<endl;
					if(body1->Shape.Flag==PHYSICSSHAPE_CIRCLE) {
						if(body2->Shape.Flag==PHYSICSSHAPE_CIRCLE) {
							// if(body1->LastCore==body2->LastCore)body1->LastCore+={0.001,0.001};
							vector2d d1=body1->LastCore-body2->LastCore;
							vector2d d2=body2->LastCore-body1->LastCore;
							vector2d v1=body1->V>>d1;
							vector2d v2=body2->V>>d2;
							real k=distance::Point_Point(body1->LastCore,body2->LastCore).dis;
							real r=body1->r+body2->r;
							body1->MoveTo(body1->LastCore+VecUnit(d1)*(r-k)/2.0);
							body2->MoveTo(body2->LastCore+VecUnit(d2)*(r-k)/2.0);
							body1->V=body1->V-v1+v2;
							body2->V=body2->V-v2+v1;
						}
					}
				}
			}
		}

	}

	// 查询
	namespace query {

		// 声明一下
		class QueryParameters;
		QueryParameters QueryPoint(vector2d);				// 点查询
		QueryParameters QueryRay(vector2d,real);			// 射线查询
		QueryParameters QueryEdge(vector2d,vector2d);		// 射线查询

		// 再声明一下
		class QueryParameters {
			private:
			public:

		};

		// 实现一下（还没有实现）

	}

	// 物理形状
	PhysicsShapeCircle::PhysicsShapeCircle(real r=1) {
		Radius=r;
	}
	vector2d PhysicsShapeCircle::GetCore() {
		return {0,0};
	}
	real PhysicsShapeCircle::GetArea() {
		return GPE_PI*Radius*Radius;
	}
	real PhysicsShapeCircle::GetRadius() {
		return Radius;
	}
	PhysicsShapeBox::PhysicsShapeBox(real A=1,real B=1) {
		a=A,b=B;
	}
	vector2d PhysicsShapeBox::GetCore() {
		return {0,0};
	}
	real PhysicsShapeBox::GetArea() {
		return a*b;
	}
	real PhysicsShapeBox::GetRadius() {
		return sqrt(a*a+b*b)/2;
	}
	PhysicsShapePolygon::PhysicsShapePolygon(int ps=0) {
		N=ps;
	}
	vector2d PhysicsShapePolygon::GetCore() {
		real areas=0;
		vector2d ans=vector2d{0,0};
		for(int i=2;i<N;i++) {
			real area=Cross(Point[i-1]-Point[0],Point[i]-Point[0])/2.0;
			areas+=area;
			ans+=(Point[0]+Point[i-1]+Point[i])*area;
		}
		ans/=areas*3;
		return ans;
	}
	real PhysicsShapePolygon::GetArea() {
		real areas=0;
		for(int i=2;i<N;i++)areas+=abs(Cross(Point[i-1]-Point[0],Point[i]-Point[0])/2.0);
		return areas;
	}
	real PhysicsShapePolygon::GetRadius() {
		vector2d core=GetCore();
		real maxn=0;
		for(int i=0;i<N;i++)maxn=max((real)maxn,Mod2(Point[i]-core));
		return sqrt(maxn);
	}
	vector2d PhysicsShapePolygon::ToOrigin() {
		vector2d core=GetCore();
		for(int i=0;i<N;i++)Point[i]-=core;
		return core;
	}
	PhysicsShapeCapsule::PhysicsShapeCapsule(real A=1,real B=1) {
		if(A>B)swap(A,B);
		a=A,b=B;
	}
	vector2d PhysicsShapeCapsule::GetCore() {
		return vector2d{0,0};
	}
	real PhysicsShapeCapsule::GetArea() {
		return (a/2.0)*(a/2.0)*GPE_PI+(b-a)*a;
	}
	real PhysicsShapeCapsule::GetRadius() {
		return b/2.0;
	}
	PhysicsShapeEdge::PhysicsShapeEdge(real L=0) {
		Length=L;
	}
	vector2d PhysicsShapeEdge::GetCore() {
		return {0,0};
	}
	real PhysicsShapeEdge::GetArea() {
		return 0;
	}
	real PhysicsShapeEdge::GetRadius() {
		return Length/2;
	}
	PhysicsShapeEdgeCircle::PhysicsShapeEdgeCircle(real r=1) {
		Radius=r;
	}
	vector2d PhysicsShapeEdgeCircle::GetCore() {
		return {0,0};
	}
	real PhysicsShapeEdgeCircle::GetArea() {
		return GPE_PI*Radius*Radius;
	}
	real PhysicsShapeEdgeCircle::GetRadius() {
		return Radius;
	}
	PhysicsShapeEdgeBox::PhysicsShapeEdgeBox(real A=1,real B=1) {
		a=A,b=B;
	}
	vector2d PhysicsShapeEdgeBox::GetCore() {
		return {0,0};
	}
	real PhysicsShapeEdgeBox::GetArea() {
		return a*b;
	}
	real PhysicsShapeEdgeBox::GetRadius() {
		return sqrt(a*a+b*b)/2;
	}
	PhysicsShapeEdgePolygon::PhysicsShapeEdgePolygon(int ps=0) {
		N=ps;
	}
	vector2d PhysicsShapeEdgePolygon::GetCore() {
		real areas=0;
		vector2d ans=vector2d{0,0};
		for(int i=2;i<N;i++) {
			real area=Cross(Point[i-1]-Point[0],Point[i]-Point[0])/2.0;
			areas+=area;
			ans+=(Point[0]+Point[i-1]+Point[i])*area;
		}
		ans/=areas*3;
		return ans;
	}
	real PhysicsShapeEdgePolygon::GetArea() {
		real areas=0;
		for(int i=2;i<N;i++)areas+=abs(Cross(Point[i-1]-Point[0],Point[i]-Point[0])/2.0);
		return areas;
	}
	real PhysicsShapeEdgePolygon::GetRadius() {
		vector2d core=GetCore();
		real maxn=0;
		for(int i=0;i<N;i++)maxn=max(maxn,Mod2(Point[i]-core));
		return sqrt(maxn);
	}
	vector2d PhysicsShapeEdgePolygon::ToOrigin() {
		vector2d core=GetCore();
		for(int i=0;i<N;i++)Point[i]-=core;
		return core;
	}
	PhysicsShapeEdgeCapsule::PhysicsShapeEdgeCapsule(real A=1,real B=1) {
		if(A>B)swap(A,B);
		a=A,b=B;
	}
	vector2d PhysicsShapeEdgeCapsule::GetCore() {
		return vector2d{0,0};
	}
	real PhysicsShapeEdgeCapsule::GetArea() {
		return (a/2.0)*(a/2.0)*GPE_PI+(b-a)*a;
	}
	real PhysicsShapeEdgeCapsule::GetRadius() {
		return b/2.0;
	}
	PhysicsShapeEdgeChain::PhysicsShapeEdgeChain(int n=0) {
		N=n;
	}
	vector2d PhysicsShapeEdgeChain::GetCore() {
		vector2d ans=vector2d{0,0};
		real len=0;
		for(int i=1;i<N;i++) {
			real l=Mod(Point[i]-Point[i-1]);
			len+=l;
			ans+=(Point[i]+Point[i-1])/2*l;
		}
		ans/=len;
		return ans;
	}
	real PhysicsShapeEdgeChain::GetArea() {
		return 0;
	}
	real PhysicsShapeEdgeChain::GetRadius() {
		vector2d core=GetCore();
		real maxn=0;
		for(int i=0;i<N;i++)maxn=max(maxn,Mod2(Point[i]-core));
		return sqrt(maxn);
	}
	vector2d PhysicsShapeEdgeChain::ToOrigin() {
		vector2d core=GetCore();
		for(int i=0;i<N;i++)Point[i]-=core;
		return core;
	}
	PhysicsShapeParticle::PhysicsShapeParticle() {
	}
	vector2d PhysicsShapeParticle::GetCore() {
		return {0,0};
	}
	real PhysicsShapeParticle::GetArea() {
		return 0;
	}
	real PhysicsShapeParticle::GetRadius() {
		return 0;
	}
	PhysicsShape::PhysicsShape() {
	}
	
	// AABB碰撞盒
	void aabb::CalcAABB(PhysicsBody* Body) {
		if(Body->Shape.Flag==PHYSICSSHAPE_CIRCLE||Body->Shape.Flag==PHYSICSSHAPE_EDGECIRCLE) {
			Minp=vector2d {Body->Core.x-Body->r,Body->Core.y-Body->r};
			Maxp=vector2d {Body->Core.x+Body->r,Body->Core.y+Body->r};
		} else if(Body->Shape.Flag==PHYSICSSHAPE_BOX) {
			vector2d k1=vector2d {Body->Shape.ShapeBox.a/2,Body->Shape.ShapeBox.b/2};
			vector2d k2=vector2d {Body->Shape.ShapeBox.a/2,-Body->Shape.ShapeBox.b/2};
			vector2d k3=vector2d {-Body->Shape.ShapeBox.a/2,-Body->Shape.ShapeBox.b/2};
			vector2d k4=vector2d {-Body->Shape.ShapeBox.a/2,Body->Shape.ShapeBox.b/2};
			k1=k1.Rotate(-Body->Rotation);
			k2=k2.Rotate(-Body->Rotation);
			k3=k3.Rotate(-Body->Rotation);
			k4=k4.Rotate(-Body->Rotation);
			k1+=Body->Core;
			k2+=Body->Core;
			k3+=Body->Core;
			k4+=Body->Core;
			Minp.x=min(min(k1.x,k2.x),min(k3.x,k4.x));
			Minp.y=min(min(k1.y,k2.y),min(k3.y,k4.y));
			Maxp.x=max(max(k1.x,k2.x),max(k3.x,k4.x));
			Maxp.y=max(max(k1.y,k2.y),max(k3.y,k4.y));
		} else if(Body->Shape.Flag==PHYSICSSHAPE_POLYGON) {
			for(int i=0;i<Body->Shape.ShapePolygon.N;i++) {
				vector2d k=Body->Shape.ShapePolygon.Point[i];
				k=k.Rotate(-Body->Rotation)+Body->Core;
				if(i==0)Maxp=Minp=k;
				Maxp.x=max(Maxp.x,k.x);
				Maxp.y=max(Maxp.y,k.y);
				Minp.x=min(Minp.x,k.x);
				Minp.y=min(Minp.y,k.y);
			}
		} else if(Body->Shape.Flag==PHYSICSSHAPE_CAPSULE) {
			real a=Body->Shape.ShapeCapsule.a;
			real b=Body->Shape.ShapeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Body->Rotation)+Body->Core;
			vector2d k2=vector2d{len/2,0}.Rotate(-Body->Rotation)+Body->Core;
			Minp.x=min(k1.x-a/2,k2.x-a/2);
			Minp.y=min(k1.y-a/2,k2.y-a/2);
			Maxp.x=max(k1.x+a/2,k2.x+a/2);
			Maxp.y=max(k1.y+a/2,k2.y+a/2);
		} else if(Body->Shape.Flag==PHYSICSSHAPE_EDGE) {
			vector2d k1=vector2d{-Body->Shape.ShapeEdge.Length/2,0}.Rotate(-Body->Rotation)+Body->Core;
			vector2d k2=vector2d{Body->Shape.ShapeEdge.Length/2,0}.Rotate(-Body->Rotation)+Body->Core;
			Minp.x=min(k1.x,k2.x);
			Minp.y=min(k1.y,k2.y);
			Maxp.x=max(k1.x,k2.x);
			Maxp.y=max(k1.y,k2.y);
		} else if(Body->Shape.Flag==PHYSICSSHAPE_EDGEBOX) {
			vector2d k1=vector2d {Body->Shape.ShapeEdgeBox.a/2,Body->Shape.ShapeEdgeBox.b/2};
			vector2d k2=vector2d {Body->Shape.ShapeEdgeBox.a/2,-Body->Shape.ShapeEdgeBox.b/2};
			vector2d k3=vector2d {-Body->Shape.ShapeEdgeBox.a/2,-Body->Shape.ShapeEdgeBox.b/2};
			vector2d k4=vector2d {-Body->Shape.ShapeEdgeBox.a/2,Body->Shape.ShapeEdgeBox.b/2};
			k1=k1.Rotate(-Body->Rotation);
			k2=k2.Rotate(-Body->Rotation);
			k3=k3.Rotate(-Body->Rotation);
			k4=k4.Rotate(-Body->Rotation);
			k1+=Body->Core;
			k2+=Body->Core;
			k3+=Body->Core;
			k4+=Body->Core;
			Minp.x=min(min(k1.x,k2.x),min(k3.x,k4.x));
			Minp.y=min(min(k1.y,k2.y),min(k3.y,k4.y));
			Maxp.x=max(max(k1.x,k2.x),max(k3.x,k4.x));
			Maxp.y=max(max(k1.y,k2.y),max(k3.y,k4.y));
		} else if(Body->Shape.Flag==PHYSICSSHAPE_EDGEPOLYGON) {
			for(int i=0;i<Body->Shape.ShapeEdgePolygon.N;i++) {
				vector2d k=Body->Shape.ShapeEdgePolygon.Point[i];
				k=k.Rotate(-Body->Rotation)+Body->Core;
				if(i==0)Maxp=Minp=k;
				Maxp.x=max(Maxp.x,k.x);
				Maxp.y=max(Maxp.y,k.y);
				Minp.x=min(Minp.x,k.x);
				Minp.y=min(Minp.y,k.y);
			}
		} else if(Body->Shape.Flag==PHYSICSSHAPE_EDGECAPSULE) {
			real a=Body->Shape.ShapeEdgeCapsule.a;
			real b=Body->Shape.ShapeEdgeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Body->Rotation)+Body->Core;
			vector2d k2=vector2d{len/2,0}.Rotate(-Body->Rotation)+Body->Core;
			Minp.x=min(k1.x-a/2,k2.x-a/2);
			Minp.y=min(k1.y-a/2,k2.y-a/2);
			Maxp.x=max(k1.x+a/2,k2.x+a/2);
			Maxp.y=max(k1.y+a/2,k2.y+a/2);
		} else if(Body->Shape.Flag==PHYSICSSHAPE_EDGECHAIN) {
			for(int i=0;i<Body->Shape.ShapeEdgeChain.N;i++) {
				vector2d k=Body->Shape.ShapeEdgeChain.Point[i];
				k=k.Rotate(-Body->Rotation)+Body->Core;
				if(i==0)Maxp=Minp=k;
				Maxp.x=max(Maxp.x,k.x);
				Maxp.y=max(Maxp.y,k.y);
				Minp.x=min(Minp.x,k.x);
				Minp.y=min(Minp.y,k.y);
			}
		}
	}

	// 力
	Force::Force(vector2d p= {0,0},vector2d d= {0,0}) {
		epointType=1;
		epoint=p;
		dir=d;
	}
	Force::Force(vector2d *p,vector2d d= {0,0}) {
		epointType=2;
		epointP=p;
		dir=d;
	}
	void Force::Del(bool d=true) {
		IsDel=d;
	}
	void Force::SetPoint(vector2d pos) {
		epointType=0;
		epoint=pos;
	}
	void Force::SetPoint(vector2d* pos,vector2d d= {0,0}) {
		epointType=1;
		epointP=pos;
		epoint=d;
	}
	void Force::SetPointR(PhysicsBody* body,vector2d d= {0,0}) {
		epointType=2;
		epointP=&body->Core;
		epointBody=body;
		epoint=d;
	}
	vector2d Force::GetPoint() {
		if(epointType==0)return epoint;
		else if(epointType==1)return (*epointP)+epoint;
		else if(epointType==2)return (*epointP)+epoint.Rotate(-epointBody->Rotation);
		return {0,0};
	}
	// 运算符重载
	bool operator ==(const Force& a,const Force& b) {
		return a.dir.x==b.dir.x&&a.dir.y==b.dir.y;
	}
	void Force::operator =(const Force& a) {
		this->epoint=a.epoint;
		this->epointP=a.epointP;
		this->epointType=a.epointType;
		this->epointBody=a.epointBody;
		this->dir=a.dir;
		this->IsDel=a.IsDel;
	}
	// 力的加法
	Force operator +(const Force& a,const Force& b) {
		Force c;
		c.epoint=a.epoint;
		c.dir=a.dir+b.dir;
		return c;
	}
	void Force::operator +=(const Force &a) {
		Force t=(*this)+a;
		(*this)=t;
	}
	// 力的减法
	Force operator -(const Force& a,const Force& b) {
		Force c;
		c.epoint=a.epoint;
		c.dir=a.dir-b.dir;
		return c;
	}
	void Force::operator -=(const Force &a) {
		Force t=(*this)-a;
		(*this)=t;
	}
	// 力的乘除
	Force operator *(const Force& a,real t) {
		Force c;
		c.epoint=a.epoint;
		c.dir=a.dir*t;
		return c;
	}
	void Force::operator *=(const real &a) {
		Force t=(*this)*a;
		(*this)=t;
	}
	Force operator /(const Force& a,real t) {
		Force c;
		c.epoint=a.epoint;
		c.dir=a.dir/t;
		return c;
	}
	void Force::operator /=(const real &a) {
		Force t=(*this)/a;
		(*this)=t;
	}

	// 冲量
	Impulse::Impulse(vector2d p= {0,0},vector2d d= {0,0}) {
		epointType=1;
		epoint=p;
		dir=d;
	}
	Impulse::Impulse(vector2d *p,vector2d d= {0,0}) {
		epointType=2;
		epointP=p;
		dir=d;
	}
	void Impulse::Del(bool d=true) {
		IsDel=d;
	}
	void Impulse::SetPoint(vector2d pos) {
		epointType=0;
		epoint=pos;
	}
	void Impulse::SetPoint(vector2d* pos,vector2d d= {0,0}) {
		epointType=1;
		epointP=pos;
		epoint=d;
	}
	void Impulse::SetPointR(PhysicsBody* body,vector2d d= {0,0}) {
		epointType=2;
		epointP=&body->Core;
		epointBody=body;
		epoint=d;
	}
	vector2d Impulse::GetPoint() {
		if(epointType==0)return epoint;
		else if(epointType==1)return (*epointP)+epoint;
		else if(epointType==2)return (*epointP)+epoint.Rotate(-epointBody->Rotation);
		return {0,0};
	}
	// 运算符重载
	bool operator ==(const Impulse& a,const Impulse& b) {
		return a.dir.x==b.dir.x&&a.dir.y==b.dir.y;
	}
	void Impulse::operator =(const Impulse& a) {
		this->epoint=a.epoint;
		this->epointP=a.epointP;
		this->epointType=a.epointType;
		this->epointBody=a.epointBody;
		this->dir=a.dir;
		this->IsDel=a.IsDel;
	}
	// 冲量的加法
	Impulse operator +(const Impulse& a,const Impulse& b) {
		Impulse c;
		c.epoint=a.epoint;
		c.dir=a.dir+b.dir;
		return c;
	}
	void Impulse::operator +=(const Impulse &a) {
		Impulse t=(*this)+a;
		(*this)=t;
	}
	// 冲量的减法
	Impulse operator -(const Impulse& a,const Impulse& b) {
		Impulse c;
		c.epoint=a.epoint;
		c.dir=a.dir-b.dir;
		return c;
	}
	void Impulse::operator -=(const Impulse &a) {
		Impulse t=(*this)-a;
		(*this)=t;
	}
	// 冲量的乘除
	Impulse operator *(const Impulse& a,real t) {
		Impulse c;
		c.epoint=a.epoint;
		c.dir=a.dir*t;
		return c;
	}
	void Impulse::operator *=(const real &a) {
		Impulse t=(*this)*a;
		(*this)=t;
	}
	Impulse operator /(const Impulse& a,real t) {
		Impulse c;
		c.epoint=a.epoint;
		c.dir=a.dir/t;
		return c;
	}
	void Impulse::operator /=(const real &a) {
		Impulse t=(*this)/a;
		(*this)=t;
	}

	// 基础函数
	void InitPhysics() {
		return;
	}
	void ClosePhysics() {
		return;
	}
	namespace physicsbody {
		// 声明
		PhysicsBody CreateCircle(vector2d,real,real);			// 创建圆形
		PhysicsBody CreateBox(vector2d,real,real,real);		// 创建矩形
		PhysicsBody CreatePolygon(vector2d,real,int,real);		// 创建多边形
		void Remove(PhysicsBody*);									// 删除
		real CalcPolygonI(PhysicsShapePolygon*,real);			// 计算多边形转动惯量

		// 实现
		real CalcPolygonI(PhysicsShapePolygon* shape,real mass) {
			real ans1=0,ans2=0;
			for(int i=0;i<shape->N;i++) {
				vector2d a1=shape->Point[i];
				vector2d a2=shape->Point[(i+1)%shape->N];
				ans1+=abs(Cross(a1,a2))*(Mod(a1)*Mod(a1)+Mod(a2)*Mod(a2)+Dot(a1,a2));
				ans2+=Cross(a1,a2);
			}
			return mass/6.0*ans1/ans2;
		}
		PhysicsBody CreateCircle(vector2d pos,real r,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_CIRCLE;
			tbody.Shape.ShapeCircle.Radius=r;
			tbody.r=r;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=0.5*r*r*mass;
			return tbody;
		}
		PhysicsBody CreateBox(vector2d pos,real w,real h,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_BOX;
			tbody.Shape.ShapeBox.a=w;
			tbody.Shape.ShapeBox.b=h;
			tbody.r=sqrt(w*w+h*w)/2;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=1.0/12*(w*w+h*h)*mass;
			return tbody;
		}
		PhysicsBody CreateTriangle(vector2d A,vector2d B,vector2d C,real mass) {
			PhysicsBody tbody;
			if(Cross(B-A,C-A)<0)swap(B,C);
			tbody.Shape.Flag=PHYSICSSHAPE_POLYGON;
			tbody.Shape.ShapePolygon.N=3;
			tbody.Shape.ShapePolygon.Point[0]=A;
			tbody.Shape.ShapePolygon.Point[1]=B;
			tbody.Shape.ShapePolygon.Point[2]=C;
			tbody.r=tbody.Shape.ShapePolygon.GetRadius();
			tbody.Mass=mass;
			tbody.Core=tbody.Shape.ShapePolygon.ToOrigin();
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			tbody.I=CalcPolygonI(&tbody.Shape.ShapePolygon,mass);
			return tbody;
		}
		PhysicsBody CreatePolygon(vector2d pos,real r,int sides,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_POLYGON;
			tbody.Shape.ShapePolygon.N=sides;
			vector2d k={0,r};
			for(int i=0;i<sides;i++)tbody.Shape.ShapePolygon.Point[i]=k.Rotate(2*GPE_PI/sides*i);
			tbody.r=r;
			tbody.Mass=mass;
			tbody.Core=tbody.Shape.ShapePolygon.ToOrigin()+pos;
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=CalcPolygonI(&tbody.Shape.ShapePolygon,mass);
			return tbody;
		}
		PhysicsBody CreateCapsule(vector2d pos,real a,real b,real mass) {
			PhysicsBody tbody;
			if(a>b)swap(a,b);
			tbody.Shape.Flag=PHYSICSSHAPE_CAPSULE;
			tbody.Shape.ShapeCapsule.a=a;
			tbody.Shape.ShapeCapsule.b=b;
			tbody.r=b/2.0;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateEdge(vector2d A,vector2d B,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_EDGE;
			tbody.Shape.ShapeEdge.Length=Mod(A-B);
			tbody.r=tbody.Shape.ShapeEdge.Length/2;
			tbody.Mass=mass;
			tbody.Core=(A+B)/2;
			if(A.x>B.x)swap(A,B);
			if((B-A).y<0)tbody.Rotation=(axisX^(B-A));
			else tbody.Rotation=-(axisX^(B-A));
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgeCircle(vector2d pos,real r,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_EDGECIRCLE;
			tbody.Shape.ShapeEdgeCircle.Radius=r;
			tbody.r=r;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=r*r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgeBox(vector2d pos,real w,real h,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_EDGEBOX;
			tbody.Shape.ShapeEdgeBox.a=w;
			tbody.Shape.ShapeEdgeBox.b=h;
			tbody.r=sqrt(w*w+h*w)/2;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=1.0/3*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgeTriangle(vector2d A,vector2d B,vector2d C,real mass) {
			PhysicsBody tbody;
			if(Cross(B-A,C-A)<0)swap(B,C);
			tbody.Shape.Flag=PHYSICSSHAPE_EDGEPOLYGON;
			tbody.Shape.ShapeEdgePolygon.N=3;
			tbody.Shape.ShapeEdgePolygon.Point[0]=A;
			tbody.Shape.ShapeEdgePolygon.Point[1]=B;
			tbody.Shape.ShapeEdgePolygon.Point[2]=C;
			tbody.r=tbody.Shape.ShapeEdgePolygon.GetRadius();
			tbody.Mass=mass;
			tbody.Core=tbody.Shape.ShapeEdgePolygon.ToOrigin();
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgePolygon(vector2d pos,real r,int sides,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_EDGEPOLYGON;
			tbody.Shape.ShapeEdgePolygon.N=sides;
			vector2d k={0,r};
			for(int i=0;i<sides;i++)tbody.Shape.ShapeEdgePolygon.Point[i]=k.Rotate(2*GPE_PI/sides*i);
			tbody.r=r;
			tbody.Mass=mass;
			tbody.Core=tbody.Shape.ShapeEdgePolygon.ToOrigin()+pos;
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=0.5*r*r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgeCapsule(vector2d pos,real a,real b,real mass) {
			PhysicsBody tbody;
			if(a>b)swap(a,b);
			tbody.Shape.Flag=PHYSICSSHAPE_EDGECAPSULE;
			tbody.Shape.ShapeEdgeCapsule.a=a;
			tbody.Shape.ShapeEdgeCapsule.b=b;
			tbody.r=b/2.0;
			tbody.Mass=mass;
			tbody.Core=pos;
			tbody.LastCore=pos;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateEdgeChain(vector2d point[],int size,real mass) {
			PhysicsBody tbody;
			tbody.Shape.Flag=PHYSICSSHAPE_EDGECHAIN;
			tbody.Shape.ShapeEdgeChain.N=size;
			for(int i=0;i<size;i++)tbody.Shape.ShapeEdgeChain.Point[i]=point[i];
			tbody.Core=tbody.Shape.ShapeEdgeChain.ToOrigin();
			tbody.r=tbody.Shape.ShapeEdgeChain.GetRadius();
			tbody.Mass=mass;
			tbody.LastCore=tbody.Core;
			tbody.id=++IDS;
			tbody.I=0.5*tbody.r*tbody.r*mass;
			return tbody;
		}
		PhysicsBody CreateBezier2(vector2d A,vector2d B,vector2d C,real k=20,real mass=1) {
			vector2d p[EDGECHAIN_EDGE_MAXN];
			int k2=0;
			for(real t=0;t<=1;t+=1.0/k)p[k2++]=A*(1-t)*(1-t)+B*(1-t)*2*t+C*t*t;
			return CreateEdgeChain(p,k2,mass);
		}
		PhysicsBody CreateBezier3(vector2d A,vector2d B,vector2d C,vector2d D,real k=20,real mass=1) {
			vector2d p[EDGECHAIN_EDGE_MAXN];
			int k2=0;
			for(real t=0;t<=1;t+=1.0/k)p[k2++]=A*(1-t)*(1-t)*(1-t)+B*(1-t)*(1-t)*3*t+C*(1-t)*3*t*t+D*t*t*t;
			return CreateEdgeChain(p,k2,mass);
		}
		PhysicsBody CreateBezier(vector2d P[],int size,real k=20,real mass=1) {
			int a[EDGECHAIN_EDGE_MAXN],b[EDGECHAIN_EDGE_MAXN],k2=0;
			vector2d p[EDGECHAIN_EDGE_MAXN];
			a[1]=b[1]=b[2]=1;
			a[0]=b[0]=0;
			for(int i=3;i<=size;i++)for(int j=1;j<=i;j++) {
					if(i%2==0)b[j]=a[j]+a[j-1];
					else a[j]=b[j]+b[j-1];
				}
			for(real t=0;t<=1;t+=1.0/k) {
				for(int i=0;i<size;i++) {
					if(size%2==1)p[k2]+=a[i+1]*P[i]*pow((1-t),size-i-1)*pow(t,i);
					else p[k2]+=b[i+1]*P[i]*pow((1-t),size-i-1)*pow(t,i);
				}
				k2++;
			}
			return CreateEdgeChain(p,k2,mass);
		}
		void Remove(PhysicsBody* body) {
			body->IsDel=true;
		}
	}
	PhysicsBody CreatePhysicsBodyCircle(vector2d pos,real r,real mass) {
		return physicsbody::CreateCircle(pos,r,mass);
	}
	PhysicsBody CreatePhysicsBodyBox(vector2d pos,real w,real h,real mass) {
		return physicsbody::CreateBox(pos,w,h,mass);
	}
	PhysicsBody CreatePhysicsBodyTriangle(vector2d A,vector2d B,vector2d C,real mass) {
		return physicsbody::CreateTriangle(A,B,C,mass);
	}
	PhysicsBody CreatePhysicsBodyPolygon(vector2d pos,real r,int sides,real mass) {
		return physicsbody::CreatePolygon(pos,r,sides,mass);
	}
	PhysicsBody CreatePhysicsBodyCapsule(vector2d pos,real a,real b,real mass) {
		return physicsbody::CreateCapsule(pos,a,b,mass);
	}
	PhysicsBody CreatePhysicsBodyEdge(vector2d A,vector2d B,real mass) {
		return physicsbody::CreateEdge(A,B,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgeCircle(vector2d pos,real r,real mass) {
		return physicsbody::CreateEdgeCircle(pos,r,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgeBox(vector2d pos,real w,real h,real mass) {
		return physicsbody::CreateBox(pos,w,h,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgeTriangle(vector2d A,vector2d B,vector2d C,real mass) {
		return physicsbody::CreateEdgeTriangle(A,B,C,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgePolygon(vector2d pos,real r,int sides,real mass) {
		return physicsbody::CreateEdgePolygon(pos,r,sides,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgeCapsule(vector2d pos,real a,real b,real mass) {
		return physicsbody::CreateEdgeCapsule(pos,a,b,mass);
	}
	PhysicsBody CreatePhysicsBodyEdgeChain(vector2d point[],int size,real mass) {
		return physicsbody::CreateEdgeChain(point,size,mass);
	}
	PhysicsBody CreatePhysicsBodyBezier2(vector2d A,vector2d B,vector2d C,real k=20,real mass=1) {
		return physicsbody::CreateBezier2(A,B,C,k,mass);
	}
	PhysicsBody CreatePhysicsBodyBezier3(vector2d A,vector2d B,vector2d C,vector2d D,real k=20,real mass=1) {
		return physicsbody::CreateBezier3(A,B,C,D,k,mass);
	}
	PhysicsBody CreateBezier(vector2d P[],int size,real k=20,real mass=1) {
		return physicsbody::CreateBezier(P,size,k,mass);
	}
	void RemovePhysicsBody(PhysicsBody* body) {
		physicsbody::Remove(body);
	}
	string GetGPEVer() {
		return GPE_VER;
	}

	// 物理物体
	PhysicsBody::PhysicsBody() {
	}
	void PhysicsBody::Update(int Clock=clock()) {
		if(!enabled) {
			LastUpdateTime=Clock;
			return;
		}
		// 卸载已被卸载的力
		bool Del[FORCE_MAXN];
		int i,k;
		for(i=0; i<FSum; i++) {
			Del[i]=F[i]->IsDel;
			if(Del[i]) {
				if(i<GP)GP--;
				if(i<ResP)ResP--;
			}
		}
		for(i=0,k=0; i<FSum; i++)if(!Del[i])F[k++]=F[i];
		FSum=k;
		// 卸载已被卸载的冲量
		for(i=0; i<ISum; i++)Del[i]=Im[i]->IsDel;
		for(i=0,k=0; i<ISum; i++)if(!Del[i])Im[k++]=Im[i];
		ISum=k;
		// 初始化
		real dt=(Clock-LastUpdateTime)/1000.0;
		if(dt>0.1)dt=0.1;
		sumF.epoint=Core;
		sumF.dir= {0,0};
		A=0;
		// 移动位置
		for(int i=0; i<FSum; i++) {
			if(i==ResP)continue;
			// 计算合力
			sumF+=(*F[i]);
			// 计算力矩
			vector2d a=Core-F[i]->GetPoint();
			vector2d b=F[i]->dir;
			real M=a.x*b.y-a.y*b.x;
			// 计算角加速度
			A+=M/I;
		}
		vector2d TempV=vector2d {0,0};
		real TempW=0;
		for(int i=0; i<ISum; i++) {
			// 计算速度
			TempV+=(Im[i]->dir)/Mass;
			// 计算扭矩
			vector2d a=Core-Im[i]->GetPoint();
			vector2d b=Im[i]->dir;
			real M=a.x*b.y-a.y*b.x;
			// 计算角速度
			TempW+=M/I;
		}
		ImV=TempV;
		// 计算角速度
		real W2=W,M2;
		W+=A*dt;
		Rotation+=(W+TempW)*dt;
		// 计算速度
		VA=sumF.dir/Mass;
		vector2d V2=V;
		V+=VA*dt;
		if(Mod2(F[ResP]->dir/Mass)<Mod2(V+TempV))V+=(F[ResP]->dir)/Mass*dt;
		else V=-1*TempV;
		Core+=(V+TempV)*dt;
		// 运行脚本
		if(ScriptSet)Script(this);
		// 计算碰撞盒
		AABB.CalcAABB(this);
		// 更新
		LastUpdateTime=Clock;
		LastCore=Core;
	}
	void PhysicsBody::SetEnabled(bool en=false) {
		enabled=en;
	}
	void PhysicsBody::LoadForce(Force* f) {
		f->IsDel=false;
		F[FSum]=f;
		FSum++;
	}
	void PhysicsBody::DelForce(Force* f) {
		f->IsDel=true;
		bool Del[FORCE_MAXN];
		int i,k;
		for(i=0; i<FSum; i++)Del[i]=F[i]->IsDel;
		for(i=0,k=0; i<FSum; i++)if(!Del[i])F[k++]=F[i];
		FSum=k;
	}
	void PhysicsBody::LoadImpulse(Impulse *i) {
		i->IsDel=false;
		Im[ISum]=i;
		ISum++;
	}
	void PhysicsBody::AddImpulse(Impulse i) {
		V+=i.dir/(1.0*Mass);
		W+=Cross(Core-i.GetPoint(),i.dir)/(1.0*I);
	}
	void PhysicsBody::AddImpulse(vector2d i) {
		Impulse I;
		I.SetPoint(&Core);
		I.dir=i;
		AddImpulse(I);
	}
	void PhysicsBody::DelImpulse(Impulse* i) {
		i->IsDel=true;
		bool Del[FORCE_MAXN];
		int j,k;
		for(j=0; j<ISum; j++)Del[j]=Im[j]->IsDel;
		for(j=0,k=0; j<ISum; j++)if(!Del[j])Im[k++]=Im[j];
		ISum=k;
	}
	void PhysicsBody::ClearForce() {
		FSum=0;
	}
	void PhysicsBody::ClearImpulse() {
		ISum=0;
	}
	void PhysicsBody::MoveTo(vector2d pos) {
		if(enabled)Core=pos;
	}
	void PhysicsBody::MoveToAbs(vector2d epoint,vector2d pos) {
		if(!enabled)return;
		vector2d move=pos-epoint;
		vector2d l=epoint-Core;
		vector2d ep=GetPosAbs2Rel(epoint);
		Rotation+=Cross(move,l)/I*Mass;
		Core+=pos-GetPosRel2Abs(ep);
	}
	void PhysicsBody::MoveToRel(vector2d epoint,vector2d pos) {
		if(!enabled)return;
		vector2d move=pos-GetPosRel2Abs(epoint);
		vector2d l=GetPosRel2Abs(epoint)-Core;
		Rotation+=Cross(move,l)/I*Mass;
		Core+=pos-GetPosRel2Abs(epoint);
	}
	void PhysicsBody::SetScript(void (*script)(PhysicsBody*)) {
		Script=script;
		ScriptSet=true;
	}
	vector2d PhysicsBody::GetLastPos() {
		return LastCore;
	}
	vector2d PhysicsBody::GetPos() {
		return Core;
	}
	vector2d PhysicsBody::GetPosRel2Abs(vector2d p) {
		return p.Rotate(-Rotation)+Core;
	}
	vector2d PhysicsBody::GetPosAbs2Rel(vector2d p) {
		return (p-Core).Rotate(Rotation);
	}
	bool PhysicsBody::PointInBody(vector2d point,real offset=GPE_EPT) {
		if(Shape.Flag==PHYSICSSHAPE_CIRCLE||Shape.Flag==PHYSICSSHAPE_EDGECIRCLE) {
			return dis(point,Core)<=r;
		} else if(Shape.Flag==PHYSICSSHAPE_BOX) {
			vector2d p=point-Core;
			vector2d p2=p.Rotate(Rotation);
			real w=Shape.ShapeBox.a;
			real h=Shape.ShapeBox.b;
			if(p2.x>=-w/2&&p2.x<=w/2&&p2.y>=-h/2&&p2.y<=h/2)return true;
			return false;
		} else if(Shape.Flag==PHYSICSSHAPE_POLYGON) {
			real area=0;
			for(int i=1; i<=Shape.ShapePolygon.N; i++) {
				vector2d p1=Shape.ShapePolygon.Point[i%Shape.ShapePolygon.N].Rotate(-Rotation)+Core;
				vector2d p2=Shape.ShapePolygon.Point[i-1].Rotate(-Rotation)+Core;
				area+=abs(Cross(p1-point,p2-point))/2;
			}
			if(abs(area-Shape.ShapePolygon.GetArea())>GPE_EPT)return false;
			return true;
		} else if(Shape.Flag==PHYSICSSHAPE_CAPSULE) {
			real a=Shape.ShapeCapsule.a;
			real b=Shape.ShapeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Rotation)+Core;
			vector2d k2=vector2d{len/2,0}.Rotate(-Rotation)+Core;
			if(distance::Point_Edge(point,k1,k2).dis<=a/2)return true;
			return false;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGE) {
			vector2d k1=vector2d{-Shape.ShapeEdge.Length/2,0}.Rotate(-Rotation)+Core;
			vector2d k2=vector2d{Shape.ShapeEdge.Length/2,0}.Rotate(-Rotation)+Core;
			if(distance::Point_Edge(point,k1,k2).dis<=offset)return true;
			else return false;
		}  else if(Shape.Flag==PHYSICSSHAPE_EDGEBOX) {
			vector2d p=point-Core;
			vector2d p2=p.Rotate(Rotation);
			real w=Shape.ShapeEdgeBox.a;
			real h=Shape.ShapeEdgeBox.b;
			if(p2.x>=-w/2&&p2.x<=w/2&&p2.y>=-h/2&&p2.y<=h/2)return true;
			return false;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGEPOLYGON) {
			real area=0;
			for(int i=1; i<=Shape.ShapeEdgePolygon.N; i++) {
				vector2d p1=Shape.ShapeEdgePolygon.Point[i%Shape.ShapeEdgePolygon.N].Rotate(-Rotation)+Core;
				vector2d p2=Shape.ShapeEdgePolygon.Point[i-1].Rotate(-Rotation)+Core;
				area+=abs(Cross(p1-point,p2-point))/2;
			}
			if(abs(area-Shape.ShapeEdgePolygon.GetArea())>GPE_EPT)return false;
			return true;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGECAPSULE) {
			real a=Shape.ShapeEdgeCapsule.a;
			real b=Shape.ShapeEdgeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Rotation)+Core;
			vector2d k2=vector2d{len/2,0}.Rotate(-Rotation)+Core;
			if(distance::Point_Edge(point,k1,k2).dis<=a/2)return true;
			return false;
		} else {
			return false;
		}
	}
	real PhysicsBody::GetWindwardArea() {
		vector2d l=V.Rotate(GPE_PI/2.0);
		if(Mod(l)<GPE_EPT)return 0;
		if(Shape.Flag==PHYSICSSHAPE_CIRCLE||Shape.Flag==PHYSICSSHAPE_EDGECIRCLE) {
			return r*2;
		} else if(Shape.Flag==PHYSICSSHAPE_BOX) {
			vector2d k1=vector2d {Shape.ShapeBox.a/2,Shape.ShapeBox.b/2};
			vector2d k2=vector2d {Shape.ShapeBox.a/2,-Shape.ShapeBox.b/2};
			vector2d k3=vector2d {-Shape.ShapeBox.a/2,-Shape.ShapeBox.b/2};
			vector2d k4=vector2d {-Shape.ShapeBox.a/2,Shape.ShapeBox.b/2};
			k1=k1.Rotate(-Rotation);
			k2=k2.Rotate(-Rotation);
			k3=k3.Rotate(-Rotation);
			k4=k4.Rotate(-Rotation);
			real l1=k1>>=l;
			real l2=k2>>=l;
			real l3=k3>>=l;
			real l4=k4>>=l;
			real maxn=max(max(l1,l2),max(l3,l4));
			real minn=min(min(l1,l2),min(l3,l4));
			return maxn-minn;
		} else if(Shape.Flag==PHYSICSSHAPE_POLYGON) {
			real maxn=0,minn=2*r;
			for(int i=0;i<Shape.ShapePolygon.N;i++) {
				vector2d k=Shape.ShapePolygon.Point[i].Rotate(-Rotation);
				real l1=k>>=l;
				maxn=max(maxn,l1);
				minn=min(minn,l1);
			}
			return maxn-minn;
		} else if(Shape.Flag==PHYSICSSHAPE_CAPSULE) {
			real a=Shape.ShapeCapsule.a;
			real b=Shape.ShapeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Rotation);
			vector2d k2=vector2d{len/2,0}.Rotate(-Rotation);
			return abs((k1>>=l)-(k2>>=l))+a;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGE) {
			vector2d k1=vector2d{-Shape.ShapeEdge.Length/2,0}.Rotate(-Rotation);
			vector2d k2=vector2d{Shape.ShapeEdge.Length/2,0}.Rotate(-Rotation);
			return abs((k1>>=l)-(k2>>=l));
		} else if(Shape.Flag==PHYSICSSHAPE_EDGEBOX) {
			vector2d k1=vector2d {Shape.ShapeEdgeBox.a/2,Shape.ShapeEdgeBox.b/2};
			vector2d k2=vector2d {Shape.ShapeEdgeBox.a/2,-Shape.ShapeEdgeBox.b/2};
			vector2d k3=vector2d {-Shape.ShapeEdgeBox.a/2,-Shape.ShapeEdgeBox.b/2};
			vector2d k4=vector2d {-Shape.ShapeEdgeBox.a/2,Shape.ShapeEdgeBox.b/2};
			k1=k1.Rotate(-Rotation);
			k2=k2.Rotate(-Rotation);
			k3=k3.Rotate(-Rotation);
			k4=k4.Rotate(-Rotation);
			real l1=k1>>=l;
			real l2=k2>>=l;
			real l3=k3>>=l;
			real l4=k4>>=l;
			real maxn=max(max(l1,l2),max(l3,l4));
			real minn=min(min(l1,l2),min(l3,l4));
			return maxn-minn;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGEPOLYGON) {
			real maxn=0,minn=2*r;
			for(int i=0;i<Shape.ShapeEdgePolygon.N;i++) {
				vector2d k=Shape.ShapeEdgePolygon.Point[i].Rotate(-Rotation);
				real l1=k>>=l;
				maxn=max(maxn,l1);
				minn=min(minn,l1);
			}
			return maxn-minn;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGECAPSULE) {
			real a=Shape.ShapeEdgeCapsule.a;
			real b=Shape.ShapeEdgeCapsule.b;
			real len=(b-a);
			vector2d k1=vector2d{-len/2,0}.Rotate(-Rotation);
			vector2d k2=vector2d{len/2,0}.Rotate(-Rotation);
			return abs((k1>>=l)-(k2>>=l))+a;
		} else if(Shape.Flag==PHYSICSSHAPE_EDGECHAIN) {
			real maxn=0,minn=2*r;
			for(int i=0;i<Shape.ShapeEdgeChain.N;i++) {
				vector2d k=Shape.ShapeEdgeChain.Point[i].Rotate(-Rotation);
				real l1=k>>=l;
				maxn=max(maxn,l1);
				minn=min(minn,l1);
			}
			return maxn-minn;
		} 
		return 0;
	}
	vector2d PhysicsBody::GetV(vector2d p=vector2d{0,0}) {
		if(p==vector2d{0,0})return V+ImV;
		else {
			if(Rotation==0)return V+ImV;
			vector2d absPos=GetPosRel2Abs(p);
			vector2d h=absPos-Core;
			vector2d dir;
			if(Rotation>0)dir=h.Rotate(-GPE_PI/2);
			else dir=h.Rotate(GPE_PI/2);
			dir*=W;
			return V+ImV+dir;
		}
	}

	// 物理世界
	PhysicsWorld::PhysicsWorld() {
		Gravity=vector2d {0,-9.8};
		sap.Init(this);
	}
	void PhysicsWorld::Update() {
		int Clock=clock();
		bool Del[BODY_MAXN];
		// 删除已删除的物体
		int k,i;
		for(i=0; i<BodySum; i++)Del[i]=Body[i]->IsDel;
		for(i=0,k=0; i<BodySum; i++) {
			if(!Del[i]) {
				G[k]=G[i];
				Res[k]=Res[i];
				Body[k]=Body[i];
				k++;
			}
		}
		Body.erase((vector<PhysicsBody*>::iterator)(&Body[k]),Body.end());
		BodySum=k;
		// 删除已删除的关节
		for(i=0; i<SpringSum; i++)Del[i]=Spring[i]->IsRemove();
		for(i=0,k=0; i<SpringSum; i++)if(!Del[i])Spring[k++]=Spring[i];
		Spring.erase((vector<PhysicsJointSpring*>::iterator)(&Spring[k]),Spring.end());
		SpringSum=k;
		for(i=0; i<LimitSum; i++)Del[i]=Limit[i]->IsRemove();
		for(i=0,k=0; i<LimitSum; i++)if(!Del[i])Limit[k++]=Limit[i];
		Limit.erase((vector<PhysicsJointLimit*>::iterator)(&Limit[k]),Limit.end());
		LimitSum=k;
		for(i=0; i<LimitBSum; i++)Del[i]=LimitB[i]->IsRemove();
		for(i=0,k=0; i<LimitBSum; i++)if(!Del[i])LimitB[k++]=LimitB[i];
		LimitB.erase((vector<PhysicsJointLimitB*>::iterator)(&LimitB[k]),LimitB.end());
		LimitBSum=k;
		for(i=0; i<DistanceSum; i++)Del[i]=Distance[i]->IsRemove();
		for(i=0,k=0; i<DistanceSum; i++)if(!Del[i])Distance[k++]=Distance[i];
		Distance.erase((vector<PhysicsJointDistance*>::iterator)(&Distance[k]),Distance.end());
		DistanceSum=k;
		for(i=0; i<AttractSum; i++)Del[i]=Attract[i]->IsRemove();
		for(i=0,k=0; i<AttractSum; i++)if(!Del[i])Attract[k++]=Attract[i];
		Attract.erase((vector<PhysicsJointAttract*>::iterator)(&Attract[k]),Attract.end());
		AttractSum=k;
		// 更新物体
		if(!IsPaused) {
			for(int i=0; i<SpringSum; i++)Spring[i]->Update();
			for(int i=0; i<AttractSum; i++)Attract[i]->Update();
			for(int i=0; i<BodySum; i++) {
				Res[i].dir=Body[i]->GetV()*Mod(Body[i]->GetV())*Body[i]->GetWindwardArea()*Resistance*(-1);
				Body[i]->Update((Clock-PauseTime));
			}
			for(int i=0; i<LimitSum+LimitBSum+DistanceSum; i++) {
				for(int j=0; j<LimitSum; j++)Limit[j]->Update();
				for(int j=0; j<LimitBSum; j++)LimitB[j]->Update();
				for(int j=0; j<DistanceSum; j++)Distance[j]->Update();
			}
		}
		// 更新碰撞
		if(CollideEnabled) {
			BroadCollidePara.CollideBody.clear();
			BroadCollidePara.CollideBodyPair.clear();
			BroadCollidePara.CollideBodySum=0;
			BroadCollidePara.IsCollided.clear();
			if(BroadphaseAlgorithm=="DSAP")sap.Update(&BroadCollidePara);
			else if(BroadphaseAlgorithm=="SAP")collision::broadphase::SAP(this,&BroadCollidePara);
			else if(BroadphaseAlgorithm=="Violence")collision::broadphase::Violence(this,&BroadCollidePara);
			NarrowCollidePara.CollideBody.clear();
			NarrowCollidePara.CollideBodyPair.clear();
			NarrowCollidePara.CollideBodySum=0;
			NarrowCollidePara.IsCollided.clear();
			collision::narrowphase::Detect(&BroadCollidePara,&NarrowCollidePara);
			collision::constraint::Constraint(&NarrowCollidePara);
		}
		// 更新时间
		CostTime=clock()-Clock;
		return;
	}
	void PhysicsWorld::AddBody(PhysicsBody* body) {
		if(BodySum<Body.size())Body[BodySum]=body;
		else Body.push_back(body);
		// 加载重力
		Force g;
		g.SetPoint(&(body->Core));
		g.dir=Gravity*body->Mass;
		G[BodySum]=g;
		body->LoadForce(&G[BodySum]);
		body->GP=body->FSum-1;
		// 加载空气阻力
		Force r;
		r.SetPoint(&(body->Core));
		r.dir=0;
		Res[BodySum]=r;
		body->LoadForce(&Res[BodySum]);
		body->ResP=body->FSum-1;
		// 更新
		BodySum++;
	}
	void PhysicsWorld::AddBody(PhysicsJointSpring* s) {
		s->Remove(false);
		if(SpringSum<Spring.size())Spring[SpringSum]=s;
		else Spring.push_back(s);
		SpringSum++;
	}
	void PhysicsWorld::AddBody(PhysicsJointAttract* s) {
		s->Remove(false);
		if(AttractSum<Attract.size())Attract[AttractSum]=s;
		else Attract.push_back(s);
		AttractSum++;
	}
	void PhysicsWorld::AddBody(PhysicsJointLimit* s) {
		s->Remove(false);
		if(LimitSum<Limit.size())Limit[LimitSum]=s;
		else Limit.push_back(s);
		LimitSum++;
	}
	void PhysicsWorld::AddBody(PhysicsJointLimitB* s) {
		s->Remove(false);
		if(LimitBSum<LimitB.size())LimitB[LimitBSum]=s;
		else LimitB.push_back(s);
		LimitBSum++;
	}
	void PhysicsWorld::AddBody(PhysicsJointDistance* s) {
		s->Remove(false);
		if(DistanceSum<Distance.size())Distance[DistanceSum]=s;
		else Distance.push_back(s);
		DistanceSum++;
	}
	void PhysicsWorld::SetGravity(real g) {
		Gravity=vector2d {0,-g*1.0};
		for(int i=0; i<BodySum; i++) {
			G[i].dir=Gravity*Body[i]->Mass;
		}
	}
	real PhysicsWorld::GetGravity() {
		return Mod(Gravity);
	}
	int PhysicsWorld::GetBodyCount() {
		return BodySum;
	}
	void PhysicsWorld::Pause() {
		if(IsPaused)return;
		int c=clock();
		IsPaused=true;
		StartPauseTime=c;
	}
	void PhysicsWorld::Continue() {
		if(!IsStarted) {
			IsStarted=true;
			MBodySum=BodySum;
			MSpringSum=SpringSum;
			MLimitSum=LimitSum;
			MLimitBSum=LimitBSum;
			MDistanceSum=DistanceSum;
			MAttractSum=AttractSum;
			MBody.resize(BodySum);
			MSpring.resize(SpringSum);
			MLimit.resize(LimitSum);
			MLimitB.resize(LimitBSum);
			MDistance.resize(DistanceSum);
			MAttract.resize(AttractSum);
			MBodyP.resize(BodySum);
			MSpringP.resize(SpringSum);
			MLimitP.resize(LimitSum);
			MLimitBP.resize(LimitBSum);
			MDistanceP.resize(DistanceSum);
			MAttractP.resize(AttractSum);
			for(int i=0;i<BodySum;i++) {
				MBody[i]=*Body[i];
				MBodyP[i]=Body[i];
				MG[i]=G[i];
				MRes[i]=Res[i];
			}
			for(int i=0;i<SpringSum;i++)MSpring[i]=*Spring[i],MSpringP[i]=Spring[i];
			for(int i=0;i<LimitSum;i++)MLimit[i]=*Limit[i],MLimitP[i]=Limit[i];
			for(int i=0;i<LimitBSum;i++)MLimitB[i]=*LimitB[i],MLimitBP[i]=LimitB[i];
			for(int i=0;i<DistanceSum;i++)MDistance[i]=*Distance[i],MDistanceP[i]=Distance[i];
			for(int i=0;i<AttractSum;i++)MAttract[i]=*Attract[i],MAttractP[i]=Attract[i];
		}
		if(!IsPaused)return;
		IsPaused=false;
		int c=clock();
		PauseTime+=c-StartPauseTime;
	}
	void PhysicsWorld::ChangeState() {
		if(!IsPaused)Pause();
		else Continue();
	}
	int PhysicsWorld::GetTime() {
		return clock()-PauseTime;
	}
	void PhysicsWorld::SetResistance(real r) {
		Resistance=r;
	}
	real PhysicsWorld::GetResistance() {
		return Resistance;
	}
	void PhysicsWorld::Restart() {
		if(!IsStarted)return;
		// BodySum=MBodySum;
		// SpringSum=MSpringSum;
		// LimitSum=MLimitSum;
		// LimitBSum=MLimitBSum;
		// DistanceSum=MDistanceSum;
		// AttractSum=MAttractSum;
		// Body.resize(BodySum);
		// Spring.resize(SpringSum);
		// Limit.resize(LimitSum);
		// LimitB.resize(LimitBSum);
		// Distance.resize(DistanceSum);
		// Attract.resize(AttractSum);
		// for(int i=0;i<BodySum;i++) {
		// 	*Body[i]=MBody[i];
		// 	G[i]=MG[i];
		// 	Res[i]=MRes[i];
		// 	// Body[i]->F[Body[i]->GP]=&G[i];
		// 	// Body[i]->F[Body[i]->ResP]=&Res[i];
		// 	G[i].SetPointR(Body[i]);
		// 	Res[i].SetPointR(Body[i]);
		// }
		// for(int i=0;i<SpringSum;i++)*Spring[i]=MSpring[i];
		// for(int i=0;i<LimitSum;i++)*Limit[i]=MLimit[i];
		// for(int i=0;i<LimitBSum;i++)*LimitB[i]=MLimitB[i];
		// for(int i=0;i<DistanceSum;i++)*Distance[i]=MDistance[i];
		// for(int i=0;i<AttractSum;i++)*Attract[i]=MAttract[i];
		for(int i=0;i<MBodySum;i++) {
			*MBodyP[i]=MBody[i];
			MBodyP[i]->DelForce(MBodyP[i]->F[MBodyP[i]->GP]);
			MBodyP[i]->DelForce(MBodyP[i]->F[MBodyP[i]->ResP]);
		}
		for(int i=0;i<SpringSum;i++)*MSpringP[i]=MSpring[i];
		for(int i=0;i<LimitSum;i++)*MLimitP[i]=MLimit[i];
		for(int i=0;i<LimitBSum;i++)*MLimitBP[i]=MLimitB[i];
		for(int i=0;i<DistanceSum;i++)*MDistanceP[i]=MDistance[i];
		for(int i=0;i<AttractSum;i++)*MAttractP[i]=MAttract[i];
		BodySum=0;
		SpringSum=0;
		LimitSum=0;
		LimitBSum=0;
		DistanceSum=0;
		AttractSum=0;
		Body.clear();
		Spring.clear();
		Limit.clear();
		LimitB.clear();
		Distance.clear();
		Attract.clear();
		for(int i=0;i<MBodySum;i++)AddBody(MBodyP[i]);
		for(int i=0;i<MSpringSum;i++)AddBody(MSpringP[i]);
		for(int i=0;i<MLimitSum;i++)AddBody(MLimitP[i]);
		for(int i=0;i<MLimitBSum;i++)AddBody(MLimitBP[i]);
		for(int i=0;i<MDistanceSum;i++)AddBody(MDistanceP[i]);
		for(int i=0;i<MAttractSum;i++)AddBody(MAttractP[i]);
	}

	// 弹簧关节
	PhysicsJointSpring::PhysicsJointSpring() {
	}
	void PhysicsJointSpring::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		if(p1Type==1) {
			if(nl>Length)F1.dir=D1*(Mod(d1)-Length)*Restitution1;
			else F1.dir=D1*(Mod(d1)-Length)*Restitution2;
		}
		if(p2Type==1) {
			if(nl>Length)F2.dir=D2*(Mod(d2)-Length)*Restitution1;
			else F2.dir=D2*(Mod(d2)-Length)*Restitution1;
		}
	}
	void PhysicsJointSpring::SetLength(real l) {
		Length=l;
	}
	void PhysicsJointSpring::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelForce(&F1);
		body1=body;
		p1=p;
		F1.SetPointR(body,p);
		F1.dir=0;
		body->LoadForce(&F1);
	}
	void PhysicsJointSpring::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelForce(&F1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointSpring::SetPoint1(vector2d* p) {
		if(body1!=NULL)body1->DelForce(&F1);
		p1Type=2;
		p1p=p;
	}
	void PhysicsJointSpring::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		p2Type=1;
		if(body2!=NULL)body2->DelForce(&F2);
		body2=body;
		p2=p;
		F2.SetPointR(body,p);
		F2.dir=0;
		body->LoadForce(&F2);
	}
	void PhysicsJointSpring::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelForce(&F2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointSpring::SetPoint2(vector2d* p) {
		if(body2!=NULL)body2->DelForce(&F2);
		p2Type=2;
		p2p=p;
	}
	void PhysicsJointSpring::SetRestitution(real r) {
		Restitution1=r;
		Restitution2=r;
	}
	void PhysicsJointSpring::SetRestitution(real r1,real r2) {
		Restitution1=r1;
		Restitution2=r2;
	}
	vector2d PhysicsJointSpring::GetP1Pos() {
		if(p1Type==1)return F1.GetPoint();
		else if(p1Type==2)return *p1p;
		else return p1;
	}
	vector2d PhysicsJointSpring::GetP2Pos() {
		if(p2Type==1)return F2.GetPoint();
		else if(p2Type==2)return *p2p;
		else return p2;
	}
	PhysicsBody* PhysicsJointSpring::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointSpring::GetP2Body() {
		return body2;
	}
	Force PhysicsJointSpring::GetF1() {
		return F1;
	}
	Force PhysicsJointSpring::GetF2() {
		return F2;
	}
	void PhysicsJointSpring::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			F1.dir=F2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointSpring::IsRemove() {
		return IsDel;
	}

	// 限制关节
	PhysicsJointLimit::PhysicsJointLimit() {
	}
	void PhysicsJointLimit::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		vector2d Mid=(P1+P2)/2;
		vector2d v1;
		if(p1Type==1)v1=body1->GetV();
		else v1=vector2d {0,0};
		if(Length>=0) {
			if(p1Type==1) {
				if(nl>Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl>Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		} else {
			if(p1Type==1) {
				if(nl<-Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl<-Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		}
	}
	void PhysicsJointLimit::SetLength(real l) {
		Length=l;
	}
	void PhysicsJointLimit::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelImpulse(&I1);
		body1=body;
		I1.dir= {0,0};
		I1.SetPointR(body1,p);
		p1=p;
	}
	void PhysicsJointLimit::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelImpulse(&I1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointLimit::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=1;
		body2=body;
		I2.dir= {0,0};
		I2.SetPointR(body2,p);
		p2=p;
	}
	void PhysicsJointLimit::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointLimit::SetRestitution(real r) {
		Restitution1=r;
		Restitution2=r;
	}
	void PhysicsJointLimit::SetRestitution(real r1,real r2) {
		Restitution1=r1;
		Restitution2=r2;
	}
	vector2d PhysicsJointLimit::GetP1Pos() {
		if(p1Type==1)return I1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointLimit::GetP2Pos() {
		if(p2Type==1)return I2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointLimit::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointLimit::GetP2Body() {
		return body2;
	}
	void PhysicsJointLimit::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			I1.dir=I2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointLimit::IsRemove() {
		return IsDel;
	}

	// 反向限制关节
	PhysicsJointLimitB::PhysicsJointLimitB() {
	}
	void PhysicsJointLimitB::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		vector2d Mid=(P1+P2)/2;
		vector2d v1;
		if(p1Type==1)v1=body1->GetV();
		else v1=vector2d {0,0};
		if(Length>=0) {
			if(p1Type==1) {
				if(nl>Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl>Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		} else {
			if(p1Type==1) {
				if(nl<-Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl<-Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		}
	}
	void PhysicsJointLimitB::SetLength(real l) {
		Length=-l;
	}
	void PhysicsJointLimitB::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelImpulse(&I1);
		body1=body;
		I1.dir= {0,0};
		I1.SetPointR(body1,p);
		p1=p;
	}
	void PhysicsJointLimitB::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelImpulse(&I1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointLimitB::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=1;
		body2=body;
		I2.dir= {0,0};
		I2.SetPointR(body2,p);
		p2=p;
	}
	void PhysicsJointLimitB::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointLimitB::SetRestitution(real r) {
		Restitution1=r;
		Restitution2=r;
	}
	void PhysicsJointLimitB::SetRestitution(real r1,real r2) {
		Restitution1=r1;
		Restitution2=r2;
	}
	vector2d PhysicsJointLimitB::GetP1Pos() {
		if(p1Type==1)return I1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointLimitB::GetP2Pos() {
		if(p2Type==1)return I2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointLimitB::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointLimitB::GetP2Body() {
		return body2;
	}
	void PhysicsJointLimitB::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			I1.dir=I2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointLimitB::IsRemove() {
		return IsDel;
	}

	// 固定距离关节
	PhysicsJointDistance::PhysicsJointDistance() {
	}
	void PhysicsJointDistance::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		vector2d Mid=(P1+P2)/2;
		vector2d v1;
		if(p1Type==1)v1=body1->GetV();
		else v1=vector2d {0,0};
		if(nl>Length) {
			if(p1Type==1) {
				if(p2Type==1) {
					vector2d TempV=body1->GetV()-body2->GetV();
					body1->MoveTo(body1->Core+D1*(Mod(d1)-Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
					I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
					body1->AddImpulse(I1);
				} else {
					body1->MoveTo(body1->Core+D1*(Mod(d1)-Length));
					I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
					body1->AddImpulse(I1);
				}
			}
			if(p2Type==1) {
				if(p1Type==1) {
					vector2d TempV=body2->GetV()-v1;
					body2->MoveTo(body2->Core+D2*(Mod(d2)-Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
					I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
					body2->AddImpulse(I2);
				} else {
					body2->MoveTo(body2->Core+D2*(Mod(d2)-Length));
					I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
					body2->AddImpulse(I2);
				}
			}
		} else if(nl<Length) {
			if(p1Type==1) {
				if(p2Type==1) {
					vector2d TempV=body1->GetV()-body2->GetV();
					body1->MoveTo(body1->Core+D1*(Mod(d1)-Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
					I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
					body1->AddImpulse(I1);
				} else {
					body1->MoveTo(body1->Core+D1*(Mod(d1)-Length));
					I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
					body1->AddImpulse(I1);
				}
			}
			if(p2Type==1) {
				if(p1Type==1) {
					vector2d TempV=body2->GetV()-v1;
					body2->MoveTo(body2->Core+D2*(Mod(d2)-Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
					I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
					body2->AddImpulse(I2);
				} else {
					body2->MoveTo(body2->Core+D2*(Mod(d2)-Length));
					I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
					body2->AddImpulse(I2);
				}
			}
		}
	}
	void PhysicsJointDistance::SetLength(real l) {
		Length=l;
	}
	void PhysicsJointDistance::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelImpulse(&I1);
		body1=body;
		I1.dir= {0,0};
		I1.SetPointR(body1,p);
		p1=p;
	}
	void PhysicsJointDistance::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelImpulse(&I1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointDistance::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		p2Type=1;
		if(body2!=NULL)body2->DelImpulse(&I2);
		body2=body;
		I2.dir= {0,0};
		I2.SetPointR(body2,p);
		p2=p;
	}
	void PhysicsJointDistance::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointDistance::SetRestitution(real r) {
		Restitution1=r;
		Restitution2=r;
	}
	void PhysicsJointDistance::SetRestitution(real r1,real r2) {
		Restitution1=r1;
		Restitution2=r2;
	}
	vector2d PhysicsJointDistance::GetP1Pos() {
		if(p1Type==1)return I1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointDistance::GetP2Pos() {
		if(p2Type==1)return I2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointDistance::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointDistance::GetP2Body() {
		return body2;
	}
	void PhysicsJointDistance::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			I1.dir=I2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointDistance::IsRemove() {
		return IsDel;
	}

	// 固定关节
	PhysicsJointPin::PhysicsJointPin() {
	}
	void PhysicsJointPin::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		vector2d Mid=(P1+P2)/2;
		vector2d v1;
		if(p1Type==1)v1=body1->GetV();
		else v1=vector2d {0,0};
		if(Length>=0) {
			if(p1Type==1) {
				if(nl>Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)-Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl>Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)-Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		} else {
			if(p1Type==1) {
				if(nl<-Length) {
					if(p2Type==1) {
						vector2d TempV=body1->GetV()-body2->GetV();
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length)*(1.0*body2->Mass/(body1->Mass+body2->Mass)));
						I1.dir=body1->Mass*(TempV>>(P1-Mid))*(-1.0*body2->Mass/(body1->Mass+body2->Mass));
						body1->AddImpulse(I1);
					} else {
						body1->MoveTo(body1->Core+D1*(Mod(d1)+Length));
						I1.dir=-body1->Mass*((body1->GetV())>>(P1-Mid));
						body1->AddImpulse(I1);
					}
				}
			}
			if(p2Type==1) {
				if(nl<-Length) {
					if(p1Type==1) {
						vector2d TempV=body2->GetV()-v1;
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length)*(1.0*body1->Mass/(body1->Mass+body2->Mass)));
						I2.dir=body2->Mass*(TempV>>(P2-Mid))*(-1.0*body1->Mass/(body1->Mass+body2->Mass));
						body2->AddImpulse(I2);
					} else {
						body2->MoveTo(body2->Core+D2*(Mod(d2)+Length));
						I2.dir=-body2->Mass*((body2->GetV())>>(P2-Mid));
						body2->AddImpulse(I2);
					}
				}
			}
		}
	}
	void PhysicsJointPin::SetLength(real l) {
		Length=l;
	}
	void PhysicsJointPin::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelImpulse(&I1);
		body1=body;
		I1.dir= {0,0};
		I1.SetPointR(body1,p);
		p1=p;
	}
	void PhysicsJointPin::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelImpulse(&I1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointPin::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		p2Type=1;
		if(body2!=NULL)body2->DelImpulse(&I2);
		body2=body;
		I2.dir= {0,0};
		I2.SetPointR(body2,p);
		p2=p;
	}
	void PhysicsJointPin::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelImpulse(&I2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointPin::SetRestitution(real r) {
		Restitution1=r;
		Restitution2=r;
	}
	void PhysicsJointPin::SetRestitution(real r1,real r2) {
		Restitution1=r1;
		Restitution2=r2;
	}
	vector2d PhysicsJointPin::GetP1Pos() {
		if(p1Type==1)return I1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointPin::GetP2Pos() {
		if(p2Type==1)return I2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointPin::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointPin::GetP2Body() {
		return body2;
	}
	void PhysicsJointPin::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			I1.dir=I2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointPin::IsRemove() {
		return IsDel;
	}

	// 吸引关节
	PhysicsJointAttract::PhysicsJointAttract() {
	}
	void PhysicsJointAttract::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		if(nl==0) {
			F1.dir=F2.dir= {0,0};
		} else {
			if(p1Type==1) {
				F1.dir=Gravity*body1->Mass*body2->Mass/nl/nl*D1;
			}
			if(p2Type==1) {
				F2.dir=Gravity*body1->Mass*body2->Mass/nl/nl*D2;
			}
		}
	}
	void PhysicsJointAttract::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		if(body1!=NULL)body1->DelForce(&F1);
		body1=body;
		p1=p;
		F1.SetPointR(body,p);
		F1.dir=0;
		body->LoadForce(&F1);
	}
	void PhysicsJointAttract::SetPoint1(vector2d p) {
		if(body1!=NULL)body1->DelForce(&F1);
		p1Type=0;
		p1=p;
	}
	void PhysicsJointAttract::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		p2Type=1;
		if(body2!=NULL)body2->DelForce(&F2);
		body2=body;
		p2=p;
		F2.SetPointR(body,p);
		F2.dir=0;
		body->LoadForce(&F2);
	}
	void PhysicsJointAttract::SetPoint2(vector2d p) {
		if(body2!=NULL)body2->DelForce(&F2);
		p2Type=0;
		p2=p;
	}
	void PhysicsJointAttract::SetGravity(real g) {
		Gravity=g;
	}
	vector2d PhysicsJointAttract::GetP1Pos() {
		if(p1Type==1)return F1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointAttract::GetP2Pos() {
		if(p1Type==1)return F2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointAttract::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointAttract::GetP2Body() {
		return body2;
	}
	void PhysicsJointAttract::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			F1.dir=F2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointAttract::IsRemove() {
		return IsDel;
	}

	// 排斥关节
	PhysicsJointRepel::PhysicsJointRepel() {
	}
	void PhysicsJointRepel::Update() {
		vector2d P1=GetP1Pos();
		vector2d P2=GetP2Pos();
		real nl=Mod(P1-P2);
		vector2d d1=P2-P1,d2=P1-P2;
		vector2d D1,D2;
		if(Mod(d1)==0)D1= {0,1};
		else D1=d1/Mod(d1);
		if(Mod(d2)==0)D2= {0,1};
		else D2=d2/Mod(d2);
		if(nl==0) {
			F1.dir=F2.dir= {0,0};
		} else {
			if(p1Type==1) {
				F1.dir=Gravity*body1->Mass*body2->Mass/nl/nl*D1;
			}
			if(p2Type==1) {
				F2.dir=Gravity*body1->Mass*body2->Mass/nl/nl*D2;
			}
		}
	}
	void PhysicsJointRepel::SetPoint1(PhysicsBody* body,vector2d p= {0,0}) {
		p1Type=1;
		body1=body;
		p1=p;
		F1.SetPointR(body,p);
		F1.dir=0;
		body->LoadForce(&F1);
	}
	void PhysicsJointRepel::SetPoint1(vector2d p) {
		p1Type=0;
		p1=p;
	}
	void PhysicsJointRepel::SetPoint2(PhysicsBody* body,vector2d p= {0,0}) {
		p2Type=1;
		body2=body;
		p2=p;
		F2.SetPointR(body,p);
		F2.dir=0;
		body->LoadForce(&F2);
	}
	void PhysicsJointRepel::SetPoint2(vector2d p) {
		p2Type=0;
		p2=p;
	}
	void PhysicsJointRepel::SetGravity(real g) {
		Gravity=g;
	}
	vector2d PhysicsJointRepel::GetP1Pos() {
		if(p1Type==1)return F1.GetPoint();
		else return p1;
	}
	vector2d PhysicsJointRepel::GetP2Pos() {
		if(p1Type==1)return F2.GetPoint();
		else return p2;
	}
	PhysicsBody* PhysicsJointRepel::GetP1Body() {
		return body1;
	}
	PhysicsBody* PhysicsJointRepel::GetP2Body() {
		return body2;
	}
	void PhysicsJointRepel::Remove(bool remove=true) {
		if(remove) {
			IsDel=true;
			F1.dir=F2.dir=vector2d {0,0};
		} else IsDel=false;
	}
	bool PhysicsJointRepel::IsRemove() {
		return IsDel;
	}

}

#endif
