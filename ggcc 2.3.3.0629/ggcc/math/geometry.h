// point.h
// ggcc数学-点/向量

#ifndef __GGCCMATHGEOMETRY_H__
#define __GGCCMATHGEOMETRY_H__

#include <ggcc/math/point.h>

namespace ggcc {
	
	namespace ui {
		class GraphDebugger;
	}
	// 平面几何
	namespace pg {
		
		// AABB碰撞盒
		struct aabb {
			realn x1;
			realn y1;
			realn x2;
			realn y2;
		};
		
		// 平面图形
		class shape {
		public:
			vector2d pos = vector2d{0,0};					// 位置
			realn rotate = 0;								// 旋转弧度
			std::string type = "empty";							// 图形类型
			// 求支撑点
			virtual vector2d Support(vector2d u) {
				return pos;
			}
			// 计算AABB碰撞盒
			virtual aabb CalcAABB() {
				return aabb{0,0,0,0};
			}
			// 计算重心
			virtual vector2d CalcCenter() {
				return vector2d{0,0};
			}
			// 校准中心
			virtual void CheckCenter() {
				pos+=CalcCenter();
			}
			// 绝对位置
			virtual vector2d Abs(vector2d p) {
				return rel2abs(p,pos,rotate);
			}
			// 相对位置
			virtual vector2d Rel(vector2d p) {
				return abs2rel(p,pos,rotate);
			}
			// 绘制
			virtual void Draw(ui::GraphDebugger* G,realn r,realn g,realn b,realn a);
		};
		
		// 圆形
		class circle : public shape {
		public:
			double r = 0;
			circle(vector2d _pos=vector2d{0,0},realn _r=1) {
				type="circle";
				pos=_pos,r=_r;
			}
			vector2d CalcCenter() {
				return vector2d{0,0};
			}
			void CheckCenter() {
				pos+=CalcCenter();
			}
			vector2d Support(vector2d u) {
				return pos+VecUnit(u)*r;
			}
			void Draw(ui::GraphDebugger* G,realn r,realn g,realn b,realn a);
		};
		// 椭圆形
		class ellipse : public shape {
		public:
			double a=0,b=0;
			ellipse(vector2d _pos=vector2d{0,0},realn _a=1,realn _b=0.5) {
				type="ellipse";
				pos=_pos,a=_a,b=_b;
			}
			vector2d CalcCenter() {
				return vector2d{0,0};
			}
			void CheckCenter() {
				pos+=CalcCenter();
			}
			vector2d Support(vector2d u) {
				u.Rotate(-rotate);
				if(u.x==0&&u.y>0)return Abs(vector2d{0,b});
				if(u.x==0&&u.y<0)return Abs(vector2d{0,-b});
				if(u.y==0&&u.x>0)return Abs(vector2d{a,0});
				if(u.y==0&&u.x<0)return Abs(vector2d{-a,0});
				realn k=u.y/u.x;
				realn d=sqrt((a*a+b*b*k*k)/k/k);
				if(u*vector2d(0,d)<0)d=-d;
				realn x=k*d-(b*b*k*k*k*d)/(a*a+b*b*k*k);
				realn y=(b*b*k*k*d)/(a*a+b*b*k*k);
				return Abs(vector2d(x,y));
			}
			void Draw(ui::GraphDebugger* G,realn r,realn g,realn b,realn a);
		};
		// 多边形
		class polygon : public shape {
		private:
			realn r;
		public:
			std::vector<vector2d> p;
			polygon(vector2d _pos=vector2d{0,0},int _n=0,realn _r=1) {
				type="polygon";
				r=_r,pos=_pos;
				vector2d v={0,r};
				for(int i=0;i<_n;i++)p.push_back(v.Rotate(PI*2*i/_n));
			}
			vector2d CalcCenter() {
				vector2d ans={0,0};
				realn s=0;
				for(int i=1;i<p.size()-1;i++){
					realn ds=Cross(p[i]-p[0],p[i+1]-p[0]);
					ans+=(p[0]+p[i]+p[i+1])*ds/3;
					s+=ds;
				}
				return ans/s;
			}
			void CheckCenter() {
				vector2d temp=CalcCenter();
				pos+=temp;
				for(int i=0;i<p.size();i++)p[i]-=temp;
			}
			vector2d Support(vector2d u) {
				realn maxn=Shadow(Abs(p[0]),u);
				int maxp=0;
				for(int i=1;i<p.size();i++) {
					if(Shadow(Abs(p[i]),u)>maxn)maxn=Shadow(Abs(p[i]),u),maxp=i;
				}
				return Abs(p[maxp]);
			}
			void Draw(ui::GraphDebugger* G,realn r,realn g,realn b,realn a);
		};
		// 矩形
		class rectangle : public polygon {
		private:
			realn a,b;
		public:
			rectangle(vector2d _pos=vector2d{0,0},realn _a=1,realn _b=1) {
				a=_a,b=_b,pos=_pos;
				p.push_back({_a/2,-_b/2});
				p.push_back({_a/2,_b/2});
				p.push_back({-_a/2,_b/2});
				p.push_back({-_a/2,-_b/2});
			}
		};
		// 三角形
		class triangle : public polygon {
		private:
			realn a,b;
		public:
			triangle(vector2d p1={0,0},vector2d p2={1,0},vector2d p3={0,1}) {
				p.push_back(p1);
				p.push_back(p2);
				p.push_back(p3);
			}
		};
		
		// 碰撞检测
		namespace collide {
			
			// 是否发生碰撞
			bool IsCollide(shape *a,shape *b) {
				return false;
			}
			
		}
		
	}
}

#endif
