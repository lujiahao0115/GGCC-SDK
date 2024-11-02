// ggcc_animation
// ggcc������

#ifndef __GGCCANIMATION_H__
#define __GGCCANIMATION_H__

#define real long double

#ifdef __GGCCANIMATION_H_OLD__

#include <bits/stdc++.h>

#define MAXANIARRAY   128
#define MAXANI 1024

using namespace std;
namespace ggcc {

	class Animation {
		private:
			real StartPos = 0;
			real TargetPos = 0;
			real NowPos;
			real Speed = 0.5;
			int LastUpdateClock = 0;
			int MoveStyle = 0;

			real CreateAni0(real Start, real End, int SpaceTime) {
				return Start + (End - Start) * (1 - pow(Speed, 1.0 * SpaceTime / 50));
			}
			real CreateAni1(real Start, real End, int Spacetime) {
				real Dis = abs(End - Start);
				real Temp = log(Dis) / log(2);
				real t;
				if (End > Start) {
					t = Start + Temp * (1.0 * Spacetime / Speed);
					if (t > End)t = End;
				} else {
					t = Start - Temp * (1.0 * Spacetime / Speed);
					if (t < End)t = End;
				}
				return t;
			}

		public:
			Animation(real spos, real tpos);
			void SetStartPos(real Pos);
			void SetTargetPos(real Pos);
			void SetMoveStyle(int Style);
			void SetSpeed(real Speed);
			void GetNowPos(real &Pos);
			real GetNowPos();
			real GetTargetPos();
			void Update();
	};

	Animation::Animation(real spos = 0, real tpos = 0) {
		StartPos = spos;
		TargetPos = tpos;
		NowPos = spos;
	}
	void Animation::SetStartPos(real Pos) {
		StartPos = Pos;
		LastUpdateClock = clock();
		NowPos = Pos;
	}
	void Animation::SetTargetPos(real Pos) {
		TargetPos = Pos;
	}
	void Animation::SetMoveStyle(int Style) {
		MoveStyle = Style;
	}
	void Animation::SetSpeed(real speed) {
		Speed = speed;
	}
	void Animation::GetNowPos(real &Pos) {
		Pos = NowPos;
	}
	real Animation::GetNowPos() {
		return NowPos;
	}
	real Animation::GetTargetPos() {
		return TargetPos;
	}
	void Animation::Update() {
		if (MoveStyle == 0) {
			NowPos = CreateAni0(NowPos, TargetPos, clock() - LastUpdateClock);
			LastUpdateClock = clock();
		} else if (MoveStyle == 1) {
			NowPos = CreateAni1(NowPos, TargetPos, clock() - LastUpdateClock);
			LastUpdateClock = clock();
		}
	}

	Animation Ani[MAXANIARRAY][MAXANI];
	int NowAniArrayID = 0;
	int NowAniID = 0;

	void SetAniArray(int id) {
		NowAniArrayID = id;
	}

	void SetStartAni(int id) {
		NowAniID = id;
	}

	void UpdateAniArray() {
		for (int i = 0; i < MAXANI; i++) {
			Ani[NowAniArrayID][i].Update();
		}
	}

	real GetAniPos(int id) {
		real k;
		Ani[NowAniArrayID][id].GetNowPos(k);
		return k;
	}

	real GetNextAniPos() {
		NowAniID++;
		return GetAniPos(NowAniID - 1);
	}

	void SetAniStartPos(int id, int Pos) {
		Ani[NowAniArrayID][id].SetStartPos(Pos);
	}

	void SetAniTargetPos(int id, int Pos) {
		Ani[NowAniArrayID][id].SetTargetPos(Pos);
	}

	void SetAniSpeed(int id, int speed) {
		Ani[NowAniArrayID][id].SetSpeed(speed);
	}
	void SetAniSpeed(int speed) {
		for (int i = 0; i < MAXANI; i++) {
			Ani[NowAniArrayID][i].SetSpeed(speed);
		}
	}

	void SetAniMoveStyle(int id, int Style) {
		Ani[NowAniArrayID][id].SetMoveStyle(Style);
	}
	void SetAniMoveStyle(int Style) {
		for (int i = 0; i < MAXANI; i++) {
			Ani[NowAniArrayID][i].SetMoveStyle(Style);
		}
	}

