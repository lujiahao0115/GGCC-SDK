// evaluate.h
// GGCC表达式分析库

#pragma once

#include <cmath>
#include <map>
#include <string>
#include <functional>
#include <unordered_map>

namespace ggcc {

	double eval(std::string str, std::unordered_map<std::string, double> para = {}) {
		static std::unordered_map<char, char> prio = {{'+', 1}, {'-', 1}, {'_', 1}, {'*', 2}, {'/', 2}, {'^', 3}};
		static std::unordered_map<std::string, char> func = {
			{"sin", 'A'}, {"cos", 'B'}, {"tan", 'C'}, {"asin", 'D'}, 
			{"acos", 'E'}, {"atan", 'F'}, {"exp", 'G'}, {"log", 'H'}, 
			{"log2", 'I'}, {"log10", 'J'}, {"sqrt", 'K'}, {"abs", 'L'}
		};
		static std::unordered_map<std::string, double> constant = {
			{"Pi", 3.1415926535897932384626433832795},
			{"e", 2.7182818284590452353602874713527},
		};
		char op[100] = {0};
		double num[100] = {0};
		int optop = 0, numtop = 0;
		auto eval_func = [&] {
			double a = num[numtop--];
			char x = op[optop--];
			if (x == 'A') num[++numtop] = sin(a);
			else if (x == 'B') num[++numtop] = cos(a);
			else if (x == 'C') num[++numtop] = tan(a);
			else if (x == 'D') num[++numtop] = asin(a);
			else if (x == 'E') num[++numtop] = acos(a);
			else if (x == 'F') num[++numtop] = atan(a);
			else if (x == 'G') num[++numtop] = exp(a);
			else if (x == 'H') num[++numtop] = log(a);
			else if (x == 'I') num[++numtop] = log2(a);
			else if (x == 'J') num[++numtop] = log10(a);
			else if (x == 'K') num[++numtop] = sqrt(a);
			else if (x == 'L') num[++numtop] = fabs(a);
		};
		auto eval_sym = [&] {
			double a, b;
			b = num[numtop--];
			a = num[numtop--];
			char x = op[optop--];
			if (x == '+') num[++numtop] = a + b;
			else if (x == '_') numtop++, num[++numtop] = -b;
			else if (x == '-') num[++numtop] = a - b;
			else if (x == '*') num[++numtop] = a * b;
			else if (x == '/') num[++numtop] = a / b;
			else if (x == '^') num[++numtop] = pow(a, b);
		};
		for (int i = 0; i < str.size(); i++) {
			if (isdigit(str[i])) {
				double temp = 0;
				while (i < str.size() && isdigit(str[i])) temp = temp * 10 + str[i++] - '0';
				if (i < str.size() && str[i] == '.') {
					i++;
					for (int k = 1; i < str.size() && isdigit(str[i]); k++)temp += (str[i++] - '0') * pow(0.1, k);
				}
				num[++numtop] = temp, i--;
			} else if (isalpha(str[i])) {
				std::string temp = "";
				while ((isalpha(str[i]) || isdigit(str[i])) && i < str.size()) temp += str[i++];
				if(para.count(temp)) num[++numtop] = para[temp];
				else if (constant.count(temp)) num[++numtop] = constant[temp];
				else op[++optop] = func[temp];
				i--;
			} else if (str[i] == '(') {
				op[++optop] = '(';
			} else if (str[i] == ')') {
				while (op[optop] != '(') eval_sym();
				if (optop && isalpha(op[--optop])) eval_func();
			} else if (prio[str[i]]) {
				if (str[i] == '-') {
					int j = i;
					while(j) if (str[--j] != ' ') break;
					if(str[j] == '(') str[i] = '_';
				}
				while (optop && op[optop] != '(' && prio[op[optop]] >= prio[str[i]]) eval_sym();
				op[++optop] = str[i];
			}
		}
		while (optop) eval_sym();
		return num[numtop];
	}

}
