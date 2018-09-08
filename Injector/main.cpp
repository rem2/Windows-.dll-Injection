// Injector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Process.h"
#include "CreateRemoteThreadInjection.h"

int main(char* arg) {
	if (arg == NULL) {
		return -1;
	}
	Process p("chrome.exe");
	HANDLE pHandle = p.GetProcessHandle();

	if (pHandle != NULL) {
		CreateRemoteThreadInjection::Inject(pHandle, arg);
	}
}
