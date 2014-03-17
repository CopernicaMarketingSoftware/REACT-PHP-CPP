<?php
/**
 *	REACT-PHP-CPP test file
 * 
 *  @copyright 2014 Copernica BV
 */
 
// create the event loop
$loop = new Async\Loop();

//// connect to and query a database
//$db = $loop->database("localhost", "root", "abc", "my_db", "SELECT * FROM Persons", function($result) {
//	
//	echo("hi\n");
//		
//	return false;
//	
//});

// set a timeout
$timer1 = $loop->onInterval(1, function() {
	
	echo("timer 1 expires\n");
	
	return false;
	
});

$timer2 = new Async\IntervalWatcher($loop, 1, 2, function() {

	echo("timer 2 expires\n");
	
	return false;
});

echo($loop->now()."\n");

// run the event loop
$loop->run();
