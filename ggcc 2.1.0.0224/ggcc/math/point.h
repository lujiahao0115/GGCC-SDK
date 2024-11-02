// point.h
// ggcc数学-点/向量

#ifndef __GGCCMATHPOINT_H__
#define __GGCCMATHPOINT_H__

#define real double
#include <bits/stdc++.h>
using namespace std;

namespace ggcc {

	// 平面直角坐标系点
	struct point2d {
		real x=0;				// （米m）
		real y=0;				// （米m）
		void operator +=(const point2d &a);
		void operator -=(const point2d &a);
		void operator +=(const real &a);
		void operator -=(const real &a);
		void operator *=(const real &a);
		void operator /=(const real &a);
		point2d(real X=0,real Y=0) {
			x=X,y=Y;
		}
		point2d Rotate(real);	// 旋转 
	};

	// 空间直角坐标系点
	struct point3d {
		real x=0;				// （米m）
		real y=0;				// （米m）
		real z=0;				// （米m）
		void operator +=(const point3d &a);
		void operator -=(const point3d &a);
		void operator +=(const real &a);
		void operator -=(const real &a);
		void operator *=(const real &a);
		void operator /=(const real &a);
		point3d(real X=0,real Y=0,real Z=0) {
			x=X,y=Y,z=Z;
		}
		point3d Rotate(point3d,real);// 旋转 
	};

#define axisX point2d {1,0}
#define axisY point2d {0,1} 
#define axisZ point3d {0,0,1} 
	
	// 声明
	point2d VecUnit(point2d); 
	point3d VecUnit(point3d);
	point2d operator +(const point2d& a,const point2d& b);
	point3d operator +(const point3d& a,const point3d& b);
	point2d operator +(const point2d& a,const real& b);
	point3d operator +(const point3d& a,const real& b);
	point2d operator -(const point2d& a,const point2d& b);
	point3d operator -(const point3d& a,const point3d& b);
	point2d operator -(const point2d& a,const real& b);
	point3d operator -(const point3d& a,const real& b);
	point2d operator *(const point2d& a,real t);
	point3d operator *(const point3d& a,real t);
	point2d operator *(real t,const point2d& a);
	point3d operator *(real t,const point3d& a);
	point2d operator /(const point2d& a,real t);
	point3d operator /(const point3d& a,real t);
	point2d operator /(real t,const point2d& a);
	point3d operator /(real t,const point3d& a);
	real operator ^(const point2d& a,const point2d& b);
	point3d operator ^(const point3d& a,const point3d& b);

