#include "StdAfx.h"
#include "CSystemTray.h"

CSystemTray::CSystemTray(HWND hWnd, UINT uCallbackMessage, string szTip, HICON icon) : _shown(false)
{
	_enabled = ( GetVersion() & 0xff ) >= 4 ;
	if (!_enabled)
		return ;

	// load up the NOTIFYICONDATA structure
	_tnd.cbSize = sizeof(NOTIFYICONDATA) ;
	_tnd.hWnd = hWnd ;
	_tnd.uID = 0 ;
	_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP ;	
	_tnd.uCallbackMessage = uCallbackMessage;  
	strcpy ( _tnd.szTip, szTip.c_str());
 
	// save the pointer to the icon list and set the initial
	// default icon.
	_tnd.hIcon = icon;
}

void CSystemTray::Notify()
{
	if(_enabled)
	{
		if(_shown)
			Shell_NotifyIcon(NIM_MODIFY, &_tnd);
		else
		{
			Shell_NotifyIcon(NIM_ADD, &_tnd);
			_shown = true;
		}
	}
}

void CSystemTray::Notify(HICON icon)
{
	//_tnd.uFlags = NIF_ICON;
	_tnd.hIcon = icon;
	Notify();
}

void CSystemTray::UnNotify()
{
	if(_enabled)
	{
		Shell_NotifyIcon(NIM_DELETE, &_tnd);
		_shown = false;
	}
}

HICON CSystemTray::GetIcon()
{
	return _tnd.hIcon;
}