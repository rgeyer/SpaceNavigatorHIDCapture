#ifndef __ADEVICELISTENER_H__
#define __ADEVICELISTENER_H__

#include "IAction.h"
#include "CDeviceContext.h"
#include "IDeviceListener.h"

class ADeviceListener : public IDeviceListener
{	
public:
	ADeviceListener() : _globalContext(NULL) {}
	virtual ~ADeviceListener();
	// IDeviceListener Methods
	virtual void AxeChanged(IDeviceCapture*, short, short);
	virtual void ButtonsChanged(IDeviceCapture*, short);

	// Getters and Setters
	void AddAction(wstring, IAction*);
	void AddDevice(wstring, IDeviceCapture*);
	void AddContext(wstring, IDeviceListener*);
	void AddDeviceContext(wstring, CDeviceContext*);

	TActionByNameMap GetActions() { return _actionsByName; }
	TDeviceByNameMap GetDevices() { return _devicesByName; }
	TContextByNameMap GetContexts() { return _contextsByName; }
	TDeviceContextByNameMap GetDeviceContexts() { return _deviceContextsByName; }

	// Misc
	void IncrementContext();
	void DecrementContext();
	void SetContext(wstring);
	void StartCapturing();
	void StopCapturing();

protected:
	TActionByNameMap _actionsByName;
	TDeviceByNameMap _devicesByName;
	TContextByNameMap _contextsByName;
	TDeviceContextByNameMap _deviceContextsByName;

	IDeviceListener* _globalContext;
	
	wstring _currentContextKey;
};

#endif