	// 运算符重载
	bool operator ==(const point2d& a,const point2d& b) {
		return a.x==b.x&&a.y==b.y;
	}
	bool operator ==(const point3d& a,const point3d& b) {
		return a.x==b.x&&a.y==b.y&&a.z==b.z;
	}
	bool operator ==(const point2d& a,const double& b) {
		return a.x==0&&a.y==0&&b==0;
	}
	bool operator ==(const point3d& a,const double& b) {
		return a.x==0&&a.y==0&&a.z==0&&b==0;
	}
	bool operator !=(const point2d& a,const point2d& b) {
		return a.x!=b.x||a.y!=b.y;
	}
	bool operator !=(const point3d& a,const point3d& b) {
		return a.x!=b.x||a.y!=b.y||a.z!=b.z;
	}
	// 向量加
	point2d operator +(const point2d& a,const point2d& b) {
		return point2d {a.x+b.x,a.y+b.y};
	}
	point3d operator +(const point3d& a,const point3d& b) {
		return point3d {a.x+b.x,a.y+b.y,a.z+b.z};
	}
	point2d operator +(const point2d& a,const real& b) {
		return a+VecUnit(a)*b;
	}
	point3d operator +(const point3d& a,const real& b) {
		return a+VecUnit(a)*b;
	}
	void point2d::operator +=(const point2d &a) {
		point2d t=(*this)+a;
		x=t.x,y=t.y;
	}
	void point3d::operator +=(const point3d &a) {
		point3d t=(*this)+a;
		x=t.x,y=t.y,z=t.z;
	}
	void point2d::operator +=(const real &a) {
		point2d t=(*this)+a;
		x=t.x,y=t.y;
	}
	void point3d::operator +=(const real &a) {
		point3d t=(*this)+a;
		x=t.x,y=t.y,z=t.z;
	}
	// 向量减
	point2d operator -(const point2d& a,const point2d& b) {
		return {a.x-b.x,a.y-b.y};
	}
	point3d operator -(const point3d& a,const point3d& b) {
		return {a.x-b.x,a.y-b.y,a.z-b.z};
	}
	point2d operator -(const point2d& a,const real& b) {
		return a-VecUnit(a)*b;
	}
	point3d operator -(const point3d& a,const real& b) {
		return a-VecUnit(a)*b;
	}
	void point2d::operator -=(const point2d &a) {
		point2d t=(*this)-a;
		x=t.x,y=t.y;
	}
	void point3d::operator -=(const point3d &a) {
		point3d t=(*this)-a;
		x=t.x,y=t.y,z=t.z;
	}
	void point2d::operator -=(const real &a) {
		point2d t=(*this)-a;
		x=t.x,y=t.y;
	}
	void point3d::operator -=(const real &a) {
		point3d t=(*this)-a;
		x=t.x,y=t.y,z=t.z;
	}
	// 向量乘除
	point2d operator *(const point2d& a,real t) {
		return {a.x*t,a.y*t};
	}
	point3d operator *(const point3d& a,real t) {
		return {a.x*t,a.y*t,a.z*t};
	}
	point2d operator *(real t,const point2d& a) {
		return {a.x*t,a.y*t};
	}
	point3d operator *(real t,const point3d& a) {
		return {a.x*t,a.y*t,a.z*t};
	}
	real operator *(const point2d& a,const point2d& b) {
		return a.x*b.x+a.y*b.y;
	}
	real operator *(const point3d& a,const point3d& b) {
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}
	void point2d::operator *=(const real &a) {
		point2d t=(*this)*a;
		x=t.x,y=t.y;
	}
	void point3d::operator *=(const real &a) {
		point3d t=(*this)*a;
		x=t.x,y=t.y,z=t.z;
	}
	point2d operator /(const point2d& a,real t) {
		return {a.x/t,a.y/t};
	}
	point3d operator /(const point3d& a,real t) {
		return {a.x/t,a.y/t,a.z/t};
	}
	point2d operator /(real t,const point2d& a) {
		return {a.x/t,a.y/t};
	}
	point3d operator /(real t,const point3d& a) {
		return {a.x/t,a.y/t,a.z/t};
	}
	void point2d::operator /=(const real &a) {
		point2d t=(*this)/a;
		x=t.x,y=t.y;
	}
	void point3d::operator /=(const real &a) {
		point3d t=(*this)/a;
		x=t.x,y=t.y,z=t.z;
	}

	// 向量点积
	real Dot(point2d a,point2d b) {
		return a.x*b.x+a.y*b.y;
	}
	real Dot(point3d a,point3d b) {
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}

