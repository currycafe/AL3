#pragma once
#include <functional>
class TimedCall {
public:
	TimedCall(std::function<void(void)>fire, uint32_t time);
	void Update();
	bool IsFinished() { return completionFlag_; }

private:
	//コールバック
	std::function<void(void)>fire_;
	uint32_t time_;
	bool completionFlag_ = false;






};

