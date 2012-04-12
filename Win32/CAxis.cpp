#include "StdAfx.h"
#include "CAxis.h"

CAxis::CAxis(unsigned short threshold, unsigned short posMotion, unsigned short negMotion, CGestureProcessor* processor, unsigned short centerMotion /* = 0*/) :
_pulse(false),
_threshold(threshold),
_positiveAction(NULL),
_negativeAction(NULL),
_lastValue(0),
_triggerBinary(true),
_gestures(true),
_processor(processor),
_posMotion(posMotion),
_negMotion(negMotion),
_centerMotion(centerMotion),
_lastGestureSent(::GetTickCount())
{

}

CAxis::CAxis(unsigned short threshold, IAction* posAction, IAction* negAction) :
_pulse(false),
_threshold(threshold),
_positiveAction(posAction),
_negativeAction(negAction),
_lastValue(0),
_lastPulseExecute(::GetTickCount()),
_triggerBinary(true),
_gestures(false),
_processor(NULL)
{
}

CAxis::CAxis(unsigned short threshold, int minPulse, int maxPulse, bool linearAccel, IAction* posAction, IAction* negAction) :
_pulse(true),
_threshold(threshold),
_minimumPulseRate(minPulse),
_maximumPulseRate(maxPulse),
_linearPulseAccel(linearAccel),
_positiveAction(posAction),
_negativeAction(negAction),
_lastValue(0),
_lastPulseExecute(::GetTickCount()),
_triggerBinary(true),
_gestures(false),
_processor(NULL)
{
}

CAxis::~CAxis(void)
{
}

void CAxis::Update(short currentValue)
{
	// This whole thing goes in a do/while, so it happens once, but we can bail out of the block
	// and perform our cleanup code at the end.
	do
	{
		// Reset the binary flag if we've gotten back inside the threshold bounds.
		if(_lastValue < _threshold && _lastValue > (_threshold * -1))
		{
			if(!_triggerBinary && _centerMotion && _gestures && _processor->_gestures.size() != 0)
			{
				_processor->newMotion(new CMotion(_centerMotion));
			}
			_triggerBinary = true;
		}

		IAction* actionToPerform = NULL;
		// Determine if we're beyond the threshold, and if so, which action to take
		if(currentValue > _threshold )
		{
			if(_gestures && !_triggerBinary)
			{
				if(::GetTickCount() - _lastGestureSent > 1000)
				{					
					_processor->newMotion(new CMotion(_posMotion));
					_lastGestureSent = ::GetTickCount();
					_triggerBinary = false;
					continue;
				}
			}
			if(_gestures && _triggerBinary)
			{
				_processor->newMotion(new CMotion(_posMotion));
				_lastGestureSent = ::GetTickCount();
				_triggerBinary = false;
				continue;
			}
			else
				actionToPerform = _positiveAction;
		}
		else if (currentValue < (_threshold *-1))
		{
			if(_gestures && !_triggerBinary)
			{
				if(::GetTickCount() - _lastGestureSent > 1000)
				{					
					_processor->newMotion(new CMotion(_negMotion));
					_lastGestureSent = ::GetTickCount();
					_triggerBinary = false;
					continue;
				}
			}
			if(_gestures && _triggerBinary)
			{
				_processor->newMotion(new CMotion(_negMotion));				
				_lastGestureSent = ::GetTickCount();
				_triggerBinary = false;
				continue;
			}
			else
				actionToPerform = _negativeAction;
		}

		// Should bail out of the do/while
		if(actionToPerform == NULL)
			continue;

		if(_pulse)
		{
			// Determine the frequency
			int currentMotionRange = 512 - _threshold;
			double multiplier = currentValue * (1.0 / currentMotionRange);
			// Normalize the multiplier to a positive value
			multiplier = multiplier < 0 ? multiplier * -1.0 : multiplier;
			int currentFrequencyRange = _maximumPulseRate - _minimumPulseRate;
			double frequency = (currentFrequencyRange * multiplier) + _minimumPulseRate;
			unsigned int requiredTicksSinceLast = 1000 / frequency;
			DWORD currentTickCount = GetTickCount();
			DWORD tickDelta = currentTickCount - _lastPulseExecute;
			if(requiredTicksSinceLast < tickDelta)
			{
				actionToPerform->Execute();
				_lastPulseExecute = currentTickCount;
			}
		}
		else if(_triggerBinary)
		{
			actionToPerform->Execute();
			_triggerBinary = false;
		}
	} while(false);

	_lastValue = currentValue;
}