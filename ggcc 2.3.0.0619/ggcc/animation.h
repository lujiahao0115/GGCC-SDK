// ggcc_animation
// ggcc动画库

#ifndef __GGCCANIMATION_H__
#define __GGCCANIMATION_H__

#include <ggcc/math/point.h>

#ifdef __GGCCANIMATION_H_OLD__

#include <bits/stdc++.h>

#define MAXANIARRAY   128
#define MAXANI 1024

using namespace std;
namespace ggcc {

	class Animation {
		private:
			realn StartPos = 0;
			realn TargetPos = 0;
			realn NowPos;
			realn Speed = 0.5;
			int LastUpdateClock = 0;
			int MoveStyle = 0;

			realn CreateAni0(realn Start, realn End, int SpaceTime) {
				return Start + (End - Start) * (1 - pow(Speed, 1.0 * SpaceTime / 50));
			}
			realn CreateAni1(realn Start, realn End, int Spacetime) {
				realn Dis = abs(End - Start);
				realn Temp = log(Dis) / log(2);
				realn t;
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
			Animation(realn spos, realn tpos);
			void SetStartPos(realn Pos);
			void SetTargetPos(realn Pos);
			void SetMoveStyle(int Style);
			void SetSpeed(realn Speed);
			void GetNowPos(realn &Pos);
			realn GetNowPos();
			realn GetTargetPos();
			void Update();
	};

