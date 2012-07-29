/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "StateManager.h"

#include <boost/thread/locks.hpp>

using namespace bit;
using namespace boost;


State &StateManager::getState()
{
	// These locks aren't really needed now, but a clearState() operation
	// may be added to block the rendering thread.
	
	lock_guard<mutex> stateLock(stateMutex);
	
	return *currentState;
}


void StateManager::changeState(StatePtr newState)
{
	lock_guard<mutex> stateLock(stateMutex);
	
	currentState = newState;
}
