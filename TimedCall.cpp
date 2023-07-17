#include "TimedCall.h"

TimedCall::TimedCall(std::function<void(void)> fire, uint32_t time) {
	fire_ = fire;
	time_ = time;
}

void TimedCall::Update() {
	if (completionFlag_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		completionFlag_ = true;
		//コールバック関数呼び出し
		fire_();
	}
}
