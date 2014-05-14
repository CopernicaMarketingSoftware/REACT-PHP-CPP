/**
 *	SynchronizeWatcher.h
 *
 *	Wrapper around the REACT-CPP Synchronize watcher class
 *
 *	@copyright 2014 Copernica BV
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
class SynchronizeWatcher : public Php::Base
{
private:
	/**
	 *  The actual Synchronize watcher object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::SynchronizeWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	SynchronizeWatcher() {}
	
	/**
	 *  Pass in an existing Synchronize watcher
	 *  @var	std::shared_ptr<React::SynchronizeWatcher>
	 */
	SynchronizeWatcher(const std::shared_ptr<React::SynchronizeWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~SynchronizeWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 *  @param	fd
	 *  @param	callback
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameters
		Php::Value loopParam = parameters[0];
		Php::Value callback = parameters[1];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual synchronize-watcher
		_watcher = std::make_shared<React::SynchronizeWatcher>(loop->loop(), [callback]() {
			
			// pass the call on to PHP
			callback();
		});
	}
	
       /**
     	*  Synchronize with the event loop
    	*  @return bool
     	*/
    	Php::Value synchronize()
    	{
		return _watcher->synchronize();
	}
	
       /**
     	*  Cancel the synchronizer
     	*  @return bool
     	*/
    	Php::Value cancel()
    	{
		return _watcher->cancel();
	}
     
};

/**
 *   End of namespace
 */
}

