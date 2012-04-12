#ifndef __IDEVICECAPTURE_H__
#define __IDEVICECAPTURE_H__

#include <map>
#include <string>

using namespace std;

class IDeviceListener; //Forward declare this so as not to include the header

class IDeviceCapture
{
public:
	virtual ~IDeviceCapture() {}
	virtual void RegisterListener(IDeviceListener*) = 0;
	virtual void UnregisterListener(IDeviceListener*) = 0;
	virtual DWORD ScanForDevice() = 0;
	virtual BOOL DevicePresent() = 0;
	virtual void StartCapturing() = 0;
	virtual void StopCapturing() = 0;
	virtual string GetType() = 0;
};

typedef map<wstring, IDeviceCapture*> TDeviceByNameMap;

#endif