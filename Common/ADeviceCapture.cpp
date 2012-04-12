#include "stdafx.h"
#include "ADeviceCapture.h"

ADeviceCapture::ADeviceCapture(string type) : _type(type)
{
	InitializeCriticalSection(&_cs);
}

ADeviceCapture::~ADeviceCapture()
{
	DeleteCriticalSection(&_cs);
}

/*virtual*/ void ADeviceCapture::RegisterListener(IDeviceListener* listener)
{
	EnterCriticalSection(&_cs);
	_listeners.push_back(listener);
	LeaveCriticalSection(&_cs);
}

/*virtual*/ void ADeviceCapture::UnregisterListener(IDeviceListener* listener)
{
	EnterCriticalSection(&_cs);
	_listeners.remove(listener);
	LeaveCriticalSection(&_cs);
}