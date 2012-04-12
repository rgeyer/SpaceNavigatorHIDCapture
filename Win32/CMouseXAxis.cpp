#include "StdAfx.h"
#include "CMouseXAxis.h"

/*virtual*/ void CMouseXAxis::Update(short currentValue)
{
	if(currentValue > _threshold || currentValue < (_threshold * -1))
	{
		INPUT inputs[1];
		ZeroMemory(&inputs[0], sizeof(INPUT));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dx -= currentValue/_divisor;
		inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, inputs, sizeof(inputs));
	}
}
