/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#include "Counter.h"
#include <iostream>
#include <boost/thread/thread.hpp>

using namespace bit;
using namespace v8;


Counter::Counter(const std::string name)
{
	this->name = name;
}


Local<Object> Counter::createInstance()
{
	HandleScope handleScope;
	
	// Create the function template
	
	Local<FunctionTemplate> functionTemplate = FunctionTemplate::New();
	functionTemplate->SetClassName(String::New("Counter"));
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	// Add functions to object instance
	
	Local<FunctionTemplate> countdownTemplate = FunctionTemplate::New(countdown);
	Local<Function> countdownFunction = countdownTemplate->GetFunction();
	objectInstance->Set(String::New("countdown"), countdownFunction);
	
	return handleScope.Close(objectInstance);
}




Handle<Value> Counter::countdown(const Arguments &args)
{
	Counter *p = static_cast<Counter *>(extractHolder(args));
	int seconds = extractInteger(args, 0);
	
	// Launch the function in a new thread
	
	boost::thread countdownThread(&Counter::countdownFrom, p, seconds);
	
	// Block until countdown is finished
	
	boost::unique_lock<boost::mutex> lock(p->mutex);
	p->paused = true;
	
	while (p->paused)
	{
		printf("Waiting...\n");
		p->cond.wait(lock);
	}
	
	return Undefined();
}


void Counter::countdownFrom(int seconds)
{
	for (int countdown = seconds; countdown >= 0; countdown--)
	{
		printf("%s: %d\n", name.c_str(), countdown);
		
		// Sleep for DeltaTime
		
		boost::posix_time::milliseconds sleepTime(1000);
		boost::this_thread::sleep(sleepTime);
	}
	
	{
		boost::lock_guard<boost::mutex> lock(mutex);
		paused = false;
	}
	
	cond.notify_all();
}