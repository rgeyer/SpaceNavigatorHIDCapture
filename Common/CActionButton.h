#ifndef __CACTIONBUTTON_H__
#define __CACTIONBUTTON_H__

#include "IAction.h"
#include "IButton.h"

class CActionButton :
	public IButton
{
public:
	CActionButton(IAction* downAction, IAction* upAction) : _downAction(downAction), _upAction(upAction) {}

	virtual void ButtonDown() { if(_downAction != NULL) _downAction->Execute(); }
	virtual void ButtonUp() { if(_upAction != NULL) _upAction->Execute(); }

private:
	IAction* _downAction;
	IAction* _upAction;
};

#endif