// geometry.h
// ggcc数学-几何

#ifndef __GGCCMATHGEOMETRY_H__
#define __GGCCMATHGEOMETRY_H__

#include <queue>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <complex>

using realn = long double;

#ifndef PI
	#define PI 3.14159265358979323846f
#endif

namespace ggcc {

	// 颜色
	namespace gc {

		unsigned rgb(unsigned r, unsigned g, unsigned b) {
			return (r << 16) | (g << 8) | b;
		}
		unsigned rgba(unsigned r, unsigned g, unsigned b, unsigned a) {
			return (a << 24) | (r << 16) | (g << 8) | b;
		}
		unsigned fade(unsigned color, realn a) {
			unsigned int alpha = (color >> 24);
			alpha = alpha * a;
			return (alpha << 24) | (color & 0x00ffffff);
		}
		const unsigned aliceBlue = 0xfff0f8ff,
		               antiqueWhite = 0xfffaebd7,
		               aqua = 0xff00ffff,
		               aquamarine = 0xff7fffd4,
		               azure = 0xfff0ffff,
		               beige = 0xfff5f5dc,
		               bisque = 0xffffe4c4,
		               black = 0xff000000,
		               blanchedAlmond = 0xffffebcd,
		               blue = 0xff0000ff,
		               blueViolet = 0xff8a2be2,
		               brown = 0xffa52a2a,
		               burlywood = 0xffdeb887,
		               cadetBlue = 0xff5f9ea0,
		               chartreuse = 0xff7fff00,
		               chocolate = 0xffd2691e,
		               coral = 0xffff7f50,
		               cornflowerBlue = 0xff6495ed,
		               cornsilk = 0xfffff8dc,
		               crimson = 0xffdc143c,
		               cyan = 0xff00ffff,
		               darkBlue = 0xff00008b,
		               darkCyan = 0xff008b8b,
		               darkGoldenrod = 0xffb8860b,
		               darkGray = 0xffa9a9a9,
		               darkGreen = 0xff006400,
		               darkKhaki = 0xffbdb76b,
		               darkMagenta = 0xff8b008b,
		               darkOliveGreen = 0xff556b2f,
		               darkOrange = 0xffff8c00,
		               darkOrchid = 0xff9932cc,
		               darkRed = 0xff8b0000,
		               darkSalmon = 0xffe9967a,
		               darkSeaGreen = 0xff8fbc8f,
		               darkSlateBlue = 0xff483d8b,
		               darkSlateGray = 0xff2f4f4f,
		               darkTurquoise = 0xff00ced1,
		               darkViolet = 0xff9400d3,
		               deepPink = 0xffff1493,
		               deepSkyBlue = 0xff00bfff,
		               dimGray = 0xff696969,
		               dodgerBlue = 0xff1e90ff,
		               firebrick = 0xffb22222,
		               floralWhite = 0xfffffaf0,
		               forestGreen = 0xff228b22,
		               fuchsia = 0xffff00ff,
		               gainsboro = 0xffdcdcdc,
		               ghostWhite = 0xfff8f8ff,
		               gold = 0xffffd700,
		               goldenrod = 0xffdaa520,
		               gray = 0xffbebebe,
		               gray1 = 0xff1a1a1a,
		               gray2 = 0xff333333,
		               gray3 = 0xff4d4d4d,
		               gray4 = 0xff666666,
		               gray5 = 0xff7f7f7f,
		               gray6 = 0xff999999,
		               gray7 = 0xffb3b3b3,
		               gray8 = 0xffcccccc,
		               gray9 = 0xffe5e5e5,
		               green = 0xff00ff00,
		               greenYellow = 0xffadff2f,
		               honeydew = 0xfff0fff0,
		               hotPink = 0xffff69b4,
		               indianRed = 0xffcd5c5c,
		               indigo = 0xff4b0082,
		               ivory = 0xfffffff0,
		               khaki = 0xfff0e68c,
		               lavender = 0xffe6e6fa,
		               lavenderBlush = 0xfffff0f5,
		               lawnGreen = 0xff7cfc00,
		               lemonChiffon = 0xfffffacd,
		               lightBlue = 0xffadd8e6,
		               lightCoral = 0xfff08080,
		               lightCyan = 0xffe0ffff,
		               lightGoldenrod = 0xffeedd82,
		               lightGoldenrodYellow = 0xfffafad2,
		               lightGray = 0xffd3d3d3,
		               lightGreen = 0xff90ee90,
		               lightPink = 0xffffb6c1,
		               lightSalmon = 0xffffa07a,
		               lightSeaGreen = 0xff20b2aa,
		               lightSkyBlue = 0xff87cefa,
		               lightSlateBlue = 0xff8470ff,
		               lightSlateGray = 0xff778899,
		               lightSteelBlue = 0xffb0c4de,
		               lightYellow = 0xffffffe0,
		               lime = 0xff00ff00,
		               limeGreen = 0xff32cd32,
		               linen = 0xfffaf0e6,
		               magenta = 0xffff00ff,
		               maroon = 0xffb03060,
		               mediumAquamarine = 0xff66cdaa,
		               mediumBlue = 0xff0000cd,
		               mediumOrchid = 0xffba55d3,
		               mediumPurple = 0xff9370db,
		               mediumSeaGreen = 0xff3cb371,
		               mediumSlateBlue = 0xff7b68ee,
		               mediumSpringGreen = 0xff00fa9a,
		               mediumTurquoise = 0xff48d1cc,
		               mediumVioletRed = 0xffc71585,
		               midnightBlue = 0xff191970,
		               mintCream = 0xfff5fffa,
		               mistyRose = 0xffffe4e1,
		               moccasin = 0xffffe4b5,
		               navajoWhite = 0xffffdead,
		               navy = 0xff000080,
		               navyBlue = 0xff000080,
		               oldLace = 0xfffdf5e6,
		               olive = 0xff808000,
		               oliveDrab = 0xff6b8e23,
		               orange = 0xffffa500,
		               orangeRed = 0xffff4500,
		               orchid = 0xffda70d6,
		               paleGoldenrod = 0xffeee8aa,
		               paleGreen = 0xff98fb98,
		               paleTurquoise = 0xffafeeee,
		               paleVioletRed = 0xffdb7093,
		               papayaWhip = 0xffffefd5,
		               peachPuff = 0xffffdab9,
		               peru = 0xffcd853f,
		               pink = 0xffffc0cb,
		               plum = 0xffdda0dd,
		               powderBlue = 0xffb0e0e6,
		               purple = 0xffa020f0,
		               rebeccaPurple = 0xff663399,
		               red = 0xffff0000,
		               rosyBrown = 0xffbc8f8f,
		               royalBlue = 0xff4169e1,
		               saddleBrown = 0xff8b4513,
		               salmon = 0xfffa8072,
		               sandyBrown = 0xfff4a460,
		               seaGreen = 0xff2e8b57,
		               seashell = 0xfffff5ee,
		               sienna = 0xffa0522d,
		               silver = 0xffc0c0c0,
		               skyBlue = 0xff87ceeb,
		               slateBlue = 0xff6a5acd,
		               slateGray = 0xff708090,
		               snow = 0xfffffafa,
		               springGreen = 0xff00ff7f,
		               steelBlue = 0xff4682b4,
		               teal = 0xff008080,
		               thistle = 0xffd8bfd8,
		               tomato = 0xffff6347,
		               turquoise = 0xff40e0d0,
		               violet = 0xffee82ee,
		               violetRed = 0xffd02090,
		               wheat = 0xfff5deb3,
		               white = 0xffffffff,
		               whiteSmoke = 0xfff5f5f5,
		               yellow = 0xffffff00,
		               yellowGreen = 0xff9acd32;
	};

