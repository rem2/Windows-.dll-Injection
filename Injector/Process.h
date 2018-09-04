#include <Windows.h>
#include <string>
#include <tlhelp32.h>
class Process {
public:
	Process(std::string processName);
	Process(int processID);
	HANDLE GetProcessHandle();
private:
	std::string processName;
	int processID;
	HANDLE processHandle;

	void SetHandleAllAccess();
	int GetProcessIDByName(std::string processName);
};