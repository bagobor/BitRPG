/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "ContentManager.h"
#include "ScriptManager.h"
#include "DisplayManager.h"
#include "EventManager.h"
#include "ConsoleObject.h"
#include "JSONValue.h"
#include "Exception.h"
#include "MapManager.h"

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
	mapManager.reset(new MapManager);
	
	// Satisfy component dependencies
	
	displayManager->eventManager = eventManager;
	displayManager->mapManager = mapManager;
	eventManager->displayManager = displayManager;
	mapManager->contentManager = contentManager;
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
	
	// TEMP Load the map
	
	string strandedText = contentManager->loadText("maps/stranded.json");
	JSONValue mapObject = scriptManager->parseJSON(strandedText);
	mapManager->loadMap(mapObject);
	
	// Run the DisplayManager in the main thread
	// OS X requires that event checking should be done in the main thread,
	// so this is the last thing this function should do.
	
	displayManager->run();
}