	// 向量叉积
	real Cross(point2d a,point2d b) {
		return a.x*b.y-a.y*b.x;
	}
	point3d Cross(point3d a,point3d b) {
		return point3d{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
	}
	real operator ^(const point2d& a,const point2d& b) {
		return Cross(a,b);
	}
	point3d operator ^(const point3d& a,const point3d& b) {
		return Cross(a,b);
	}

	// 转化函数
	string to_string(point2d a,int p=2) {
		stringstream ss;
//		ss.setf(fixed);
		ss.precision(p);
		ss<<"("<<a.x<<","<<a.y<<")";
		return ss.str();
	}
	string to_string(point3d a,int p=2) {
		stringstream ss;
//		ss.setf(std::ios::fixed);
		ss.precision(p);
		ss<<setprecision(p)<<"("<<a.x<<","<<a.y<<","<<a.z<<")";
		return ss.str();
	}
	real r2a(real r) {			// 弧度转角度
		return r/3.1415926*180.0;
	}
	real a2r(real a) {			// 角度转弧度
		return a*3.1415626/180.0;
	}
#define R2A 57.295779513082320876798154814105
#define A2R 0.01745329251994329576923690768489
#define G_PI 3.1415926535897932384626433832795

	// 输出流重载
	ostream& operator <<(ostream& out,const point2d& a) {
		out<<'('<<a.x<<','<<a.y<<')';
		return out;
	}
	ostream& operator <<(ostream& out,const point3d& a) {
		out<<'('<<a.x<<','<<a.y<<','<<a.z<<')';
		return out;
	}

	// 向量模
	real Mod(point2d a) {
		return sqrt(a.x*a.x+a.y*a.y);
	}
	real Mod(point3d a) {
		return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}
	real Mod2(point2d a) {
		return a.x*a.x+a.y*a.y;
	}
	real Mod2(point3d a) {
		return a.x*a.x+a.y*a.y+a.z*a.z;
	}

	// 距离函数
	real dis(point2d a,point2d b) {
		real dx=abs(a.x-b.x);
		real dy=abs(a.y-b.y);
		return sqrt(dx*dx+dy*dy);
	}
	real dis(point3d a,point3d b) {
		real dx=abs(a.x-b.x);
		real dy=abs(a.y-b.y);
		real dz=abs(a.z-b.z);
		return sqrt(dx*dx+dy*dy+dz*dz);
	}
	real disx(point2d a,point2d b) {
		return abs(a.x-b.x);
	}
	real disx(point3d a,point3d b) {
		return abs(a.x-b.x);
	}
	real disy(point2d a,point2d b) {
		return abs(a.y-b.y);
	}
	real disy(point3d a,point3d b) {
		return abs(a.y-b.y);
	}
	real disz(point3d a,point3d b) {
		return abs(a.z-b.z);
	}
	
	// 夹角
	real VecAngle(point2d a,point2d b) {
		real ans=1.0*Dot(a,b)/Mod(a)/Mod(b);
		if(ans<=-1)return G_PI;
		else return acos(ans);
	}  
	real VecAngle(point3d a,point3d b) {
		real c=1.0*Dot(a,b)/Mod(a)/Mod(b);
		point3d z=Cross(a,b)/Mod(a)/Mod(b);
		real s=1.0*Mod(z);
		if(s==0)return atan2(s,c);
		real A,B,C,x1=0,y1=0,z1=0,x2=a.x,y2=a.y,z2=a.z,x3=b.x,y3=b.y,z3=b.y;
		A = (y3 - y1)*(z3 - z1) - (z2 -z1)*(y3 - y1);
		B = (x3 - x1)*(z2 - z1) - (x2 - x1)*(z3 - z1);
		C = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
		real k=A*z.x+B*z.y+C*z.z;
		if(k>0)return atan2(s,c);
		return -atan2(s,c);
	}  
//	real operator ^(const point2d& a,const point2d& b) {
//		return VecAngle(a,b);
//	}
	
	// 单位向量
	point2d VecUnit(point2d a) {
		if(Mod(a)==0)return {0,0};
		return a/(1.0*Mod(a));
	}
	point3d VecUnit(point3d a) {
		if(Mod(a)==0)return {0,0};
		return a/(1.0*Mod(a));
	}
	
	// 投影
	point2d operator >>(const point2d& a,const point2d& b) {
		return VecUnit(b)*Dot(a,VecUnit(b));
	} 
	real operator >>=(const point2d& a,const point2d& b) {
		return Dot(a,VecUnit(b));
	} 
	point3d operator >>(const point3d& a,const point3d& b) {
		return VecUnit(b)*Dot(a,VecUnit(b));
	} 
	real operator >>=(const point3d& a,const point3d& b) {
		return Dot(a,VecUnit(b));
	} 
	
	// 向量旋转 
	point2d point2d::Rotate(real a) {
		real x2=x*cos(a)-y*sin(a);
		real y2=x*sin(a)+y*cos(a);
		return point2d {x2,y2};
	}
	point3d point3d::Rotate(point3d v,real a) {
		v=VecUnit(v);
		return (*this)*cos(a)+(v^(*this))*sin(a)+((*this)*v)*v*(1-cos(a));
	}

	// 向量
	typedef point2d vector2d;
	typedef point3d vector3d;

}

#endif
