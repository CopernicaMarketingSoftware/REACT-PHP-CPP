<?php

/**
 *	REACT-PHP-CPP test file
 * 
 *  	@copyright 2014 Copernica BV
 */
 
// create the event loop
$loop = new Async\Loop();

// set a timeout
$timer1 = $loop->onTimeout(1, function() {
	
	echo("timeout 1 expires\n");
	
	return false;
	
});

// set a timeout
$timer2 = new Async\TimeoutWatcher($loop, 2, function() {

	echo("timeout 2 expires\n");
	
	return false;
});

// the current time
echo($loop->now()."\n");

// run the event loop
$loop->run();
