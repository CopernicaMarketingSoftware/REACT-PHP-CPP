/**
 *  Loop.cpp
 * 
 *  Implementation of the event loop
 * 
 * 	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "loop.h"
//#include "timer.h"


/**
 *	Set up namespace
 */
namespace ReactPhp {

/**
 *  Run a timeout after a while
 * 	@param	timeout		Number of seconds (as a float) to wait for the timer to be called
 *  @param	callback	Function that is called when timer expires
 * 	@return	integer		Event ID
 */
Php::Value Loop::onTimeout(Php::Parameters &parameters)
{
	// the timeout, and the callback function
	React::Timestamp timeout = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onTimeout function
	auto watcher = _loop.onTimeout(timeout, [callback]() {
		
		// call the PHP callback
		callback();
	});

	// for now, we return true
	return true;
}

/**
 *  Call a callback with a certain interval
 *  @param	timeout		Number of seconds for each iteration
 *  @param	callback	Function that is called every timeout seconds
 *  @return	integer		Event ID
 */
Php::Value Loop::onInterval(Php::Parameters &parameters)
{
	// the interval, and the callback function
	React::Timestamp interval = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onInterval function
	auto watcher = _loop.onInterval(interval, interval, [callback]() {
		
		// call the PHP callback
		callback();
	});

	// for now, we return true
	return true;
}

/**
 *  End namespace
 */
}

