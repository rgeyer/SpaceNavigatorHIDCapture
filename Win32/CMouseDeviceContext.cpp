#include "StdAfx.h"
#include "CMouseDeviceContext.h"

/*virtual*/ void CMouseDeviceContext::ButtonsChanged(short buttons)
{	
	if(buttons != 0)
	{
		_okToSend = true;
		_gestureProcessor.clear();
		// TODO: The commented out code will center the mouse whenever a button
		// is pushed.  Need to determine the usefulness of this, and a way to "bail out"
		// so that normal mouse function can be regained.
		/*
		UINT mx = ::GetSystemMetrics(SM_CXSCREEN);
		UINT my = ::GetSystemMetrics(SM_CYSCREEN);
		mx--;
		my--;
		::SetCursorPos(mx/2, my/2);*/
		::GetCursorPos(&_basePosition);
	}
	else
		_okToSend = false;

	TRACE("Mouse Device Context 0x%X okToSend is %d\r\n", this, _okToSend);
	TRACE("Mouse Device Context 0x%X basePosition is %d x %d\r\n", this, _basePosition.x, _basePosition.y);

	CDeviceContext::ButtonsChanged(buttons);
}

/*virtual*/ void CMouseDeviceContext::AxeChanged(short axeNum, short axeVal)
{
	if(_okToSend && axeNum < _axes.size())
	{
		switch(axeNum)
		{
		case 0: _axes[axeNum]->Update(axeVal - _basePosition.x); break;
		case 1: _axes[axeNum]->Update(axeVal - _basePosition.y); break;
		default: break;
		}
	}
}

/*virtual*/ void CMouseDeviceContext::CopyStatus(CDeviceContext* oldContext)
{
	CMouseDeviceContext* oldMouseContext = dynamic_cast<CMouseDeviceContext*>(oldContext);
	if(oldMouseContext != NULL)
	{
		_okToSend = oldMouseContext->_okToSend;
		_basePosition = oldMouseContext->_basePosition;
	}

	TRACE("Mouse Device Context 0x%X okToSend is %d\r\n", this, _okToSend);
	TRACE("Mouse Device Context 0x%X basePosition is %d x %d\r\n", this, _basePosition.x, _basePosition.y);

	CDeviceContext::CopyStatus(oldContext);
}