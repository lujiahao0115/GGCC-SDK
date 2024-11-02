// point.h
// ggcc数学-点/向量

#ifndef __GGCCMATHPOINT_H__
#define __GGCCMATHPOINT_H__

#include <bits/stdc++.h>

using realn=long double;

#ifndef PI
#define PI 3.14159265358979323846f
#endif

namespace ggcc {

	// 平面直角坐标系点
	struct point2d {
		realn x=0;				// （米m）
		realn y=0;				// （米m）
		void operator +=(const point2d &a);
		void operator -=(const point2d &a);
		void operator >>=(const point2d &a);
		void operator +=(const realn &a);
		void operator -=(const realn &a);
		void operator *=(const realn &a);
		void operator /=(const realn &a);
		point2d(realn X=0,realn Y=0) {
			x=X,y=Y;
		}
		const point2d operator-() const {
			return point2d(-x, -y);
		}
		point2d Rotate(realn);	// 旋转 
	};

	// 空间直角坐标系点
	struct point3d {
		realn x=0;				// （米m）
		realn y=0;				// （米m）
		realn z=0;				// （米m）
		void operator +=(const point3d &a);
		void operator -=(const point3d &a);
		void operator >>=(const point3d &a);
		void operator +=(const realn &a);
		void operator -=(const realn &a);
		void operator *=(const realn &a);
		void operator /=(const realn &a);
		point3d(realn X=0,realn Y=0,realn Z=0) {
			x=X,y=Y,z=Z;
		}
		const point3d operator-() const {
			return point3d(-x, -y, -z);
		}
		point3d Rotate(point3d,realn);// 旋转 
	};

#define axisX point2d {1,0}
#define axisY point2d {0,1} 
#define axisZ point3d {0,0,1} 
	
	// 声明
	point2d VecUnit(point2d); 
	point3d VecUnit(point3d);
	point2d operator +(const point2d& a,const point2d& b);
	point3d operator +(const point3d& a,const point3d& b);
	point2d operator +(const point2d& a,const realn& b);
	point3d operator +(const point3d& a,const realn& b);
	point2d operator -(const point2d& a,const point2d& b);
	point3d operator -(const point3d& a,const point3d& b);
	point2d operator -(const point2d& a,const realn& b);
	point3d operator -(const point3d& a,const realn& b);
	point2d operator *(const point2d& a,realn t);
	point3d operator *(const point3d& a,realn t);
	point2d operator *(realn t,const point2d& a);
	point3d operator *(realn t,const point3d& a);
	point2d operator /(const point2d& a,realn t);
	point3d operator /(const point3d& a,realn t);
	point2d operator /(realn t,const point2d& a);
	point3d operator /(realn t,const point3d& a);
	realn operator ^(const point2d& a,const point2d& b);
	point3d operator ^(const point3d& a,const point3d& b);

