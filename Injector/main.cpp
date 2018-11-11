// Injector.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Process.h"
#include "CreateRemoteThreadInjection.h"
#include "PEInjection.h"

// Usage: processName, injectionType, dll/message
// chrome.exe c hello
int main(int argc, char** argv) {
	if (argv[1] == NULL) {
		return -1;
	}
	// Get handle to process
	Process p(argv[1]);
	HANDLE pHandle = p.GetProcessHandle();

	if (pHandle != NULL && argv[2] == 'c') {
		CreateRemoteThreadInjection::Inject(pHandle, argv[3]);
	}
	if (pHandle != NULL && argv[2] == 'p') {
		PEInjection::Inject(pHandle, argv[3]);
	}
	else {
		// Couldn't get handle or bad args
		return -1;
	}

	return 1;
}
