#ifndef __CEXECUTEATION_H__
#define __CEXECUTEATION_H__

#include "IAction.h"

#include <string>

using namespace std;

class CExecuteAction :
	public IAction
{
public:
	CExecuteAction(string executable, string commandline);

	virtual void Execute();

private:
	string _executable;
	string _commandline;
};

#endif