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
	 *  @var	React::MainLoop
	 */
	React::MainLoop _loop;
	
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
	 *  Run the loop
	 * 	@return	bool
	 */
	Php::Value run()
	{
		_loop.run();
		return true;
	}
	
	/**
	 *  Stop the loop
	 * 	@return bool
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
		_loop.step();
		return true;
	}
	
	/**
	 *  Run a timeout after a while
	 * 	@param	timeout		Number of seconds (as a float) to wait for the timer to be called
	 *  @param	callback	Function that is called when timer expires
	 * 	@return	integer		Event ID
	 */
	Php::Value onTimeout(Php::Parameters &parameters);
	
	/**
	 *  Call a callback with a certain interval
	 *  @param	timeout		Number of seconds for each iteration
	 *  @param	callback	Function that is called every timeout seconds
	 *  @return	integer		Event ID
	 */
	Php::Value onInterval(Php::Parameters &parameters);
	

};

/**
 *	End namespace
 */
};
