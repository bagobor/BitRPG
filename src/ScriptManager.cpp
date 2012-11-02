/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptManager.h"
#include "Exception.h"
#include "JSONValue.h"
#include "ScriptObject.h"

#include <v8.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace bit;
using namespace v8;
using namespace std;


ScriptManager::ScriptManager()
{
	// Init V8
	
	V8::Initialize();
	// Locker::StartPreemption(10);
	
	mainIsolate = Isolate::New();
	
	if (!mainIsolate)
		throw bit::Exception("V8 isolate could not be created");
	
	// Create context
	
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	
	mainContext = Context::New();
	mainContext->Enter();
	
	initializeJSON();
}


void ScriptManager::initializeJSON()
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	
	Local<Object> global = mainContext->Global();
	
	// Grab the JSON.parse() function
	
	Local<String> JSONString = String::New("JSON");
	Local<Object> JSONObject = Local<Object>::Cast(global->Get(JSONString));
	
	Local<Value> parseValue = JSONObject->Get(String::New("parse"));
	Local<Function> parseFunction = Local<Function>::Cast(parseValue);
	jsonParse = Persistent<Function>::New(parseFunction);
	
	if (jsonParse.IsEmpty() || !jsonParse->IsFunction())
		throw bit::Exception("Could not grab JSON.parse()");
	
	Local<Value> stringifyValue = JSONObject->Get(String::New("stringify"));
	Local<Function> stringifyFunction = Local<Function>::Cast(stringifyValue);
	jsonStringify = Persistent<Function>::New(stringifyFunction);
}


ScriptManager::~ScriptManager()
{
	jsonParse.Dispose();
	jsonStringify.Dispose();
	
	mainContext.Dispose();
}


void ScriptManager::registerObject(ScriptObject *scriptObject, string name)
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	
	Local<Object> global = mainContext->Global();
	
	// Make the object a global in the V8 context
	
	Local<Object> obj = scriptObject->createInstance();
	global->Set(String::New(name.c_str()), obj);
}


void ScriptManager::registerConstructor(InvocationCallback constructor, string name)
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	
	// Create a V8 function from the constructor callback function
	
	Local<FunctionTemplate> constructorTemplate = FunctionTemplate::New(constructor);
	Local<Function> constructorFunction = constructorTemplate->GetFunction();
	
	// Make the constructor function a global
	
	Local<Object> global = mainContext->Global();
	
	global->Set(String::New(name.c_str()), constructorFunction);
}


void ScriptManager::runScript(const std::string &source)
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Compile script
	
	Local<String> sourceString = String::New(source.c_str());
	Local<Script> script = Script::Compile(sourceString);
	
	if (script.IsEmpty())
		throw bit::Exception("Script could not compile");
	
	catchException(tryCatch);
	
	// Run script
	
	script->Run();
	
	catchException(tryCatch);
}


string ScriptManager::evaluate(const string &statement)
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Compile statement
	
	Local<String> source = String::New(statement.c_str());
	Local<Script> script = Script::Compile(source);
	
	catchException(tryCatch);
	
	if (script.IsEmpty())
		throw bit::Exception("Script did not compile");
	
	// Run script
	
	Handle<Value> result = script->Run();
	
	catchException(tryCatch);
	
	if (result->IsUndefined())
	{
		return string();
	}
	else
	{
		// Assign result value to "_" global variable
		
		Handle<Object> globalObject = mainContext->Global();
		globalObject->Set(String::New("_"), result);
		
		// Return value as string
		
		String::Utf8Value resultUtf(result);
		return string(*resultUtf);
	}
}


JSONValue ScriptManager::parseJSON(const string &data)
{
	if (jsonParse.IsEmpty() || !jsonParse->IsFunction())
		throw bit::Exception("It seems JSON.parse() has disappeared");
	
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Call the JSON.parse() function
	
	Handle<Value> args[] = { String::New(data.c_str()) };
	Local<Value> result = jsonParse->Call(mainContext->Global(), 1, args);
	
	catchException(tryCatch);
	
	// Contruct root JSONValue
	
	HandleScope returnScope;
	Local<Value> rootValue = handleScope.Close(result);
	return JSONValue(rootValue, mainIsolate);
}


string ScriptManager::toJSON(const JSONValue &value, bool pretty)
{
	Locker locker(mainIsolate);
	Isolate::Scope isolateScope(mainIsolate);
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Set the 'space' argument if the JSON needs to be prettified
	
	Handle<Value> spaceArg = pretty ? String::New("\t") : Undefined();
	
	// Call the JSON.stringify() function
	
	Handle<Value> args[] = { value.value, Undefined(), spaceArg };
	Local<Value> resultValue = jsonStringify->Call(mainContext->Global(), 3, args);
	
	catchException(tryCatch);
	
	// Return string
	
	Local<String> resultString = Local<String>::Cast(resultValue);
	String::Utf8Value resultUtf(resultString);
	return string(*resultUtf);
}


void ScriptManager::catchException(const TryCatch &tryCatch)
{
	// Check if an error has occurred
	
	if (tryCatch.HasCaught())
	{
		HandleScope handleScope;
		
		// Throw an exception with the TryCatch message
		
		Local<Message> message = tryCatch.Message();
		Local<String> messageString = message->Get();
		String::Utf8Value messageUtf(messageString);
		
		stringstream output;
		output << *messageUtf << " at ";
		output << message->GetLineNumber() << ":";
		output << message->GetEndColumn();
		
		// std::cerr << output.str() << std::endl;
		throw bit::Exception(*messageUtf);
	}
}
