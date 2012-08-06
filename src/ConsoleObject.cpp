/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ConsoleObject.h"
#include "ScriptException.h"
 
#include <iostream>

using namespace bit;
using namespace v8;
using namespace std;


Local<Object> ConsoleObject::createInstance()
{
	HandleScope handleScope;
	
	Local<FunctionTemplate> functionTemplate = createClass("Console");
	Local<ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
	
	// Add the methods
	
	addPrototypeMethod(prototypeTemplate, print, "print");
	addPrototypeMethod(prototypeTemplate, input, "input");
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	return handleScope.Close(objectInstance);
}


Handle<Value> ConsoleObject::print(const Arguments &args)
{
	HandleScope handleScope;
	
	try
	{
		string message = ScriptObject::extractString(args, 0);
		
		// Print the string with a newline at the end
		
		cout << message << endl;
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


Handle<Value> ConsoleObject::input(const Arguments &args)
{
	HandleScope handleScope;
	
	// Query the user for a line of console input
	
	string result;
	getline(cin, result);
	
	// Create the V8 string and return it
	
	Local<String> resultString = String::New(result.c_str());
	
	return handleScope.Close(resultString);
}
