#include <conio.h>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

namespace ggcc {

	namespace pn {
		float persistence = 0.50;
		int Number_Of_Octaves = 2;

		float Noise(long long x, long long y) {	// 根据(x, y)获取一个初步噪声值
			long long n = x + y * 3275231;
			n = (n << 13) ^ n;
			return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
		}
		float SmoothedNoise(int x, int y) {	// 光滑噪声
			float corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
			float sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
			float center = Noise(x, y) / 4;
			return corners + sides + center;
		}
		float Cosine_Interpolate(float a, float b, float x) {	// 余弦插值
			float ft = x * 3.1415927;
			float f = (1 - cos(ft)) * 0.5;
			return a * (1 - f) + b * f;
		}
		float InterpolatedNoise(float x, float y) {	// 获取插值噪声
			int integer_X = int(x);
			float fractional_X = x - integer_X;
			int integer_Y = int(y);
			float fractional_Y = y - integer_Y;
			float v1 = SmoothedNoise(integer_X, integer_Y);
			float v2 = SmoothedNoise(integer_X + 1, integer_Y);
			float v3 = SmoothedNoise(integer_X, integer_Y + 1);
			float v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
			float i1 = Cosine_Interpolate(v1, v2, fractional_X);
			float i2 = Cosine_Interpolate(v3, v4, fractional_X);
			return Cosine_Interpolate(i1, i2, fractional_Y);
		}
		float PerlinNoise(float x, float y) {	// 最终调用：根据(x, y)获得其对应的 PerlinNoise 值
			float total = 0;
			float p = persistence;
			int n = Number_Of_Octaves;
			for (int i = 0; i < n; i++) {
				float frequency = pow(2, i);
				float amplitude = pow(p, i);
				total = total + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
			}
			return total;
		}
	}
}
