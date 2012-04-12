#include "stdafx.h"
#include "CWin32SpaceNavigatorHIDCapture.h"

#include <process.h>

CWin32SpaceNavigatorHIDCapture::CWin32SpaceNavigatorHIDCapture() :
	ADeviceCapture("hid"),
	_hidDevInfo(NULL),
	_spaceNavPresent(FALSE),
	_spaceNavFileHandle(NULL),
	_threadHandle(NULL),
	_threadId(NULL),
	_hidDll(NULL),
	_HidD_GetHidGuid(NULL),
	_HidD_GetAttributes(NULL),
	_HidD_GetPreparsedData(NULL),
	_HidP_GetCaps(NULL)
{
	_hidDll = LoadLibrary("hid.dll");
	if(_hidDll != NULL)
	{
		_HidD_GetHidGuid = (PHidD_GetHidGuid)GetProcAddress(_hidDll, "HidD_GetHidGuid");
		_HidD_GetAttributes = (PHidD_GetAttributes)GetProcAddress(_hidDll, "HidD_GetAttributes");
		_HidD_GetPreparsedData = (PHidD_GetPreparsedData)GetProcAddress(_hidDll, "HidD_GetPreparsedData");
		_HidD_FreePreparsedData = (PHidD_FreePreparsedData)GetProcAddress(_hidDll, "HidD_FreePreparsedData");
		_HidP_GetCaps = (PHidP_GetCaps)GetProcAddress(_hidDll, "HidP_GetCaps");
	}
	_runThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// Get the device GUID for HID devices
	_HidD_GetHidGuid(&_hidGuid);

	return;
}

CWin32SpaceNavigatorHIDCapture::~CWin32SpaceNavigatorHIDCapture()
{
	if(_spaceNavFileHandle != NULL)
		CloseHandle(_spaceNavFileHandle);
	if(_runThreadEvent != NULL)
		CloseHandle(_runThreadEvent);

	if(_hidDll != NULL)
		FreeLibrary(_hidDll);
}

/*virtual*/ DWORD CWin32SpaceNavigatorHIDCapture::ScanForDevice()
{
	// Set it false first, just incase we don't get to true below.
	_spaceNavPresent = FALSE;	
	// Get a list of currently available devices
	_hidDevInfo = SetupDiGetClassDevs(&_hidGuid, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if(_hidDevInfo != NULL)
	{
		// Enumerate through the list, looking for the SpaceNavigator
		DWORD deviceCount = 0;
		DWORD size = 0;
		DWORD requiredSize = 0;

		SP_DEVICE_INTERFACE_DATA devIfaceData;
		ZeroMemory((void*)&devIfaceData, sizeof(devIfaceData));
		devIfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		
		BOOL result = true;

		while(result)
		{
			// Get the next device in the list
			result = SetupDiEnumDeviceInterfaces(_hidDevInfo,0,&_hidGuid,deviceCount,&devIfaceData);

			// Find out how big the path name will be
			SetupDiGetDeviceInterfaceDetail(_hidDevInfo, &devIfaceData, NULL, size, &requiredSize, NULL);

			// Allocate a new Device_Interface_Detail_Data big enough to hold the string
			int sizeToAllocDevDetail = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) + requiredSize;
			PSP_DEVICE_INTERFACE_DETAIL_DATA devDetail;
			devDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)new BYTE[sizeToAllocDevDetail];
			ZeroMemory(devDetail, sizeToAllocDevDetail);
			size = requiredSize;
			devDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			// Get the Device_Interface_Detail_Data which will give us the device path
			SetupDiGetDeviceInterfaceDetail(_hidDevInfo, &devIfaceData, devDetail, size, &requiredSize, NULL);			

			// Create a file handle for the current device so we can read some details about it
			HANDLE tempFileHandle = CreateFile(devDetail->DevicePath,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				0,
				OPEN_EXISTING,
				FILE_FLAG_OVERLAPPED,
				0);
			if(tempFileHandle != NULL)
			{
				// Get the device details, and check against the space nav vendor and product ID's
				HIDD_ATTRIBUTES attributes;
				if(_HidD_GetAttributes(tempFileHandle, &attributes))
				{
					if(attributes.VendorID == 0x046D && attributes.ProductID == 0xC626)
					{
						_spaceNavPresent = TRUE;
						_spaceNavFileHandle = tempFileHandle;

						// Grab some superfoulus stuff that we might use later
						if(_HidD_GetPreparsedData(_spaceNavFileHandle, &_preparsedData))
						{
							_HidP_GetCaps(_preparsedData, &_capabilities);
							_HidD_FreePreparsedData(_preparsedData);
						}						
						return 0;
					}
				}
				CloseHandle(tempFileHandle);
			}
			else
				return GetLastError();

			deviceCount++;
		}
		SetupDiDestroyDeviceInfoList(_hidDevInfo);
	}
	return 0;
}

/*virtual*/ BOOL CWin32SpaceNavigatorHIDCapture::DevicePresent()
{
	return _spaceNavPresent;
}

/*virtual*/ BOOL CWin32SpaceNavigatorHIDCapture::SetLED(const bool ledOn)
{
	if(_spaceNavFileHandle != NULL)
	{
		OVERLAPPED op;
		ZeroMemory(&op, sizeof(OVERLAPPED));
		op.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		BYTE* outReport = new BYTE[_capabilities.OutputReportByteLength];
		outReport[0] = 0x0004;
		outReport[1] = ledOn ? 0x0001 : 0x0000;
		DWORD bytesWritten = 0;		
		WriteFile(_spaceNavFileHandle, &outReport[0], _capabilities.OutputReportByteLength, &bytesWritten, &op);
		WaitForSingleObject(op.hEvent, INFINITE);
		CloseHandle(op.hEvent);
		delete [] outReport;
		return true;
	}
	return true;
}

