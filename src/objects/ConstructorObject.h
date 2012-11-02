/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ConstructorObject_h
#define BitRPG_ConstructorObject_h

#include "../ScriptObject.h"
#include <v8.h>


namespace bit
{
	/**
	 * Creates constructors for the scripting environment to utilize the
	 * "new" keyword for creating new JavaScript objects
	 */
	class ConstructorObject : public ScriptObject
	{
	public:
		v8::Local<v8::Object> createEntityConstructor();
		static v8::Handle<v8::Value> entityConstructor(const v8::Arguments &args);
	};
}

#endif
