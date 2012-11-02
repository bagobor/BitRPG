/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ConstructorObject.h"
#include "ItemObject.h"

using namespace bit;
using namespace v8;


Handle<Value> ConstructorObject::entityConstructor(const Arguments &args)
{
	HandleScope handleScope;
	
	// Make sure the constructor is called with the new keyword
	
	if (!args.IsConstructCall())
	{
		Local<String> message = String::New("Cannot call constructor as a function");
		return ThrowException(Exception::SyntaxError(message));
	}
	
	// Instantiate a new ScriptTemplate
	
	ItemObject *itemObject = new ItemObject();
	Local<Object> itemInstance = itemObject->createInstance();
	itemInstance->SetInternalField(0, External::New(itemObject));
	
	return handleScope.Close(itemInstance);
}