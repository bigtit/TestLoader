#include <Windows.h>
#include <strsafe.h>

#include "SvcManager.h"
#include "DevManager.h"

int main() {
    constexpr static TCHAR svcName[] = L"MatchIo";
    constexpr static TCHAR sysName[] = L"204.sys";
    MatchIo::SvcManager sm{ L"MatchIo", L"204.sys" };
    MatchIo::DevManager dm{ L"MatchIo" };
    //TCHAR szPath[MAX_PATH];
    //StringCbPrintf(szPath, MAX_PATH, TEXT("\"%s\\%s\""), L"C:", L"204.sys");
    //wprintf_s(L"%s", szPath);
    sm.SvcInstall();
    sm.DoStartSvc();

    dm.OpenDevice();
    // dm.ControlDevice(MatchIo::DevManager::CTL_KEY_DOWN, 0x1f);
    Sleep(3000);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_DOWN, 0x1F);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_UP, 0x1F);
    Sleep(1000);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_DOWN, 0x1E);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_UP, 0x1E);
    Sleep(1000);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_DOWN, 0x20);
    dm.ControlKey(MatchIo::DevManager::CTL_KEY_UP, 0x20);
    dm.CloseDevice();

    // Sleep(3000);
    sm.DoStopSvc();
    sm.DoDeleteSvc();
    return 0;
}
