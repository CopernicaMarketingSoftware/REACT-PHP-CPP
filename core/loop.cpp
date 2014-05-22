/**
 *  Loop.cpp
 * 
 *  Implementation of the event loop
 * 
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <iostream>
#include "loop.h"
#include "timeoutwatcher.h"
#include "intervalwatcher.h"
#include "readwatcher.h"
#include "writewatcher.h"
#include "synchronizewatcher.h"
#include "signalwatcher.h"
#include "statuswatcher.h"

/**
 *  Set up namespace
 */
namespace ReactPhp {

/**
 * Function which is called the moment a file descriptor becomes readable
 * @param	fd			The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		ReadWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onReadable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onReadable function
	auto reader = _loop.onReadable(fd, [callback]() -> bool{
		
		// call the PHP callback
		callback();
		
		return true;
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\ReadWatcher", new ReadWatcher(reader));
}

/**
 * Function which is called the moment a file descriptor becomes writable
 * @param	fd			The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		WriteWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onWritable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	//call the Loop::onReadable function
	auto writer = _loop.onWritable(fd, [callback]() -> bool {
		
		//call the PHP callback
		callback();
		
		return true;
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\WriteWatcher", new WriteWatcher(writer));
}

/**
 * Register a synchronize function
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		SynchronizeWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onSynchronize(Php::Parameters &parameters)
{
	// the callback function
	Php::Value callback = parameters[0];
	
	//call the Loop::onReadable function
	auto synchronizer = _loop.onSynchronize([callback]() -> bool {
		
		//call the PHP callback
		callback();
		
		return true;
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\SynchronizeWatcher", new SynchronizeWatcher(synchronizer));
}

/**
 *  Run a timeout after a while
 *  @param	timeout		Number of seconds (as a float) to wait for the timer to be called
 *  @param	callback	Function that is called when timer expires
 *  @return	object		TimeoutWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onTimeout(Php::Parameters &parameters)
{
	// the timeout, and the callback function
	React::Timestamp timeout = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onTimeout function
	auto timer = _loop.onTimeout(timeout, [callback]() -> bool {
		
		// call the PHP callback
		callback();
		
		return true;
	});

	// create a new PHP object, and return that
	return Php::Object("Async\\TimeoutWatcher", new TimeoutWatcher(timer));
}

/**
 *  Call a callback with a certain interval
 *  @param	interval	Number of seconds for each iteration
 *  @param	callback	Function that is called every timeout seconds
 *  @return	object		IntervalWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onInterval(Php::Parameters &parameters)
{
	// the interval, and the callback function
	React::Timestamp interval = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onInterval function
	auto watcher = _loop.onInterval(interval, interval, [callback]() -> bool {
		
		// call the PHP callback
		callback();
		
		return true;
	});

	// create a new PHP object, and return that
	return Php::Object("Async\\IntervalWatcher", new IntervalWatcher(watcher));
}

/**
 *  Register a function that is called the moment a signal is fired.
 *  @param signum The signal
 *  @param callback Function that is called the moment the signal is caught
 *  @return Object that can be used to stop checking for signals
 */
Php::Value Loop::onSignal(Php::Parameters &parameters)
{
	// the signal and the callback function
	int signum = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the MainLoop::onSignal function
	auto signal = _mainLoop.onSignal(signum, [callback] () -> bool {
		
		// call the PHP callback
		callback();
		
		return false;
	});
	
	return Php::Object("Async\\SignalWatcher", new SignalWatcher(signal));
}

/**
 *  Register a function that is called the moment the status of a child changes
 *  @param pid The child PID
 *  @param trace Monitor for all status changes (true) or only for child exits (false)
 *  @param callback Function that is called the moment the child changes status
 *  @return Object that can be used to stop checking for status changes
 */
Php::Value Loop::onStatusChange(Php::Parameters &parameters)
{
	// the pid, trace and callback function
	Php::Value pid = parameters[0];
	Php::Value trace = parameters[1];
	Php::Value callback = parameters[2];
	
	// call the MainLoop::onStatusChange function
	auto status = _mainLoop.onStatusChange(pid, trace, [callback] (int, int) -> bool {
		
		// call the PHP callback
		callback();
		
		return true;
	});
	
	return Php::Object("Async\\StatusWatcher", new StatusWatcher(status));
}
/**
 *  End of namespace
 */
}

