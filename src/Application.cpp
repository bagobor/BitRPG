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
#include "EventManager.h"
#include "ConsoleObject.h"
#include "JSONValue.h"
#include "Exception.h"

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
	eventManager.reset(new EventManager);
	stateManager.reset(new StateManager);
	
	// Satisfy component dependencies
	
	displayManager->eventManager = eventManager;
	displayManager->stateManager = stateManager;
	eventManager->displayManager = displayManager;
}


void Application::start()
{
	// Register console object
	
	ConsoleObject *consoleObject = new ConsoleObject;
	scriptManager->registerObject(consoleObject, "console");
	
	// Load configuration file
	
	string configData = contentManager->loadText("config.json");
	JSONValue configValue = scriptManager->parseJSON(configData);
	
	// Open the DisplayManager window
	
	JSONValue windowValue = configValue["window"];
	displayManager->openWindow(windowValue);
	
	eventManager->window = displayManager->window;
	
	// TEMP Load the splash state
	
	boost::shared_ptr<SplashState> splashState(new SplashState);
	splashState->setFadeTimes(1.0f, 2.0f, 0.5f);
	splashState->setTexture(contentManager->loadTexture("images/bitrpg.gif"));
	
	stateManager->changeState(splashState);
	
	// Run the DisplayManager in the main thread
	// OS X requires that event checking should be done in the main thread,
	// so this is the last thing this function should do.
	
	displayManager->run();
}
