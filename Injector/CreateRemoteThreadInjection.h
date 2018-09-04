#pragma once
#include <Windows.h>

class CreateRemoteThreadInjection {
public: 
	static void Inject(HANDLE pHandle, char* buffer);
};