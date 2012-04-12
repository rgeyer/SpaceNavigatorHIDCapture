#include "StdAfx.h"
#include "CExecuteAction.h"

CExecuteAction::CExecuteAction(string executable, string commandline) : _executable(executable),
_commandline(commandline)
{
}

/*virtual*/ void CExecuteAction::Execute()
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	CreateProcess(_executable.c_str(), (LPSTR)_commandline.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
