#ifndef __IDEVICELISTENER_H__
#define __IDEVICELISTENER_H__

#include <map>
#include <list>
#include <string>

using namespace std;

class IDeviceCapture; //Forward declare this so as not to include the header

class IDeviceListener
{
public:
	virtual ~IDeviceListener() {}
	virtual void AxeChanged(IDeviceCapture*, short, short) = 0;
	virtual void ButtonsChanged(IDeviceCapture*, short) = 0;
};

typedef list<IDeviceListener*> TListenerList;
typedef map<wstring, IDeviceListener*> TContextByNameMap;

#endif