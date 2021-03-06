/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameObject.h"
#include "../Exception.h"
#include "../ScriptException.h"
#include "../SplashState.h"
#include "../ContentManager.h"
#include "../StateManager.h"
#include "../ScriptManager.h"
#include "../JSONValue.h"

#include <string>
#include <iostream>
#include <boost/thread.hpp>

using namespace bit;
using namespace v8;
using namespace std;


GameObject::GameObject()
{
}


Local<Object> GameObject::createInstance()
{
	HandleScope handleScope;
	
	Local<FunctionTemplate> functionTemplate = createClass("Game");
	Local<ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
	
	// Create the methods
	
	addPrototypeMethod(prototypeTemplate, runScript, "runScript");
	addPrototypeMethod(prototypeTemplate, splash, "splash");
	addPrototypeMethod(prototypeTemplate, sleep, "sleep");
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	return handleScope.Close(objectInstance);
}


Handle<Value> GameObject::runScript(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		string scriptFilename = extractString(args, 0);
		GameObject *p = static_cast<GameObject *>(extractHolder(args));
		
		// Call member function
		
		p->runScript(scriptFilename);
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


Handle<Value> GameObject::splash(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		string splashFilename = extractString(args, 0);
		
		// TODO
		// Make these optional
		
		double fadeIn = extractDouble(args, 1);
		double hold = extractDouble(args, 2);
		double fadeOut = extractDouble(args, 3);
		GameObject *p = static_cast<GameObject *>(extractHolder(args));
		
		// Call member function
		
		p->splash(splashFilename, fadeIn, hold, fadeOut);
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


Handle<Value> GameObject::sleep(const v8::Arguments &args)
{
	try
	{
		double sleepTime = extractDouble(args, 0);
		
		boost::posix_time::time_duration duration =
			boost::posix_time::milliseconds(sleepTime * 1000);
		boost::this_thread::sleep(duration);
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


void GameObject::runScript(const string &filename)
{
	// Load the script from the file
	
	string scriptText = contentManager->loadText(filename);
	
	// Run the script, blocking the current script
	
	scriptManager->runScript(scriptText);
}


void GameObject::splash(const string &filename, double fadeIn,
	double hold, double fadeOut)
{
	// Create the splash state
	
	// shared_ptr<SplashState> splashState = stateManager->getSplashState();
	
	// shared_ptr<sf::Texture> splashTexture = contentManager->loadTexture(filename);
	// splashState->setTexture(splashTexture);
	// splashState->setFadeTimes(fadeIn, hold, fadeOut);
	
	// stateManager->changeState(StateManager::SPLASHSTATE);
}
