<?php
/**
 *	REACT-PHP-CPP test file
 * 
 *  @copyright 2014 Copernica BV
 */
 
// create the event loop
$loop = new React\Loop();

// set an interval
$loop->onInterval(1.0, function() {
	
	echo("timer expires\n");
	
});

// run the event loop
$loop->run();
