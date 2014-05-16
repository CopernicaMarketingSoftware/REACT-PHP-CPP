/**
 *	ReadWatcher.h
 *
 *	Wrapper around the REACT-CPP Read watcher class
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
class ReadWatcher : public Php::Base
{
private:
	/**
	 *  The actual Read watcher object
	 * 	@var	std::shared_ptr
	 */
	std::shared_ptr<React::ReadWatcher> _watcher;
	
public:
	/**
	 *  Constructor
	 */
	ReadWatcher() {}
	
	/**
	 *  Pass in an existing Read watcher
	 *  @var	std::shared_ptr<React::ReadWatcher>
	 */
	ReadWatcher(const std::shared_ptr<React::ReadWatcher> &watcher) : _watcher(watcher) {}
	
	/**
	 *  Destructor
	 */
	virtual ~ReadWatcher() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 * 	@param	fd
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
		
		// create the actual read-watcher
		_watcher = std::make_shared<React::ReadWatcher>(loop->loop(), fd, [callback]() -> bool {
			
			// pass the call on to PHP
			callback();
			
			return true;
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
 * 	End of namespace
 */
}
