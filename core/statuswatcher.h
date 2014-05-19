/**
 *  StatusWatcher.h
 *
 *  Wrapper around the REACT-CPP Status Watcher class
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
class StatusWatcher : public Php::Base
{
private:
	/**
	 *  The actual Status Watcher object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::StatusWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	StatusWatcher() {}
	
	/**
	 *  Pass in an existing Status Watcher
	 *  @var	std::shared_ptr<React::StatusWatcher>
	 */
	StatusWatcher(const std::shared_ptr<React::StatusWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~StatusWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 *  @param	pid
	 *  @param	trace
	 *  @param	callback
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameters
		Php::Value loopParam = parameters[0];
		Php::Value pid = parameters[1];
		Php::Value trace = parameters[2];
		Php::Value callback = parameters[3];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual timer-watcher
		_watcher = std::make_shared<React::StatusWatcher>(loop->mainLoop(), pid, trace, [callback](int, int) -> bool {
			
			// pass the call on to PHP
			callback();
			
			return true;
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
