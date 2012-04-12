#ifndef __CWINAMPMUTE_H__
#define __CWINAMPMUTE_H__

#include "IAction.h"

class CWinampMute :
	public IAction
{
public:
	CWinampMute() : _lastVol(-1) {}
	virtual void Execute();

private:
	int _lastVol;
};

#endif