/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapObject_h
#define BitRPG_MapObject_h

#include "BitRPG.h"
#include "ScriptObject.h"

#include <v8.h>
#include <string>


namespace bit
{
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
		
		ContentManagerPtr contentManager;
		ScriptManagerPtr scriptManager;
		StateManagerPtr stateManager;
		
	private:
		
	};
}

#endif
