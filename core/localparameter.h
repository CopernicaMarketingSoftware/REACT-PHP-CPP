/**
 *	LocalParameter.h
 *
 *	A parameter in a local prepared-statement-like query.
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
class LocalParameter : public Php::Base
{
private:
	/**
	 *  The actual Localparameter object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::MySQL::LocalParameter> _localParameter;
	
public:
	/**
	 *  Constructor
	 */
	LocalParameter() {}
	
	/**
	 *  Pass in an existing local parameter
	 *  @var	React::MySQL::LoacalParameter
	 */
	LocalParameter(const std::shared_ptr<React::MySQL::LocalParameter> &LocalParameter) : _localParameter(LocalParameter) {}
	
	/**
	 *  Destructor
	 */
	virtual ~LocalParameter() {}
	
	/**
	 *  Get access to the internal parameter object that is wrapped
	 *  by this PHP local parameter class
	 *  @return	React::MySQL::Parameter
	 */
	React::MySQL::LocalParameter *localParam()
	{
		React::MySQL::LocalParameter *_localParam = _localParameter.get();
		return _localParam;
	}
	
	/**
	 * 	Constructor
	 * 
	 * 	@param value	parameter value
	 */
	void __construct(Php::Parameters &parameters)
	{
		// retrieve the parameter
		const std::string value = parameters[0];
		
		_localParameter = std::make_shared<React::MySQL::LocalParameter>(value);
	}
};

/**
 *	End namespace
 */
}
