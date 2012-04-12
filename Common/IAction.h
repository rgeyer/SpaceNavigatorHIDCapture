#ifndef __IACTION_H__
#define __IACTION_H__

#include <map>
#include <string>

using namespace std;

class IAction
{
public:
	virtual ~IAction() {}
	virtual void Execute() = 0;
};

typedef map<wstring, IAction*> TActionByNameMap;

#endif