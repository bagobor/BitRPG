/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapObject.h"
#include "ContentManager.h"
#include "ScriptManager.h"
#include "JSONValue.h"
#include "StateManager.h"
#include "MapState.h"
#include "Exception.h"
#include "ScriptException.h"

using namespace bit;
using namespace v8;
using namespace std;


MapObject::MapObject()
{
}


Local<Object> MapObject::createInstance()
{
	HandleScope handleScope;
	
	// Create the function template
	
	Local<FunctionTemplate> functionTemplate = FunctionTemplate::New();
	functionTemplate->SetClassName(String::New("Map"));
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	// Add functions to object instance
	
	Local<FunctionTemplate> loadTemplate = FunctionTemplate::New(load);
	Local<Function> loadFunction = loadTemplate->GetFunction();
	objectInstance->Set(String::New("load"), loadFunction);
	
	Local<FunctionTemplate> showTemplate = FunctionTemplate::New(show);
	Local<Function> showFunction = showTemplate->GetFunction();
	objectInstance->Set(String::New("show"), showFunction);
	
	return handleScope.Close(objectInstance);
}


Handle<Value> MapObject::load(const v8::Arguments &args)
{
	string mapFilename;
	MapObject *p = NULL;
	
	try
	{
		// Extract arguments
		
		mapFilename = extractString(args, 0);
		p = static_cast<MapObject *>(extractHolder(args));
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	// Call member function
	
	try
	{
		p->loadMap(mapFilename);
	}
	catch (Exception &e)
	{
		e.throwV8Exception();
	}
	
	return Undefined();
}


Handle<Value> MapObject::show(const v8::Arguments &args)
{
	// Extract arguments
	
	MapObject *p = static_cast<MapObject *>(extractHolder(args));
	
	// Call member function
	
	p->show();
	
	return Undefined();
}


void MapObject::loadMap(const std::string &filename)
{
	string mapText = contentManager->loadText(filename);
	
	// Parse the JSON data
	
	JSONValue mapObject = scriptManager->parseJSON(mapText);
	
	// Load the map in the MapState
	
	MapStatePtr mapState = stateManager->getMapState();
	mapState->loadMap(mapObject);
}


void MapObject::show()
{
	// Change the state to MapState
	
	stateManager->changeState(StateManager::MAPSTATE);
}
