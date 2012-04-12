#ifndef __CMOUSEXAXIS_H__
#define __CMOUSEXAXIS_H__

#include "IAxis.h"

class CMouseXAxis :
	public IAxis
{
private:
	short _threshold;
	int _divisor;

public:	
	CMouseXAxis(short threshold, int divisor) : _threshold(threshold), _divisor(divisor) {}

	virtual void Update(short currentValue);
};

#endif