/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_DisplayManager_h
#define BitRPG_DisplayManager_h

#include "BitRPG.h"

#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>


namespace bit
{
	/**
	 * Manages the window and final graphics rendering of the game
	 */
	class DisplayManager
	{
	public:
		DisplayManager();
		
		/**
		 * Opens a window with the given window configuration
		 */
		void openWindow(JSONValue &windowValue);
		void closeWindow();
		void run();
		
		EventManagerPtr eventManager;
		MapManagerPtr mapManager;
		boost::shared_ptr<sf::RenderWindow> window;
		
	private:
		void render();
		
		int zoom;
		bool running;
		
		boost::shared_ptr<sf::View> windowView;
	};
}

#endif
