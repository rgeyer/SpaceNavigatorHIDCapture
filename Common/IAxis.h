#ifndef __IAXIS_H__
#define __IAXIS_H__

class IAxis
{
public:
	virtual ~IAxis() {}
	virtual void Update(short currentValue) = 0;
};


#endif