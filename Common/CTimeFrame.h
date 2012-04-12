#ifndef __CTIMEFRAME_H__
#define __CTIMEFRAME_H__

#include "AGesture.h"

class CTimeFrame : public AGesture
{
public:
	CTimeFrame(long delay) : _delay(delay) {}
	CTimeFrame() {}
	long getDelay();

// Static variance accessors
	static void setVariance(long variance);
	static long getVariance();

// AGesture methods
public:
	virtual long getValue();
	virtual bool equals(AGesture*);

private:
	long _delay;

// Static variance
	static long _variance;

};

static CTimeFrame TIMEFRAMEIGNORE(-1);

#endif