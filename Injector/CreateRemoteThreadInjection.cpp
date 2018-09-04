#include "CreateRemoteThreadInjection.h"



void CreateRemoteThreadInjection::Inject(HANDLE pHandle, char* buffer) {
	// Get the address of LoadLibraryA so that we can call it without using the WinAPI function LoadLibraryA
	LPVOID addressLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	// Allocate the memory needed for us to inject our dll
	LPVOID allocation = (LPVOID)VirtualAllocEx(pHandle, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// Write our dll into the memory of the remote process
	WriteProcessMemory(pHandle, allocation, buffer, strlen(buffer), NULL);

	// Create our remote thread
	CreateRemoteThread(pHandle, NULL, 0, (LPTHREAD_START_ROUTINE)addressLoadLibrary, allocation, NULL, NULL);
}