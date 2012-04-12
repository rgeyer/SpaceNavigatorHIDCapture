#ifndef __CMOUSEYAXIS_H__
#define __CMOUSEYAXIS_H__

#include "IAxis.h"

class CMouseYAxis :
	public IAxis
{
private:
	short _threshold;
	int _divisor;

public:
	CMouseYAxis(short threshold, int divisor) : _threshold(threshold), _divisor(divisor) {}
	virtual void Update(short currentValue);
};

#endif