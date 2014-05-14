/**
 *  	ResultField.h
 *
 *  	A single field from a single row from
 *  	a MySQL result set
 *
 *  	@copyright 2014 Copernica BV
 */
 
/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>
#include <reactcpp/mysql.h>

/**
 *  Set up namespace
 */
namespace ReactPhp {
	
/**
 *  Class definition
 */
class ResultField : public Php::Base
{
private:
	/**
	 *  The actual result field object
	 *  @var React::MySQL::ResultField
	 */
	React::MySQL::ResultField _resultField;
	
public:
	/**
	 *  Constructor
	 */
	ResultField();

	/**
	 *  Pass in an existing result field
	 *  @param resultField	Movable result field object
	 */
	ResultField(React::MySQL::ResultField &&resultField) : _resultField(std::move(resultField)) {}
	
	/**
	 *  Destructor
	 */
	virtual ~ResultField() {}
	
	/**
	 *  Get whether this field is NULL
	 */
    	bool isNULL() const
    	{
		return _resultField.isNULL();
	}	
	
       /**
     	*  Cast to a number
     	*
     	*  Note that if the value is NULL, this will yield 0.
     	*  To check for NULL values, use the isNULL function.
     	*
     	*  @throws std::invalid_argument   if this field does not contain a number
     	*  @throws std::out_of_range       if the value is too small or too big to fit in the requested type
     	*/
    	operator int8_t()   const {return _resultField.operator int8_t();}
    	operator uint16_t() const {return _resultField.operator uint16_t();}
    	operator int16_t()  const {return _resultField.operator int16_t();}
    	operator uint32_t() const {return _resultField.operator uint32_t();}
    	operator int32_t()  const {return _resultField.operator int32_t();}
    	operator uint64_t() const {return _resultField.operator uint64_t();}
    	operator int64_t()  const {return _resultField.operator int64_t();}
    	operator float()    const {return _resultField.operator float();}
    	operator double()   const {return _resultField.operator double();}

       /**
     	*  Cast to a string
	*
     	*  Note that if the value is NULL, this will yield
     	*  an empty string. To check for NULL values, use
     	*  the isNULL function.
     	*/
    	operator std::string() const
	{
		return _resultField.operator std::string();
	}
};

/**
 *  End of namespace
 */
}
