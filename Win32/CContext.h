#ifndef __CCONTEXT_H__
#define __CCONTEXT_H__

#include "IDeviceListener.h"
#include "CDeviceContext.h"

using namespace std;

class CContext :
	public IDeviceListener
{
public:
	// IDeviceListener Methods
	virtual void AxeChanged(IDeviceCapture*, short, short);
	virtual void ButtonsChanged(IDeviceCapture*, short);
	virtual void CopyStatus(CContext*);

	void AddDeviceContext(IDeviceCapture* device, CDeviceContext* deviceContext);

private:
	TDeviceContextByDeviceMap _deviceContexts;
};

#endif