/**
 *	ResultRow.h
 *
 *	Class with result data for a single MySQL row
 *
 *	@copyright 2014 Copernica BV
 */
 
/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>
#include <reactcpp/mysql.h>
#include "resultfield.h"
#include <iostream>

/**
 *	Set up namespace
 */
namespace ReactPhp {
	
/**
 *	Class definition
 */
class ResultRow : public Php::Base, public Php::Traversable
{
private:
	/**
	 *  The actual resultRow object
	 *  @var	React::MySQL::ResultRow
	 */
	React::MySQL::ResultRow _resultRow;
	
public:
	
	class ResultRowIterator : public Php::Iterator
	{
	private:
	/**
	 *  The result that is being iterated over
	 *  This is a pointer to the actual result
	 *  @var React::MySQL::Result
	 */
	React::MySQL::ResultRow *_resultRow;
			
	/**
	 *  The current position in the result set
	 *  @var int
	 */
	int _current = 0;
			
	public:
		/**
		 * 	Constructor
		 */
		ResultRowIterator();
		
		/**
		 *  Constructor
		 *  @param  object      The Php::Base object that is being iterated over
		 *  @param  result		The result from the database query
		 */
		ResultRowIterator(ResultRow *object, React::MySQL::ResultRow *resultRow) :
			Php::Iterator(object), _resultRow(resultRow) {}
						
		/**
		 * 	Destructor
		 */
		virtual ~ResultRowIterator() {}
					
		/**
		 *  Is the iterator on a valid position
		 *  @return bool
		 */
		virtual bool valid() override
		{
			// the iterator is valid as long as the current position points
			// to a valid field
			return (unsigned int)_current < _resultRow->size();
		}
				
		/**
		 *  The value at the current position
		 *  @return Value
		 */
		virtual Php::Value current() override
		{
			// create an instance of a single field
			auto field = _resultRow->operator[](_current);
			
			// return the field
			return (std::string)field;
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
	 * 	Constructor
	 */
	ResultRow();
		
	/**
	 *  Pass in an existing resultRow
	 *  @var	React::MySQL::ResultRow
	 */
	ResultRow(React::MySQL::ResultRow &&resultRow) : _resultRow(std::move(resultRow)) {}
	
	/**
	 *  Destructor
	 */
	virtual ~ResultRow() {}
	
       /**
     	*  Get the iterator
     	*  @return Php::Iterator
     	*/
	virtual Php::Iterator *getIterator() override
    	{
        	// construct a new result iterator on the heap
        	// the (PHP-CPP library will delete it when ready)
        	return new ResultRowIterator(this, &_resultRow);
    	}
    
       /**
     	*  Get the number of fields in the row
     	*  @return size_t
     	*/
    	size_t size() const;

       /**
     	*  Retrieve a field by index
     	*
     	*  This function throws an exception if no field
	*  exists under the given index (i.e. index
     	*  is not smaller than size()).
     	*
     	*  @param  index   field index
     	*/
    	Php::Value operator [] (size_t index) const;

       /**
     	*  Retrieve a field by name
     	*
     	*  This function throws an exception if no field
     	*  exists under the given key.
     	*
     	*  @param  key     field name
     	*/
    	Php::Value operator [] (const std::string &key) const; 
};

/**
 * 	End namespace
 */
}