	// 平面直角坐标系点
	struct point2d {
		realn x = 0;				// （米m）
		realn y = 0;				// （米m）
		void operator +=(const point2d &a);
		void operator -=(const point2d &a);
		void operator >>=(const point2d &a);
		void operator +=(const realn &a);
		void operator -=(const realn &a);
		void operator *=(const realn &a);
		void operator /=(const realn &a);
		point2d(realn X, realn Y) : x(X), y(Y) {}
		point2d(std::complex<double> p) : x(p.real()), y(p.imag()) {}
		point2d(std::vector<realn>& v) : x(v[0]), y(v[1]) {}
		point2d() : x(0), y(0) {}
		const point2d operator-() const {
			return point2d(-x, -y);
		}
		point2d& operator=(const std::complex<double>& p) {
			x = p.real(), y = p.imag();
			return *this;
		}
		point2d& operator=(const std::vector<realn>& p) {
			x = p[0], y = p[1];
			return *this;
		}
		const realn Arg() {		// 辐角
			return atan2(y, x);
		}
		point2d Rotate(realn);	// 旋转
	};

	// 空间直角坐标系点
	struct point3d {
		realn x = 0;				// （米m）
		realn y = 0;				// （米m）f
		realn z = 0;				// （米m）
		void operator +=(const point3d &a);
		void operator -=(const point3d &a);
		void operator >>=(const point3d &a);
		void operator +=(const realn &a);
		void operator -=(const realn &a);
		void operator *=(const realn &a);
		void operator /=(const realn &a);
		point3d(realn X, realn Y, realn Z) : x(X), y(Y), z(Z) {}
		point3d(point2d p) : x(p.x), y(p.y), z(0) {}
		point3d(std::vector<realn>& v) : x(v[0]), y(v[1]), z(v[2]) {}
		point3d() : x(0), y(0), z(0) {}
		const point3d operator-() const {
			return point3d(-x, -y, -z);
		}
		point3d& operator=(const point2d& p) {
			x = p.x, y = p.y, z = 0.0;
			return *this;
		}
		point3d& operator=(const std::vector<realn>& p) {
			x = p[0], y = p[1], z = p[2];
			return *this;
		}
		point3d Rotate(point3d, realn); // 旋转
	};

	namespace pg {
		const point2d axisX = point2d(1, 0);
		const point2d axisY = point2d(0, 1);
		const point2d origin = point2d(0, 0);
	}
	namespace sg {
		const point3d axisX = point3d(1, 0, 0);
		const point3d axisY = point3d(0, 1, 0);
		const point3d axisZ = point3d(0, 0, 1);
		const point3d origin = point3d(0, 0, 0);
	}

	// 声明
	point2d VecUnit(point2d);
	point3d VecUnit(point3d);
	point2d operator +(const point2d& a, const point2d& b);
	point3d operator +(const point3d& a, const point3d& b);
	point2d operator +(const point2d& a, const realn& b);
	point3d operator +(const point3d& a, const realn& b);
	point2d operator -(const point2d& a, const point2d& b);
	point3d operator -(const point3d& a, const point3d& b);
	point2d operator -(const point2d& a, const realn& b);
	point3d operator -(const point3d& a, const realn& b);
	point2d operator *(const point2d& a, realn t);
	point3d operator *(const point3d& a, realn t);
	point2d operator *(realn t, const point2d& a);
	point3d operator *(realn t, const point3d& a);
	point2d operator /(const point2d& a, realn t);
	point3d operator /(const point3d& a, realn t);
	point2d operator /(realn t, const point2d& a);
	point3d operator /(realn t, const point3d& a);
	realn operator ^(const point2d& a, const point2d& b);
	point3d operator ^(const point3d& a, const point3d& b);

