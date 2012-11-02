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
#include "MapState.h"
#include "ScriptException.h"

#include "objects/ConsoleObject.h"
#include "objects/GameObject.h"
#include "objects/MapObject.h"
#include "objects/AudioObject.h"

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
	stateManager->getMapState()->contentManager = contentManager;
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
	gameObject->scriptManager = scriptManager;
	scriptManager->registerObject(gameObject, "game");
	
	// audio
	
	AudioObject *audioObject = new AudioObject;
	audioObject->contentManager = contentManager;
	scriptManager->registerObject(audioObject, "audio");
	
	// map
	
	MapObject *mapObject = new MapObject;
	mapObject->contentManager = contentManager;
	mapObject->scriptManager = scriptManager;
	mapObject->stateManager = stateManager;
	scriptManager->registerObject(mapObject, "map");
}


void Application::startScriptThread(const string &text)
{
	// Run the requested script
	
	try
	{
		scriptManager->runScript(text);
	}
	catch (bit::Exception &e)
	{
		cout << e.what() << endl;
	}
	
	// Once that's complete, just offer a console for further commands
	
	string input;
	
	while (true)
	{
		try
		{
			cout << "> ";
			getline(cin, input);
			
			if (input == "")
				break;
			
			string output = scriptManager->evaluate(input);
			
			if (output != "")
				cout << output << endl;
		}
		catch (Exception &e)
		{
			cout << e.what() << endl;
		}
	}
	
	cout << endl;
	cout << "Script thread finished" << endl;
}
