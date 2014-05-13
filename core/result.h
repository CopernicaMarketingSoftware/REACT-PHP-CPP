/**
 *	Result.h
 *
 *	Class representing a MySQL result set
 *
 *	@copyright 2014 Copernica BV
 */
 
/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>
#include <reactcpp/mysql.h>
#include <iostream>
#include "resultrow.h"

/**
 *	Set up namespace
 */
namespace ReactPhp {
	
/**
 *	Class definition
 */
class Result : public Php::Base, public Php::Traversable
{
private:
	/**
	 *  The actual result object
	 *  @var React::MySQL::Result
	 */
	React::MySQL::Result _result;
	
public:

	class ResultIterator : public Php::Iterator
	{
	private:
	/**
	 *  The result that is being iterated over
	 *  This is a pointer to the actual result
	 *  @var React::MySQL::Result
	 */
	React::MySQL::Result *_result;
			
	/**
	 *  The current position in the result set
	 *  @var int
	 */
	int _current = 0;
			
	public:
		/**
		 * 	Constructor
		 */
		ResultIterator();
		
		/**
		 *  Constructor
		 *  @param  object      The Php::Base object that is being iterated over
		 *  @param  result		The result from the database query
		 */
		ResultIterator(Result *object, React::MySQL::Result *result) :
			Php::Iterator(object), _result(result) {}
						
		/**
		 * 	Destructor
		 */
		virtual ~ResultIterator() {}
					
		/**
		 *  Is the iterator on a valid position
		 *  @return bool
		 */
		virtual bool valid() override
		{
			// the iterator is valid as long as the current position points
			// to a valid row
			return (unsigned int)_current < _result->size();
		}
				
		/**
		 *  The value at the current position
		 *  @return Php::Object
		 */
		virtual Php::Value current() override
		{
			// create an instance of a single row
			ResultRow *row = new ResultRow(_result->operator[](_current));
						
			// return the PHP object
			return Php::Object("Async\\ResultRow", row);
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
	Result();
	
	/**
	 *  Pass in an existing result
	 *  @param	result		Movable result object
	 */
	Result(React::MySQL::Result &&result) : _result(std::move(result)) {}
	
	/**
	 *  Destructor
	 */
	virtual ~Result() {}
	
	/**
     *  Get the iterator
     *  @return Php::Iterator
     */
    virtual Php::Iterator *getIterator() override
	{
		// construct a new result iterator on the heap
		// the (PHP-CPP library will delete it when ready)
		return new ResultIterator(this, &_result);
	}

	/**
	 * 	Retrieve row at given offset
	 */
	void fetchRow(Php::Parameters &params);

	/**
     *  Is this a valid result?
     */
    Php::Value valid();
	
	/**
     *  The number of rows affected
     */
    size_t affectedRows();
    
    /**
     *  Get the number of rows in this result
     */
    Php::Value size();
    
	/**
     *  Retrieve iterator for first row
     */
    Php::Value begin();

    /**
     *  Retrieve iterator past the end
     */
    Php::Value end();   
};
	
/**
 *	End namespace
 */
}
