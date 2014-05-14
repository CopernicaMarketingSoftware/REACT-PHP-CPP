/**
 *	Parameter.h
 *
 *	Input parameter for MySQL prepared statement
 *
 *	@copyright 2014 Copernica BV
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
class Parameter : public Php::Base
{
private:
	/**
	 *  The actual parameter object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::MySQL::Parameter> _parameter;
	
public:
	
	/**
	 *  Constructor
	 */
	Parameter() {}
	
	/**
	 *  Pass in an existing parameter
	 *  @var	React::MySQL::Parameter
	 */
	Parameter(const std::shared_ptr<React::MySQL::Parameter> &parameter) : _parameter(parameter) {}
	
	/**
	 *  Destructor
	 */
	~Parameter() {}
	
	/**
	 *  Get access to the internal parameter object that is wrapped
	 *  by this PHP parameter class
	 *  @return	React::MySQL::Parameter
	 */
	React::MySQL::Parameter *param()
	{
		React::MySQL::Parameter *_param = _parameter.get();
		return _param;
	}
	
	/**
	 *  Constructor
	 * 
	 *  @param value	parameter value
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameter
		const std::string value = parameters[0];
		
		_parameter = std::make_shared<React::MySQL::Parameter>(value);
	}
};

/**
 *  End namespace
 */
}
