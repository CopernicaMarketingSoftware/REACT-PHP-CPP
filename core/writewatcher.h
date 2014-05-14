/**
 *	WriteWatcher.h
 *
 *	Wrapper around the REACT-CPP Write watcher class
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
class WriteWatcher : public Php::Base
{
private:
	/**
	 *  The actual Write watcher object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::WriteWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	WriteWatcher() {}
	
	/**
	 *  Pass in an existing Write watcher
	 *  @var	std::shared_ptr<React::WriteWatcher>
	 */
	WriteWatcher(const std::shared_ptr<React::WriteWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~WriteWatcher() {}
	
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
		int fd = parameters[1];
		Php::Value callback = parameters[2];
		
		// get the actual base object
		Loop *loop = (Loop *)loopParam.implementation();
		
		// create the actual write-watcher
		_watcher = std::make_shared<React::WriteWatcher>(loop->loop(), fd, [callback]() {
			
			// pass the call on to PHP
			callback();
		});
	}
	
       /**
     	*  Cancel the watcher
     	*  @return bool
     	*/
    	Php::Value cancel()
    	{
		return _watcher->cancel();
	}

       /**
     	*  Start/resume the watcher
     	*  @return bool
     	*/
    	Php::Value resume()
    	{
		return _watcher->resume();
	}
     
};

/**
 *   End of namespace
 */
}

