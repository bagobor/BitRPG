/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "AudioObject.h"
#include "../Exception.h"
#include "../ScriptException.h"

#include <string>

using namespace bit;
using namespace v8;
using namespace std;


AudioObject::AudioObject()
{
}


Local<Object> AudioObject::createInstance()
{
	HandleScope handleScope;
	
	Local<FunctionTemplate> functionTemplate = createClass("Audio");
	Local<ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
	
	// Create the methods
	
	addPrototypeMethod(prototypeTemplate, playMusic, "playMusic");
	addPrototypeMethod(prototypeTemplate, stopMusic, "stopMusic");
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	return handleScope.Close(objectInstance);
}


Handle<Value> AudioObject::playMusic(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		string musicFilename = extractString(args, 0);
		AudioObject *p = static_cast<AudioObject *>(extractHolder(args));
		
		// Call member function
		
		p->playMusic(musicFilename);
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


Handle<Value> AudioObject::stopMusic(const v8::Arguments &args)
{
	try
	{
		// Extract arguments
		
		AudioObject *p = static_cast<AudioObject *>(extractHolder(args));
		
		// Call member function
		
		p->stopMusic();
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
	return Undefined();
}


void AudioObject::playMusic(const string &filename)
{
	// Stop the music if needed
	
	stopMusic();
	
	currentMusic = contentManager->loadMusic(filename);
	
	currentMusic->play();
}


void AudioObject::stopMusic()
{
	// Stop the music if currently playing
	
	if (currentMusic)
		currentMusic->stop();
	
	currentMusic.reset();
}
