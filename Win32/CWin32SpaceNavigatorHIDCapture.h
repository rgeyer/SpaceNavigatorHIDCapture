#ifndef __CWIN32SPACENAVIGATORHIDCAPTURE_H__
#define __CWIN32SPACENAVIGATORHIDCAPTURE_H__

#include <string>
#include <iostream>
#include "ADeviceCapture.h"
#include "IDeviceListener.h"

#include <setupapi.h>

extern "C"
{
#include <hidsdi.h>
#include <hidpi.h>
}

//Pointers to a function are used, therefore:
typedef VOID    (__stdcall *PHidD_GetHidGuid)(LPGUID);
typedef BOOLEAN (__stdcall *PHidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef BOOLEAN (__stdcall *PHidD_GetPreparsedData)(HANDLE, PHIDP_PREPARSED_DATA*);
typedef BOOLEAN (__stdcall *PHidD_FreePreparsedData)(PHIDP_PREPARSED_DATA);
typedef NTSTATUS (__stdcall *PHidP_GetCaps)(PHIDP_PREPARSED_DATA, PHIDP_CAPS);

//Some typedefs to make _beginthreadex behave nicely
typedef unsigned (__stdcall *PBEGINTHREADEX_THREADFUNC)(LPVOID);
typedef unsigned *PBEGINTHREADEX_THREADID;


typedef std::map<wstring, std::pair<BYTE, BYTE>> TCommandByName;

// This class is exported from the SpaceNavigatorHIDCapture.dll
///<summary>This is the implementation of <see cref="ISpaceNavigatorHIDCapture"/> interface for Windows 2000, XP, and 2003.  Might also work on Vista?</summary>
class CWin32SpaceNavigatorHIDCapture : public ADeviceCapture {
public:
	CWin32SpaceNavigatorHIDCapture(void);
	~CWin32SpaceNavigatorHIDCapture(void);

private:
	HMODULE _hidDll;
	PHidD_GetHidGuid _HidD_GetHidGuid;
	PHidD_GetAttributes _HidD_GetAttributes;
	PHidD_GetPreparsedData _HidD_GetPreparsedData;
	PHidD_FreePreparsedData _HidD_FreePreparsedData;
	PHidP_GetCaps _HidP_GetCaps;

	HANDLE _threadHandle;
	unsigned int _threadId;


	// Some required HID stuff etc
private:
	BOOL _spaceNavPresent;
	GUID _hidGuid;
	HDEVINFO _hidDevInfo;
	PHIDP_PREPARSED_DATA _preparsedData;
	HIDP_CAPS _capabilities;
	HANDLE _spaceNavFileHandle;

	HANDLE _runThreadEvent;

	TCommandByName _commandsByName;

	// Methods from IDeviceCapture
public:
	virtual DWORD ScanForDevice();	
	virtual BOOL DevicePresent();
	virtual void StartCapturing();
	virtual void StopCapturing();

public:
	virtual void AddCommand(wstring name, BYTE report, BYTE value);
	virtual void RunCommand(wstring command);
	GUID GetHIDGuid();
	BOOL SetLED(const bool);

public:
	// The static method called in a thread when new data is available to be sent
	static DWORD __stdcall CaptureAndDispatchThread(LPVOID);
};

#endif