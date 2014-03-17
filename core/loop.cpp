/**
 *  Loop.cpp
 * 
 *  Implementation of the event loop
 * 
 * 	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <iostream>
#include "loop.h"
#include "my_global.h" 
#include "mysql.h"
#include "timeoutwatcher.h"
#include "intervalwatcher.h"
#include "readwatcher.h"
#include "writewatcher.h"
#include "synchronizewatcher.h"

/**
 *	Set up namespace
 */
namespace ReactPhp {

/**
 * Function which is called the moment a file descriptor becomes readable
 * @param	fd			The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		ReadWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onReadable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	//call the Loop::onReadable function
	auto reader = _loop.onReadable(fd, [callback]() {
		
		//call the PHP callback
		callback();
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\ReadWatcher", new ReadWatcher(reader));
}

/**
 * Function which is called the moment a file descriptor becomes writable
 * @param	fd			The file descriptor
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		WriteWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onWritable(Php::Parameters &parameters)
{
	// the filedescriptor and the callback function
	int fd = parameters[0];
	Php::Value callback = parameters[1];
	
	//call the Loop::onReadable function
	auto writer = _loop.onWritable(fd, [callback]() {
		
		//call the PHP callback
		callback();
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\WriteWatcher", new WriteWatcher(writer));
}

/**
 * Register a synchronize function
 * @param	callback	Function that is called when the file descriptor is readable
 * @return	object		SynchronizeWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onSynchronize(Php::Parameters &parameters)
{
	// the callback function
	Php::Value callback = parameters[0];
	
	//call the Loop::onReadable function
	auto synchronizer = _loop.onSynchronize([callback]() {
		
		//call the PHP callback
		callback();
	});
	
	// create a new PHP object, and return that
	return Php::Object("Async\\SynchronizeWatcher", new SynchronizeWatcher(synchronizer));
}

/**
 *  Run a timeout after a while
 * 	@param	timeout		Number of seconds (as a float) to wait for the timer to be called
 *  @param	callback	Function that is called when timer expires
 * 	@return	object		TimeoutWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onTimeout(Php::Parameters &parameters)
{
	// the timeout, and the callback function
	React::Timestamp timeout = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onTimeout function
	auto timer = _loop.onTimeout(timeout, [callback]() {
		
		// call the PHP callback
		callback();
	});

	// create a new PHP object, and return that
	return Php::Object("Async\\TimeoutWatcher", new TimeoutWatcher(timer));
}

/**
 *  Call a callback with a certain interval
 *  @param	interval	Number of seconds for each iteration
 *  @param	callback	Function that is called every timeout seconds
 *  @return	object		IntervalWatcher object that can be used for cancelling the timer
 */
Php::Value Loop::onInterval(Php::Parameters &parameters)
{
	// the interval, and the callback function
	React::Timestamp interval = parameters[0];
	Php::Value callback = parameters[1];
	
	// call the Loop::onInterval function
	auto watcher = _loop.onInterval(interval, interval, [callback]() {
		
		// call the PHP callback
		callback();
	});

	// create a new PHP object, and return that
	return Php::Object("Async\\IntervalWatcher", new IntervalWatcher(watcher));
}

/**
 *	Function that connects to mysql database
 * 	@param 
 *	@return object that established the connection
 */
/*
Php::Value Loop::database(Php::Parameters &parameters)
{
	Php::Value server = parameters[0];
	Php::Value userName = parameters[1];
	Php::Value password = parameters[2];
	Php::Value dbName = parameters[3];
	Php::Value dbQuery = parameters[4];
	Php::Value callback = parameters[5];
	
	// Create a pointer to the MySQL instance
	MYSQL *connect;
	
	// Initialize the instance
    connect = mysql_init(NULL);
    
    // If instance didn't initialize, exit with error
    if(!connect)    
    {
        fprintf(stderr, "MySQL Initialization Failed");
        return 1;
    }
    
    // Now we will actually connect to the specific database
    connect = mysql_real_connect(connect, server, userName, password, dbName, 0, NULL, 0);
    
	// Check whether the connection to the mysql server is established
    if(connect)
    {
        std::cout << "Connection Succeeded" << std::endl;
    }
    else
    {
        std::cout << "Connection Failed" << std::endl;
    } 
    
    // Create a pointer to receive the return value
    MYSQL_RES *result; 
    
    // Assign variable for rows
    MYSQL_ROW row;  
    
    // Send a query to the database
    mysql_query(connect, dbQuery);
    
    // Create a counter for the rows
    // unsigned int i = 0; 
 
	// Receive the result and store it in res_set
    result = mysql_store_result(connect);
	
	// Create the count to print all rows
    // unsigned int numrows = mysql_num_rows(res_set); 

	// Lambda function which executes the query
	auto func = [&](Php::Parameters &parameters) { 
		
		// Receive the result and store it in result
		//result = mysql_store_result(connect);
		
		// Print all rows
		while ((row = mysql_fetch_row(result)) != NULL){
			
			std::cout << row[0] << " " << row[1] << std::endl; 
		}
		
		// Call the PHP callback
		callback(); 

	};
	
	// Call the lambda function
	func();
	
    // Close and shutdown
    mysql_close(connect);
    
    return connect;    
}
*/

/**
 * 	Function that performs a mysql query
 *	@param query		The query that needs to be performed on the database
 * 	@param callback		Function that is called when the query is ready to be executed
 * 	@return 
 */
/*Php::Value Loop::query(Php::Parameters &parameters)
{
	const char *dbQuery = parameters[0];
	Php::Value callback = parameters[1];
	
	auto db = Loop::database(Php::Parameters);
	
	// Create a pointer to recieve the return value
	MYSQL_RES *res_set;
	
	// Assign variable for rows
    MYSQL_ROW row;  
    mysql_query(db, dbQuery);
    
    // Send a query to the database
    // Create a counter for the rows
    unsigned int i = 0; 
 
	// Receive the result and store it in res_set
    res_set = mysql_store_result(db); 
 
	// Create the count to print all rows
    unsigned int numrows = mysql_num_rows(res_set); 
 
    // This while is to print all rows and not just the first row found
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        printf("%s\n",row[i] != NULL ?
        
        // Print the row data
        row[i] : "NULL"); 
    }
    
    // Close and shutdown
    mysql_close(db);   
    
    return 0;
}
*/

/**
 *  End namespace
 */
}

