<?php

/**
 *	REACT-PHP-CPP test file
 * 
 *  @copyright 2014 Copernica BV
 */
 
// create the event loop
$loop = new Async\Loop();

// create a resolver
$resolver = new Async\Resolver($loop);

// fetch all IPs
$resolver->ip("www.copernica.com", 4, function() {
	
	echo("IPs:\n");
	
	return false;
});

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
/*$reader1 = $loop->onReadable('STDIN_FILENO', function() {
	
	echo("Input is available at first reader\n");
	
	return false;
});

// notify us when input is available -- alternative way
$reader2 = new Async\ReadWatcher($loop, 'STDIN_FILENO', function() {
	
	echo("Input is available at second reader\n");
	
	return false;
});*/

// the current time
echo($loop->now()."\n");

// run the event loop
$loop->run();

