/**
 *  ResultRow.cpp
 *
 *  Class with result data for a single MySQL row.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "resultrow.h"

/**
 *  Set up namespace
 */
namespace ReactPhp {

/**
 *  Get the number of fields in the row
 *  @return size_t
 */
size_t ResultRow::size() const
{
	return _resultRow.size();
}

/**
 *  Retrieve a field by index
 *
 *  This function throws an exception if no field
 *  exists under the given index (i.e. index
 *  is not smaller than size()).
 *
 *  @param  index   field index
 */
Php::Value ResultRow::operator [] (size_t index) const
{
	return (std::string)_resultRow.operator[](index);	
}

/**
 *  Retrieve a field by name
 *
 *  This function throws an exception if no field
 *  exists under the given key.
 *
 *  @param  key     field name
 */
Php::Value ResultRow::operator [] (const std::string &key) const
{
	return (std::string)_resultRow.operator[](key);
}

/**
 *  End of namespace
 */
}
