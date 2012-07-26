/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Application_h
#define BitRPG_Application_h

#include "BitRPG.h"


namespace bit
{
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
		
		ContentManagerPtr contentManager;
		ScriptManagerPtr scriptManager;
		DisplayManagerPtr displayManager;
	};
}


#endif
