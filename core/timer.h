/**
 *	Timer.h
 *
 *	Implementation class that takes care of running a timer or interval
 *
 *	@copyright 2014 Copernica BV
 */

/**
 *	Set up namespace
 */
namespace PhpEvent {

/**
 *	Class definition
 */
class Timer : private Copernica::Event::TimerHandler
{
private:
	/**
	 *  The copernica timer
	 * 	@var	Copernica::Event::TimerWatcher
	 */
	Copernica::Event::TimerWatcher _timer;
	
	/**
	 *  The PHP callback that gets called when the timer expires
	 *  @var	Php::Value
	 */
	Php::Value _callback;

	/**
	 *  Method that is called when timer expires
	 */
	virtual void onExpired() override
	{
		// call the PHP callback
		_callback();
	}

public:
	/**
	 *  Constructor
	 *  @param	loop		The event loop
	 *  @param	timeout		Initial timeout
	 *  @param	interval	Interval after initial timeout
	 *  @param	callback	The callback to call
	 */
	Timer(Copernica::Event::Loop *loop, ev_tstamp timeout, ev_tstamp interval, Php::Value callback) :
		_timer(timeout, interval, this), _callback(callback)
	{
		// add the timer to the loop
		loop->add(&_timer);
	}
	
	/**
	 *  Destructor
	 */
	virtual ~Timer()
	{
	}
};

/**
 *	End namespace
 */
}

