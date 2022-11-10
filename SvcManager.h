#pragma once
#include <windows.h>
#include <tchar.h>

// #define SVCNAME TEXT("SvcName") // service name

namespace MatchIo {

// open, close, control driver service
class SvcManager {

	constexpr static size_t SVCNAME_LEN = 80;

private:
	// Svc.h
	/*
	SERVICE_STATUS          gSvcStatus;
	SERVICE_STATUS_HANDLE   gSvcStatusHandle;
	HANDLE                  ghSvcStopEvent = NULL;
	*/
	// SvcConfig.cpp
	// TCHAR szCommand[10];
	TCHAR szSvcName[SVCNAME_LEN];
	TCHAR szPath[MAX_PATH];
	// SvcControl.cpp
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

public:
	SvcManager() = delete;
	SvcManager(const TCHAR* svcName, const TCHAR* fileName);

public:
	// Svc.cpp
	VOID SvcInstall(void);
	// SvcConfig.cpp
	// VOID __stdcall DoQuerySvc(void);
	// VOID __stdcall DoUpdateSvcDesc(void);
	VOID __stdcall DoDisableSvc(void);
	VOID __stdcall DoEnableSvc(void);
	VOID __stdcall DoDeleteSvc(void);
	// SvcControl.cpp
	VOID __stdcall DoStartSvc(void);
	// VOID __stdcall DoUpdateSvcDacl(void);
	VOID __stdcall DoStopSvc(void);

private:
	BOOL __stdcall StopDependentServices(void);
};

}