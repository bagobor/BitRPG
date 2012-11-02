/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_GameObject_h
#define BitRPG_GameObject_h

#include "../ScriptObject.h"

#include <v8.h>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class StateManager;
	class ScriptManager;
	
	class GameObject : public ScriptObject
	{
	public:
		GameObject();
		
		v8::Local<v8::Object> createInstance();
		
		// GameObject specific functions
		
		/**
		 * Blocks the currently running script to run another script
		 * 
		 * Once the script is finished, the script calling this function
		 * resumes.
		 */
		static v8::Handle<v8::Value> runScript(const v8::Arguments &args);
		static v8::Handle<v8::Value> splash(const v8::Arguments &args);
		
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
