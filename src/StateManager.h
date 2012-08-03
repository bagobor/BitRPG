/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_StateManager_h
#define BitRPG_StateManager_h

#include "BitRPG.h"

#include <boost/thread/mutex.hpp>


namespace bit
{
	class StateManager
	{
	public:
		StatePtr getState();
		void changeState(StatePtr newState);
		
	private:
		StatePtr currentState;
		boost::mutex stateMutex;
	};
}

#endif
