/**
 *	IntervalWatcher.h
 *
 *	Wrapper around the REACT-CPP Interval watcher class
 *
 *	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>

/**
 * Set up namespace
 */
namespace ReactPhp {

/**
 * Class definition
 */
class IntervalWatcher : public Php::Base
{
private:
	/**
	 *  The actual Interval watcher object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::IntervalWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	IntervalWatcher() {}
	
	/**
	 *  Pass in an existing Interval watcher
	 *  @var	std::shared_ptr<React::IntervalWatcher>
	 */
	IntervalWatcher(const std::shared_ptr<React::IntervalWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~IntervalWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 *  @param	Initial timeout
	 *  @param	Timeout interval period
	 *  @param	Function that is called when timer is expired
	 */
	 void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameters
		Php::Value loopParam = parameters[0];
		React::Timestamp initial = parameters[1];
		React::Timestamp interval = parameters[2];
		Php::Value callback = parameters[3];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual interval-watcher
		_watcher = std::make_shared<React::IntervalWatcher>(loop->loop(), initial, interval, [callback]() {
			
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
     	*  Set the timer to a new time
     	*  @param  initial     Initial timeout for the first timeout
     	*  @param  interval    Interval for subsequent timeouts
     	*  @return bool
     	*/
	Php::Value set(Php::Parameters &parameters)
	{
		return _watcher->set(parameters[0], parameters[1]);
	}
	
};

/**
 *  End namespace
 */
}
