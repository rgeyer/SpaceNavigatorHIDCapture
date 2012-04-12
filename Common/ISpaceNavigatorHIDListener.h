#ifndef __ISPACENAVIGATORHIDLISTENER_H__
#define __ISPACENAVIGATORHIDLISTENER_H__

class ISpaceNavigatorHIDListener
{
public:
	virtual ~ISpaceNavigatorHIDListener() {}
	virtual void ChannelOneChanged(short, short, short) = 0;
	virtual void ChannelTwoChanged(short, short, short) = 0;
	virtual void ButtonsChanged(short) = 0;
};

#endif