	void SetAniPos(int id, int StartPos, int TargetPos) {
		Ani[NowAniArrayID][id].SetStartPos(StartPos);
		Ani[NowAniArrayID][id].SetTargetPos(TargetPos);
	}

	void SetNextAniPos(int StartPos, int TargetPos) {
		Ani[NowAniArrayID][NowAniID].SetStartPos(StartPos);
		Ani[NowAniArrayID][NowAniID].SetTargetPos(TargetPos);
		NowAniID++;
	}

}

#endif

#ifndef __GGCCANIMATION_H_OLD__

#include <bits/stdc++.h>

#define MAXANIARRAY   128
#define MAXANI 1024

namespace ggcc {

	// ����Ԥ��
	namespace anif {
		// ���Զ���
		#define linear linearFun,0,1
		real linearFun(real x) {
			return x;
		}
		// ���䶯��
		#define classics classicsFun,10,0
		real classicsFun(real x) {
			return pow(1.618, x);
		}
		// sin����
		#define sine sineFun,-3.1415926/2,3.1415926/2
		real sineFun(real x) {
			return sin(x);
		}
		// tan����
		#define tanf tanFun,-1.35, 1.35
		real tanFun(real x) {
			return sin(x) / cos(x);
		}
		// tanh����
		#define tanh tanhFun,-2.5, 2.5
		real tanhFun(real x) {
			return (exp(x)-exp(-x)) / (exp(x)+exp(-x));
		}
		// �ص�����1 (����1.4,�̶�С)
		#define bounce bounceFun,-8.9726,0
		#define bounce1 bounceFun,-8.9726,0
		real bounceFun(real x) {
			return -7.0 / 51 * sqrt(51) * exp(-7.0 / 10 * x) * sin(1.0 / 10 * sqrt(51) * x) - exp(-7.0 / 10 * x) * cos(1.0 / 10 * sqrt(51) * x);
		}
		// �ص�����2 (����1.3,�̶Ƚ�С)
		#define bounce2 bounce2Fun,-8.2645,0
		real bounce2Fun(real x) {
			return -13.0 / 231 * sqrt(231) * exp(-13.0 / 20 * x) * sin(1.0 / 20 * sqrt(231) * x) - exp(-13.0 / 20 * x) * cos(1.0 / 20 * sqrt(231) * x);
		}
		// �ص�����3 (����1.2,�̶��е�)
		#define bounce3 bounce3Fun,-7.9188,0
		real bounce3Fun(real x) {
			return -3.0 / 4 * exp(-3.0 / 5 * x) * sin(4.0 / 5 * x) - exp(-3.0 / 5 * x) * cos(4.0 / 5 * x);
		}
		// �ص�����4 (����1.1,�̶Ƚϴ�)
		#define bounce4 bounce4Fun,-7.5220,0
		real bounce4Fun(real x) {
			return -11.0 / 93 * sqrt(31) * exp(-11.0 / 20 * x) * sin(3.0 / 20 * sqrt(31) * x) - exp(-11.0 / 20 * x) * cos(3.0 / 20 * sqrt(31) * x);
		}
		// �ص�����5 (����1.0,�̶ȴ�)
		#define bounce5 bounce5Fun,-7.3448,0
		real bounce5Fun(real x) {
			return -1.0 / 3 * sqrt(3) * exp(-1.0 / 2 * x) * sin(1.0 / 2 * sqrt(3) * x) - exp(-1.0 / 2 * x) * cos(1.0 / 2 * sqrt(3) * x);
		}
	}

	int AniTotal = 0;
	int AniEnabled = 1;
	class Animation {
		private:
			real StartPos = 0;
			real TargetPos = 0;
			real StartTime = 0;
			real Duration = 500;
			real NowPos;
			int LastUpdateClock = 0;
			real (*Fun)(real) = anif::classicsFun;
			real FunStart = 10;
			real FunEnd = 0;
			bool IsStopped = false;
			bool Repeat_ = false;
			real RepeatDelay = 0;
			bool Return_ = false;
			bool Returned = false;
			real ReturnDelay = 0;

		public:
			~Animation() {AniTotal--;}
			Animation();
			Animation(real);
			Animation(real, real);
			void SetStartPos(real);
			void SetTargetPos(real, real);
			void SetMoveStyle(real (*fun)(real), real, real);
			void SetDuration(real);
			real GetNowPos();
			real GetTargetPos();
			bool IsRunning();
			void Stop();
			void Pause();
			void Continue();
			void Update();
			void Reset();
			void Repeat(bool, real);
			void Return(bool, real);

