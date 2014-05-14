/**
 *  Result.cpp
 * 
 *  Class representing a MySQL result set
 * 
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "result.h"
#include <iostream>

/**
 *  Set up namespace
 */
namespace ReactPhp {
	
/**
 *  Retrieve row at given offset
 */
void Result::fetchRow(Php::Parameters &params)
{
	// retrieve the parameter
	int index = params[0];
		
	// check for valid input
	if(index > (int)_result.size() || index < 0) throw Php::Exception("Invalid result object");
		
	for (auto field : _result[index])
	{
		// print the rows to the screen
		std::cout << field.first << " => " << field.second << std::endl;
	}
}

/**
 *  Is this a valid result?
 */
Php::Value Result::valid()
{
	_result.valid();
		
	return true;
}
	
/**
 *  The number of rows affected
 */
size_t Result::affectedRows()
{
	return (int)_result.affectedRows();
}

/**
 *  Get the number of rows in this result
 */
Php::Value Result::size()
{
	return (int)_result.size();
}
	
/**
 *  Retrieve iterator for first row
 */
Php::Value Result::begin()
{
	_result.begin();
		
	return true;
}
 
/**
 *  Retrieve iterator past the end
 */
Php::Value Result::end()
{
	_result.end();
		
	return true;
}

/**
 *   End of namespace
 */	
}
