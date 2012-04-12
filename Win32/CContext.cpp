#include "StdAfx.h"
#include "CContext.h"

/*virtual*/ void CContext::ButtonsChanged(IDeviceCapture* device, short buttons)
{
	if(_deviceContexts.find(device) != _deviceContexts.end())
		_deviceContexts[device]->ButtonsChanged(buttons);
}

/*virtual*/ void CContext::AxeChanged(IDeviceCapture* device, short axeNum, short axeVal)
{
	if(_deviceContexts.find(device) != _deviceContexts.end())
		_deviceContexts[device]->AxeChanged(axeNum, axeVal);
}

/*virtual*/ void CContext::CopyStatus(CContext* oldContext)
{
	for(TDeviceContextByDeviceMap::iterator i = _deviceContexts.begin(); i != _deviceContexts.end(); i++)
	{
		if(oldContext->_deviceContexts.find(i->first) != oldContext->_deviceContexts.end())
			i->second->CopyStatus(oldContext->_deviceContexts[i->first]);
	}
}

void CContext::AddDeviceContext(IDeviceCapture* device, CDeviceContext* deviceContext)
{
	_deviceContexts[device] = deviceContext;
}