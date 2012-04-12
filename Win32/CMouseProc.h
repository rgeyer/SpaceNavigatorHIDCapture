#ifndef __CMOUSEPROC_H__
#define __CMOUSEPROC_H__

#include "ADeviceCapture.h"

//Some typedefs to make _beginthreadex behave nicely
typedef unsigned (__stdcall *PBEGINTHREADEX_THREADFUNC)(LPVOID);
typedef unsigned *PBEGINTHREADEX_THREADID;

class CMouseProc : public ADeviceCapture
{
public:
	CMouseProc();

	// IDeviceCapture Methods
	virtual DWORD ScanForDevice();
	virtual BOOL DevicePresent();
	virtual void StartCapturing();
	virtual void StopCapturing();

private:
	bool _mousePresent;	
	HANDLE _threadHandle;
	unsigned int _threadId;
	HANDLE _runThreadEvent;

	////////////////////////////////////////////// Static stuff below here /////////////////////////////////////////
public:
	static DWORD init(void);
	static __w64 long __stdcall MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
	static DWORD __stdcall CaptureAndDispatchThread(LPVOID);

private:
	static HHOOK _mouseHook;
	static POINT _pt;
	static POINT _lastPt;
	static short _buttons;
	static short _lastButtons;
	static CCriticalSection _criticalSection;
};

#endif
