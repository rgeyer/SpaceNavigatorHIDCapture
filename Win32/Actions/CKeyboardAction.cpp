#include "StdAfx.h"
#include "CKeyboardAction.h"

CKeyboardAction::CKeyboardAction(TKeyList keys) : _keys(keys)
{
}

/*virtual*/ void CKeyboardAction::Execute()
{
	INPUT* inputs = new INPUT[_keys.size()];
	for(int i=0; i < _keys.size(); i++)
	{
		ZeroMemory(&inputs[i], sizeof(INPUT));
	}
	int index = 0;
	for(TKeyList::iterator i = _keys.begin(); i != _keys.end(); i++)
	{
		inputs[index].type = INPUT_KEYBOARD;
		inputs[index].ki.wVk = *i;
		index++;
	}
	if(!SendInput(_keys.size(), inputs, sizeof(INPUT)))
	{
		TRACE("SendInput Last Error %i\r\n", GetLastError());
	}
	index = 0;
	for(TKeyList::iterator i = _keys.begin(); i != _keys.end(); i++)
	{
		inputs[index].ki.dwFlags = KEYEVENTF_KEYUP;
		index++;
	}
	if(!SendInput(_keys.size(), inputs, sizeof(INPUT)))
	{
		TRACE("SendInput Last Error %i\r\n", GetLastError());
	}
	delete [] inputs;
}