#include "StdAfx.h"
#include "CDeviceContext.h"

#include <math.h>

#include "CAxis.h"

#include "CActionButton.h"
#include "CMouseYAxis.h"
#include "CMouseXAxis.h"
#include "CLeftMouseButtonAction.h"
#include "CRightMouseButtonAction.h"

#include "CMotion.h"
#include "CTimeFrame.h"

CDeviceContext::~CDeviceContext(void)
{
	for(TAxisList::iterator axis = _axes.begin(); axis != _axes.end(); axis++)
	{
		delete *axis;
	}

	for(TButtonByStateMap::iterator iter = _buttons.begin(); iter != _buttons.end(); iter++)
	{
		delete iter->second;
	}
}

/*virtual*/ void CDeviceContext::ButtonsChanged(short buttons)
{	
	int i=0;
	for(TButtonByStateMap::iterator iter = _buttons.begin(); iter != _buttons.end(); i++, iter++)
	{
		int buttonBitVal = pow((double)2, (double)i);		
		bool currentState = false;
		if((buttons & buttonBitVal) == buttonBitVal)
			currentState = true;

		bool previousState = iter->first;
		IButton* btn = iter->second;
		if(currentState != iter->first && iter->second != NULL)
		{
			currentState ? iter->second->ButtonDown() : iter->second->ButtonUp();
			iter->first = currentState;
		}
	}
}

/*virtual*/ void CDeviceContext::AxeChanged(short axeNum, short axeVal)
{
	if(axeNum < _axes.size())
		_axes[axeNum]->Update(axeVal);
}

/*virtual*/ void CDeviceContext::CopyStatus(CDeviceContext* oldContext)
{
	int idx = 0;
	for(TButtonByStateMap::iterator i = oldContext->_buttons.begin(); i != oldContext->_buttons.end(); idx++, i++)
	{
		// This used to copy the "second" parameter, which was actually the pointer to the action.
		// Switched it to the "first" parameter, since I think the intended logic was get in-sync the
		// current status of the button, not to copy the action.
		if(_buttons.size() >= idx)
			_buttons[idx].first = i->first;
	}
}

void CDeviceContext::AddAxe(IAxis* axe)
{
	_axes.push_back(axe);
}

void CDeviceContext::AddButton(IButton* button)
{
	_buttons.push_back(make_pair(false, button));
}