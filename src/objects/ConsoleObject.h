/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ConsoleObject_h
#define BitRPG_ConsoleObject_h

#include "../ScriptObject.h"


namespace bit
{
	class ConsoleObject : public ScriptObject
	{
	public:
		v8::Local<v8::Object> createInstance();
		
		static v8::Handle<v8::Value> log(const v8::Arguments &args);
		static v8::Handle<v8::Value> input(const v8::Arguments &args);
	};
}


#endif
