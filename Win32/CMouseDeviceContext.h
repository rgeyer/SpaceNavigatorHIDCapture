#ifndef __CMOUSEDEVICECONTEXT_H__
#define __CMOUSEDEVICECONTEXT_H__

#include "CDeviceContext.h"

class CMouseDeviceContext :
	public CDeviceContext
{
public:
	CMouseDeviceContext(bool gestures, wstring deviceName) : CDeviceContext(gestures, deviceName), _okToSend(false) {}

	// IDeviceListener Methods
	virtual void AxeChanged(short, short);
	virtual void ButtonsChanged(short);

	virtual void CopyStatus(CDeviceContext*);

private:
	bool _okToSend;
	POINT _basePosition;
};

#endif