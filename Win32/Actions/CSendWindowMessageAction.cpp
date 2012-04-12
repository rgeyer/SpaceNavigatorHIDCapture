#include "StdAfx.h"
#include "CSendWindowMessageAction.h"

CSendWindowMessageAction::CSendWindowMessageAction(std::string message, std::string windowName, bool findByClass /*= FALSE*/) : _strMessage(message),
_windowName(windowName),
_messageType(WM_COPYDATA),
_findByClass(findByClass)
{

}

CSendWindowMessageAction::CSendWindowMessageAction(UINT message, std::string windowName, bool findByClass /*= FALSE*/) : _uintMessage(message),
_windowName(windowName),
_messageType(WM_COMMAND),
_findByClass(findByClass)
{

}

/*virtual*/ void CSendWindowMessageAction::Execute()
{	
	HWND hwnd = _findByClass ? FindWindow(_windowName.c_str(), (LPCTSTR)NULL) : FindWindow((LPCTSTR)NULL, _windowName.c_str());
	switch (_messageType)
	{
	case WM_COPYDATA:
		{
			COPYDATASTRUCT cs;
			ZeroMemory(&cs, sizeof(COPYDATASTRUCT));
			cs.dwData = 1;
			cs.cbData = sizeof(char) * _strMessage.length();
			cs.lpData = (void*)_strMessage.c_str();

			if(hwnd != NULL)
				SendMessage(hwnd, _messageType, NULL, (LPARAM)&cs);
			break;
		}
	case WM_COMMAND:
		{
			if(hwnd != NULL)
				SendMessage(hwnd, _messageType, _uintMessage, 0);
			break;
		}
	}
}
