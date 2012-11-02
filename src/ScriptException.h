/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ScriptException_h
#define BitRPG_ScriptException_h

#include <v8.h>


namespace bit
{
	/**
	 * Whenever a ScriptException is thrown, it is the fault
	 * of the JavaScript code and should be ultimately caught
	 * in a JavaScript try block.
	 */
	class ScriptException
	{
	public:
		ScriptException(v8::Handle<v8::Value> exception);
		~ScriptException();
		
		v8::Local<v8::Value> getException();
		
	private:
		v8::Persistent<v8::Value> exception;
	};
}

#endif
