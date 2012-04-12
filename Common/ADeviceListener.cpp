#include "stdafx.h"
#include "ADeviceListener.h"
#include "CContext.h"

ADeviceListener::~ADeviceListener()
{
	for(TDeviceByNameMap::iterator i = _devicesByName.begin(); i != _devicesByName.end(); i++)
	{
		i->second->StopCapturing();
		i->second->UnregisterListener(this);
	}
	for(TContextByNameMap::iterator i = _contextsByName.begin(); i != _contextsByName.end(); i++)
	{
		delete i->second;
	}
	for(TDeviceContextByNameMap::iterator i = _deviceContextsByName.begin(); i != _deviceContextsByName.end(); i++)
	{
		delete i->second;
	}
	for(TDeviceByNameMap::iterator i = _devicesByName.begin(); i != _devicesByName.end(); i++)
	{
		delete i->second;
	}
	for(TActionByNameMap::iterator i = _actionsByName.begin(); i != _actionsByName.end(); i++)
	{
		delete i->second;
	}
}

/*virtual*/ void ADeviceListener::AxeChanged(IDeviceCapture* device, short axeNum, short axeVal)
{
	if(_globalContext)
		_globalContext->AxeChanged(device, axeNum, axeVal);

	if(_contextsByName.find(_currentContextKey) != _contextsByName.end())
		_contextsByName[_currentContextKey]->AxeChanged(device, axeNum, axeVal);
}

/*virtual*/ void ADeviceListener::ButtonsChanged(IDeviceCapture* device, short buttons)
{
	if(_globalContext)
		_globalContext->ButtonsChanged(device, buttons);

	if(_contextsByName.find(_currentContextKey) != _contextsByName.end())
		_contextsByName[_currentContextKey]->ButtonsChanged(device, buttons);
}

void ADeviceListener::AddAction(wstring name, IAction* action)
{
	_actionsByName[name] = action;
}

void ADeviceListener::AddDevice(wstring name, IDeviceCapture* deviceCapture)
{
	_devicesByName[name] = deviceCapture;
	deviceCapture->RegisterListener(this);
	deviceCapture->ScanForDevice();
}

void ADeviceListener::AddContext(wstring name, IDeviceListener* context)
{
	if(name.compare(L"Global") == 0)
		_globalContext = context;
	_contextsByName[name] = context;
}

void ADeviceListener::AddDeviceContext(wstring name, CDeviceContext* deviceContext)
{
	_deviceContextsByName[name] = deviceContext;
}

void ADeviceListener::IncrementContext()
{
	TContextByNameMap::iterator tempIter = _contextsByName.find(_currentContextKey);

	tempIter++;
	if(tempIter == _contextsByName.end())
		tempIter == _contextsByName.begin();

	_currentContextKey = tempIter->first;
}

void ADeviceListener::DecrementContext()
{
	TContextByNameMap::iterator beginIter = _contextsByName.begin();
	TContextByNameMap::iterator tempIter = _contextsByName.find(_currentContextKey);

	tempIter--;
	if(tempIter == _contextsByName.end())
	{
		tempIter = _contextsByName.end();
		tempIter--;
	}

	_currentContextKey = tempIter->first;
}

void ADeviceListener::SetContext(wstring name)
{
	if(_contextsByName.find(name) != _contextsByName.end())
	{
		// Do the context switch
		TRACE("Switching to context %S\r\n", name.c_str());
		TContextByNameMap::iterator tempIter = _contextsByName.find(name);		

		// If the new and old context are both contexts (They sure better be!) do a CopyStatus
		// This will allow contexts of similar types to copy their device context status' so they're
		// the same.
		CContext* oldContext = dynamic_cast<CContext*>(_contextsByName[_currentContextKey]);				
		CContext* newContext = dynamic_cast<CContext*>(_contextsByName[name]);		
		if(oldContext != NULL && newContext != NULL)
			newContext->CopyStatus(oldContext);

		// Can't actually make the context switch until after we've gotten old and new
		_currentContextKey = tempIter->first;
	}
}

void ADeviceListener::StartCapturing()
{
	for(TDeviceByNameMap::iterator i = _devicesByName.begin(); i != _devicesByName.end(); i++)
	{
		if(i->second->DevicePresent())
			i->second->StartCapturing();
	}
}

void ADeviceListener::StopCapturing()
{
	for(TDeviceByNameMap::iterator i = _devicesByName.begin(); i != _devicesByName.end(); i++)
	{
		if(i->second->DevicePresent())
			i->second->StopCapturing();
	}
}