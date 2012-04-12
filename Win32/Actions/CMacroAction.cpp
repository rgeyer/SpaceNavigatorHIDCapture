#include "StdAfx.h"
#include "CMacroAction.h"

CMacroAction::CMacroAction(bool all) : _all(all)
{
}

void CMacroAction::AddAction(IAction* action)
{
	_actions.push_back(action);
	_lastAction = _actions.begin();
}

/*virtual*/ void CMacroAction::Execute()
{	
	if(_all)
	{
		for(vector<IAction*>::iterator i = _actions.begin(); i != _actions.end(); i++)
		{
			IAction* executeMe = *i;
			executeMe->Execute();
		}
	}
	else
	{
		_lastAction++;
		if(_lastAction == _actions.end())
			_lastAction = _actions.begin();
		IAction* executeMe = *_lastAction;
		executeMe->Execute();
	}
}
