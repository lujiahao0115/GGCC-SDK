// particle.h
// ggcc物理-粒子库

#ifndef _GGCCPARTICLE_H_
#define _GGCCPARTICLE_H_

#include <bits/stdc++.h>
#include <ggcc/math/point.h>
using namespace std;

namespace ggcc {

// 粒子类
	class Particle {
		private:
			vector3d pos= {0,0,0};				// 坐标
			vector3d v= {0,0,0};				// 速度
			vector3d vv= {0,0,0};				// 加速度
			double g=9.8;						// 重力常数
			double mess=0.001;					// 质量
			int LastUpdateTime=clock();			// 上次更新时间
			int CreateTime=clock();				// 创建时间

		public:
			Particle(vector3d Pos);				// 构造函数
			void SetPos(vector3d Pos);			// 设置坐标
			void SetG(int gr);					// 设置重力常数（默认9.8N/kg)
			void SetMess(int M);				// 设置质量
			void Force(vector3d f);				// 施加一个持续一秒的力
			void Update();						// 更新
			vector3d GetPos();					// 获取坐标
			int GetLifeTime();					// 设置生命周期

	};
	Particle::Particle(vector3d Pos= {0,0,0}) {
		pos=Pos;
	}
	void Particle::SetPos(vector3d Pos) {
		pos=Pos;
	}
	void Particle::SetG(int gr) {
		g=gr;
	}
	void Particle::SetMess(int M) {
		mess=M;
	}
	void Particle::Force(vector3d f) {
		v+=f/mess/g;
	}
	void Particle::Update() {
		int k=clock()-LastUpdateTime;
		v+=vector3d {0,g,0} *(1.0*k/1000);
		pos+=v*(1.0*k/1000);
		LastUpdateTime=clock();
	}
	vector3d Particle::GetPos() {
		return pos;
	}
	int Particle::GetLifeTime() {
		return clock()-CreateTime;
	}

// 发射器类
	class Launcher {
		private:
			vector3d pos;						// 坐标
			int life=10000;						// 生命周期

		public:
			queue<Particle> par;				// 粒子队列
			Launcher(vector3d Pos);				// 构造函数
			void SetPos(vector3d Pos);			// 设置发射器坐标
			void SetLife(int L);				// 设置粒子生命周期
			void Launch(vector3d F);			// 以力F发射一颗粒子
			void Update();						// 更新

	};
	Launcher::Launcher(vector3d Pos= {0,0,0}) {
		pos=Pos;
	}
	void Launcher::SetPos(vector3d Pos= {0,0,0}) {
		pos=Pos;
	}
	void Launcher::SetLife(int L) {
		life=L;
	}
	void Launcher::Launch(vector3d F) {
		Particle P;
		P.SetPos(pos);
		P.Force(F);
		par.push(P);
	}
	void Launcher::Update() {
		int len=par.size();
		for(int i=0; i<len; i++) {
			par.front().Update();
			if(par.front().GetLifeTime()>life)par.pop();
			else {
				par.push(par.front());
				par.pop();
			}
		}
	}
}

#endif
