#include "stdafx.h"
#include "PEInjection.h"

DWORD PEInjection::InjectableThread(injectableData * iData) {
	MessageBox(NULL, iData->messageBoxContents, (LPCSTR)iData->messageBoxTitle, MB_ICONEXCLAMATION);
	return 0;
}

void PEInjection::Inject(HANDLE processHandle, char* messageBoxContents, char* messageBoxTitle) {

	injectableData iData;
	iData.messageBoxContents = messageBoxContents;
	iData.messageBoxTitle = messageBoxTitle;

	HINSTANCE userDLL = LoadLibrary("user32.dll");
	iData.injectableThreadAddress = (DWORD)GetProcAddress(userDLL, "MessageBoxA");

	// Frees the loaded dll and passes it to injectableThreadAddress
	FreeLibrary(userDLL);

	// Allocate memory for our remotethread
	LPVOID remoteThread = VirtualAllocEx(processHandle, NULL, sizeof(&iData), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	// Write the remote thread to the selected process
	WriteProcessMemory(processHandle, remoteThread, (LPVOID)remoteThread, sizeof(&iData), 0);
	// Allocate memory for cavediData to be injected into the remote process
	injectableData * cavediData = (injectableData*)VirtualAllocEx(processHandle, NULL, sizeof(injectableData), MEM_COMMIT, PAGE_READWRITE);
	// Write our cavediData pointer to our selected process
	WriteProcessMemory(processHandle, cavediData, &iData, sizeof(iData), NULL);
	// Create our remote thread
	HANDLE processThread = CreateRemoteThread(processHandle, 0, 0, (LPTHREAD_START_ROUTINE)remoteThread, cavediData, 0, 0);
	
	// Clean up
	CloseHandle(remoteThread);
	VirtualFreeEx(processThread, remoteThread, sizeof(iData), MEM_RELEASE);
	CloseHandle(remoteThread);

}