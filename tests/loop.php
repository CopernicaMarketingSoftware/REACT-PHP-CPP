<?php

/**
 *	REACT-PHP-CPP test file
 * 
 *  @copyright 2014 Copernica BV
 */

// create the event loop
$loop = new Async\Loop();

// Set a timer
// This way the application is going to stop if
// it is in idle state for five seconds
$timer = new Async\TimeoutWatcher($loop, 5.0, function() {

	// report that the timer has expired
	echo("Timer expired\n");
	
	return false;
});

// Notify us when input is available on stdin
$reader = new Async\ReadWatcher($loop, 'STDIN_FILENO', function() use($timer) {
	
	// report that input is available
	echo("Input is available at reader\n");
	
	// read the input
	$stdin = fopen('php://stdin', 'r');
	$buffer = fgets($stdin);
	
	// print what was read
	echo("Input: $buffer\n");
	
	// set the timer again to five seconds
	echo("Timer was set again\n");
	$timer->set(5.0);
	
	// we also want to be notified for future readability events 
	return true;
});

// Set a handler to notify us when control+c is pressed
$handler = $loop->onSignal(SIGINT, function() use($loop, $timer, $reader) {
	
	// report that control+c was pressed
	echo("control+c detected");
	
	// Now the timer and the reader can be cancelled
	$timer->cancel();
	$reader->cancel();
	
	// In one second the application will be terminated
	$loop->onTimeout(1.0, function() {
	
		// report that the internal timer has expired
		echo("Internal timer expired\n");
	
		return false;
	});
	
	return false;
});

// run the event loop
$loop->run();
