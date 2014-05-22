<?php

/**
 *  REACT-PHP-CPP test mysql connection file
 * 
 *  @copyright 2014 Copernica BV
 */

// create the event loop
$loop = new Async\Loop();

// establish a connection to MySQL
$connection = new Async\Connection($loop, "localhost", "root", "abc", "my_db", function() {
	
	echo("Connection established\n");
	
	return false;
});

// initialize a statement
$statement = new Async\Statement($connection, "SELECT * FROM Persons", function() {
	
	echo("Initializing query statement\n");
	
	return false;
});

// execute the statement
$statement->executeQuery(function($result) {
	
	echo("Executing the query statement:\n");
	
	// iterate over the result set
	foreach ($result as $resultRow)
	{
		// wrap each row in curly braces
		echo("{ ");
		
		// iterate over each individual row of the result set
		foreach ($resultRow as $resultField)
		{
			// and dump all the result fields to the screen
			echo("$resultField ");
		}
		
		// close the row
		echo("}\n");	
	}
	
	return false;	
});

// run the event loop
$loop->run();
