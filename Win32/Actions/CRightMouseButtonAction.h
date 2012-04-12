#ifndef __CRIGHTMOUSEBUTTONACTION_H__
#define __CRIGHTMOUSEBUTTONACTION_H__

#include "IButton.h"
#include "IAction.h"

class CRightMouseButtonAction :
	public IButton,
	public IAction
{
public:
	CRightMouseButtonAction(void);	

	// IAction methods
	virtual void Execute();

	// IButton methods
	virtual void ButtonDown();
	virtual void ButtonUp();
};

#endif