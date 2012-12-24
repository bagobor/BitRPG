/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#ifndef BitRPG_Counter_h
#define BitRPG_Counter_h

#include "ScriptObject.h"
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>


namespace bit
{
	class Counter : public ScriptObject
	{
	public:
		Counter(const std::string name);
		v8::Local<v8::Object> createInstance();
		
		static v8::Handle<v8::Value> countdown(const v8::Arguments &args);
		void countdownFrom(int seconds);
		
	private:
		std::string name;
		
		boost::condition_variable cond;
		boost::mutex mutex;
		bool paused;
	};
}

#endif
