/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Application_h
#define BitRPG_Application_h

#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class ScriptManager;
	class WindowManager;
	class StateManager;
	
	/**
	 * Initializes all components needed to launch the game
	 */
	class Application
	{
	public:
		/**
		 * Creates all managers needed in the Application
		 */
		Application();
		
		/**
		 * Starts the application
		 */
		void start();
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<ScriptManager> scriptManager;
		shared_ptr<WindowManager> windowManager;
		shared_ptr<StateManager> stateManager;
		
	private:
		void registerScriptObjects();
		void startScriptThread(const std::string &text);
	};
}


#endif