	// 运算符重载
	bool operator ==(const point2d& a, const point2d& b) {
		return std::fabs(a.x - b.x) <= 0.0000001 && std::fabs(a.y - b.y) <= 0.0000001;
	}
	bool operator ==(const point3d& a, const point3d& b) {
		return std::fabs(a.x - b.x) <= 0.0000001 && std::fabs(a.y - b.y) <= 0.0000001 && std::fabs(a.z - b.z) <= 0.0000001;
	}
	bool operator ==(const point2d& a, const double& b) {
		return a.x == 0 && a.y == 0 && b == 0;
	}
	bool operator ==(const point3d& a, const double& b) {
		return a.x == 0 && a.y == 0 && a.z == 0 && b == 0;
	}
	bool operator !=(const point2d& a, const point2d& b) {
		return !(a == b);
	}
	bool operator !=(const point3d& a, const point3d& b) {
		return !(a == b);
	}
	// 向量加
	point2d operator +(const point2d& a, const point2d& b) {
		return point2d {a.x + b.x, a.y + b.y};
	}
	point3d operator +(const point3d& a, const point3d& b) {
		return point3d {a.x + b.x, a.y + b.y, a.z + b.z};
	}
	point2d operator +(const point2d& a, const realn& b) {
		return a + VecUnit(a) * b;
	}
	point3d operator +(const point3d& a, const realn& b) {
		return a + VecUnit(a) * b;
	}
	void point2d::operator +=(const point2d &a) {
		point2d t = (*this) + a;
		x = t.x, y = t.y;
	}
	void point3d::operator +=(const point3d &a) {
		point3d t = (*this) + a;
		x = t.x, y = t.y, z = t.z;
	}
	void point2d::operator +=(const realn &a) {
		point2d t = (*this) + a;
		x = t.x, y = t.y;
	}
	void point3d::operator +=(const realn &a) {
		point3d t = (*this) + a;
		x = t.x, y = t.y, z = t.z;
	}
	// 向量减
	point2d operator -(const point2d& a, const point2d& b) {
		return {a.x - b.x, a.y - b.y};
	}
	point3d operator -(const point3d& a, const point3d& b) {
		return {a.x - b.x, a.y - b.y, a.z - b.z};
	}
	point2d operator -(const point2d& a, const realn& b) {
		return a - VecUnit(a) * b;
	}
	point3d operator -(const point3d& a, const realn& b) {
		return a - VecUnit(a) * b;
	}
	void point2d::operator -=(const point2d &a) {
		point2d t = (*this) - a;
		x = t.x, y = t.y;
	}
	void point3d::operator -=(const point3d &a) {
		point3d t = (*this) - a;
		x = t.x, y = t.y, z = t.z;
	}
	void point2d::operator -=(const realn &a) {
		point2d t = (*this) - a;
		x = t.x, y = t.y;
	}
	void point3d::operator -=(const realn &a) {
		point3d t = (*this) - a;
		x = t.x, y = t.y, z = t.z;
	}
	// 向量乘除
	point2d operator *(const point2d& a, realn t) {
		return {a.x*t, a.y*t};
	}
	point3d operator *(const point3d& a, realn t) {
		return {a.x*t, a.y*t, a.z*t};
	}
	point2d operator *(realn t, const point2d& a) {
		return {a.x*t, a.y*t};
	}
	point3d operator *(realn t, const point3d& a) {
		return {a.x*t, a.y*t, a.z*t};
	}
	realn operator *(const point2d& a, const point2d& b) {
		return a.x*b.x + a.y*b.y;
	}
	realn operator *(const point3d& a, const point3d& b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
	void point2d::operator *=(const realn &a) {
		point2d t = (*this) * a;
		x = t.x, y = t.y;
	}
	void point3d::operator *=(const realn &a) {
		point3d t = (*this) * a;
		x = t.x, y = t.y, z = t.z;
	}
	point2d operator /(const point2d& a, realn t) {
		return {a.x / t, a.y / t};
	}
	point3d operator /(const point3d& a, realn t) {
		return {a.x / t, a.y / t, a.z / t};
	}
	point2d operator /(realn t, const point2d& a) {
		return {a.x / t, a.y / t};
	}
	point3d operator /(realn t, const point3d& a) {
		return {a.x / t, a.y / t, a.z / t};
	}
	void point2d::operator /=(const realn &a) {
		point2d t = (*this) / a;
		x = t.x, y = t.y;
	}
	void point3d::operator /=(const realn &a) {
		point3d t = (*this) / a;
		x = t.x, y = t.y, z = t.z;
	}

	// 向量点积
	realn Dot(point2d a, point2d b) {
		return a.x*b.x + a.y*b.y;
	}
	realn Dot(point3d a, point3d b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	// 向量叉积
	realn Cross(point2d a, point2d b) {
		return a.x*b.y - a.y*b.x;
	}
	point3d Cross(point3d a, point3d b) {
		return point3d{a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
	}
	realn operator ^(const point2d& a, const point2d& b) {
		return Cross(a, b);
	}
	point3d operator ^(const point3d& a, const point3d& b) {
		return Cross(a, b);
	}

	// 转化函数
	realn r2a(realn r) {			// 弧度转角度
		return r / 3.1415926 * 180.0;
	}
	realn a2r(realn a) {			// 角度转弧度
		return a * 3.1415626 / 180.0;
	}
	const realn R2A = 57.295779513082320876798154814105;
	const realn A2R = 0.01745329251994329576923690768489;
	const realn G_PI = 3.1415926535897932384626433832795;

	// 输出流重载
	std::ostream& operator <<(std::ostream& out, const point2d& a) {
		out << '(' << a.x << ',' << a.y << ')';
		return out;
	}
	std::ostream& operator <<(std::ostream& out, const point3d& a) {
		out << '(' << a.x << ',' << a.y << ',' << a.z << ')';
		return out;
	}

	// 向量模
	realn Mod(const point2d& a) {
		return sqrt(a.x*a.x + a.y*a.y);
	}
	realn Mod(const point3d& a) {
		return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	}
	realn Mod2(const point2d& a) {
		return a.x*a.x + a.y*a.y;
	}
	realn Mod2(const point3d& a) {
		return a.x*a.x + a.y*a.y + a.z*a.z;
	}

	// 距离函数
	realn dis(point2d a, point2d b) {
		realn dx = std::fabs(a.x - b.x);
		realn dy = std::fabs(a.y - b.y);
		return sqrt(dx*dx + dy*dy);
	}
	realn dis(point3d a, point3d b) {
		realn dx = std::fabs(a.x - b.x);
		realn dy = std::fabs(a.y - b.y);
		realn dz = std::fabs(a.z - b.z);
		return sqrt(dx*dx + dy*dy + dz*dz);
	}
	realn disx(point2d a, point2d b) {
		return std::fabs(a.x - b.x);
	}
	realn disx(point3d a, point3d b) {
		return std::fabs(a.x - b.x);
	}
	realn disy(point2d a, point2d b) {
		return std::fabs(a.y - b.y);
	}
	realn disy(point3d a, point3d b) {
		return std::fabs(a.y - b.y);
	}
	realn disz(point3d a, point3d b) {
		return std::fabs(a.z - b.z);
	}

	// 夹角
	realn VecAngle(const point2d& a, const point2d& b) {
		realn ma = Mod(a), mb = Mod(b);
		if (ma == 0 || mb == 0) return 0;
		realn c = 1.0 * Dot(a, b) / ma / mb;
		realn s = 1.0 * Cross(a, b) / ma / mb;
		return atan2(s, c);
	}
	realn VecAngle(const point3d& a, const point3d& b) {
		realn ma = Mod(a), mb = Mod(b);
		if (ma == 0 || mb == 0) return 0;
		realn c = 1.0 * Dot(a, b) / ma / mb;
		point3d z = Cross(a, b) / ma / mb;
		realn s = 1.0 * Mod(z);
		if (s == 0)return atan2(s, c);
		realn A, B, C, x1 = 0, y1 = 0, z1 = 0, x2 = a.x, y2 = a.y, z2 = a.z, x3 = b.x, y3 = b.y, z3 = b.y;
		A = (y3 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1);
		B = (x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1);
		C = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
		realn k = A*z.x + B*z.y + C*z.z;
		if (k > 0)return atan2(s, c);
		return -atan2(s, c);
	}

	// 单位向量
	point2d VecUnit(point2d a) {
		if (Mod(a) == 0)return {0, 0};
		return a / (1.0 * Mod(a));
	}
	point2d VecUnit(realn deg) {
		return point2d(cos(deg), sin(deg));
	}
	point3d VecUnit(point3d a) {
		if (Mod(a) == 0)return {0, 0, 0};
		return a / (1.0 * Mod(a));
	}
	point3d VecUnit(realn l, realn v) {
		return point3d(cos(l) * cos(v), sin(l) * cos(v), sin(v));
	}

	// 投影
	point2d operator >>(const point2d& a, const point2d& b) {
		return VecUnit(b) * Dot(a, VecUnit(b));
	}
	void point2d::operator >>=(const point2d& a) {
		*this = VecUnit(a) * Dot(*this, VecUnit(a));
	}
	realn Shadow(point2d a, point2d b) {
		return Dot(a, VecUnit(b));
	}
	point2d ShadowV(point2d a, point2d b) {
		return VecUnit(b) * Dot(a, VecUnit(b));
	}
	point3d operator >>(const point3d& a, const point3d& b) {
		return VecUnit(b) * Dot(a, VecUnit(b));
	}
	void point3d::operator >>=(const point3d& a) {
		*this = VecUnit(a) * Dot(*this, VecUnit(a));
	}
	realn Shadow(point3d a, point3d b) {
		return Dot(a, VecUnit(b));
	}
	point3d ShadowV(point3d a, point3d b) {
		return VecUnit(b) * Dot(a, VecUnit(b));
	}

	// 向量旋转
	point2d point2d::Rotate(realn a) {
		realn x2 = x*cos(a) - y*sin(a);
		realn y2 = x*sin(a) + y*cos(a);
		return point2d {x2, y2};
	}
	point3d point3d::Rotate(point3d v, realn a) {
		v = VecUnit(v);
		return (*this) * cos(a) + (v^(*this)) * sin(a) + ((*this) * v) * v*(1 - cos(a));
	}

	// 绝对位置-相对位置转化
	point2d rel2abs(point2d p, point2d rfrc, realn rotate) {
		return p.Rotate(rotate) + rfrc;
	}
	point2d rel2abs(point2d p, point2d rfrc, point2d dir) {
		return p.Rotate(atan2(dir.y, dir.x)) + rfrc;
	}
	point2d abs2rel(point2d p, point2d rfrc, realn rotate) {
		return (p - rfrc).Rotate(-rotate);
	}
	point2d abs2rel(point2d p, point2d rfrc, point2d dir) {
		return (p - rfrc).Rotate(-atan2(dir.y, dir.x));
	}

	// 对称
	point2d AxialSymmetry(point2d dir, point2d v) {
		return v.Rotate(VecAngle(v, dir) * 2);
	}
	point2d CentralSymmetry(point2d o, point2d v) {
		return 2 * o - v;
	}

	// 向量
	typedef point2d vector2d;
	typedef point3d vector3d;

	// 平面几何
	namespace pg {

		// AABB碰撞盒
		struct aabb {
			realn x1;
			realn y1;
			realn x2;
			realn y2;
			static aabb Merge(const aabb& a, const aabb& b) {
				realn x1 = std::min(a.x1, b.x1);
				realn x2 = std::min(a.x2, b.x2);
				realn y1 = std::min(a.y1, b.y1);
				realn y2 = std::min(a.y2, b.y2);
				return aabb {x1, x2, y1, y2};
			}
			static bool Collide(const aabb& a, const aabb& b) {
				if (a.x2 < b.x1) return false;
				if (a.x1 > b.x2) return false;
				if (a.y2 < b.y1) return false;
				if (a.y1 > b.y2) return false;
				return true;
			}
		};

		// 图形类型
		enum ShapeType {
			shapetype_empty = 0,		// 空白图形
			shapetype_point = 1,		// 点
			shapetype_segment = 2,		// 线段
			shapetype_circle = 3,		// 圆形
			shapetype_ellipse = 4,		// 椭圆形
			shapetype_polygon = 5,		// 多边形
			shapetype_roundpoly = 6,	// 圆角多边形
			shapetype_capsule = 7		// 胶囊形
		};

		// 平面图形
		class shape {
		protected:
			ShapeType type = shapetype_empty;				// 图形类型

		public:
			vector2d pos = vector2d{0, 0};					// 位置
			vector2d bias = vector2d{0, 0};					// 重心偏移量
			realn rotate = 0;								// 旋转弧度
			// 获取形状类型
			ShapeType GetShapeType() {
				return type;
			}
			// 求支撑点
			virtual vector2d Support(vector2d u) {
				return pos;
			}
			// 计算AABB碰撞盒
			virtual aabb CalcAABB() {
				return aabb{0, 0, 0, 0};
			}
			// 计算重心
			virtual vector2d CalcCenter() {
				return vector2d{0, 0};
			}
			// 偏移重心
			void SetBias(vector2d bias_) {
				bias = bias_;
			}
			// 计算面积
			virtual realn CalcArea() {
				return 0;
			}
			// 计算转动惯量
			virtual realn CalcInertia() {
				return 0;
			}
			// 校准中心
			virtual void CheckCenter() {
				pos += CalcCenter();
			}
			// 绝对位置
			vector2d Abs(const vector2d& p) {
				return rel2abs(p, pos, rotate);
			}
			// 相对位置
			vector2d Rel(const vector2d& p) {
				return abs2rel(p, pos, rotate);
			}
			// 运动
			void MoveForward(realn dis) {
				pos += VecUnit(rotate) * dis;
			}
			void TurnLeft(realn angle) {
				rotate += angle;
			}
			void TurnRight(realn angle) {
				rotate -= angle;
			}
			void FaceTo(vector2d target) {
				rotate = (target - pos).Arg();
			}
			void FaceTo(realn target) {
				rotate = target;
			}
			// 绘制
			virtual void Draw(unsigned color) = 0;
			virtual void DrawLines(unsigned color) = 0;
		};

		// 点
		class point : public shape {
		public:
			point(vector2d pos_ = vector2d(0, 0)) {
				type = shapetype_point;
				pos = pos_;
			}
			vector2d Support(vector2d u) {
				return pos;
			}
			aabb CalcAABB() {
				return aabb{pos.x, pos.y, pos.x, pos.y};
			}
			vector2d CalcCenter() {
				return pos;
			}
			void CheckCenter() {}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 线段
		class segment : public shape {
		public:
			vector2d p1;
			vector2d p2;
			segment(vector2d p1_, vector2d p2_) {
				type = shapetype_segment;
				p1 = p1_, p2 = p2_;
			}
			segment() {};
			realn Length() {
				return Mod(p1 - p2);
			}
			vector2d Support(vector2d u) {
				u = u.Rotate(-rotate);
				vector2d v = p2 - p1;
				if (u * v > 0) return Abs(p2);
				return Abs(p1);
			}
			aabb CalcAABB() {
				aabb ans;
				vector2d v1 = Abs(p1);
				vector2d v2 = Abs(p2);
				ans.x1 = std::min(v1.x, v2.x);
				ans.x2 = std::max(v1.x, v2.x);
				ans.y1 = std::min(v1.y, v2.y);
				ans.y2 = std::max(v1.y, v2.y);
				return ans;
			}
			vector2d CalcCenter() {
				return (p1 + p2) / 2 + bias;
			}
			void CheckCenter() {
				vector2d v = CalcCenter();
				pos += v, p1 -= v, p2 -= v;
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 圆形
		class circle : public shape {
		public:
			double r = 0;
			circle(vector2d _pos = vector2d{0, 0}, realn _r = 1) {
				type = shapetype_circle;
				pos = _pos, r = _r;
			}
			vector2d Support(vector2d u) override {
				return pos + VecUnit(u) * r;
			}
			aabb CalcAABB() override {
				aabb ans;
				ans.x1 = pos.x - r;
				ans.x2 = pos.x + r;
				ans.y1 = pos.y - r;
				ans.y2 = pos.y + r;
				return ans;
			}
			realn CalcArea() override {
				return G_PI * r * r;
			}
			vector2d CalcCenter() override {
				return vector2d{0, 0} + bias;
			}
			void CheckCenter() override {
				pos += CalcCenter();
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 椭圆形
		class ellipse : public shape {
		public:
			double a = 0, b = 0;
			ellipse(vector2d _pos = vector2d{0, 0}, realn _a = 1, realn _b = 0.5) {
				type = shapetype_ellipse;
				pos = _pos, a = _a, b = _b;
			}
			vector2d Support(vector2d u) override {
				u = u.Rotate(-rotate);
				if (u.x == 0 && u.y > 0)return Abs(vector2d{0, b});
				if (u.x == 0 && u.y < 0)return Abs(vector2d{0, -b});
				if (u.y == 0 && u.x > 0)return Abs(vector2d{a, 0});
				if (u.y == 0 && u.x < 0)return Abs(vector2d{-a, 0});
				realn k = u.y / u.x;
				realn d = sqrt((a*a + b*b*k*k) / k / k);
				if (u * vector2d(0, d) < 0)d = -d;
				realn x = k*d - (b*b*k*k*k*d) / (a*a + b*b*k*k);
				realn y = (b*b*k*k*d) / (a*a + b*b*k*k);
				return Abs(vector2d(x, y));
			}
			aabb CalcAABB() override {
				aabb ans;
				vector2d v1, v2;
				v1 = Support(pg::axisY);
				v2 = Support(pg::axisX);
				v1 -= pos, v2 -= pos;
				ans.x1 = -v2.x + pos.x;
				ans.x2 = v2.x + pos.x;
				ans.y1 = -v1.y + pos.y;
				ans.y2 = v1.y + pos.y;
				return ans;
			}
			vector2d CalcCenter() override {
				return bias;
			}
			void CheckCenter() override {
				pos += CalcCenter();
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 多边形
		class polygon : public shape {
		protected:
			std::vector <vector2d> p;
		public:
			polygon(vector2d _pos, int _n, realn r) {
				type = shapetype_polygon;
				pos = _pos;
				vector2d v = {0, r};
				for (int i = 0; i < _n; i++)p.push_back(v.Rotate(PI * 2 * i / _n));
			}
			polygon(std::vector<vector2d>& p_) : p(p_) {
				type = shapetype_polygon;
			}
			polygon() {
				type = shapetype_polygon;
			}
			vector2d Support(vector2d u) override {
				u = u.Rotate(-rotate);
				realn maxn = Shadow(p[0], u);
				int maxp = 0;
				for (int i = 1; i < p.size(); i++) {
					realn t = Shadow(p[i], u);
					if (t > maxn) maxn = t, maxp = i;
				}
				return Abs(p[maxp]);
			}
			aabb CalcAABB() override {
				aabb ans;
				ans.x1 = ans.x2 = Abs(p[0]).x;
				ans.y1 = ans.y2 = Abs(p[0]).y;
				for (int i = 1; i < p.size(); i++) {
					vector2d v = Abs(p[i]);
					if (v.x < ans.x1) ans.x1 = v.x;
					if (v.x > ans.x2) ans.x2 = v.x;
					if (v.y < ans.y1) ans.y1 = v.y;
					if (v.y > ans.y2) ans.y2 = v.y;
				}
				return ans;
			}
			vector2d CalcCenter() override {
				vector2d ans = {0, 0};
				realn s = 0;
				for (int i = 1; i < p.size() - 1; i++) {
					realn ds = Cross(p[i] - p[0], p[i + 1] - p[0]);
					ans += (p[0] + p[i] + p[i + 1]) * ds / 3;
					s += ds;
				}
				return ans / s + bias;
			}
			void CheckCenter() override {
				vector2d temp = CalcCenter();
				pos += temp;
				for (int i = 0; i < p.size(); i++)p[i] -= temp;
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 圆角多边形
		class roundpoly : public shape {
		protected:
			realn r;
			std::vector <vector2d> p;
			std::vector <vector2d> inner_p;
			realn roundness;
			void CheckInnerP() {
				inner_p.resize(p.size());
				for (int i = 1; i <= p.size(); i++) {
					vector2d t1 = VecUnit(p[i % p.size()] - p[(i + 1) % p.size()]);
					vector2d t2 = VecUnit(p[i % p.size()] - p[(i - 1) % p.size()]);
					vector2d t = VecUnit(t1 + t2) * roundness;
					vector2d o = p[i % p.size()] - t / cos((PI - std::fabs(VecAngle(t1, t2))) / 2);
					inner_p[i % p.size()] = o;
				}
			}
		public:
			roundpoly() {
				type = shapetype_roundpoly;
			};
			roundpoly(vector2d _pos, int _n, realn _r, realn roundness_) {
				type = shapetype_roundpoly;
				r = _r, pos = _pos, roundness = roundness_;
				vector2d v = {0, r};
				for (int i = 0; i < _n; i++) p.push_back(v.Rotate(PI * 2 * i / _n));
				CheckInnerP();
			}
			roundpoly(std::vector<vector2d> p_) : p(p) {
				type = shapetype_roundpoly;
				CheckInnerP();
			}
			vector2d Support(vector2d u) override {
				u = u.Rotate(-rotate);
				realn maxn = Shadow(p[0], u);
				int maxp = 0;
				for (int i = 1; i < p.size(); i++) {
					realn t = Shadow(p[i], u);
					if (t > maxn) maxn = t, maxp = i;
				}
				return Abs(inner_p[maxp] + VecUnit(u) * roundness);
			}
			aabb CalcAABB() override {
				aabb ans;
				ans.x1 = ans.x2 = Abs(inner_p[0]).x;
				ans.y1 = ans.y2 = Abs(inner_p[0]).y;
				for (int i = 0; i < inner_p.size(); i++) {
					vector2d t = Abs(inner_p[i]);
					ans.x1 = std::min(t.x - roundness, ans.x1);
					ans.x2 = std::max(t.x + roundness, ans.x2);
					ans.y1 = std::min(t.y - roundness, ans.y1);
					ans.y2 = std::max(t.y + roundness, ans.y2);
				}
				return ans;
			}
			vector2d CalcCenter() override {
				vector2d ans = {0, 0};
				realn s = 0;
				for (int i = 1; i < p.size() - 1; i++) {
					realn ds = Cross(p[i] - p[0], p[i + 1] - p[0]);
					ans += (p[0] + p[i] + p[i + 1]) * ds / 3;
					s += ds;
				}
				return ans / s + bias;
			}
			void CheckCenter() override {
				vector2d temp = CalcCenter();
				pos += temp;
				for (int i = 0; i < p.size(); i++)p[i] -= temp;
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 胶囊形
		class capsule : public shape {
		public:
			vector2d p1;
			vector2d p2;
			realn r;
			capsule(vector2d p1_, vector2d p2_, realn r_) {
				type = shapetype_capsule;
				p1 = p1_, p2 = p2_, r = r_;
			}
			capsule() {};
			vector2d Support(vector2d u) override {
				u = u.Rotate(-rotate);
				vector2d v = p2 - p1;
				if (u * v >= 0) return Abs(p2 + VecUnit(u) * r);
				return Abs(p1 + VecUnit(u) * r);
			}
			aabb CalcAABB() override {
				aabb ans;
				vector2d v1 = Abs(p1);
				vector2d v2 = Abs(p2);
				ans.x1 = std::min(v1.x, v2.x) - r;
				ans.x2 = std::max(v1.x, v2.x) + r;
				ans.y1 = std::min(v1.y, v2.y) - r;
				ans.y2 = std::max(v1.y, v2.y) + r;
				return ans;
			}
			vector2d CalcCenter() override {
				return (p1 + p2) / 2 + bias;
			}
			void CheckCenter() override {
				vector2d v = CalcCenter();
				pos += v, p1 -= v, p2 -= v;
			}
			void Draw(unsigned color);
			void DrawLines(unsigned color);
		};
		// 矩形
		class rectangle : public polygon {
		private:
		public:
			realn a, b;
			rectangle(vector2d _pos, realn _a, realn _b) {
				a = _a, b = _b, pos = _pos;
				p.push_back({_a / 2, -_b / 2});
				p.push_back({_a / 2, _b / 2});
				p.push_back({-_a / 2, _b / 2});
				p.push_back({-_a / 2, -_b / 2});
			}
			rectangle() {}
			void Set(int a_, int b_) {
				a = a_, b = b_;
			}
		};
		// 圆角矩形
		class roundrect : public roundpoly {
		private:
			realn a, b;
		public:
			roundrect(vector2d _pos = vector2d{0, 0}, realn _a = 1, realn _b = 1, realn roundness_ = 0.5) {
				a = _a, b = _b, pos = _pos, roundness = roundness_;
				p.push_back({_a / 2, -_b / 2});
				p.push_back({_a / 2, _b / 2});
				p.push_back({-_a / 2, _b / 2});
				p.push_back({-_a / 2, -_b / 2});
				CheckInnerP();
			}
			void Set(int a_, int b_) {
				a = a_, b = b_;
				CheckInnerP();
			}
		};
		// 三角形
		class triangle : public polygon {
		private:
			realn a, b;
		public:
			triangle(vector2d p1 = {0, 0}, vector2d p2 = {1, 0}, vector2d p3 = {0, 1}) {
				p.push_back(p1);
				p.push_back(p2);
				p.push_back(p3);
			}
		};
		// 圆角三角形
		class roundtriangle : public roundpoly {
		private:
			realn a, b;
		public:
			roundtriangle(vector2d p1 = {0, 0}, vector2d p2 = {1, 0}, vector2d p3 = {0, 1}, realn roundness_ = 0.5) {
				roundness = roundness_;
				p.push_back(p1);
				p.push_back(p2);
				p.push_back(p3);
				CheckInnerP();
			}
		};

		// 二维凸包
		std::vector <vector2d> ConvexHull(std::vector <vector2d> p) {
			if (p.size() <= 2) return {};
			// 按纵坐标排序
			auto cmp1 = [] (const vector2d & a, const vector2d & b) -> const bool {return a.y < b.y;};
			std::sort(p.begin(), p.end(), cmp1);
			// 按张角排序
			auto cmp2 = [&] (const vector2d & a, const vector2d & b) -> const bool {
				realn a1 = -VecAngle(a - p[0], pg::axisX);
				realn a2 = -VecAngle(b - p[0], pg::axisX);
				return a1 < a2;
			};
			std::sort(p.begin() + 1, p.end(), cmp2);
			// 计算凸包
			auto get_angle = [](const vector2d & v) -> const realn {
				realn t = atan2(v.y, v.x);
				if (t < 0) return t + PI * 2;
				return t;
			};
			std::vector <vector2d> id(p.size());
			id[0] = p[0], id[1] = p[1];
			int top = 1;
			for (int i = 2; i < p.size(); i++) {
				realn a1 = get_angle(id[top] - id[top - 1]);
				realn a2 = get_angle(p[i] - id[top]);
				while (a2 < a1) {
					top--;
					a1 = get_angle(id[top] - id[top - 1]);
					a2 = get_angle(p[i] - id[top]);
				}
				id[++top] = p[i];
			}
			id.resize(top + 1);
			return id;
		}

		// 闵可夫斯基差
		struct Minkowski_t {
			vector2d m_body1;
			vector2d m_body2;
			vector2d m_result;
			Minkowski_t(vector2d body1, vector2d body2) {
				m_body1 = body1, m_body2 = body2;
				m_result = body2 - body1;
			}
			Minkowski_t() {}
		};
		struct MinkowskiLine {
			Minkowski_t p1;
			Minkowski_t p2;
			MinkowskiLine(Minkowski_t p1_, Minkowski_t p2_) : p1(p1_), p2(p2_) {}
			MinkowskiLine() {}
			inline realn Length() {
				return Mod(p2.m_result - p1.m_result);
			}
			inline vector2d CalcCenter() {
				return (p2.m_result + p1.m_result) / 2;
			}
		};

		// 碰撞检测
		namespace collision {

			// 详细碰撞数据
			struct CollisionData {
				bool detect = false;			// 是否碰撞
				vector2d penetrate = {0, 0};	// 穿透向量
				MinkowskiLine line;				// 闵可夫斯基差
				vector2d p1, p2;				// 碰撞点对
				realn deep = 0;					// 穿透深度
			};

			// 精细碰撞检测
			CollisionData NarrowPhase(pg::shape &a, pg::shape &b) {
				// ============== 初始化 ==============
				CollisionData cp;
				cp.detect = false;
				// ============== GJK 阶段 ==============
				vector2d u1(0, 0);							// 搜索起点
				vector2d u = b.pos - a.pos;					// 搜索方向
				if (Mod2(u) == 0) u = pg::axisX;			// 重置搜索方向
				Minkowski_t m1(a.Support(-u), b.Support(u));// 第一个闵可夫斯基差
				Minkowski_t m2(a.Support(u), b.Support(-u));// 第一个闵可夫斯基差
				Minkowski_t m3;								// 第三个闵可夫斯基差
				Minkowski_t pure[3] = {m1, m2, m3};			// 单纯性三个顶点
				if (m1.m_result * u < 0 || m2.m_result * u > 0) return cp;
				vector2d last_p1 = {INT_MAX, INT_MAX};
				bool flag = false;
				while (1) {
					// 寻找单纯形最靠近原点的边
					realn min_dis = INT_MAX;
					int min_p1, min_p2, del_p;
					if (!flag) min_p1 = 0, min_p2 = 1, del_p = 2, flag = true;
					else {
						for (int i = 0; i < 3; i++) {
							vector2d p1 = pure[i % 3].m_result;
							vector2d p2 = pure[(i + 1) % 3].m_result;
							realn dis = std::fabs(Cross(p2 - p1, -p1) / Mod(p2 - p1));
							if (dis < min_dis)min_dis = dis, min_p1 = i, min_p2 = (i + 1) % 3, del_p = (i + 2) % 3;
						}
						if (pure[min_p1].m_result == last_p1) return cp;
						last_p1 = pure[min_p1].m_result;
					}
					// 计算搜索方向
					u1 = (pure[min_p1].m_result + pure[min_p2].m_result) / 2;			// 中点
					u = (pure[min_p2].m_result - pure[min_p1].m_result).Rotate(PI / 2);	// 中垂线
					// 计算支撑点
					if (u * u1 > 0)u = -u;							// 选择指向原点的方向
					m1 = Minkowski_t(a.Support(-u), b.Support(u));	// 计算u方向的支撑点
					// 修改单纯形
					pure[del_p] = m1;
					// 判断是否包含原点
					realn t1 = ((-pure[0].m_result) ^ (pure[1].m_result - pure[0].m_result));
					realn t2 = ((-pure[1].m_result) ^ (pure[2].m_result - pure[1].m_result));
					realn t3 = ((-pure[2].m_result) ^ (pure[0].m_result - pure[2].m_result));
					if ((t1 >= -0.00001 && t2 >= -0.00001 && t3 >= -0.00001) || (t1 <= 0.00001 && t2 <= 0.00001 && t3 <= 0.00001)) break;
					if (m1.m_result * u < 0) return cp;
				}
				// ============== EPA 阶段 ==============
				auto cmp = [&](MinkowskiLine& A, MinkowskiLine& B) -> const bool {
					realn s1 = (A.p2.m_result - A.p1.m_result) ^ (pg::origin - A.p1.m_result);
					realn s2 = (B.p2.m_result - B.p1.m_result) ^ (pg::origin - B.p1.m_result);
					return std::fabs(s1 / A.Length()) > std::fabs(s2 / B.Length());
				};	// 根据到原点的距离排序
				std::priority_queue <MinkowskiLine, std::vector <MinkowskiLine>, decltype(cmp)> seg(cmp);
				seg.push(MinkowskiLine(pure[0], pure[1]));
				seg.push(MinkowskiLine(pure[1], pure[2]));
				seg.push(MinkowskiLine(pure[2], pure[0]));
				vector2d pure_o = (pure[0].m_result + pure[1].m_result + pure[2].m_result) / 3;
				int deep = 0;
				while (!seg.empty() && deep < 30) {
					deep ++;
					// 寻找扩展单纯性最靠近原点的边
					MinkowskiLine top = seg.top();
					cp.line = top;
					seg.pop();
					// 计算搜索方向
					u1 = top.CalcCenter();									// 中点
					u = (top.p2.m_result - top.p1.m_result).Rotate(PI / 2);	// 中垂线
					// 计算穿透向量
					cp.penetrate = pg::origin - top.p1.m_result - ShadowV(pg::origin - top.p1.m_result, top.p2.m_result - top.p1.m_result);
					// 计算支撑点
					realn t1 = (top.p2.m_result - top.p1.m_result) ^ u;
					realn t2 = (top.p2.m_result - top.p1.m_result) ^ (pure_o - u1);
					if (std::fabs(t2) < 0.00001) break;
					if (t1 * t2 > 0) u = -u;						// 选择背离单纯形的方向搜索
					m3 = Minkowski_t(a.Support(-u), b.Support(u));	// 计算u方向的新节点
					if (m3.m_result == top.p1.m_result) break;		// 重复，退出
					if (m3.m_result == top.p2.m_result) break;		// 重复，退出
					// 扩展单纯形
					seg.push(MinkowskiLine(top.p1, m3));
					seg.push(MinkowskiLine(m3, top.p2));
				}
				// ============== 计算碰撞参数 ==============
				cp.deep = Mod(cp.penetrate);
				if (cp.deep > 0.000001) cp.detect = true;
				realn d1 = Mod2(cp.line.p1.m_body1 - cp.line.p2.m_body1);
				realn d2 = Mod2(cp.line.p1.m_body2 - cp.line.p2.m_body2);
				if (d1 < d2) {
					cp.p1 = cp.line.p1.m_body1;
					cp.p2 = cp.p1 - cp.penetrate;
				} else {
					cp.p2 = cp.line.p1.m_body2;
					cp.p1 = cp.p2 + cp.penetrate;
				}
				return cp;
			}

		}

	}

	// 2D物理引擎
	namespace pe {

		// 物体
		class Body {
		public:
			pg::shape* shape;
			realn mass;
			vector2d vel;
			vector2d acc;
			vector2d pos;
		};

		// 世界
		class World {
		public:

		};

	}

}

#endif
