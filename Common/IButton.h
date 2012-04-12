#ifndef __IBUTTON_H__
#define __IBUTTON_H__

#include <vector>

using namespace std;

class IButton
{
public:
	virtual ~IButton() {}
	virtual void ButtonDown() = 0;
	virtual void ButtonUp() = 0;
};

typedef vector<pair<bool, IButton*>> TButtonByStateMap;

#endif