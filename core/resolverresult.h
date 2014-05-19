/**
 *  ResolverResultResult.h
 *
 *  Implementation-only class that parses the result of IP and MX records
 *
 *  @copyright 2014 Copernica BV
 */
 
/**
 *  Set up namespace
 */
namespace ReactPhp{

/**
 *  Class definition
 */
class ResolverResult : public Php::Base, public Php::Traversable
{
private:
	/**
	 *  The actual MxResult object
	 *  @var React::Dns::MxResult
	 */
	React::Dns::MxResult _mxResult;
	
public:

	class ResolverResultIterator : public Php::Iterator
	{
	private:
	/**
	 *  The result that is being iterated over
	 *  This is a pointer to the actual result
	 *  @var React::MySQL::MxResult
	 */
	React::Dns::MxResult *_mxResult;
			
	/**
	 *  The current position in the result set
	 *  @var int
	 */
	int _current = 0;
			
	public:
		/**
		 *  Constructor
		 */
		ResolverResultIterator();
		
		/**
		 *  Constructor
		 *  @param  object      The Php::Base object that is being iterated over
		 *  @param  result		The result from the database query
		 */
		ResolverResultIterator(ResolverResult *object, React::Dns::MxResult *mxResult) :
			Php::Iterator(object), _mxResult(mxResult) {}
						
		/**
		 *  Destructor
		 */
		virtual ~ResolverResultIterator() {}
					
		/**
		 *  Is the iterator on a valid position
		 *  @return bool
		 */
		virtual bool valid() override
		{
			// the iterator is valid as long as the current position points
			// to a valid row
			return true;
		}
				
		/**
		 *  The value at the current position
		 *  @return Php::Object
		 */
		virtual Php::Value current() override
		{
			return _mxResult;
		}
				
		/**
		 *  The key at the current position
		 *  @return Value
		 */
		virtual Php::Value key() override
		{
			// this is simply the current index
			return _current;
		}
					
		/**
		 *  Move to the next position
		 */
		virtual void next() override
		{
			// move to the next position
			_current++;
		}
				
		/**
		 *  Rewind the iterator to the front position
		 */ 
		virtual void rewind() override
		{
			// go back to the beginning
			_current = 0;
		}
	};

	/**
	 *  Constructor
	 */
	ResolverResult() {}
	
	/**
	 *  Pass in an existing result
	 *  @param	result		Movable result object
	 */
	ResolverResult(React::Dns::MxResult &&mxResult) : _mxResult(std::move(mxResult)) {}
	
	/**
	 *  Destructor
	 */
	virtual ~ResolverResult() {}
	
       /**
     	*  Get the iterator
     	*  @return Php::Iterator
     	*/
    	virtual Php::Iterator *getIterator() override
	{
		// construct a new result iterator on the heap
		// the (PHP-CPP library will delete it when ready)
		return new ResolverResultIterator(this, &_mxResult);
	}
};

/**
 * End of namespace
 */
}
