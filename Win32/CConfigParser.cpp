#include "stdafx.h"
#include "CConfigParser.h"

#include "CAxis.h"
#include "CContext.h"
#include "CTimeFrame.h"
#include "CMouseProc.h"
#include "CMouseXAxis.h"
#include "CMouseYAxis.h"
#include "CWinampMute.h"
#include "CMacroAction.h"
#include "CActionButton.h"
#include "CDeviceContext.h"
#include "CExecuteAction.h"
#include "CKeyboardAction.h"
#include "CWinampPlayPause.h"
#include "CMouseDeviceContext.h"
#include "CLeftMouseButtonAction.h"
#include "CRightMouseButtonAction.h"
#include "CSendWindowMessageAction.h"
#include "CWin32SpaceNavigatorHIDCapture.h"

bool CConfigParser::ParseConfig(string configFile, ADeviceListener& configClass)
{
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch(const XMLException& xmlEx)
	{	
		wstring message = L"Error initializing Xerces: ";
		message += xmlEx.getMessage();
		MessageBoxW(NULL, message.c_str(), L"Settings Error", MB_OK | MB_ICONERROR);
		return false;
	}

	XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMBuilder* parser = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

	if(parser->canSetFeature(XMLUni::fgDOMValidation, true))
        parser->setFeature(XMLUni::fgDOMValidation, true);
    if(parser->canSetFeature(XMLUni::fgDOMNamespaces, true))
        parser->setFeature(XMLUni::fgDOMNamespaces, true);
    if(parser->canSetFeature(XMLUni::fgDOMDatatypeNormalization, true))
        parser->setFeature(XMLUni::fgDOMDatatypeNormalization, true);

	char currentDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, (LPSTR)&currentDir);
	
	xercesc_2_7::DOMDocument* doc = NULL;

	// TODO: Should check to see if the file exists or not

	try
	{
		doc = parser->parseURI(configFile.c_str());
	}
	catch(const XMLException& xmlEx)
	{
		wstring message = L"Error parsing: ";
		message += xmlEx.getMessage();
		MessageBoxW(NULL, message.c_str(), L"Setting Parse Error", MB_OK | MB_ICONERROR);
		return false;
	}
	catch(const DOMException& domEx)
	{
		wstring message = L"Error parsing: ";
		message += domEx.getMessage();
		MessageBoxW(NULL, message.c_str(), L"Setting Parse Error", MB_OK | MB_ICONERROR);
		return false;
	}
	catch (...)
	{
		MessageBoxW(NULL, L"Unexpected error occured", L"Setting Parse Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if(doc->getDocumentElement()->getAttributes()->getNamedItem(L"gestureTimeVariance"))
	{
		long variance = _wtoi(doc->getDocumentElement()->getAttributes()->getNamedItem(L"gestureTimeVariance")->getNodeValue());
		CTimeFrame::setVariance(variance);
	}

	if(!ParseDevices(doc->getElementsByTagName(L"devices"), configClass))
		return false;
	if(!ParseActions(doc->getElementsByTagName(L"actions"), configClass))
		return false;
	if(!ParseDeviceContexts(doc->getElementsByTagName(L"deviceContexts"), configClass))
		return false;
	if(!ParseContexts(doc->getElementsByTagName(L"contexts"), configClass))
		return false;

	// Set the current context to the first one in the list
	configClass.SetContext(configClass.GetContexts().begin()->first);

	parser->release();
	XMLPlatformUtils::Terminate();
	return true;
}

bool CConfigParser::ParseDevices(DOMNodeList* deviceNodeList, ADeviceListener& configClass)
{
	ASSERT(deviceNodeList->getLength() >= 1);
	DOMNode* deviceNode = deviceNodeList->item(0);
	DOMNodeList* devices = deviceNode->getChildNodes();
	for(unsigned long idx = 0; idx < devices->getLength(); idx++)
	{
		DOMNode* currentDevice = devices->item(idx);
		wstring deviceNodeName = currentDevice->getNodeName();
		if(deviceNodeName.compare(L"#text") == 0)
			continue;
		wstring deviceName = currentDevice->getAttributes()->getNamedItem(L"name")->getNodeValue();
		//wstring deviceType = currentDevice->getAttributes()->getNamedItem(L"type")->getNodeValue();
		wstring deviceType = deviceNodeName;
		if(deviceType.compare(L"mouse") == 0)
		{
			configClass.AddDevice(deviceName, new CMouseProc());
		}
		else
		{
			CWin32SpaceNavigatorHIDCapture* deviceToAdd = new CWin32SpaceNavigatorHIDCapture();
			if(currentDevice->hasChildNodes())
			{
				if(!ParseHIDDeviceCommands(currentDevice->getChildNodes(), deviceToAdd))
					return false;
			}
			configClass.AddDevice(deviceName, deviceToAdd);
		}
	}
	return true;
}

bool CConfigParser::ParseHIDDeviceCommands(DOMNodeList* commandNodeList, CWin32SpaceNavigatorHIDCapture* device)
{
	if(commandNodeList == NULL)
		return true;

	for(unsigned long idx = 0; idx < commandNodeList->getLength(); idx++)
	{
		DOMNode* currentCommand = commandNodeList->item(idx);
		wstring commandNodeName = currentCommand->getNodeName();
		if(commandNodeName.compare(L"command") != 0)
			continue;
		wstring commandName = currentCommand->getAttributes()->getNamedItem(L"name")->getNodeValue();
		wstring commandReport = currentCommand->getAttributes()->getNamedItem(L"report")->getNodeValue();
		wstring commandValue = currentCommand->getAttributes()->getNamedItem(L"value")->getNodeValue();

		unsigned int report = NULL;
		unsigned int value = NULL;
		
		swscanf(commandReport.c_str(), L"0x%04X", &report);
		swscanf(commandValue.c_str(), L"0x%04X", &value);

		device->AddCommand(commandName, report, value);
	}
	return true;
}

bool CConfigParser::ParseActions(DOMNodeList* actionNodeList, ADeviceListener& configClass)
{
	USES_CONVERSION;
	// Parse all the actions	
	if(actionNodeList != NULL && actionNodeList->getLength() > 0)
	{
		DOMNodeList* actionNodes = actionNodeList->item(0)->getChildNodes();
		for(unsigned long i = 0; i < actionNodes->getLength(); i++)
		{
			DOMNode* actionNode = actionNodes->item(i);
			wstring actionType = actionNode->getNodeName();
			if(actionType.compare(L"#text") == 0)
				continue;
			XMLCh* xmlChNameTxt = L"name";
			wstring actionName;
			if(actionNode->hasAttributes())
			{
				DOMNode* nameAttribute = actionNode->getAttributes()->getNamedItem(xmlChNameTxt);
				actionName = nameAttribute->getNodeValue();
			}			
			if(actionType.compare(L"sendCopyDataWindowMessage") == 0 || actionType.compare(L"sendCommandWindowMessage") == 0)
			{
				wstring message = actionNode->getAttributes()->getNamedItem(L"message")->getNodeValue();
				bool findByClass = FALSE;
				wstring windowAttributeName = L"window";
				if(actionNode->getAttributes()->getNamedItem(L"window") == NULL)
				{
					findByClass = TRUE;
					windowAttributeName = L"windowClass";
				}
				wstring window = actionNode->getAttributes()->getNamedItem(windowAttributeName.c_str())->getNodeValue();

				CSendWindowMessageAction* messageActionToAdd = NULL;
				if(actionType.compare(L"sendCommandWindowMessage") == 0)
				{
					messageActionToAdd = new CSendWindowMessageAction(_wtol(message.c_str()), OLE2T(window.c_str()), findByClass);
				}
				if(actionType.compare(L"sendCopyDataWindowMessage") == 0)
				{
					messageActionToAdd = new CSendWindowMessageAction(OLE2T(message.c_str()), OLE2T(window.c_str()), findByClass);
				}

				if(messageActionToAdd != NULL)
					configClass.AddAction(actionName, messageActionToAdd);
			}
			if(actionType.compare(L"execute") == 0)
			{
				char* executable = XMLString::transcode(
					actionNode->getAttributes()->getNamedItem(L"executable")->getNodeValue());
				char* commandline = XMLString::transcode(
					actionNode->getAttributes()->getNamedItem(L"commandline")->getNodeValue());
				configClass.AddAction(actionName, new CExecuteAction(executable, commandline));
				XMLString::release(&executable);
				XMLString::release(&commandline);
			}
			if(actionType.compare(L"keyPress") == 0)
			{
				TKeyList keys;

				DOMNodeList* keyNodes = actionNode->getChildNodes();
				unsigned long count = keyNodes->getLength();
				for(unsigned long keyIdx=0; keyIdx < keyNodes->getLength(); keyIdx++)
				{
					DOMNode* keyNode = keyNodes->item(keyIdx);
					if(wcscmp(keyNode->getNodeName(), L"#text") == 0)
						continue;
					
					const XMLCh* keyValue = keyNode->getFirstChild()->getNodeValue();
					if(keyValue == NULL)
						continue;

					int test = VK_CONTROL;
					keys.push_back(_wtoi(keyValue));					
				}
				configClass.AddAction(actionName, new CKeyboardAction(keys));
			}
			if(actionType.compare(L"winampPlayPause") == 0)
			{
				configClass.AddAction(actionName, new CWinampPlayPause());
			}
			if(actionType.compare(L"winampMute") == 0)
			{
				configClass.AddAction(actionName, new CWinampMute());
			}
			// We make the assumption that the macros were put at the end of the
			// config file, otherwise the actions they execute may not exist!
			if(actionType.compare(L"macro") == 0)
			{
				wstring type = actionNode->getAttributes()->getNamedItem(L"type")->getNodeValue();
				CMacroAction* actionToAdd = new CMacroAction(type.compare(L"all") == 0 ? true : false);
				DOMNodeList* macroActions = actionNode->getChildNodes();
				unsigned long count = macroActions->getLength();
				for(unsigned long actionIdx=0; actionIdx < count; actionIdx++)
				{
					DOMNode* macroActionNode = macroActions->item(actionIdx);
					if(wcscmp(macroActionNode->getNodeName(), L"#text") == 0)
						continue;

					wstring macroActionName = macroActionNode->getAttributes()->getNamedItem(L"name")->getNodeValue();
					actionToAdd->AddAction(configClass.GetActions()[macroActionName]);
				}
				configClass.AddAction(actionName, actionToAdd);
			}
		}
	}
	return true;
}

bool CConfigParser::ParseDeviceContexts(DOMNodeList* deviceContextNodes, ADeviceListener& configClass)
{
	ASSERT(deviceContextNodes->getLength() == 1);
	DOMNode* deviceContextNode = deviceContextNodes->item(0);
	DOMNodeList* deviceContexts = deviceContextNode->getChildNodes();
	for(unsigned long idx = 0; idx < deviceContexts->getLength(); idx++)
	{
		DOMNode* currentDeviceContext = deviceContexts->item(idx);
		wstring deviceContextNodeName = currentDeviceContext->getNodeName();
		if(deviceContextNodeName.compare(L"#text") == 0)
			continue;
		if(deviceContextNodeName.compare(L"#comment") == 0)
			continue;
		wstring deviceContextName = currentDeviceContext->getAttributes()->getNamedItem(L"name")->getNodeValue();
		wstring deviceName = currentDeviceContext->getAttributes()->getNamedItem(L"device")->getNodeValue();
		bool gestures = false;
		if(currentDeviceContext->getAttributes()->getNamedItem(L"gestures") != NULL)
			gestures = true;
		// Create the device context to add
		CDeviceContext* deviceContextToAdd = NULL;
		if(configClass.GetDevices()[deviceName]->GetType().compare("mouse") == 0)
			deviceContextToAdd = new CMouseDeviceContext(gestures, deviceName);
		else
			deviceContextToAdd = new CDeviceContext(gestures, deviceName);

		// Get the device contexts axis and buttons added
		if(currentDeviceContext->hasChildNodes())
		{
			unsigned char axeIdx = 0;
			DOMNodeList* children = currentDeviceContext->getChildNodes();
			unsigned long childCount = children->getLength();
			for(unsigned long idx = 0; idx < childCount; idx++)
			{
				DOMNode* childNode = children->item(idx);			
				wstring nodeName = childNode->getNodeName();

				if(nodeName.compare(L"axe") == 0)
				{
					ParseAxe(childNode, configClass.GetActions(), deviceContextToAdd, axeIdx);
					axeIdx++;
				}
				if(nodeName.compare(L"buttons") == 0)
					ParseButtons(childNode, configClass.GetActions(), deviceContextToAdd);
				if(nodeName.compare(L"gesture") == 0)
					ParseGesture(childNode, configClass.GetActions(), deviceContextToAdd);
			}
		}
		configClass.AddDeviceContext(deviceContextName, deviceContextToAdd);
		TRACE("Device Context <%S> is 0x%X\r\n", deviceContextName.c_str(), deviceContextToAdd);
	}
	return true;
}

bool CConfigParser::ParseGesture(DOMNode* node, TActionByNameMap actions, CDeviceContext* device)
{
	TGestureList gestures;
	wstring actionName = node->getAttributes()->getNamedItem(L"action")->getNodeValue();
	unsigned long length = node->getChildNodes()->getLength();
	for(unsigned long i = 0; i < length; i++)
	{
		DOMNode* gestNode = node->getChildNodes()->item(i);
		wstring nodeType = gestNode->getNodeName();
		if(nodeType.compare(L"#text") == 0)
			continue;
		if(nodeType.compare(L"motion") == 0)
		{
			wstring position = gestNode->getAttributes()->getNamedItem(L"position")->getNodeValue();
			wstring axe = gestNode->getAttributes()->getNamedItem(L"axe")->getNodeValue();
			EGesturePosition pos;
			if(position.compare(L"positive") == 0)
				pos = EGesturePosition::POSITIVE;
			if(position.compare(L"negative") == 0)
				pos = EGesturePosition::NEGATIVE;
			if(position.compare(L"center") == 0)
				pos = EGesturePosition::CENTER;
			gestures.push_back(new CMotion(pos, _wtoi(axe.c_str())));
		}
		if(nodeType.compare(L"wait") == 0)
			gestures.push_back(new CTimeFrame(_wtoi(gestNode->getAttributes()->getNamedItem(L"length")->getNodeValue())));
	}
	device->_gestureProcessor.addMacro(gestures, actions[actionName]);
	return true;
}

bool CConfigParser::ParseAxe(DOMNode* node, TActionByNameMap actions, CDeviceContext* device, unsigned char axeIdx)
{
	wstring threshold = node->getAttributes()->getNamedItem(L"threshold")->getNodeValue();

	// We can end this right here if it's a gesture axis
	if(device->IsGesturesContext())
	{
		wstring sendCenter = node->getAttributes()->getNamedItem(L"sendCenter")->getNodeValue();
		if(sendCenter.compare(L"true") == 0)
		{	
			device->AddAxe((IAxis*)new CAxis(_wtoi(threshold.c_str()),
				CMotion::MakePositionAndAxis(EGesturePosition::POSITIVE, axeIdx),
				CMotion::MakePositionAndAxis(EGesturePosition::NEGATIVE, axeIdx),
				&device->_gestureProcessor,
				CMotion::MakePositionAndAxis(EGesturePosition::CENTER, axeIdx)));
		}
		else
		{
			device->AddAxe((IAxis*)new CAxis(_wtoi(threshold.c_str()),
				CMotion::MakePositionAndAxis(EGesturePosition::POSITIVE, axeIdx),
				CMotion::MakePositionAndAxis(EGesturePosition::NEGATIVE, axeIdx),
				&device->_gestureProcessor));
		}
		return true;
	}

	wstring actionType;
	wstring posAction;
	wstring negAction;
	bool mouseX = false;
	bool mouseY = false;
	if(node->getAttributes()->getNamedItem(L"simulateMouseMove") != NULL)
	{
		DOMNode* mouseAxisNode = node->getAttributes()->getNamedItem(L"simulateMouseMove");
		wstring mouseAxisValue = mouseAxisNode->getNodeValue();
		if(mouseAxisValue.compare(L"x") == 0)
			mouseX = true;
		if(mouseAxisValue.compare(L"y") == 0)
			mouseY = true;
	}
	if(!mouseX && !mouseY)
	{
		if(node->getAttributes()->getNamedItem(L"type") != NULL)
			actionType = node->getAttributes()->getNamedItem(L"type")->getNodeValue();			
		else
			actionType = L"binary";
		if(node->getAttributes()->getNamedItem(L"posAction") != NULL)
			posAction = node->getAttributes()->getNamedItem(L"posAction")->getNodeValue();			
		else
			posAction = L"";
		if(node->getAttributes()->getNamedItem(L"negAction") != NULL)
			negAction = node->getAttributes()->getNamedItem(L"negAction")->getNodeValue();
		else
			negAction = L"";
	}
	else
	{
		wstring divisor = node->getAttributes()->getNamedItem(L"divisor")->getNodeValue();
		if(mouseX)
		{
			device->AddAxe((IAxis*)new CMouseXAxis(_wtoi(threshold.c_str()), _wtoi(divisor.c_str())));
			return true;
		}
		else if(mouseY)
		{
			device->AddAxe((IAxis*)new CMouseYAxis(_wtoi(threshold.c_str()), _wtoi(divisor.c_str())));
			return true;
		}
	}
	

	bool pulse = false;
	bool linear = false;
	if(actionType.compare(L"linear") == 0)
	{
		pulse = true;
		linear = true;
	}
	if(actionType.compare(L"exponential") == 0)
	{
		pulse = true;
		linear = false;
	}
	if(pulse)
	{
		wstring startPulse = node->getAttributes()->getNamedItem(L"startPulse")->getNodeValue();
		wstring endPulse = node->getAttributes()->getNamedItem(L"endPulse")->getNodeValue();
		
		device->AddAxe((IAxis*)new CAxis(_wtoi(threshold.c_str()), _wtoi(startPulse.c_str()),
			_wtoi(endPulse.c_str()), linear,
			actions[posAction],actions[negAction]));
		return true;
	}
	else
	{
		device->AddAxe((IAxis*)new CAxis(_wtoi(threshold.c_str()), actions[posAction], actions[negAction]));
		return true;
	}
	return false;
}

bool CConfigParser::ParseButtons(DOMNode* node, TActionByNameMap actions, CDeviceContext* device)
{
	if(node->hasChildNodes())
	{
		DOMNodeList* buttonNodes = node->getChildNodes();
		unsigned long length = buttonNodes->getLength();
		for(unsigned long idx = 0; idx < length; idx++)
		{
			DOMNode* buttonNode = buttonNodes->item(idx);
			wstring nodeName = buttonNode->getNodeName();
			if(buttonNode->hasAttributes())
			{
				DOMNode* mouseSim = buttonNode->getAttributes()->getNamedItem(L"simulateMouseButton");
				if(mouseSim != NULL)
				{
					wstring mouseSimBtn = mouseSim->getNodeValue();
					if(mouseSimBtn.compare(L"left") == 0)
						device->AddButton(new CLeftMouseButtonAction());
					if(mouseSimBtn.compare(L"right") == 0)
						device->AddButton(new CRightMouseButtonAction());
				}
				else
				{
					wstring downAction = buttonNode->getAttributes()->getNamedItem(L"downAction")->getNodeValue();
					wstring upAction = buttonNode->getAttributes()->getNamedItem(L"upAction")->getNodeValue();
					device->AddButton(new CActionButton(actions[downAction], actions[upAction]));
				}
			}
			else if (nodeName.compare(L"button") == 0)
			{
				device->AddButton((IButton*)NULL);
			}
		}
	}
	return false;
}

bool CConfigParser::ParseContexts(DOMNodeList* contextNodes, ADeviceListener& configClass)
{
	ASSERT(contextNodes->getLength() == 1);
	DOMNode* contextNode = contextNodes->item(0);
	DOMNodeList* contexts = contextNode->getChildNodes();
	for(unsigned long idx = 0; idx < contexts->getLength(); idx++)
	{
		DOMNode* currentContext = contexts->item(idx);
		wstring contextNodeName = currentContext->getNodeName();
		if(contextNodeName.compare(L"#text") == 0)
			continue;
		wstring contextName = currentContext->getAttributes()->getNamedItem(L"name")->getNodeValue();
		CContext* contextToAdd = new CContext();
		unsigned long attrLen = currentContext->getAttributes()->getLength();
		for(unsigned long attr = 0; attr < attrLen; attr++)
		{
			DOMNode* deviceContextAttr = currentContext->getAttributes()->item(attr);
			if(wcscmp(deviceContextAttr->getNodeName(), L"deviceContext") == 0)
			{
				wstring deviceContextName = deviceContextAttr->getNodeValue();
				CDeviceContext* deviceContext = configClass.GetDeviceContexts()[deviceContextName];
				IDeviceCapture* device = configClass.GetDevices()[deviceContext->GetDeviceName()];
				contextToAdd->AddDeviceContext(device, deviceContext);
			}
		}
		configClass.AddContext(contextName, contextToAdd);
	}
	return true;
}