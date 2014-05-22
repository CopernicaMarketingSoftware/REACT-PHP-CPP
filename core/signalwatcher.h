/**
 *  SignalWatcher.h
 *
 *  Wrapper around the REACT-CPP Signal watcher class
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
class SignalWatcher : public Php::Base
{
private:
	/**
	 *  The actual Signal watcher object
	 * 	@var	std::shared_ptr
	 */
	std::shared_ptr<React::SignalWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	SignalWatcher() {}
	
	/**
	 *  Pass in an existing Signal watcher
	 *  @var	std::shared_ptr<React::SignalWatcher>
	 */
	SignalWatcher(const std::shared_ptr<React::SignalWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~SignalWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 *  @param	signum
	 *  @param	callback
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameters
		Php::Value loopParam = parameters[0];
		int signum = parameters[1];
		Php::Value callback = parameters[2];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual timer-watcher
		_watcher = std::make_shared<React::SignalWatcher>(loop->mainLoop(), signum, [callback]() -> bool {
			
			// pass the call on to PHP
			callback();
			
			return false;
		});
	}
	
	/**
	 *  Start the signal watcher
	 *  @return bool
	 */
	Php::Value start()
	{
		return _watcher->start();
	}
	
	/**
	 *  Cancel the signal watcher
	 *  @return bool
	 */
	Php::Value cancel()
	{
		return _watcher->cancel();
	}

};

/**
 *  End of namespace
 */
}
