// ggcc_animation
// ggcc动画库

#pragma once

#include <functional>
#include <cmath>
#include <chrono>

using realn = float;

namespace ggcc {

	// 计时器
	auto StartGClcok = std::chrono::high_resolution_clock::now();
	auto LastRecordGClock = std::chrono::high_resolution_clock::now();
	auto GClockInterval = LastRecordGClock - StartGClcok;
	long long gclock() {
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - StartGClcok);
		return duration.count();
	}
	void update_gclock() {
		auto now = std::chrono::high_resolution_clock::now();
		GClockInterval = now - LastRecordGClock;
		LastRecordGClock = now;
	}
	long long gclock_interval() {
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(GClockInterval);
		return duration.count();
	}

	// 动画函数
	namespace anif {

		// 动画参数结构体
		struct AniPara {
			realn startp;						// 动画起始点
			realn endp;							// 动画终止点
			std::function <realn(realn)> fun;	// 动画函数
			AniPara(realn start, realn end, std::function <realn(realn)> f) {
				fun = f;
				startp = start;
				endp = end;
			}
		};
		// 瞬间动画
		const AniPara moment{0, 1, [](realn x) {
				return x <= 0 ? 0 : 1;
			}};
		// 线性动画
		const AniPara linear{0, 1, [](realn x) {
			return x;
		}};
		// 经典动画（先快后慢）
		const AniPara classics {10, 0, [](realn x) {
			return std::pow(1.618, x);
		}};
		// 经典动画（先慢后快）
		const AniPara classics_r {10, 0, [](realn x) {
			return std::pow(1.618, x);
		}};
		// 经典动画（先慢后快再快）
		const AniPara classics_d {0, 20, [](realn x) {
			if (x < 10) return std::pow(1.618, x);
			return std::pow(1.618, 10) * 2 - std::pow(1.618, 20 - x) + 1;
		}};
		// sin函数动画
		const AniPara sine {-3.1415926 / 2, 3.1415926 / 2, [](realn x) {
			return std::sin(x);
		}};
		// tan函数动画
		const AniPara tanf { -1.35, 1.35, [](realn x) {
			return std::tan(x);
		}};
		// tanh函数动画
		const AniPara tanh {-2.5, 2.5, [](realn x) {
			return std::tanh(x);
		}};
		// 回弹动画（阻力5）
		const AniPara bounce {-8.9726, 0, [](realn x) {
			return -7.0 / 51 * std::sqrt(51) * std::exp(-7.0 / 10 * x) * std::sin(1.0 / 10 * sqrt(51) * x) - std::exp(-7.0 / 10 * x) * std::cos(1.0 / 10 * std::sqrt(51) * x);
		}};
		// 回弹动画（阻力5）
		const AniPara bounce1 {-8.9726, 0, [](realn x) {
			return -7.0 / 51 * std::sqrt(51) * std::exp(-7.0 / 10 * x) * std::sin(1.0 / 10 * sqrt(51) * x) - std::exp(-7.0 / 10 * x) * std::cos(1.0 / 10 * std::sqrt(51) * x);
		}};
		// 回弹动画（阻力4）
		const AniPara bounce2 {-8.2645, 0, [](realn x) {
			return -13.0 / 231 * std::sqrt(231) * std::exp(-13.0 / 20 * x) * std::sin(1.0 / 20 * std::sqrt(231) * x) - std::exp(-13.0 / 20 * x) * std::cos(1.0 / 20 * std::sqrt(231) * x);
		}};
		// 回弹动画（阻力3）
		const AniPara bounce3 {-7.9188, 0, [](realn x) {
			return -3.0 / 4 * std::exp(-3.0 / 5 * x) * std::sin(4.0 / 5 * x) - std::exp(-3.0 / 5 * x) * std::cos(4.0 / 5 * x);
		}};
		// 回弹动画（阻力2）
		const AniPara bounce4 {-7.5220, 0, [](realn x) {
			return -11.0 / 93 * std::sqrt(31) * std::exp(-11.0 / 20 * x) * std::sin(3.0 / 20 * std::sqrt(31) * x) - std::exp(-11.0 / 20 * x) * std::cos(3.0 / 20 * std::sqrt(31) * x);
		}};
		// 回弹动画（阻力2）
		const AniPara bounce5 {-7.3448, 0, [](realn x) {
			return -1.0 / 3 * std::sqrt(3) * std::exp(-1.0 / 2 * x) * std::sin(1.0 / 2 * std::sqrt(3) * x) - std::exp(-1.0 / 2 * x) * std::cos(1.0 / 2 * std::sqrt(3) * x);
		}};
		// G3动画（左连右连）
		const AniPara g3 {0, 3.14159 * 2, [](realn x) {
			return x - std::sin(x);
		}};
		const AniPara g3r {3.14158, 3.14159 * 2, [](realn x) {
			return x - std::sin(x);
		}};
		const AniPara g3l {0, 3.14159, [](realn x) {
			return x - std::sin(x);
		}};
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
		anif::AniPara anipara = anif::classics;
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
		Animation(realn, realn, anif::AniPara);

		Animation& SetStartPos(realn);
		Animation& SetTargetPos(realn, int);
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
			realn dtf = anipara.endp - anipara.startp;
			realn l = anipara.fun(anipara.endp) - anipara.fun(anipara.startp);
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = x / Duration * dtf;
			return (anipara.fun(anipara.startp + dt) - anipara.fun(anipara.startp)) * zoom + StartPos;
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
	Animation::Animation(realn spos, realn tpos, anif::AniPara para = anif::classics) {
		NowPos = StartPos = spos;
		TargetPos = tpos;
		StartTime = gclock();
		anipara = para;
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
	Animation& Animation::SetMoveStyle(anif::AniPara para) {
		anipara = para;
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
		realn dtf = anipara.endp - anipara.startp;
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
			realn l = anipara.fun(anipara.endp) - anipara.fun(anipara.startp);
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = 1.0 * (NowTime - StartTime) / Duration * dtf;
			NowPos = (anipara.fun(anipara.startp + dt) - anipara.fun(anipara.startp)) * zoom + StartPos;
		} else if (AniEnabled == 0) {
			NowPos = TargetPos;
		} else if (AniEnabled == 2) {
			realn dtf = 1;
			realn l = 1;
			realn zoom = 1.0 * (TargetPos - StartPos) / l;
			realn dt = 1.0 * (NowTime - StartTime) / Duration * dtf;
			NowPos = (anipara.startp + dt - anipara.startp) * zoom + StartPos;
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
