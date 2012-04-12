#ifndef __ADEVICECAPTURE_H__
#define __ADEVICECAPTURE_H__

#include "IDeviceCapture.h"
#include "IDeviceListener.h"

class ADeviceCapture : public IDeviceCapture
{
public:
	ADeviceCapture(string _type);
	virtual ~ADeviceCapture();

	virtual void RegisterListener(IDeviceListener*);
	virtual void UnregisterListener(IDeviceListener*);

	virtual string GetType() { return _type; }
protected:
	CRITICAL_SECTION _cs;
	TListenerList _listeners;
	string _type;
};

#endif