/**
 * 	Loop.cpp
 * 
 * 	Implementation of the event loop
 * 
 * 	@copyright 2014 Copernica BV
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

/**
 * Set up namespace
 */
namespace ReactPhp {

/**
 * Function which is called the moment a file descriptor becomes readable
 * @param	fd		The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		ReadWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onReadable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	//call the Loop::onReadable function
	auto reader = _loop.onReadable(fd, [callback]() {
		
		//call the PHP callback
		callback();
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\ReadWatcher", new ReadWatcher(reader));
}

/**
 * Function which is called the moment a file descriptor becomes writable
 * @param	fd		The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		WriteWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onWritable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	//call the Loop::onReadable function
	auto writer = _loop.onWritable(fd, [callback]() {
		
		//call the PHP callback
		callback();
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
	auto synchronizer = _loop.onSynchronize([callback]() {
		
		//call the PHP callback
		callback();
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
	auto timer = _loop.onTimeout(timeout, [callback]() {
		
		// call the PHP callback
		callback();
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
	auto watcher = _loop.onInterval(interval, interval, [callback]() {
		
		// call the PHP callback
		callback();
	});

	// create a new PHP object, and return that
	return Php::Object("Async\\IntervalWatcher", new IntervalWatcher(watcher));
}

/**
 *  End namespace
 */
}

