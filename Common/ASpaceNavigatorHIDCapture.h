#include "ISpaceNavigatorHIDCapture.h"
#include <list>

#ifndef __ASPACENAVIGATORHIDCAPTURE_H__
#define __ASPACENAVIGATORHIDCAPTURE_H__

typedef std::list<ISpaceNavigatorHIDListener*> TListenerList;

class ASpaceNavigatorHIDCapture : ISpaceNavigatorHIDCapture
{
public:
	ASpaceNavigatorHIDCapture();
	~ASpaceNavigatorHIDCapture();

	virtual void RegisterListener(ISpaceNavigatorHIDListener*);
	virtual void UnregisterListener(ISpaceNavigatorHIDListener*);
protected:
	CRITICAL_SECTION _cs;
	TListenerList _listeners;
};

#endif