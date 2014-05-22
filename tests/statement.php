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
	
	// report after the connection has been established
	echo("Connection established\n");
	
	return false;
});

// initialize a statement
$statement = new Async\Statement($connection, "INSERT INTO Persons". "(FirstName, LastName)" .
"VALUES ('Francois', 'Truffaut'), ('Francis', 'Coppola'), ('David', 'Lean')", function() {
	
	echo("Initializing statement\n");
	
	return false;
});

// execute the statement
$statement->execute(function() {
	
	echo("Statement was executed\n");
	
	return false;	
});

// run the event loop
$loop->run();
