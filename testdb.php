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
/*$statement = new Async\Statement($connection, "INSERT INTO Persons". "(FirstName,LastName,Age)" .
"VALUES ('Francois', 'Truffaut',?),('Francis', 'Coppola', ?), ('David', 'Lean', ?)", function() {
	
	echo("Hi from statement!\n");
	
	return false;
});

// execute the statement
$statement->execute(function() {
	
	echo("Executing statement....\n");
	
	return false;
	
});

// execute the statement
/*$statement->executeQuery(function($res) {
	
	echo("Executing statement....\n");
	
	foreach ($res as $resultRow)
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
*/

// query the database
$connection->query("SELECT * FROM Persons LIMIT 2", function($result) {
	
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
	
	// alternative way -> iterate over the result set and fetch each individual row
/*	for ($i = 0; $i < $result->size(); $i++)
	{
		// wrap each row in curly braces
		echo("{\n");
		
		// fetch the row and dump it to the screen
		$result->fetchRow($i);
		 
		// close the row
		echo("}\n");
	}
*/	
	return false;
});

// run the event loop
$loop->run();

