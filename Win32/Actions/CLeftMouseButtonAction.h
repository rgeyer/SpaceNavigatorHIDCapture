#ifndef __CLEFTMOUSEBUTTONACTION_H__
#define __CLEFTMOUSEBUTTONACTION_H__

#include "IButton.h"
#include "IAction.h"

class CLeftMouseButtonAction :
	public IButton,
	public IAction
{
public:
	CLeftMouseButtonAction(void);

	// IAction methods
	virtual void Execute();

	// IButton methods
	virtual void ButtonDown();
	virtual void ButtonUp();
};

#endif