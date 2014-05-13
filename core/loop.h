/**
 *	Loop.h
 *
 *	Main event loop class that runs the main PHP event loop
 *
 *	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>

/**
 *	Set up namespace
 */
namespace ReactPhp {

/**
 *	Class definition
 */
class Loop : public Php::Base
{
private:
	/**
	 *  The loop object from the React-CPP library
	 *  @var	React::Loop
	 */
	React::Loop _loop;
	
public:
	/**
	 *  Constructor
	 */
	Loop() {}
	
	/**
	 *  Destructor
	 */
	virtual ~Loop() {}
	
	/**
	 *  Get access to the internal loop object that is wrapped
	 *  by this PHP loop class
	 *  @return	React::Loop
	 */
	React::Loop *loop()
	{
		return &_loop;
	}
	
	/**
	 *  The current time
	 *  @return double
	 */
	Php::Value now()
	{
		return _loop.now();
	}
	
	/**
	 *  Run the loop
	 *  @return	bool
	 */
	Php::Value run()
	{
		return _loop.run();
	}
	
	/**
	 *  Stop the loop
	 *  @return bool
	 */
	Php::Value stop()
	{
		_loop.stop();
		return true;
	}
	
	/**
	 *  Run one iteration of the event loop
	 *  @return	bool
	 */
	Php::Value step()
	{
		return _loop.step();
	}

	/**
	 * Resume the loop after it was suspended
	 */
	void resume()
	{
		_loop.resume();
	}
	
	/**
	 *  Suspend the loop. While the loop is suspended, timers will not be processed,
	 *  and the time for the timers does not proceed. Once the loop is resumed, the
	 *  timers continue to run.
	 */
	void suspend()
	{
		_loop.suspend();	
	}
	
	/**
	 *  Run a timeout after a while
	 *  @param	timeout		Number of seconds (as a float) to wait for the timer to be called
	 *  @param	callback	Function that is called when timer expires
	 *  @return	object		TimeoutWatcher object that can be used for cancelling the timer
	 */
	Php::Value onTimeout(Php::Parameters &parameters);
	
	/**
	 *  Call a callback with a certain interval
	 *  @param	interval	Number of seconds for each iteration
	 *  @param	callback	Function that is called every timeout seconds
	 *  @return	object		IntervalWatcher object that can be used for cancelling the timer
	 */
	Php::Value onInterval(Php::Parameters &parameters);

	/**
 	 *  Function which is called the moment a file descriptor becomes readable
 	 *  @param	fd			The file descriptor
 	 *  @param	callback	Function that is called when the file descriptor is readable
 	 *  @return	object		ReadWatcher object that can be used for cancelling the timer
 	 */
	Php::Value onReadable(Php::Parameters &parameters);

	/**
	 *  Function which is called the moment a file descriptor becomes writable
	 *  @param	fd			The file descriptor
	 *  @param	callback	Function that is called when the file descriptor is readable
	 *  @return	object		WriteWatcher object that can be used for cancelling the timer
	 */
	Php::Value onWritable(Php::Parameters &parameters);

	/**
	 * Register a synchronize function
	 * @param	callback	Function that is called when the file descriptor is readable
	 * @return	object		SynchronizeWatcher object that can be used for cancelling the timer
	 */
	Php::Value onSynchronize(Php::Parameters &parameters);

};

/**
 *	End namespace
 */
};
