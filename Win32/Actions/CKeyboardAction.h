#ifndef __CKEYBOARDACTION_H__
#define __CKEYBOARDACTION_H__

#include <list>
#include "IAction.h"

using namespace std;

typedef list<WORD> TKeyList;

class CKeyboardAction :
	public IAction
{
public:
	CKeyboardAction(TKeyList keys);

	virtual void Execute();

private:
	TKeyList _keys;
};

#endif
