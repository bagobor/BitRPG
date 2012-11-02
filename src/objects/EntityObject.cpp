/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "EntityObject.h"

using namespace bit;
using namespace v8;


EntityObject::EntityObject()
{
	printf("EntityObject()\n");
}


EntityObject::~EntityObject()
{
	printf("~EntityObject()\n");
}


Local<Object> EntityObject::createInstance()
{
	HandleScope handleScope;
	
	Local<FunctionTemplate> functionTemplate = createClass("Entity");
	// Local<ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
	
	// Add the methods
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	return handleScope.Close(objectInstance);
}
