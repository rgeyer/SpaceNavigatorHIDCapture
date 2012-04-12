#include "stdafx.h"
#include "CTimeFrame.h"

long CTimeFrame::_variance = 100;

long CTimeFrame::getVariance()
{
	return _variance;
}

void CTimeFrame::setVariance(long variance)
{
	_variance = variance;
}

long CTimeFrame::getDelay()
{
	return _delay;
}

long CTimeFrame::getValue()
{
	return _delay;
}

bool CTimeFrame::equals(AGesture* compVal)
{
	// Check first if this is a CTimeFrame
	CTimeFrame* compValPtr = dynamic_cast<CTimeFrame*>(compVal);
	if(compValPtr == NULL)
		return false;

	// always true if this is an ignored timeframe
	if(AGesture::equals(&TIMEFRAMEIGNORE))
		return true;

	// check for equality of the delays, give or take the variance
	if(_delay > compValPtr->_delay - _variance &&
		_delay < compValPtr->_delay + _variance)
		return true;

	return false;
}