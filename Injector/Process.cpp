#include "Process.h"

Process::Process(std::string processName) {
	// Get the processID with the provided name
	processID = GetProcessIDByName(processName);

	// If the process ID is valid, continue
	if (processID != -1) {
		SetHandleAllAccess();
	}
}
Process::Process(int processID) {
	SetHandleAllAccess();
}

HANDLE Process::GetProcessHandle() {
	if (processHandle != NULL) {
		return processHandle;
	}
	else {
		return 0x0;
	}
}

int Process::GetProcessIDByName(std::string processName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	// Create a snapshot of all running processes
	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	// If the size of our snapshot is greater than 1, continue
	if (Process32First(processSnapshot, &entry) == TRUE) {
		while (Process32Next(processSnapshot, &entry) == TRUE) {
			// Found our process
			if (stricmp(entry.szExeFile, processName.c_str()) == 0) {
				return entry.th32ProcessID;
			}
		}
	}
	
	// Didn't find our process :(
	return -1;
}

void Process::SetHandleAllAccess() {
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
}