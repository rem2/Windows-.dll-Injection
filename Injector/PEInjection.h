#pragma once
#include "stdafx.h"

class PEInjection {
public:
	static void Inject(HANDLE processHandle, char* messageBoxContents);
private:
	struct injectableData
	{
		char * messageBoxContents;
		char * messageBoxTitle;

		DWORD injectableThreadAddress;
	};
	DWORD InjectableThread(injectableData * iData);
};