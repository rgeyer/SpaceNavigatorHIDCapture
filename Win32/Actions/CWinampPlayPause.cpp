#include "stdafx.h"
#include "wa_ipc.h"
#include "CWinampPlayPause.h"

/*virtual*/ void CWinampPlayPause::Execute()
{
	// Get the current play status
	HWND hwnd_winamp = FindWindow("Winamp v1.x", (LPCTSTR)NULL);
	int playVal = ::SendMessage(hwnd_winamp,WM_WA_IPC,0,IPC_ISPLAYING);

	// Take the correct action
	if(playVal)
	{
		::SendMessage(hwnd_winamp,WM_COMMAND,WINAMP_BUTTON3,0);
	}
	else
	{
		::SendMessage(hwnd_winamp,WM_COMMAND,WINAMP_BUTTON2,0);
	}
}