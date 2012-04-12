#ifndef __CSENDWINDOWMESSAGEACTION_H__
#define __CSENDWINDOWMESSAGEACTION_H__

#include "IAction.h"

#include <string>

using namespace std;

class CSendWindowMessageAction :
	public IAction
{
public:
	CSendWindowMessageAction(string message, string windowName, bool findByClass = FALSE);
	CSendWindowMessageAction(UINT message, string windowName, bool findByClass = FALSE);
	virtual void Execute();

private:
	bool _findByClass;
	string _strMessage;
	UINT _uintMessage;
	string _windowName;
	UINT _messageType;
};

#endif