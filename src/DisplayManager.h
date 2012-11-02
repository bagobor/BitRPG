/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_DisplayManager_h
#define BitRPG_DisplayManager_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class EventManager;
	class StateManager;
	class JSONValue;
	
	/**
	 * Manages the window and final graphics rendering of the game
	 */
	class DisplayManager
	{
	public:
		DisplayManager();
		~DisplayManager();
		
		/**
		 * Opens a window with the given window configuration
		 */
		void openWindow(JSONValue &windowValue);
		void closeWindow();
		void run();
		
		shared_ptr<EventManager> eventManager;
		shared_ptr<StateManager> stateManager;
		shared_ptr<sf::RenderWindow> window;
		
	private:
		void render();
		
		int zoom;
		float deltaTime;
		
		boost::shared_ptr<sf::View> windowView;
	};
}

#endif
