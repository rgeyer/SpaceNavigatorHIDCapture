#include "stdafx.h"
#include "AGesture.h"

/*virtual*/ bool AGesture::equals(AGesture* compVal)
{
	if(getValue() == compVal->getValue())
		return true;

	return false;
}