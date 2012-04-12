#include "stdafx.h"
#include "wa_ipc.h"
#include "CWinampMute.h"

/*virtual*/ void CWinampMute::Execute()
{
	// Get the current volume
	HWND hwnd_winamp = FindWindow("Winamp v1.x", (LPCTSTR)NULL);
	int curVol = ::SendMessage(hwnd_winamp,WM_WA_IPC,-666,IPC_SETVOLUME);

	// Take the correct action
	if(curVol)
	{
		_lastVol = curVol;
		::SendMessage(hwnd_winamp,WM_WA_IPC,0,IPC_SETVOLUME);
	}
	else
	{
		::SendMessage(hwnd_winamp,WM_WA_IPC,_lastVol,IPC_SETVOLUME);
	}
}