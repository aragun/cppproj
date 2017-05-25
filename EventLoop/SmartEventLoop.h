#pragma once
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

class SmartEventLoop
{
public:
	void AddTask(std::function<void()>);

	SmartEventLoop();
	~SmartEventLoop();

private:
	void Process();
	std::mutex mQueueMutex;
	std::condition_variable mCv;
	std::atomic_bool mShouldQuit = false;
	std::queue<std::function<void()>> mTaskQueue;
	std::unique_ptr<std::thread> mEventThread;
};

