#pragma once
#include <windows.h>
#include <tchar.h>

namespace MatchIo {

// device manager: open, close, control device
class DevManager {
	constexpr static size_t DEVNAME_LEN = 80;
public:
	constexpr static DWORD CTL_KEY_UP = 0x80102130;
	constexpr static DWORD CTL_KEY_DOWN = 0x80102110;
private:
	TCHAR szDevName[DEVNAME_LEN];
	HANDLE hDevice;
public:
	DevManager(const TCHAR* svcName);

public:
	VOID __stdcall OpenDevice(void);
	VOID __stdcall CloseDevice(void);
	VOID __stdcall ControlKey(DWORD, int scanCode);
};

}