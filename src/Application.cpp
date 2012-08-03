/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "ContentManager.h"
#include "ScriptManager.h"
#include "DisplayManager.h"
#include "StateManager.h"
#include "JSONValue.h"
#include "Exception.h"

#include "ConsoleObject.h"
#include "GameObject.h"
#include "SplashState.h"

#include <boost/thread/thread.hpp>
#include <string>
#include <iostream>

using namespace bit;
using namespace std;


Application::Application()
{
	// Allocate the components
	
	contentManager.reset(new ContentManager);
	scriptManager.reset(new ScriptManager);
	displayManager.reset(new DisplayManager);
	stateManager.reset(new StateManager);
	
	// Satisfy component dependencies
	
	displayManager->stateManager = stateManager;
}


void Application::start()
{
	// Load configuration file
	
	string configText = contentManager->loadText("config.json");
	JSONValue configValue = scriptManager->parseJSON(configText);
	
	// Start the scripting engine
	
	registerScriptObjects();
	
	JSONValue scriptingValue = configValue["scripting"];
	string entryFilename = scriptingValue["entry"].toString();
	string entryText = contentManager->loadText(entryFilename);
	
	// Open the DisplayManager window
	
	JSONValue windowValue = configValue["window"];
	displayManager->openWindow(windowValue);
	
	// Start the script thread
	
	boost::thread scriptThread(&Application::startScriptThread,
		this, entryText);
	
	// Run the DisplayManager in the main thread
	// OS X requires that event checking should be done in the main thread,
	// so this is the last thing this function should do.
	
	displayManager->run();
}


void Application::registerScriptObjects()
{
	// console
	
	ConsoleObject *consoleObject = new ConsoleObject;
	scriptManager->registerObject(consoleObject, "console");
	
	// game
	
	GameObject *gameObject = new GameObject;
	gameObject->contentManager = contentManager;
	gameObject->stateManager = stateManager;
	
	scriptManager->registerObject(gameObject, "game");
}


void Application::startScriptThread(const string &text)
{
	try
	{
		scriptManager->runScript(text);
	}
	catch (bit::Exception &e)
	{
		cout << e.what() << endl;
	}
}
