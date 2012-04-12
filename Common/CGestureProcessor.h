#ifndef __CGESTUREPROCESSOR_H__
#define __CGESTUREPROCESSOR_H__

#include <map>
#include <vector>
#include "IAction.h"
#include "CMotion.h"
#include "AGesture.h"

class CAxis; // Define ahead so we need not include the header

using namespace std;

typedef vector<AGesture*> TGestureList;
typedef map<TGestureList, IAction*> TActionByGesturesMap;

class CGestureProcessor
{
	friend CAxis;
public:
	CGestureProcessor() : _lastTimeMillis(GetTickCount()), _largestMacro(0) {}
	~CGestureProcessor();
	void addMacro(TGestureList gestureList, IAction* action);
	void newMotion(CMotion* motion);
	void clear();

private:
	void processGestures();

	TGestureList _gestures;
	TActionByGesturesMap _actionByGestures;
	int _largestMacro;
	DWORD _lastTimeMillis;
};

#endif