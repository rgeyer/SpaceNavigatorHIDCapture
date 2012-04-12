#include "stdafx.h"
#include "ASpaceNavigatorHIDCapture.h"

ASpaceNavigatorHIDCapture::ASpaceNavigatorHIDCapture()
{
	InitializeCriticalSection(&_cs);
}

ASpaceNavigatorHIDCapture::~ASpaceNavigatorHIDCapture()
{
	DeleteCriticalSection(&_cs);
}

/*virtual*/ void ASpaceNavigatorHIDCapture::RegisterListener(ISpaceNavigatorHIDListener* listener)
{
	EnterCriticalSection(&_cs);
	_listeners.push_back(listener);
	LeaveCriticalSection(&_cs);
}

/*virtual*/ void ASpaceNavigatorHIDCapture::UnregisterListener(ISpaceNavigatorHIDListener* listener)
{
	EnterCriticalSection(&_cs);
	_listeners.remove(listener);
	LeaveCriticalSection(&_cs);
}