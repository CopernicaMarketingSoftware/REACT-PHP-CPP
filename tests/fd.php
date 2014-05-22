<?php

/**
 *  REACT-PHP-CPP test file for file descriptors
 * 
 *  @copyright 2014 Copernica BV
 */

// create the event loop
$loop = new Async\Loop();

// Notify us when input is available on stdin
$reader1 = $loop->onReadable('STDIN_FILENO', function() {
	
	// report that input is available
	echo("Input is available at first reader\n");
	
	return false;
});

// Notify us when input is available on stdin -- alternative way: creating a reader object
$reader2 = new Async\ReadWatcher($loop, 'STDIN_FILENO', function() {
	
	// report that input is available
	echo("Input is available at second reader\n");
	
	return false;
});

// run the event loop
$loop->run();