/*virtual*/ void CWin32SpaceNavigatorHIDCapture::AddCommand(wstring command, BYTE report, BYTE value)
{
	_commandsByName[L"Led On"] = std::make_pair(0x0004, 0x0001);
	_commandsByName[L"Led Off"] = std::make_pair(0x0004, 0x0000);
}

/*virtual*/ void CWin32SpaceNavigatorHIDCapture::RunCommand(wstring command)
{
	if(_spaceNavFileHandle != NULL)
	{
		BYTE report = _commandsByName[command].first;
		BYTE value = _commandsByName[command].second;
		OVERLAPPED op;
		ZeroMemory(&op, sizeof(OVERLAPPED));
		op.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		BYTE* outReport = new BYTE[_capabilities.OutputReportByteLength];
		/*outReport[0] = 0x0004;
		outReport[1] = ledOn ? 0x0001 : 0x0000;*/
		outReport[0] = report;
		outReport[1] = value;
		DWORD bytesWritten = 0;		
		WriteFile(_spaceNavFileHandle, &outReport[0], _capabilities.OutputReportByteLength, &bytesWritten, &op);
		WaitForSingleObject(op.hEvent, INFINITE);
		CloseHandle(op.hEvent);
		delete [] outReport;
		return;
	}
	return;
}

/*virtual*/ void CWin32SpaceNavigatorHIDCapture::StartCapturing()
{
	if(!_spaceNavPresent)
		return;
	if(_threadHandle == NULL)
	{
		_threadHandle = (HANDLE)_beginthreadex(NULL,
			0,
			(PBEGINTHREADEX_THREADFUNC)CWin32SpaceNavigatorHIDCapture::CaptureAndDispatchThread,
			(LPVOID)this,
			0,
			&_threadId);
	}
}

/*virtual*/ void CWin32SpaceNavigatorHIDCapture::StopCapturing()
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

DWORD __stdcall CWin32SpaceNavigatorHIDCapture::CaptureAndDispatchThread(LPVOID inParam)
{
	CWin32SpaceNavigatorHIDCapture* captureClass = dynamic_cast<CWin32SpaceNavigatorHIDCapture*>((CWin32SpaceNavigatorHIDCapture*)inParam);
	if(captureClass == NULL)
		return 1;
	
	BYTE* readBuf = new BYTE[captureClass->_capabilities.InputReportByteLength];
	DWORD bytesRead = 0;
	HANDLE waitHandles[2];
	waitHandles[0] = captureClass->_runThreadEvent;
	while(TRUE)
	{
		if(captureClass->_spaceNavFileHandle != NULL)
		{
			OVERLAPPED overLap;
			ZeroMemory(&overLap, sizeof(OVERLAPPED));
			waitHandles[1] = overLap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			ReadFile(captureClass->_spaceNavFileHandle, readBuf, captureClass->_capabilities.InputReportByteLength, &bytesRead, &overLap);
			DWORD waitResult = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);
			CloseHandle(overLap.hEvent);
			if(waitResult == WAIT_OBJECT_0)
				break;			
			else if(waitResult == WAIT_OBJECT_0 + 1)
			{
				if(readBuf[0] == 0x0001)
				{

					short axis1 = readBuf[2] << 8 | readBuf[1];
					short axis2 = readBuf[4] << 8 | readBuf[3];
					short axis3 = readBuf[6] << 8 | readBuf[5];
					EnterCriticalSection(&captureClass->_cs);
					for(TListenerList::iterator i = captureClass->_listeners.begin(); i != captureClass->_listeners.end(); i++)
					{
						IDeviceListener* listener = *i;
						//listener->ChannelOneChanged(axis1, axis2, axis3);
						listener->AxeChanged(captureClass, 0, axis1);
						listener->AxeChanged(captureClass, 1, axis2);
						listener->AxeChanged(captureClass, 2, axis3);
					}
					LeaveCriticalSection(&captureClass->_cs);
				}
				else if(readBuf[0] == 0x0002)
				{
					short axis1 = readBuf[2] << 8 | readBuf[1];
					short axis2 = readBuf[4] << 8 | readBuf[3];
					short axis3 = readBuf[6] << 8 | readBuf[5];
					EnterCriticalSection(&captureClass->_cs);
					for(TListenerList::iterator i = captureClass->_listeners.begin(); i != captureClass->_listeners.end(); i++)
					{
						IDeviceListener* listener = *i;
						//listener->ChannelTwoChanged(axis1, axis2, axis3);
						listener->AxeChanged(captureClass, 3, axis1);
						listener->AxeChanged(captureClass, 4, axis2);
						listener->AxeChanged(captureClass, 5, axis3);
					}
					LeaveCriticalSection(&captureClass->_cs);
				}
				else if(readBuf[0] == 0x0003)
				{
					EnterCriticalSection(&captureClass->_cs);
					for(TListenerList::iterator i = captureClass->_listeners.begin(); i != captureClass->_listeners.end(); i++)
					{
						IDeviceListener* listener = *i;
						//listener->ButtonsChanged(readBuf[1]);
						listener->ButtonsChanged(captureClass, readBuf[1]);
					}
					LeaveCriticalSection(&captureClass->_cs);
				}
			}
		}
	}
	delete [] readBuf;
	return 0;
}

GUID CWin32SpaceNavigatorHIDCapture::GetHIDGuid()
{
	return _hidGuid;
}