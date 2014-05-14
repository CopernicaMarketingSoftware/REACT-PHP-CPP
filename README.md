REACT-PHP-CPP
=============

Event loop library for PHP implemented in C++. Support for asynchronous non-blocking sockets, DNS lookups and database connections.

REACT-PHP-CPP utilizes the features of the PHP-CPP library and is a wrapper around the REACT-CPP and REACT-CPP-MYSQL libraries. Thus, it depends on the aforementioned libraries.


Event Loop
==========

The ReactPhp::Loop class is wrapped around the React::Loop class of the REACT-CPP library and runs the main PHP event loop. It contains methods to set timers, while it also utilizes callback functions which will be called whenever a filedescriptor becomes readable or writable.

Below is a typical application, where an instance of the event loop is created, which can then be used to register timers and filedescriptors that will be checked for readability:

```php

<?php

// create the event loop
$loop = new Async\Loop();

// set a timeout
$timer1 = $loop->onTimeout(1, function() {
	
	echo("timeout 1 expires\n");
	
	return false;
	
});

// set a timeout -- alternative way
$timer2 = new Async\TimeoutWatcher($loop, 2, function() {

	echo("timeout 2 expires\n");
	
	return false;
});

// notify us when input is available
$reader1 = $loop->onReadable('STDIN_FILENO', function() {
	
	echo("Input is available at first reader\n");
	
	return false;
});

// notify us when input is available -- alternative way
$reader2 = new Async\ReadWatcher($loop, 'STDIN_FILENO', function() {
	
	echo("Input is available at second reader\n");
	
	return false;
});

// the current time
echo($loop->now()."\n");

// run the event loop
$loop->run();

?>

```

After the instance of the event loop is created, it should be run in order to register the timers and filedescriptors.


Connection class
================

The ReactPhp::Connection class is wrapped around the React::MySQL::Connection class of the REACT-CPP-MYSQL library and it can be used to establish a connection to a MySQL daemon, as the following script illustrates: 

```php

<?php

// create the event loop
$loop = new Async\Loop();

// establish a connection to MySQL
$connection = new Async\Connection($loop, "mysql.example.org", "example user", "example password", "example database", function() {
	
	echo("Connection established\n");
	
	return false;
});

// run the event loop
$loop->run();

?>

```

Again, an instance of the event loop needs to be created, so that the connection class can be used, whilst the callback function notifies us when the connection is established.


Statements
==========

Naturally, the next step after establishing a connection to a MySQL daemon is to use statements in order to define or manipulate a certain table in a database. 

To achieve this we can use the ReactPhp::Statement class, which is also wrapped around the React::MySQL::Statement class of the REACT-CPP-MYSQL library. First, a ReactPhp::Statement object needs to be created in the following fashion:

```php

// initialize a statement
$statement = new Async\Statement($connection, "INSERT INTO Persons (FirstName, LastName, Age) VALUES ('A', 'B', 10), ('C', 'D', 20), ('E', 'F', 30)", function() {
	
	echo("Statement initialized\n");
	
	return false;
});

```

From the above script it is obvious that the connection object is essential in order to create the statement object, since it constitutes the first parameter of the constructor. The second parameter is the actual MySQL statement and the third is the callback function, which notifies us that the statement can be executed.
For the execution to take place, we need to call the ReactPhp::Statement::execute() function. However, when the statement is a SELECT statement, the ReactPhp::Statement::executeQuery() function needs to be called. This happens, because in the case of a query a result object needs to be passed as a parameter in the callback function, so that the result set can be dumped to the screen:

```php

<?php

// create the event loop
$loop = new Async\Loop();

// establish a connection to MySQL
$connection = new Async\Connection($loop, "mysql.example.org", "example user", "example password", "example database", function() {
	
	echo("Connection established\n");
	
	return false;
});

// initialize a statement
$statement = new Async\Statement($connection, "INSERT INTO Persons (FirstName, LastName, Age) VALUES ('A', 'B', 10), ('C', 'D', 20), ('E', 'F', 30)", function() {
	
	echo("Statement initialized\n");
	
	return false;
});

// execute the statement
$statement->execute(function() {
	
	echo("Executing statement\n");
	
	return false;
	
});

// execute a query statement -- should only be used when we have a SELECT statement
$statement->executeQuery(function($result) {
	
	echo("Executing a SELECT statement\n");
	
	// iterate over the result set
	foreach ($result as $row)
	{
		// wrap the row in curly braces
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
	
	return false;	
});  

// run the event loop
$loop->run();

?>

```

That, practically, means that all MySQL statements are executed using the ReactPhp::Statement::execute() function, except the SELECT statement, which demands the ReactPhp::Statement::executeQuery() function to execute.
This is the reason why there is a separate function, which can be used for executing queries only, namely the ReactPhp::Connection::query() function. As a result, whenever a query has to be executed, the best approach is to use the aforementioned function and not the ReactPhp::Statement::executeQuery() function, since the former is more straightforward:

```php

<?php

// create the event loop
$loop = new Async\Loop();

// establish a connection to MySQL
$connection = new Async\Connection($loop, "mysql.example.org", "example user", "example password", "example database", function() {
	
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
	
	// alternative way -> iterate over the result set and dump each individual row to the screen
/*	for ($i = 0; $i < $result->size(); $i++)
	{
		// wrap each row in curly braces
		echo("{\n");
		
		// fetch the row and dump it to screen
		$result->fetchRow($i);
		
		// close the row
		echo("\n}\n");
	}
*/	
	return false;
});

// run the event loop
$loop->run();

?>

```

At this point, we should state that there are two ways to iterate over the result set produced by the query:
The first (used in the above script) uses the Php::Traversable class of the PHP-CPP library, which enables classes to be used in foreach loops, just like regular arrays.
The second way (in comments at the above script) iterates over each valid result and dumps each individual row to the screen, as long as the size of the result set is not exceeded.
The difference between these two ways lies in the fact that when using the foreach loop the results of the query are being printed in the PHP user space, whereas when using the for loop they are put to the screen through C++. As a consequence, we can say that the former way is a more 'valid' way to output the query results.
