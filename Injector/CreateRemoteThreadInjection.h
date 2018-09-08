#pragma once
#include "stdafx.h"

class CreateRemoteThreadInjection {
public:
	static void Inject(HANDLE pHandle, char* buffer);
};