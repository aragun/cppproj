// EventLoop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SmartEventLoop.h"

int main()
{
	{
		auto eventLoop = std::make_shared<SmartEventLoop>();
		for (int i = 1; i <= 2; i++)
			eventLoop->AddTask([i]() {std::cout << i << std::endl; });
	}
    return 0;
}

