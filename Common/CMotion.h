#ifndef __CMOTION_H__
#define __CMOTION_H__

#include "AGesture.h"

enum EGesturePosition
{
	NEGATIVE = 1,
	CENTER = 2,
	POSITIVE = 4
};

class CMotion : public AGesture
{
private:
	unsigned short _positionAndAxis;

public:
	CMotion(unsigned short positionAndAxis) : _positionAndAxis(positionAndAxis) {};
	CMotion(unsigned char position, unsigned char axis);
	CMotion() {};

	unsigned char getPosition();
	unsigned char getAxis();
	virtual long getValue();

public:
	static unsigned short MakePositionAndAxis(unsigned char position, unsigned char axis);
};

#endif