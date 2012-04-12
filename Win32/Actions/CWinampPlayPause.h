#ifndef __CWINAMPPLAYPAUSE_H__
#define __CWINAMPPLAYPAUSE_H__

#include "IAction.h"

class CWinampPlayPause :
	public IAction
{
	virtual void Execute();
};

#endif