#include "stdafx.h"
#include "CTimeFrame.h"
#include "CGestureProcessor.h"

CGestureProcessor::~CGestureProcessor()
{
	clear();
	for(TActionByGesturesMap::iterator i = _actionByGestures.begin(); i != _actionByGestures.end(); i++)
	{
		for(TGestureList::const_iterator gest = i->first.begin(); gest != i->first.end(); gest++)
		{
			delete *gest;
		}
	}
}

void CGestureProcessor::newMotion(CMotion* motion)
{
	TRACE("Entering CGestureProcessor::newMotion and _lastTimeMillis is %d\r\n", _lastTimeMillis);
	// calculate the delay between the last gesture and now
	CTimeFrame* delay = new CTimeFrame(GetTickCount() - _lastTimeMillis);
	// add the delay between this action and the last to the gestures list
	//only if this isn't the first motion in the list
	if(_gestures.size() >= 1)
	{
		_gestures.push_back(delay);
		TRACE("Added Gesture Delay of %d\r\n", delay->getDelay());
	}

	// add the motion to the gestures list
	_gestures.push_back(motion);
	TRACE("Added Gesture Motion %d\r\n", motion->getValue());
	
	// mark the current time for the next motion
	_lastTimeMillis = GetTickCount();
	
	// process the gestures we have so far to see if we have a match
	processGestures();
}

void CGestureProcessor::addMacro(TGestureList gestureList, IAction* action)
{
	// keep track of the largest macros
	if (gestureList.size() > _largestMacro) {
		_largestMacro = gestureList.size();
	}

	// and add the macro
	_actionByGestures[gestureList] = action;
}

void CGestureProcessor::clear()
{
	for(TGestureList::iterator i = _gestures.begin(); i != _gestures.end(); i++)
	{
		delete *i;
	}
	_gestures.clear();
	TRACE("Cleared Gestures\r\n");
}

void CGestureProcessor::processGestures()
{
	// check if the gesture list is greater than the largest macro, and
	// remove any excess gestures from the end if it is
	if (_gestures.size() > _largestMacro)
		_gestures.resize(_largestMacro);

	// check if the new addition to the gestures completes a macro
	//for (int eachMacroIndex = 0; eachMacroIndex < macros.size(); eachMacroIndex++)
	for(TActionByGesturesMap::iterator macro = _actionByGestures.begin(); macro != _actionByGestures.end(); macro++)
	{
		TGestureList::size_type sizeOfMacroList = macro->first.size();
		//List<Gesture> macro = macros.get(eachMacroIndex);

		// ignore this macro if it is larger than collected gesture list
		if (_gestures.size() < sizeOfMacroList) {
			continue;
		}

		// cycle through the macro's gestures backwards, comparing each
		// gesture with those in the current gesture que
		//for (int eachGestureInMacroIndex = macro.size() - 1; eachGestureInMacroIndex >= 0; eachGestureInMacroIndex--)
		int eachGestureInMacroIdx = sizeOfMacroList - 1;
		for(TGestureList::const_reverse_iterator macroGesture = macro->first.rbegin(); macroGesture != macro->first.rend(); macroGesture++, eachGestureInMacroIdx--)
		{
			//Gesture macroGesture = macro.get(eachGestureInMacroIndex);
			int offset = _gestures.size() - sizeOfMacroList;
			AGesture* macroGesturePointer = *macroGesture;
			AGesture* currentGesture = _gestures.at(eachGestureInMacroIdx + offset);

			// check the equality of these gestures and abort if no match
			if (!macroGesturePointer->equals(currentGesture)) {
				break;
			}

			// if this far and this is the last cycle, we have a match
			if (macroGesture == --macro->first.rend()) {

				// notify exchange listeners
				macro->second->Execute();

				// flush the gestures list
				clear();
			}
		}
	}
}