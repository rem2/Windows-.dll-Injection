#include "CreateRemoteThreadInjection.h"

void CreateRemoteThreadInjection::Inject(HANDLE pHandle, char* buffer) {

	// Get the address of LoadLibrary in order to call it later without having to use the default WinAPI
	LPTHREAD_START_ROUTINE loadLibraryAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	// Allocate the length of our loaded .dll into memory
	LPVOID allocation = VirtualAllocEx(pHandle, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (allocation != NULL) {
		// Write our allocation into memory
		WriteProcessMemory(pHandle, allocation, buffer, strlen(buffer), NULL);

		// Create our remote thread
		CreateRemoteThread(pHandle, NULL, 0, loadLibraryAddress, allocation, NULL, NULL);
	}
}