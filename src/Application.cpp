/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "ContentManager.h"
#include "ScriptManager.h"
#include "WindowManager.h"
#include "JSONValue.h"
#include "Exception.h"
#include "ScriptException.h"

#include "objects/ConsoleObject.h"
#include "objects/GameObject.h"
#include "objects/MapObject.h"
#include "objects/AudioObject.h"

#include <boost/thread/thread.hpp>
#include <string>
#include <iostream>
 
#include "game/GameScreen.h"
#include "game/Entity.h"
#include "SharedSprite.h"
#include "game/Map.h"

using namespace bit;
using namespace std;


Application::Application()
{
	// Allocate the components
	
	contentManager.reset(new ContentManager);
	scriptManager.reset(new ScriptManager);
	windowManager.reset(new WindowManager);
	
	// Satisfy Manager dependencies
	
	// stateManager->getMapState()->contentManager = contentManager;
}


void Application::start()
{
	// Load configuration file
	
	string configText = contentManager->loadText("config.json");
	JSONValue configValue = scriptManager->parseJSON(configText);
	
	// Start the scripting engine
	
	// registerScriptObjects();
	
	// JSONValue scriptingValue = configValue["scripting"];
	// string entryFilename = scriptingValue["start"].toString();
	// string entryText = contentManager->loadText(entryFilename);
	
	// Open the WindowManager window
	
	JSONValue windowValue = configValue["window"];
	windowManager->openWindow(windowValue);
	
	// Start the script thread
	
	// boost::thread scriptThread(&Application::startScriptThread,
	// 	this, entryText);
	
	boost::thread scriptThread(&Application::runScript, this);
	
	// Run the WindowManager in the main thread
	// OS X requires that event checking should be done in the main thread,
	// so this function will block until the window is closed.
	
	windowManager->run();
}


void Application::registerScriptObjects()
{
	/*
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
	*/
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


void Application::runScript()
{
	// Create the game screen
	
	shared_ptr<GameScreen> gameScreen(new GameScreen(windowManager->screenSize));
	gameScreen->contentManager = contentManager;
	
	// Load the map
	
	std::string mapJSON = contentManager->loadText("maps/stranded.json");
	JSONValue mapObject = scriptManager->parseJSON(mapJSON);
	gameScreen->loadMap(mapObject);
	
	// Add an entity
	
	shared_ptr<sf::Image> megamanImage = contentManager->loadImage("images/megaman.gif");
	shared_ptr<sf::Texture> megamanTexture(new sf::Texture);
	megamanTexture->loadFromImage(*megamanImage);
	shared_ptr<SharedSprite> megamanSprite(new SharedSprite(megamanTexture));
	
	shared_ptr<Entity> megamanEntity(new Entity);
	megamanEntity->sprite = megamanSprite;
	megamanEntity->setMapPosition(sf::Vector2i(3, 3));
	gameScreen->map->addEntity(megamanEntity, 10);
	
	// Set the active screen
	
	windowManager->activeScreen = gameScreen;
}
