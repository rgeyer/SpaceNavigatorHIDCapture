#include "StdAfx.h"
#include "CLeftMouseButtonAction.h"

CLeftMouseButtonAction::CLeftMouseButtonAction()
{

}

/*virtual*/ void CLeftMouseButtonAction::Execute()
{
	ButtonDown();
	ButtonUp();
}

/*virtual*/ void CLeftMouseButtonAction::ButtonDown()
{
	INPUT inputs[1];
	ZeroMemory(&inputs[0], sizeof(INPUT));
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, inputs, sizeof(inputs));
}

/*virtual*/ void CLeftMouseButtonAction::ButtonUp()
{
	INPUT inputs[1];
	ZeroMemory(&inputs[0], sizeof(INPUT));
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, inputs, sizeof(inputs));
}