	// 运算符重载
	bool operator ==(const point2d& a,const point2d& b) {
		return abs(a.x-b.x)<=0.0000001&&abs(a.y-b.y)<=0.0000001;
	}
	bool operator ==(const point3d& a,const point3d& b) {
		return abs(a.x-b.x)<=0.0000001&&abs(a.y-b.y)<=0.0000001&&abs(a.z-b.z)<=0.0000001;
	}
	bool operator ==(const point2d& a,const double& b) {
		return a.x==0&&a.y==0&&b==0;
	}
	bool operator ==(const point3d& a,const double& b) {
		return a.x==0&&a.y==0&&a.z==0&&b==0;
	}
	bool operator !=(const point2d& a,const point2d& b) {
		return !(a==b);
	}
	bool operator !=(const point3d& a,const point3d& b) {
		return !(a==b);
	}
	// 向量加
	point2d operator +(const point2d& a,const point2d& b) {
		return point2d {a.x+b.x,a.y+b.y};
	}
	point3d operator +(const point3d& a,const point3d& b) {
		return point3d {a.x+b.x,a.y+b.y,a.z+b.z};
	}
	point2d operator +(const point2d& a,const realn& b) {
		return a+VecUnit(a)*b;
	}
	point3d operator +(const point3d& a,const realn& b) {
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
	void point2d::operator +=(const realn &a) {
		point2d t=(*this)+a;
		x=t.x,y=t.y;
	}
	void point3d::operator +=(const realn &a) {
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
	point2d operator -(const point2d& a,const realn& b) {
		return a-VecUnit(a)*b;
	}
	point3d operator -(const point3d& a,const realn& b) {
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
	void point2d::operator -=(const realn &a) {
		point2d t=(*this)-a;
		x=t.x,y=t.y;
	}
	void point3d::operator -=(const realn &a) {
		point3d t=(*this)-a;
		x=t.x,y=t.y,z=t.z;
	}
	// 向量乘除
	point2d operator *(const point2d& a,realn t) {
		return {a.x*t,a.y*t};
	}
	point3d operator *(const point3d& a,realn t) {
		return {a.x*t,a.y*t,a.z*t};
	}
	point2d operator *(realn t,const point2d& a) {
		return {a.x*t,a.y*t};
	}
	point3d operator *(realn t,const point3d& a) {
		return {a.x*t,a.y*t,a.z*t};
	}
	realn operator *(const point2d& a,const point2d& b) {
		return a.x*b.x+a.y*b.y;
	}
	realn operator *(const point3d& a,const point3d& b) {
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}
	void point2d::operator *=(const realn &a) {
		point2d t=(*this)*a;
		x=t.x,y=t.y;
	}
	void point3d::operator *=(const realn &a) {
		point3d t=(*this)*a;
		x=t.x,y=t.y,z=t.z;
	}
	point2d operator /(const point2d& a,realn t) {
		return {a.x/t,a.y/t};
	}
	point3d operator /(const point3d& a,realn t) {
		return {a.x/t,a.y/t,a.z/t};
	}
	point2d operator /(realn t,const point2d& a) {
		return {a.x/t,a.y/t};
	}
	point3d operator /(realn t,const point3d& a) {
		return {a.x/t,a.y/t,a.z/t};
	}
	void point2d::operator /=(const realn &a) {
		point2d t=(*this)/a;
		x=t.x,y=t.y;
	}
	void point3d::operator /=(const realn &a) {
		point3d t=(*this)/a;
		x=t.x,y=t.y,z=t.z;
	}

	// 向量点积
	realn Dot(point2d a,point2d b) {
		return a.x*b.x+a.y*b.y;
	}
	realn Dot(point3d a,point3d b) {
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}

	// 向量叉积
	realn Cross(point2d a,point2d b) {
		return a.x*b.y-a.y*b.x;
	}
	point3d Cross(point3d a,point3d b) {
		return point3d{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
	}
	realn operator ^(const point2d& a,const point2d& b) {
		return Cross(a,b);
	}
	point3d operator ^(const point3d& a,const point3d& b) {
		return Cross(a,b);
	}

	// 转化函数
	std::string to_string(point2d a,int p=2) {
		std::stringstream ss;
//		ss.setf(fixed);
		ss.precision(p);
		ss<<"("<<a.x<<","<<a.y<<")";
		return ss.str();
	}
	std::string to_string(point3d a,int p=2) {
		std::stringstream ss;
//		ss.setf(std::ios::fixed);
		ss.precision(p);
		ss<<std::setprecision(p)<<"("<<a.x<<","<<a.y<<","<<a.z<<")";
		return ss.str();
	}
	std::string to_string(realn a,int p=2) {
		std::stringstream ss;
//		ss.setf(std::ios::fixed);
		ss.precision(p);
		ss<<std::setprecision(p)<<a;
		return ss.str();
	}
	realn r2a(realn r) {			// 弧度转角度
		return r/3.1415926*180.0;
	}
	realn a2r(realn a) {			// 角度转弧度
		return a*3.1415626/180.0;
	}
#define R2A 57.295779513082320876798154814105
#define A2R 0.01745329251994329576923690768489
#define G_PI 3.1415926535897932384626433832795

	// 输出流重载
	std::ostream& operator <<(std::ostream& out,const point2d& a) {
		out<<'('<<a.x<<','<<a.y<<')';
		return out;
	}
	std::ostream& operator <<(std::ostream& out,const point3d& a) {
		out<<'('<<a.x<<','<<a.y<<','<<a.z<<')';
		return out;
	}

	// 向量模
	realn Mod(point2d a) {
		return sqrt(a.x*a.x+a.y*a.y);
	}
	realn Mod(point3d a) {
		return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}
	realn Mod2(point2d a) {
		return a.x*a.x+a.y*a.y;
	}
	realn Mod2(point3d a) {
		return a.x*a.x+a.y*a.y+a.z*a.z;
	}

	// 距离函数
	realn dis(point2d a,point2d b) {
		realn dx=abs(a.x-b.x);
		realn dy=abs(a.y-b.y);
		return sqrt(dx*dx+dy*dy);
	}
	realn dis(point3d a,point3d b) {
		realn dx=abs(a.x-b.x);
		realn dy=abs(a.y-b.y);
		realn dz=abs(a.z-b.z);
		return sqrt(dx*dx+dy*dy+dz*dz);
	}
	realn disx(point2d a,point2d b) {
		return abs(a.x-b.x);
	}
	realn disx(point3d a,point3d b) {
		return abs(a.x-b.x);
	}
	realn disy(point2d a,point2d b) {
		return abs(a.y-b.y);
	}
	realn disy(point3d a,point3d b) {
		return abs(a.y-b.y);
	}
	realn disz(point3d a,point3d b) {
		return abs(a.z-b.z);
	}
	
	// 夹角
	realn VecAngle(point2d a,point2d b) {
		realn ans=1.0*Dot(a,b)/Mod(a)/Mod(b);
		if(ans<=-1)return G_PI;
		else return acos(ans);
	}  
	realn VecAngle(point3d a,point3d b) {
		realn c=1.0*Dot(a,b)/Mod(a)/Mod(b);
		point3d z=Cross(a,b)/Mod(a)/Mod(b);
		realn s=1.0*Mod(z);
		if(s==0)return atan2(s,c);
		realn A,B,C,x1=0,y1=0,z1=0,x2=a.x,y2=a.y,z2=a.z,x3=b.x,y3=b.y,z3=b.y;
		A = (y3 - y1)*(z3 - z1) - (z2 -z1)*(y3 - y1);
		B = (x3 - x1)*(z2 - z1) - (x2 - x1)*(z3 - z1);
		C = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
		realn k=A*z.x+B*z.y+C*z.z;
		if(k>0)return atan2(s,c);
		return -atan2(s,c);
	}  
//	realn operator ^(const point2d& a,const point2d& b) {
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
	void point2d::operator >>=(const point2d& a) {
		*this=VecUnit(a)*Dot(*this,VecUnit(a));
	} 
	realn Shadow(point2d a,point2d b) {
		return Dot(a,VecUnit(b));
	}
	point2d ShadowV(point2d a,point2d b) {
		return VecUnit(b)*Dot(a,VecUnit(b));
	}
	point3d operator >>(const point3d& a,const point3d& b) {
		return VecUnit(b)*Dot(a,VecUnit(b));
	} 
	void point3d::operator >>=(const point3d& a) {
		*this=VecUnit(a)*Dot(*this,VecUnit(a));
	} 
	realn Shadow(point3d a,point3d b) {
		return Dot(a,VecUnit(b));
	}
	point3d ShadowV(point3d a,point3d b) {
		return VecUnit(b)*Dot(a,VecUnit(b));
	}
	
	// 向量旋转 
	point2d point2d::Rotate(realn a) {
		realn x2=x*cos(a)-y*sin(a);
		realn y2=x*sin(a)+y*cos(a);
		return point2d {x2,y2};
	}
	point3d point3d::Rotate(point3d v,realn a) {
		v=VecUnit(v);
		return (*this)*cos(a)+(v^(*this))*sin(a)+((*this)*v)*v*(1-cos(a));
	}
	
	// 绝对位置-相对位置转化
	point2d rel2abs(point2d p,point2d rfrc,realn rotate) {
		return p.Rotate(rotate)+rfrc;
	}
	point2d rel2abs(point2d p,point2d rfrc,point2d dir) {
		return p.Rotate(atan2(dir.y,dir.x))+rfrc;
	}
	point2d abs2rel(point2d p,point2d rfrc,realn rotate) {
		return (p-rfrc).Rotate(-rotate);
	}
	point2d abs2rel(point2d p,point2d rfrc,point2d dir) {
		return (p-rfrc).Rotate(-atan2(dir.y,dir.x));
	}

	// 向量
	typedef point2d vector2d;
	typedef point3d vector3d;

}

#endif
