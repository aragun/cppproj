#include "stdafx.h"
#include "SmartEventLoop.h"


void SmartEventLoop::AddTask(std::function<void()> f)
{
	if (mShouldQuit)
		return;

	std::lock_guard<std::mutex> lock(mQueueMutex);
	mTaskQueue.push(f);
	mCv.notify_one();
}

SmartEventLoop::SmartEventLoop() : mEventThread(new std::thread(&SmartEventLoop::Process, this))
{}


SmartEventLoop::~SmartEventLoop()
{
	mShouldQuit = true;
	if (mEventThread.get())
		mEventThread->join();
}

void SmartEventLoop::Process()
{
	while (1)
	{
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(mQueueMutex);
			mCv.wait(lock, [&] {return !mTaskQueue.empty() || mShouldQuit; });

			if (mTaskQueue.empty() && mShouldQuit)
				return;

			if (!mTaskQueue.empty())
			{
				task = mTaskQueue.front();
				mTaskQueue.pop();
			}
		}
		task();
	}
}
