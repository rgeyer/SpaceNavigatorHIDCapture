#ifndef __CCONFIGPARSER_H__
#define __CCONFIGPARSER_H__

#include <string>
using namespace std;

#include "ADeviceListener.h"
#include "CWin32SpaceNavigatorHIDCapture.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc_2_7;

class CConfigParser
{
public:
	static bool ParseConfig(string configFile, ADeviceListener& configClass);
	static bool ParseDevices(DOMNodeList* deviceNodeList, ADeviceListener& configClass);
	static bool ParseHIDDeviceCommands(DOMNodeList* commandNodeList, CWin32SpaceNavigatorHIDCapture* device);
	static bool ParseActions(DOMNodeList* actionNodeList, ADeviceListener& configClass);
	static bool ParseDeviceContexts(DOMNodeList* deviceContextNodes, ADeviceListener& configClass);
	static bool ParseAxe(DOMNode* node, TActionByNameMap actions, CDeviceContext* device, unsigned char axeIdx);
	static bool ParseButtons(DOMNode* node, TActionByNameMap actions, CDeviceContext* device);
	static bool ParseGesture(DOMNode* node, TActionByNameMap actions, CDeviceContext* device);
	static bool ParseContexts(DOMNodeList* contextNodes, ADeviceListener& configClass);
};

#endif