/**
 *  TimeoutWatcher.h
 *
 *  Wrapper around the REACT-CPP Timeout watcher class
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>

/**
 *  Set up namespace
 */
namespace ReactPhp {

/**
 *  Class definition
 */
class TimeoutWatcher : public Php::Base
{
private:
	/**
	 *  The actual Timeout watcher object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::TimeoutWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	TimeoutWatcher() {}
	
	/**
	 *  Pass in an existing Timeout watcher
	 *  @var	std::shared_ptr<React::TimeoutWatcher>
	 */
	TimeoutWatcher(const std::shared_ptr<React::TimeoutWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~TimeoutWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 *  @param	timeout
	 *  @param	callback
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameters
		Php::Value loopParam = parameters[0];
		React::Timestamp timeout = parameters[1];
		Php::Value callback = parameters[2];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual timer-watcher
		_watcher = std::make_shared<React::TimeoutWatcher>(loop->loop(), timeout, [callback]() {
			
			// pass the call on to PHP
			callback();
		});
	}
	
	/**
	 *  Start the timer
	 *  This is only meaningful if the timer is not yet running
	 *  @return bool
	 */
	Php::Value start()
	{
		return _watcher->start();
	}
	
	/**
	 *  Cancel the timer
	 *  @return bool
	 */
	Php::Value cancel()
	{
		return _watcher->cancel();
	}
	
	/**
	 *  Set the timeout
	 *  @param	timeout
	 *  @return	bool
	 */
	Php::Value set(Php::Parameters &parameters)
	{
		return _watcher->set(parameters[0]);
	}
};

/**
 *  End of namespace
 */
}
