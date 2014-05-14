/**
 *	Statement.h
 *
 *	Class for executing prepared statements
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
class Statement : public Php::Base
{
private:
	
	/**
	 *  The actual statement object
	 *  @var	std::shared_ptr
	 */
	std::shared_ptr<React::MySQL::Statement> _statement;
	
public:
	
	/**
	 *  Constructor
	 */
	Statement() {}
	
	/**
	 *  Pass in an existing statement
	 *  @var	React::MySQL::Statement
	 */
	Statement(const std::shared_ptr<React::MySQL::Statement> &statement) : _statement(statement) {}
	
	/**
	 *  Destructor
	 */
	virtual ~Statement() {}
	
       /**
     	*  Constructor
     	*
     	*  @param  connection  the connection to run the statement on
     	*  @param  statement   the statement to execute
     	*  @param  callback    the callback to inform of success or failure
     	*/
    	void __construct(Php::Parameters &parameters);
    
       /**
     	*  Execute statement with given parameters
     	*
     	*  @param  parameters  input parameters
     	*  @param  count       number of parameters
     	*  @param  callback    callback to inform of success or failure
     	*/
	void execute(Php::Parameters &parameters);
	
       /**
     	*  Execute statement query with given parameters
     	*
     	*  @param  callback    callback to inform of success or failure
     	*/
    	void executeQuery(Php::Parameters &parameters);
};

/**
 *  End of namespace
 */	
}
