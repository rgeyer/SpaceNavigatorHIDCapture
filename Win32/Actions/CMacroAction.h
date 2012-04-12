#ifndef __CMACROACTION_H__
#define __CMACROACTION_H__

#include "IAction.h"

#include <string>
#include <vector>

using namespace std;

class CMacroAction :
	public IAction
{
public:
	CMacroAction(bool all);
	void AddAction(IAction* action);
	virtual void Execute();

private:
	bool _all;
	vector<IAction*>::iterator _lastAction;
	vector<IAction*> _actions;
};

#endif