			inline void ssp(real pos) {SetStartPos(pos);}
			inline void stp(real pos, real delay = 0) {SetTargetPos(pos, delay);}
			inline void sms(real (*fun)(real), real st, real end) {SetMoveStyle(fun, st, end);}
			inline void sd(real duration) {SetDuration(duration);}
			inline real gnp() {return GetNowPos();}
			inline real gtp() {return GetTargetPos();}
			inline bool is_run() {return IsRunning();}
			inline void stop() {Stop();}
			inline void pause() {Pause();}
			inline void cont() {Continue();}
			inline void update() {Update();}
			inline void reset() {Reset();}
			inline void repeat(bool b, real delay = 0) {Repeat(b, delay);}
			inline void retn(bool b, real delay = 0) {Return(b, delay);}
	};

	Animation::Animation() {
		NowPos = StartPos = TargetPos = 0;
		StartTime = clock();
		AniTotal++;
	}
	Animation::Animation(real pos) {
		NowPos = StartPos = TargetPos = pos;
		StartTime = clock();
		AniTotal++;
	}
	Animation::Animation(real spos, real tpos) {
		NowPos = StartPos = spos;
		TargetPos = tpos;
		StartTime = clock();
		AniTotal++;
	}
	void Animation::SetStartPos(real pos) {
		StartPos = NowPos = TargetPos = pos;
		StartTime = clock();
	}
	void Animation::SetTargetPos(real pos, real delay = 0) {
		if (pos == TargetPos)return;
		StartPos = NowPos;
		TargetPos = pos;
		StartTime = clock() + delay;
	}
	void Animation::SetMoveStyle(real (*fun)(real), real start, real end) {
		Fun = fun;
		FunStart = start;
		FunEnd = end;
	}
	void Animation::SetDuration(real time) {
		Duration = time;
	}
	real Animation::GetNowPos() {
		if(AniEnabled==0)return TargetPos;
		return NowPos;
	}
	real Animation::GetTargetPos() {
		return TargetPos;
	}
	bool Animation::IsRunning() {
		if (clock() < StartTime || clock() > StartTime + Duration || IsStopped||!AniEnabled)return false;
		else return true;
	}
	void Animation::Pause() {
		IsStopped = true;
	}
	void Animation::Continue() {
		IsStopped = false;
	}
	void Animation::Update() {
		int NowTime = clock();
		real dtf = FunEnd - FunStart;
		if (NowTime < StartTime) {
			LastUpdateClock = StartTime;
			return;
		}
		if (NowTime > StartTime + Duration) {
			if (Repeat_) {
				if(!Return_||Returned) {
					Returned=false;
					NowPos = StartPos;
					NowTime = clock();
					StartTime += Duration + RepeatDelay;
				}
			}
			if(Return_) {
				NowPos = TargetPos;
				real t=StartPos;
				StartPos=TargetPos;
				TargetPos=t;
				NowTime = clock();
				StartTime += Duration + ReturnDelay;
				Returned=true;
			}
			else NowPos = TargetPos;
			return;
		}
		if (AniEnabled == 1) {
			real l = Fun(FunEnd) - Fun(FunStart);
			real zoom = 1.0 * (TargetPos - StartPos) / l;
			real dt = (NowTime - StartTime) / Duration * dtf;
			NowPos = (Fun(FunStart + dt) - Fun(FunStart)) * zoom + StartPos;
		} else if (AniEnabled == 0) {
			NowPos = TargetPos;
		} else if (AniEnabled == 2) {
			real dtf = 1;
			real l = 1;
			real zoom = 1.0 * (TargetPos - StartPos) / l;
			real dt = (NowTime - StartTime) / Duration * dtf;
			NowPos = (FunStart + dt - FunStart) * zoom + StartPos;
		}
	}
	void Animation::Reset() {
		NowPos = StartPos;
		StartTime = clock();
	}
	void Animation::Repeat(bool b, real delay = 0) {
		Repeat_ = b;
		RepeatDelay = delay;
	}
	void Animation::Return(bool b, real delay = 0) {
		Return_ = b;
		if(Returned) {
			NowPos = TargetPos;
			real t=StartPos;
			StartPos=TargetPos;
			TargetPos=t;
			Returned = false;
		}
		ReturnDelay = delay;
	}

};

#endif
#endif
