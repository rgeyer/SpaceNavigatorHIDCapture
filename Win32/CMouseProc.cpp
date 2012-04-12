#include "StdAfx.h"
#include "CMouseProc.h"

#include "IDeviceListener.h"

#include <process.h>

CMouseProc::CMouseProc() :
ADeviceCapture("mouse"),
_mousePresent(true),
_threadHandle(NULL),
_threadId(0)
{
	CMouseProc::init();
	_runThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

/*virtual*/ DWORD CMouseProc::ScanForDevice()
{
	return 0;
}

/*virtual*/ BOOL CMouseProc::DevicePresent()
{
	return true;
}

/*virtual*/ void CMouseProc::StartCapturing()
{
	if(!_mousePresent)
		return;
	if(_threadHandle == NULL)
	{
		_threadHandle = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)CMouseProc::CaptureAndDispatchThread,
			(LPVOID)this,
			0,
			&_threadId);
	}
}

/*virtual*/ void CMouseProc::StopCapturing()
{
	SetEvent(_runThreadEvent);
	if(_threadHandle && _threadId)
	{
		WaitForSingleObject(_threadHandle, INFINITE);
		CloseHandle(_threadHandle);
		_threadId = NULL;
		_threadHandle = NULL;
	}
	ResetEvent(_runThreadEvent);
	return;
}

////////////////////////////////////////////// Static stuff below here /////////////////////////////////////////
HHOOK CMouseProc::_mouseHook = NULL;
POINT CMouseProc::_pt;
POINT CMouseProc::_lastPt;
short CMouseProc::_buttons = 0;
short CMouseProc::_lastButtons = 0;
CCriticalSection CMouseProc::_criticalSection;

DWORD CMouseProc::init(void)
{
	if(_mouseHook == NULL)
		_mouseHook = ::SetWindowsHookEx(WH_MOUSE_LL, &CMouseProc::MouseProc, ::AfxGetInstanceHandle(), NULL);
	else
		return 0;
	if(!_mouseHook)
		return ::GetLastError();
	return 0;
}

LRESULT CALLBACK CMouseProc::MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode == HC_ACTION)
	{
		if(lParam)
		{
			MSLLHOOKSTRUCT *pMH = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);
			if(pMH)
			{
				CSingleLock lock(&_criticalSection);
				lock.Lock();
				_pt = pMH->pt;
				switch (wParam)
				{
				case WM_LBUTTONDOWN:
					{
						_buttons ^= 1;
						break;
					}
				case WM_LBUTTONUP:
					{
						_buttons ^= 1;
						break;
					}
				case WM_RBUTTONDOWN:
					{
						_buttons ^= 2;
						break;
					}
				case WM_RBUTTONUP:
					{
						_buttons ^= 2;
						break;
					}
				default: break;
				}
				lock.Unlock();
			}
		}
	}

	return ::CallNextHookEx(_mouseHook, nCode, wParam, lParam);
}

DWORD __stdcall CMouseProc::CaptureAndDispatchThread(LPVOID ptr)
{
	CMouseProc* device = dynamic_cast<CMouseProc*>((CMouseProc*)ptr);
	if(device == NULL)
		return 1;
	while(TRUE)
	{
		if(WaitForSingleObject(device->_runThreadEvent, 10) == WAIT_OBJECT_0)
			return 0;
		CSingleLock lock(&_criticalSection);
		lock.Lock();
		if(_buttons != _lastButtons)
		{
			EnterCriticalSection(&device->_cs);
			for(TListenerList::iterator i = device->_listeners.begin(); i != device->_listeners.end(); i++)
			{
				IDeviceListener* listener = *i;
				listener->ButtonsChanged((IDeviceCapture*)device, _buttons);
			}
			LeaveCriticalSection(&device->_cs);
			_lastButtons = _buttons;
		}
		EnterCriticalSection(&device->_cs);
		for(TListenerList::iterator i = device->_listeners.begin(); i != device->_listeners.end(); i++)
		{
			IDeviceListener* listener = *i;
			listener->AxeChanged((IDeviceCapture*)device, 0, _pt.x);
			listener->AxeChanged((IDeviceCapture*)device, 1, _pt.y);
		}
		LeaveCriticalSection(&device->_cs);
		_lastButtons = _buttons;

		lock.Unlock();
	}
	return 0;
}