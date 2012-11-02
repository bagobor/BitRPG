/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapObject.h"
#include "../ContentManager.h"
#include "../ScriptManager.h"
#include "../JSONValue.h"
#include "../StateManager.h"
#include "../MapState.h"
#include "../Exception.h"
#include "../ScriptException.h"

using namespace bit;
using namespace v8;
using namespace std;


MapObject::MapObject()
{
}


Local<Object> MapObject::createInstance()
{
	HandleScope handleScope;
	
	Local<FunctionTemplate> functionTemplate = createClass("Map");
	Local<ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
	
	// Add the methods
	
	addPrototypeMethod(prototypeTemplate, load, "load");
	addPrototypeMethod(prototypeTemplate, show, "show");
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	return handleScope.Close(objectInstance);
}


Handle<Value> MapObject::load(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		string mapFilename = extractString(args, 0);
		MapObject *p = static_cast<MapObject *>(extractHolder(args));
		
		// Call member function
		
		p->loadMap(mapFilename);
	}
	catch (Exception &e)
	{
		e.throwV8Exception();
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


Handle<Value> MapObject::show(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		MapObject *p = static_cast<MapObject *>(extractHolder(args));
		
		// Call member function
		
		p->show();
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
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
