<?php

/**
 *  REACT-PHP-CPP timers test file 
 * 
 *  @copyright 2014 Copernica BV
 */

// create the event loop
$loop = new Async\Loop();
 
// Set a timer
// The timer will stop executing after 1.0 second
// and the callback function will notify us of that fact
$timer1 = $loop->onTimeout(1.0, function() {
	
	// report that the timer has expired
	echo("Timer 1 expired\n");
	
	return false;	
});

// Set a timer -- alternative way: creating a timer object
// The timer will stop executing after 2.0 seconds
// and the callback function will notify us of that fact
$timer2 = new Async\TimeoutWatcher($loop, 2.0, function() {

	// report that the timer has expired
	echo("Timer 2 expired\n");
	
	return false;
});

// The current time is displayed
echo("Current time: ".$loop->now()."\n");

// run the event loop
$loop->run();
