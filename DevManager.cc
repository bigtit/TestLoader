#include <strsafe.h>

#include "DevManager.h"

namespace MatchIo {
DevManager::DevManager(const TCHAR* svcName) : hDevice{ 0 } {
	StringCbPrintf(szDevName, DEVNAME_LEN, TEXT("\\\\.\\%s"), svcName);
}

VOID __stdcall DevManager::OpenDevice(void)
{
	hDevice = CreateFile(szDevName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hDevice == INVALID_HANDLE_VALUE) {
		printf("Failed to CreateFile: %d\n", GetLastError());
		return;
	}
#ifdef _DEBUG
	printf("CreateFile succeed\n");
#endif
}

VOID __stdcall DevManager::CloseDevice(void)
{
	if (!CloseHandle(hDevice)) {
		printf("Failed to CloseHandle: %d\n", GetLastError());
		return;
	}
#ifdef _DEBUG
	printf("CloseHandle succeed\n");
#endif
}

VOID __stdcall DevManager::ControlKey(DWORD ctlCode, int scanCode)
{
	char outBuffer[4];
	if (!DeviceIoControl(hDevice, ctlCode, &scanCode, 4u, outBuffer, 4, 0, 0)) {
		printf("Failed to DeviceIoControl: %d\n", GetLastError());
		return;
	}
#ifdef _DEBUG
	printf("ControlDevice succeed: 0x%x\n", ctlCode);
#endif
	return VOID();
}

}