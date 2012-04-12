#ifndef __ISPACENAVIGATORHIDCAPTURE_H__
#define __ISPACENAVIGATORHIDCAPTURE_H__

#include "ISpaceNavigatorHIDListener.h"

class ISpaceNavigatorHIDCapture
{
public:
	virtual ~ISpaceNavigatorHIDCapture() {}
	virtual void RegisterListener(ISpaceNavigatorHIDListener*) = 0;
	virtual void UnregisterListener(ISpaceNavigatorHIDListener*) = 0;
	virtual DWORD ScanForSpaceNavigator() = 0;
	virtual BOOL SpaceNavigatorPresent() = 0;
	virtual BOOL SetLED(const bool) = 0;
	virtual void StartCapturing() = 0;
	virtual void StopCapturing() = 0;
};

#endif