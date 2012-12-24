/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_WindowManager_h
#define BitRPG_WindowManager_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class JSONValue;
	class Screen;
	
	/**	Manages the window and final graphics rendering of the game
	 */
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();
		
		/**	Opens a window with the given window configuration
		 */
		void openWindow(JSONValue &windowValue);
		void closeWindow();
		void run();
		
		shared_ptr<sf::RenderWindow> window;
		shared_ptr<Screen> activeScreen;
		
		sf::Vector2u screenSize;
		
	private:
		/**	Renders the current frame to the render window
		*/
		void render();
		
		/**	The zoom factor of the active screen rendered onto the window
			
			This equals the ratio of window pixels to screen pixels in each
			dimension.
		*/
		int zoom;
		
		/**	The reciprocal of the framerate
		*/
		float deltaTime;
	};
}

#endif
