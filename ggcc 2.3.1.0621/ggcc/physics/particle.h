// particle.h
// ggcc����-���ӿ�

#ifndef _GGCCPARTICLE_H_
#define _GGCCPARTICLE_H_

#include <bits/stdc++.h>
#include <ggcc/math/point.h>
using namespace std;

namespace ggcc {

// ������
	class Particle {
		private:
			vector3d pos= {0,0,0};				// ����
			vector3d v= {0,0,0};				// �ٶ�
			vector3d vv= {0,0,0};				// ���ٶ�
			double g=9.8;						// ��������
			double mess=0.001;					// ����
			int LastUpdateTime=clock();			// �ϴθ���ʱ��
			int CreateTime=clock();				// ����ʱ��

		public:
			Particle(vector3d Pos);				// ���캯��
			void SetPos(vector3d Pos);			// ��������
			void SetG(int gr);					// ��������������Ĭ��9.8N/kg)
			void SetMess(int M);				// ��������
			void Force(vector3d f);				// ʩ��һ������һ�����
			void Update();						// ����
			vector3d GetPos();					// ��ȡ����
			int GetLifeTime();					// ������������

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

// ��������
	class Launcher {
		private:
			vector3d pos;						// ����
			int life=10000;						// ��������

		public:
			queue<Particle> par;				// ���Ӷ���
			Launcher(vector3d Pos);				// ���캯��
			void SetPos(vector3d Pos);			// ���÷���������
			void SetLife(int L);				// ����������������
			void Launch(vector3d F);			// ����F����һ������
			void Update();						// ����

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
