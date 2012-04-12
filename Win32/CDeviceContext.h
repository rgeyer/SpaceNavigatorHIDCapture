#ifndef __CDEVICECONTEXT_H__
#define __CDEVICECONTEXT_H__

#include "IAxis.h"
#include "IAction.h"
#include "IButton.h"
#include "IDeviceCapture.h"
#include "CGestureProcessor.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

typedef vector<IAxis*> TAxisList;

class CDeviceContext
{
public:
	CDeviceContext(bool gestures, wstring deviceName) : _gestures(gestures), _deviceName(deviceName) {}
	virtual ~CDeviceContext();

	// IDeviceListener Methods
	virtual void AxeChanged(short, short);
	virtual void ButtonsChanged(short);

	virtual void CopyStatus(CDeviceContext*);

	void AddAxe(IAxis* axe);
	void AddButton(IButton* button);

	bool IsGesturesContext() { return _gestures; }
	wstring GetDeviceName() { return _deviceName; }

	CGestureProcessor _gestureProcessor;

protected:	
	TAxisList _axes;
	TButtonByStateMap _buttons;
	bool _gestures;
	wstring _deviceName;
};

typedef map<wstring, CDeviceContext*> TDeviceContextByNameMap;
typedef map<IDeviceCapture*, CDeviceContext*> TDeviceContextByDeviceMap;

#endif