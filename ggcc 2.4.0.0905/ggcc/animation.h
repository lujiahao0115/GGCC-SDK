// ggcc_animation
// ggcc动画库

#ifndef __GGCCANIMATION_H__
#define __GGCCANIMATION_H__

#include <functional>
#include <ctime>
#include <cmath>

using realn = long double;

#ifdef __GGCCANIMATION_H_OLD__

#define MAXANIARRAY   128
#define MAXANI 1024

using namespace std;
namespace ggcc {

	// 计时器
	unsigned long long StartGClcok = 0;
	unsigned long long LastUpdateGClock = 0;
	bool GClockInited = false;
	long long gclock() {
		if (!GClockInited) {
			GClockInited = true;
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			StartGClcok = (unsigned long long)(tp.tv_sec) * 1000 + (unsigned long long)(tp.tv_nsec / 1000000);
			LastUpdateGClock = StartGClcok;
			return 0;
		}
		timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		unsigned long long now = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
		return (long long)(now - StartGClcok);
	}
	void update_gclock() {
		if (!GClockInited) {
			GClockInited = true;
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			StartGClcok = (unsigned long long)(tp.tv_sec) * 1000 + (unsigned long long)(tp.tv_nsec / 1000000);
			LastUpdateGClock = StartGClcok;
		} else {
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			unsigned long long now = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
			if (now - LastUpdateGClock > 100) StartGClcok += now - LastUpdateGClock - 16;
			LastUpdateGClock = now;
		}
	}

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
		LastUpdateClock = gclock();
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
			NowPos = CreateAni0(NowPos, TargetPos, gclock() - LastUpdateClock);
			LastUpdateClock = gclock();
		} else if (MoveStyle == 1) {
			NowPos = CreateAni1(NowPos, TargetPos, gclock() - LastUpdateClock);
			LastUpdateClock = gclock();
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

#define MAXANIARRAY   128
#define MAXANI 1024
#include <iostream>

namespace ggcc {

	// 计时器
	unsigned long long StartGClcok = 0;
	unsigned long long LastUpdateGClock = 0;
	long long LastRecordGClock = 0;
	long long GClockInterval = 0;
	bool GClockInited = false;
	long long gclock() {
		if (!GClockInited) {
			GClockInited = true;
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			StartGClcok = (unsigned long long)(tp.tv_sec) * 1000 + (unsigned long long)(tp.tv_nsec / 1000000);
			LastUpdateGClock = StartGClcok;
			return 0;
		}
		timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		unsigned long long now = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
		return (long long)(now - StartGClcok);
	}
	void update_gclock() {
		if (!GClockInited) {
			GClockInited = true;
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			StartGClcok = (unsigned long long)(tp.tv_sec) * 1000 + (unsigned long long)(tp.tv_nsec / 1000000);
			LastUpdateGClock = StartGClcok;
		} else {
			timespec tp;
			clock_gettime(CLOCK_REALTIME, &tp);
			unsigned long long now = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
			if (now - LastUpdateGClock > 100) StartGClcok += now - LastUpdateGClock - 16;
			LastUpdateGClock = now;
		}
		long long tmp = gclock();
		GClockInterval = tmp - LastRecordGClock;
		LastRecordGClock = tmp;
	}
	long long gclock_interval() {
		return GClockInterval;
	}

	// 动画函数
	namespace anif {

		// 动画参数结构体
		struct AniPara {
			std::function <realn(realn)> fun;	// 动画函数
			realn startp;						// 动画起始点
			realn endp;							// 动画终止点
			AniPara(std::function <realn(realn)> f, realn start, realn end) {
				fun = f;
				startp = start;
				endp = end;
			}
		};
		// 瞬间动画
		realn momentFun(realn x) {
			if (x <= 0)return 0;
			return 1;
		}
		// 线性动画
		realn linearFun(realn x) {
			return x;
		}
		// 经典动画
		realn classicsFun(realn x) {
			return pow(1.618, x);
		}
		realn classicsdFun(realn x) {
			if (x < 10)return pow(1.618, x);
			else return pow(1.618, 10) * 2 - pow(1.618, 20 - x) + 1;
		}
		// sin动画
		realn sineFun(realn x) {
			return sin(x);
		}
		// tan动画
		realn tanFun(realn x) {
			return sin(x) / cos(x);
		}
		// tanh动画
		realn tanhFun(realn x) {
			return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
		}
		// 回弹动画（阻力5）
		realn bounceFun(realn x) {
			return -7.0 / 51 * sqrt(51) * exp(-7.0 / 10 * x) * sin(1.0 / 10 * sqrt(51) * x) - exp(-7.0 / 10 * x) * cos(1.0 / 10 * sqrt(51) * x);
		}
		// 回弹动画（阻力4）
		realn bounce2Fun(realn x) {
			return -13.0 / 231 * sqrt(231) * exp(-13.0 / 20 * x) * sin(1.0 / 20 * sqrt(231) * x) - exp(-13.0 / 20 * x) * cos(1.0 / 20 * sqrt(231) * x);
		}
		// 回弹动画（阻力3）
		realn bounce3Fun(realn x) {
			return -3.0 / 4 * exp(-3.0 / 5 * x) * sin(4.0 / 5 * x) - exp(-3.0 / 5 * x) * cos(4.0 / 5 * x);
		}
		// 回弹动画（阻力2）
		realn bounce4Fun(realn x) {
			return -11.0 / 93 * sqrt(31) * exp(-11.0 / 20 * x) * sin(3.0 / 20 * sqrt(31) * x) - exp(-11.0 / 20 * x) * cos(3.0 / 20 * sqrt(31) * x);
		}
		// 回弹动画（阻力1）
		realn bounce5Fun(realn x) {
			return -1.0 / 3 * sqrt(3) * exp(-1.0 / 2 * x) * sin(1.0 / 2 * sqrt(3) * x) - exp(-1.0 / 2 * x) * cos(1.0 / 2 * sqrt(3) * x);
		}
		
		AniPara moment{momentFun, 0, 1};						// 瞬间动画
		AniPara linear{linearFun, 0, 1};						// 线性动画
		AniPara classics {classicsFun, 10, 0};				// 经典动画（先快后慢）
		AniPara classics_r {classicsFun, 0, 10};				// 经典动画（先慢后快）
		AniPara classics_d {classicsdFun, 0, 20};			// 经典动画（先慢后快再慢）
		AniPara sine {sineFun, -3.1415926/2, 3.1415926/2};	// sin函数动画
		AniPara tanf {tanFun,-1.35, 1.35};					// tan函数动画
		AniPara tanh {tanhFun,-2.5, 2.5};					// tanh函数动画
		AniPara bounce {bounceFun,-8.9726,0};  				// 回弹动画（阻力5）
		AniPara bounce1 {bounceFun,-8.9726,0}; 				// 回弹动画（阻力5）
		AniPara bounce2 {bounce2Fun,-8.2645,0};				// 回弹动画（阻力4）
		AniPara bounce3 {bounce3Fun,-7.9188,0};				// 回弹动画（阻力3）
		AniPara bounce4 {bounce4Fun,-7.5220,0};				// 回弹动画（阻力2）
		AniPara bounce5 {bounce5Fun,-7.3448,0};				// 回弹动画（阻力1）
	}

	int AniTotal = 0;
	bool AniEnabled = 1;
	bool ContinuityCheck = true;

	class Animation {
	private:
		realn StartPos = 0;
		realn TargetPos = 0;
		int StartTime = 0;
		int Duration = 500;
		int RepeatDelay = 0;
		int ReturnDelay = 0;
		realn NowPos;
		std::function<realn(realn)> Fun = anif::classicsFun;
		realn FunStart = 10;
		realn FunEnd = 0;
		bool IsStopped = false;
		bool Repeat_ = false;
		bool Return_ = false;
		bool Returned = false;

	public:
		~Animation() {
			AniTotal--;
		}
		Animation();
		Animation(realn);
		Animation(realn, realn);

		Animation& SetStartPos(realn);
		Animation& SetTargetPos(realn, int);
		Animation& SetMoveStyle(std::function<realn(realn)>, realn, realn);
		Animation& SetMoveStyle(anif::AniPara);
		Animation& SetDuration(int);
		realn GetNowPos();
		realn GetTargetPos();
		realn GetStartPos();
		int GetStartTime();
		bool IsRunning();
		Animation& Stop();
		Animation& Pause();
		Animation& Continue();
		Animation& Update();
		Animation& Reset();
		Animation& Repeat(bool, int);
		Animation& Return(bool, int);
		Animation& Goto(realn);

		inline Animation& ssp(realn pos) {
			return SetStartPos(pos);
		}
		inline Animation& stp(realn pos, int delay = 0) {
			return SetTargetPos(pos, delay);
		}
		inline Animation& sms(std::function<realn(realn)> fun, realn st, realn end) {
			return SetMoveStyle(fun, st, end);
		}
		inline Animation& sms(anif::AniPara para) {
			return SetMoveStyle(para);
		}
		inline Animation& sd(int duration) {
			return SetDuration(duration);
		}
		inline realn gp(int time) {
			return GetPos(time);
		}
		inline realn gnp() {
			return GetNowPos();
		}
		inline realn gsp() {
			return GetStartPos();
		}
		inline realn gtp() {
			return GetTargetPos();
		}
		inline int gst() {
			return GetStartTime();
		}
		inline bool is_run() {
			return IsRunning();
		}
		inline Animation& stop() {
			return Stop();
		}
		inline Animation& pause() {
			return Pause();
		}
		inline Animation& cont() {
			return Continue();
		}
		inline Animation& update() {
			return Update();
		}
		inline Animation& reset() {
			return Reset();
		}
		inline Animation& repeat(bool b, int delay = 0) {
			return Repeat(b, delay);
		}
		inline Animation& retn(bool b, int delay = 0) {
			return Return(b, delay);
		}
		inline Animation& gt(realn pos) {
			return Goto(pos);
		};

		realn AniFun(realn x) {
			if (x < 0)return StartPos;
			if (x > Duration)return TargetPos;
			realn dtf = FunEnd - FunStart;
			realn l = Fun(FunEnd) - Fun(FunStart);
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = x / Duration * dtf;
			return (Fun(FunStart + dt) - Fun(FunStart)) * zoom + StartPos;
		}
		realn GetPos(realn x) {
			x -= StartTime;
			if (Repeat_ && Return_) {
				x -= floor(x / (Duration * 2 + RepeatDelay + ReturnDelay)) * (Duration * 2 + RepeatDelay + ReturnDelay);
				if (x < Duration + ReturnDelay)return AniFun(x);
				else return AniFun((Duration * 2 + ReturnDelay) - x);
			} else if (Repeat_ && !Return_) {
				x -= floor(x / (Duration + RepeatDelay)) * (Duration + RepeatDelay);
				return AniFun(x);
			} else if (!Repeat_ && Return_) {
				if (x < Duration)return AniFun(x);
				else if (x < Duration * 2 + ReturnDelay)return AniFun(2 * Duration + ReturnDelay - x);
			}
			return AniFun(x);
		}
	};

	Animation::Animation() {
		NowPos = StartPos = TargetPos = 0;
		StartTime = gclock();
		AniTotal++;
	}
	Animation::Animation(realn pos) {
		NowPos = StartPos = TargetPos = pos;
		StartTime = gclock();
		AniTotal++;
	}
	Animation::Animation(realn spos, realn tpos) {
		NowPos = StartPos = spos;
		TargetPos = tpos;
		StartTime = gclock();
		AniTotal++;
	}
	Animation& Animation::SetStartPos(realn pos) {
		StartPos = NowPos = TargetPos = pos;
		StartTime = gclock();
		return *this;
	}
	Animation& Animation::SetTargetPos(realn pos, int delay = 0) {
		if (pos == TargetPos)return *this;
		StartPos = NowPos;
		TargetPos = pos;
		StartTime = gclock() + delay;
		return *this;
	}
	Animation& Animation::SetMoveStyle(std::function<realn(realn)> fun, realn start, realn end) {
		Fun = fun;
		FunStart = start;
		FunEnd = end;
		return *this;
	}
	Animation& Animation::SetMoveStyle(anif::AniPara para) {
		Fun = para.fun;
		FunStart = para.startp;
		FunEnd = para.endp;
		return *this;
	}
	Animation& Animation::SetDuration(int time) {
		Duration = time;
		return *this;
	}
	realn Animation::GetNowPos() {
		if (AniEnabled == 0)return TargetPos;
		return NowPos;
	}
	realn Animation::GetTargetPos() {
		return TargetPos;
	}
	int Animation::GetStartTime() {
		return StartTime;
	}
	realn Animation::GetStartPos() {
		return StartPos;
	}
	bool Animation::IsRunning() {
		if (gnp() == gtp())return false;
		else return true;
	}
	Animation& Animation::Pause() {
		IsStopped = true;
		return *this;
	}
	Animation& Animation::Continue() {
		IsStopped = false;
		return *this;
	}
	Animation& Animation::Update() {
		int NowTime = gclock();
		realn dtf = FunEnd - FunStart;
		if (NowTime < StartTime) return *this;
		if (NowTime > StartTime + Duration) {
			if (Repeat_) {
				if (!Return_ || Returned) {
					Returned = false;
					NowPos = StartPos;
					NowTime = gclock();
					StartTime += Duration + RepeatDelay;
				}
			}
			if (Return_) {
				NowPos = TargetPos;
				realn t = StartPos;
				StartPos = TargetPos;
				TargetPos = t;
				NowTime = gclock();
				StartTime += Duration + ReturnDelay;
				Returned = true;
			} else NowPos = TargetPos;
			return *this;
		}
		if (AniEnabled == 1) {
			realn l = Fun(FunEnd) - Fun(FunStart);
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = 1.0 * (NowTime - StartTime) / Duration * dtf;
			NowPos = (Fun(FunStart + dt) - Fun(FunStart)) * zoom + StartPos;
		} else if (AniEnabled == 0) {
			NowPos = TargetPos;
		} else if (AniEnabled == 2) {
			realn dtf = 1;
			realn l = 1;
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = 1.0 * (NowTime - StartTime) / Duration * dtf;
			NowPos = (FunStart + dt - FunStart) * zoom + StartPos;
		}
		return *this;
	}
	Animation& Animation::Reset() {
		NowPos = StartPos;
		StartTime = gclock();
		return *this;
	}
	Animation& Animation::Repeat(bool b, int delay = 0) {
		Repeat_ = b;
		RepeatDelay = delay;
		return *this;
	}
	Animation& Animation::Return(bool b, int delay = 0) {
		Return_ = b;
		if (Returned) {
			NowPos = TargetPos;
			realn t = StartPos;
			StartPos = TargetPos;
			TargetPos = t;
			Returned = false;
		}
		ReturnDelay = delay;
		return *this;
	}
	Animation& Animation::Stop() {
		Update();
		TargetPos = NowPos;
		StartPos = NowPos;
		return *this;
	}
	Animation& Animation::Goto(realn pos) {
		TargetPos = pos;
		StartPos = pos;
		NowPos = pos;
		StartTime = gclock() - Duration;
		return *this;
	}

};

#endif
#endif