	Animation::Animation(realn spos = 0, realn tpos = 0) {
		StartPos = spos;
		TargetPos = tpos;
		NowPos = spos;
	}
	void Animation::SetStartPos(realn Pos) {
		StartPos = Pos;
		LastUpdateClock = clock();
		NowPos = Pos;
	}
	void Animation::SetTargetPos(realn Pos) {
		TargetPos = Pos;
	}
	void Animation::SetMoveStyle(int Style) {
		MoveStyle = Style;
	}
	void Animation::SetSpeed(realn speed) {
		Speed = speed;
	}
	void Animation::GetNowPos(realn &Pos) {
		Pos = NowPos;
	}
	realn Animation::GetNowPos() {
		return NowPos;
	}
	realn Animation::GetTargetPos() {
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

	realn GetAniPos(int id) {
		realn k;
		Ani[NowAniArrayID][id].GetNowPos(k);
		return k;
	}

	realn GetNextAniPos() {
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

	// 动画函数
	namespace anif {
		// 瞬间动画
		#define moment momentFun,0,1
		realn momentFun(realn x) {
			if(x<=0)return 0;
			return 1;
		}
		// 线性动画
		#define linear linearFun,0,1
		realn linearFun(realn x) {
			return x;
		}
		// 经典动画
		#define classics classicsFun,10,0
		realn classicsFun(realn x) {
			return pow(1.618, x);
		}
		// sin动画
		#define sine sineFun,-3.1415926/2,3.1415926/2
		realn sineFun(realn x) {
			return sin(x);
		}
		// tan动画
		#define tanf tanFun,-1.35, 1.35
		realn tanFun(realn x) {
			return sin(x) / cos(x);
		}
		// tanh动画
		#define tanh tanhFun,-2.5, 2.5
		realn tanhFun(realn x) {
			return (exp(x)-exp(-x)) / (exp(x)+exp(-x));
		}
		// 回弹动画（阻力5）
		#define bounce bounceFun,-8.9726,0
		#define bounce1 bounceFun,-8.9726,0
		realn bounceFun(realn x) {
			return -7.0 / 51 * sqrt(51) * exp(-7.0 / 10 * x) * sin(1.0 / 10 * sqrt(51) * x) - exp(-7.0 / 10 * x) * cos(1.0 / 10 * sqrt(51) * x);
		}
		// 回弹动画（阻力4）
		#define bounce2 bounce2Fun,-8.2645,0
		realn bounce2Fun(realn x) {
			return -13.0 / 231 * sqrt(231) * exp(-13.0 / 20 * x) * sin(1.0 / 20 * sqrt(231) * x) - exp(-13.0 / 20 * x) * cos(1.0 / 20 * sqrt(231) * x);
		}
		// 回弹动画（阻力3）
		#define bounce3 bounce3Fun,-7.9188,0
		realn bounce3Fun(realn x) {
			return -3.0 / 4 * exp(-3.0 / 5 * x) * sin(4.0 / 5 * x) - exp(-3.0 / 5 * x) * cos(4.0 / 5 * x);
		}
		// 回弹动画（阻力2）
		#define bounce4 bounce4Fun,-7.5220,0
		realn bounce4Fun(realn x) {
			return -11.0 / 93 * sqrt(31) * exp(-11.0 / 20 * x) * sin(3.0 / 20 * sqrt(31) * x) - exp(-11.0 / 20 * x) * cos(3.0 / 20 * sqrt(31) * x);
		}
		// 回弹动画（阻力1）
		#define bounce5 bounce5Fun,-7.3448,0
		realn bounce5Fun(realn x) {
			return -1.0 / 3 * sqrt(3) * exp(-1.0 / 2 * x) * sin(1.0 / 2 * sqrt(3) * x) - exp(-1.0 / 2 * x) * cos(1.0 / 2 * sqrt(3) * x);
		}
	}

	int AniTotal = 0;
	int AniEnabled = 1;
	class Animation {
		private:
			realn StartPos = 0;
			realn TargetPos = 0;
			realn StartTime = 0;
			realn Duration = 500;
			realn NowPos;
			int LastUpdateClock = 0;
			realn (*Fun)(realn) = anif::classicsFun;
			realn FunStart = 10;
			realn FunEnd = 0;
			bool IsStopped = false;
			bool Repeat_ = false;
			realn RepeatDelay = 0;
			bool Return_ = false;
			bool Returned = false;
			realn ReturnDelay = 0;

		public:
			~Animation() {AniTotal--;}
			Animation();
			Animation(realn);
			Animation(realn, realn);
		
			void SetStartPos(realn);
			void SetTargetPos(realn, realn);
			void SetMoveStyle(realn (*fun)(realn), realn, realn);
			void SetDuration(realn);
			realn GetNowPos();
			realn GetTargetPos();
			realn GetStartTime();
			bool IsRunning();
			void Stop();
			void Pause();
			void Continue();
			void Update();
			void Reset();
			void Repeat(bool, realn);
			void Return(bool, realn);
			void Goto(realn);

			inline void ssp(realn pos) {SetStartPos(pos);}
			inline void stp(realn pos, realn delay = 0) {SetTargetPos(pos, delay);}
			inline void sms(realn (*fun)(realn), realn st, realn end) {SetMoveStyle(fun, st, end);}
			inline void sd(realn duration) {SetDuration(duration);}
			inline realn gnp() {return GetNowPos();}
			inline realn gp(realn time) {return GetPos(time);}
			inline realn gtp() {return GetTargetPos();}
			inline realn gst() {return GetStartTime();}
			inline bool is_run() {return IsRunning();}
			inline void stop() {Stop();}
			inline void pause() {Pause();}
			inline void cont() {Continue();}
			inline void update() {Update();}
			inline void reset() {Reset();}
			inline void repeat(bool b, realn delay = 0) {Repeat(b, delay);}
			inline void retn(bool b, realn delay = 0) {Return(b, delay);}
			inline void gt(realn pos) {Goto(pos);};
		
			realn AniFun(realn x) {
				if(x<0)return StartPos;
				if(x>Duration)return TargetPos;
				realn dtf = FunEnd - FunStart;
				realn l = Fun(FunEnd) - Fun(FunStart);
				realn zoom = 1.0 * (TargetPos - StartPos) / l;
				realn dt = x / Duration * dtf;
				return (Fun(FunStart + dt) - Fun(FunStart)) * zoom + StartPos;
			}
			realn GetPos(realn x) {
				x-=StartTime;
				if(Repeat_&&Return_) {
					x-=int(x/Duration/2)*Duration*2;
					if(x<Duration)return AniFun(x);
					else return AniFun(2*Duration-x);
				} else if(Repeat_&&!Return_) {
					x-=int(x/Duration)*Duration;
					return AniFun(x);
				} else if(!Repeat_&&Return_) {
					if(x<Duration)return AniFun(x);
					else if(x<Duration*2)return AniFun(2*Duration-x);
				} else {
					return AniFun(x);
				}
			}
	};

	Animation::Animation() {
		NowPos = StartPos = TargetPos = 0;
		StartTime = clock();
		AniTotal++;
	}
	Animation::Animation(realn pos) {
		NowPos = StartPos = TargetPos = pos;
		StartTime = clock();
		AniTotal++;
	}
	Animation::Animation(realn spos, realn tpos) {
		NowPos = StartPos = spos;
		TargetPos = tpos;
		StartTime = clock();
		AniTotal++;
	}
	void Animation::SetStartPos(realn pos) {
		StartPos = NowPos = TargetPos = pos;
		StartTime = clock();
	}
	void Animation::SetTargetPos(realn pos, realn delay = 0) {
		if (pos == TargetPos)return;
		StartPos = NowPos;
		TargetPos = pos;
		StartTime = clock() + delay;
	}
	void Animation::SetMoveStyle(realn (*fun)(realn), realn start, realn end) {
		Fun = fun;
		FunStart = start;
		FunEnd = end;
	}
	void Animation::SetDuration(realn time) {
		Duration = time;
	}
	realn Animation::GetNowPos() {
		if(AniEnabled==0)return TargetPos;
		return NowPos;
	}
	realn Animation::GetTargetPos() {
		return TargetPos;
	}
	realn Animation::GetStartTime() {
		return StartTime;
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
		realn dtf = FunEnd - FunStart;
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
				realn t=StartPos;
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
			realn l = Fun(FunEnd) - Fun(FunStart);
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = (NowTime - StartTime) / Duration * dtf;
			NowPos = (Fun(FunStart + dt) - Fun(FunStart)) * zoom + StartPos;
		} else if (AniEnabled == 0) {
			NowPos = TargetPos;
		} else if (AniEnabled == 2) {
			realn dtf = 1;
			realn l = 1;
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = (NowTime - StartTime) / Duration * dtf;
			NowPos = (FunStart + dt - FunStart) * zoom + StartPos;
		}
	}
	void Animation::Reset() {
		NowPos = StartPos;
		StartTime = clock();
	}
	void Animation::Repeat(bool b, realn delay = 0) {
		Repeat_ = b;
		RepeatDelay = delay;
	}
	void Animation::Return(bool b, realn delay = 0) {
		Return_ = b;
		if(Returned) {
			NowPos = TargetPos;
			realn t=StartPos;
			StartPos=TargetPos;
			TargetPos=t;
			Returned = false;
		}
		ReturnDelay = delay;
	}
	void Animation::Stop() {
		Update();
		TargetPos=NowPos;
		StartPos=NowPos;
	}
	void Animation::Goto(realn pos) {
		TargetPos=pos;
		StartPos=pos;
	}

};

#endif
#endif
