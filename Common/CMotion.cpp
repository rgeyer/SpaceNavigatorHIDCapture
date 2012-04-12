#include "stdafx.h"
#include "CMotion.h"

CMotion::CMotion(unsigned char position, unsigned char axis) : _positionAndAxis(0)
{
	_positionAndAxis = MakePositionAndAxis(position, axis);
	TRACE("Position is %d and axis is %d resulting in %d\r\n", position, axis, _positionAndAxis);
}

unsigned char CMotion::getPosition()
{
	return _positionAndAxis;
}

unsigned char CMotion::getAxis()
{
	return _positionAndAxis >> 8;
}

long CMotion::getValue()
{
	return _positionAndAxis;
}

unsigned short CMotion::MakePositionAndAxis(unsigned char position, unsigned char axis)
{
	unsigned short retVal = 0;
	retVal = position;
	retVal += axis << 8;
	return retVal;
}