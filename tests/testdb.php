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


// query the database
$connection->query("SELECT * FROM Persons", function($result) {
	
	// iterate over the result set
	foreach ($result as $row)
	{
		// wrap each row in curly braces
		echo("{ ");
		
		// iterate over each individual row of the result set
		foreach ($row as $field)
		{
			// and dump all the result fields to the screen
			echo("$field ");
		}
		
		// close the row
		echo("}\n");
	}
	
	echo("\nAlternative way produces the following results:\n");
	
	// alternative way -> iterate over the result set and fetch each individual row
	for ($i = 0; $i < $result->size(); $i++)
	{
		// wrap each row in curly braces
		echo("{\n");
		
		// fetch the row and dump it to the screen
		$result->fetchRow($i);
		 
		// close the row
		echo("}\n");
	}
	
	return false;
});

// run the event loop
$loop->run();

