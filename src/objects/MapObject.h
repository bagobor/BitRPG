/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapObject_h
#define BitRPG_MapObject_h

#include "../ScriptObject.h"

#include <v8.h>
#include <string>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class ScriptManager;
	class StateManager;
	
	class MapObject : public ScriptObject
	{
	public:
		MapObject();
		
		v8::Local<v8::Object> createInstance();
		
		// MapObject specific functions
		
		static v8::Handle<v8::Value> load(const v8::Arguments &args);
		static v8::Handle<v8::Value> show(const v8::Arguments &args);
		
		void loadMap(const std::string &filename);
		void show();
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<ScriptManager> scriptManager;
		shared_ptr<StateManager> stateManager;
		
	private:
	};
}

#endif
