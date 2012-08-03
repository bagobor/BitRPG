/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameObject.h"
#include "Exception.h"
#include "SplashState.h"
#include "ContentManager.h"
#include "StateManager.h"

#include <boost/thread/thread.hpp>
#include <string>
#include <iostream>

using namespace bit;
using namespace v8;
using namespace std;


GameObject::GameObject()
{
}


Local<Object> GameObject::createInstance()
{
	HandleScope handleScope;
	
	// Create the function template
	
	Local<FunctionTemplate> functionTemplate = FunctionTemplate::New();
	functionTemplate->SetClassName(String::New("Game"));
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	// Add functions to object instance
	
	Local<FunctionTemplate> loadMapTemplate = FunctionTemplate::New(loadMap);
	Local<Function> loadMapFunction = loadMapTemplate->GetFunction();
	objectInstance->Set(String::New("loadMap"), loadMapFunction);
	
	Local<FunctionTemplate> splashTemplate = FunctionTemplate::New(splash);
	Local<Function> splashFunction = splashTemplate->GetFunction();
	objectInstance->Set(String::New("splash"), splashFunction);
	
	return handleScope.Close(objectInstance);
}


Handle<Value> GameObject::loadMap(const v8::Arguments &args)
{
	// Extract arguments
	
	//string mapName;
	//extractArguments(args, "s", &mapName);
	
	// Get pointer to GameObject
	
	//GameObject *gameObject = reinterpret_cast<GameObject *>(getThis(args));
	
	// Call member function with given arguments
	
	//string mapData = launcher->contentManager->loadFile(mapName + ".json");
	//JSONValue mapObject = launcher->scriptEngine->parseJSON(mapData);
	//launcher->displayManager->mapManager->loadMap(mapObject);
	
	// Return stuff
	
	return Undefined();
}


Handle<Value> GameObject::splash(const v8::Arguments &args)
{
	// Extract arguments
	
	GameObject *p = static_cast<GameObject *>(extractHolder(args));
	
	string splashFilename = extractString(args, 0);
	double fadeIn = extractDouble(args, 1);
	double hold = extractDouble(args, 2);
	double fadeOut = extractDouble(args, 3);
	
	p->splash(splashFilename, fadeIn, hold, fadeOut);
	
	return Undefined();
}


void GameObject::splash(const string &filename, double fadeIn,
	double hold, double fadeOut)
{
	// Create the splash state
	
	boost::shared_ptr<SplashState> splashState(new SplashState);
	sf::TexturePtr splashTexture = contentManager->loadTexture(filename);
	
	splashState->setTexture(splashTexture);
	splashState->setFadeTimes(fadeIn, hold, fadeOut);
	stateManager->changeState(splashState);
}
