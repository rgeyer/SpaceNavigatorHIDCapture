#ifndef __CAXIS_H__
#define __CAXIS_H__

#include "IAxis.h"
#include "IAction.h"
#include "CGestureProcessor.h"

class CAxis : IAxis
{
// Common methods and variables
public:
	~CAxis(void);
	virtual void Update(short currentValue);

private:
	unsigned short _threshold;
	short _lastValue;

	IAction* _positiveAction;
	IAction* _negativeAction;


// Methods and variables for Gestures
public:
	CAxis(unsigned short threshold, unsigned short posMotion, unsigned short negMotion, CGestureProcessor* processor, unsigned short centerMotion = 0);

private:
	bool _gestures;
	CGestureProcessor* _processor;
	unsigned short _posMotion;
	unsigned short _negMotion;
	unsigned short _centerMotion;

// Methods and variables for binary
public:	
	CAxis(unsigned short threshold, IAction* posAction, IAction* negAction);	

private:	
	bool _triggerBinary;

// Methods and variables for pulse
public:
	CAxis(unsigned short threshold, int minPulse, int maxPulse, bool linearAccel, IAction* posAction, IAction* negAction);

private:
	bool _pulse;		
	DWORD _lastPulseExecute;
	DWORD _lastGestureSent;
	int _minimumPulseRate;
	int _maximumPulseRate;
	bool _linearPulseAccel;
};

#endif