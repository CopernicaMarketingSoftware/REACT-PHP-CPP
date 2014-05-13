/**
 *  Statement.cpp
 * 
 *  Class for executing prepared statements
 * 
 * 	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "statement.h"
#include "connection.h"
#include "parameter.h"
#include "result.h"

/**
 *	Set up namespace
 */
namespace ReactPhp {

/**
 *  Constructor
 *
 *  @param  connection  the connection to run the statement on
 *  @param  statement   the statement to execute
 *  @param  callback    the callback to inform of success or failure
 */
void Statement::__construct(Php::Parameters &parameters)
{
	// retrieve the parameters
	Php::Value connectionParam = parameters[0];
	Php::Value state = parameters[1];
	Php::Value callback = parameters[2];
	
	// get the actual base objects
	Connection *connection = (Connection *)connectionParam.implementation();
	
	// create the actual statement
	_statement = std::make_shared<React::MySQL::Statement>(connection->conn(), state, [callback] (React::MySQL::Statement *statement, const char *error) {
		
		// check for possible errors
		if (error) throw Php::Exception(error);
        
        // call the PHP callback
        callback();	
	});
}
	
/**
 *  Execute statement with given parameters
 *
 *  @param  parameters  input parameters
 *  @param  count       number of parameters
 *  @param  callback    callback to inform of success or failure
 */
void Statement::execute(Php::Parameters &parameters)
{
	// retrieve the parameters
	Php::Value callback = parameters[0];
	
	// get the actual base objects
	//Parameter *parameter = (Parameter *)parameterParam.implementation();
	
	// call the React::MySQL::Statement execute function
	_statement->execute([callback](React::MySQL::Result&& result, const char *error) {
		
		// check for possible errors
		if (error) throw Php::Exception(error);
        
        // call the PHP callback
		callback();
	});
}

/**
 *  Execute statement query with given parameters
 *
 *  @param  callback    callback to inform of success or failure
 */
void Statement::executeQuery(Php::Parameters &parameters)
{
	// retrieve the parameters
	Php::Value callback = parameters[0];
	
	// call the React::MySQL::Statement execute function
	_statement->execute([callback](React::MySQL::Result&& result, const char *error) {
	
		// check if there is a query error
		if (error) throw Php::Exception(error);
		
		// wrap the result in a PHP object
		Result *object = new Result(std::move(result));

		// call the PHP callback
		callback(Php::Object("Async\\Result", object));	
	});

}
	
/**
 *  End namespace
 */
}
