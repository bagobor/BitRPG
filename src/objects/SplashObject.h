/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_SplashObject_h
#define BitRPG_SplashObject_h

#include "../ScriptObject.h"

#include <v8.h>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class StateManager;
	class ScriptManager;
	
	class SplashObject : public ScriptObject
	{
	public:
		SplashObject();
		
		v8::Local<v8::Object> createInstance();
		
		// GameObject specific functions
		
		static v8::Handle<v8::Value> show(const v8::Arguments &args);
		static v8::Handle<v8::Value> wait(const v8::Arguments &args);
		
		void runScript(const std::string &filename);
		void splash(const std::string &filename, double fadeIn,
			double hold, double fadeOut);
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<StateManager> stateManager;
		shared_ptr<ScriptManager> scriptManager;
		
	private:
	};
}

#endif
