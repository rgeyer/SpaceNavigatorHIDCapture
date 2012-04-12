#include "StdAfx.h"
#include "CRightMouseButtonAction.h"

CRightMouseButtonAction::CRightMouseButtonAction(void)
{
}

/*virtual*/ void CRightMouseButtonAction::Execute()
{
	ButtonDown();
	ButtonUp();
}

/*virtual*/ void CRightMouseButtonAction::ButtonDown()
{
	INPUT inputs[1];
	ZeroMemory(&inputs[0], sizeof(INPUT));
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, inputs, sizeof(inputs));
}

/*virtual*/ void CRightMouseButtonAction::ButtonUp()
{
	INPUT inputs[1];
	ZeroMemory(&inputs[0], sizeof(INPUT));
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, inputs, sizeof(inputs));
}