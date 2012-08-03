/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_GameObject_h
#define BitRPG_GameObject_h

#include "BitRPG.h"
#include "ScriptObject.h"

#include <boost/shared_ptr.hpp>
#include <v8.h>

class Launcher;


namespace bit
{
	class GameObject : public ScriptObject
	{
	public:
		GameObject();
		
		v8::Local<v8::Object> createInstance();
		
		// GameObject specific functions
		
		static v8::Handle<v8::Value> loadMap(const v8::Arguments &args);
		static v8::Handle<v8::Value> splash(const v8::Arguments &args);
		void splash(const std::string &filename, double fadeIn,
			double hold, double fadeOut);
		
		ContentManagerPtr contentManager;
		StateManagerPtr stateManager;
		
	private:
		
	};
}

#endif
