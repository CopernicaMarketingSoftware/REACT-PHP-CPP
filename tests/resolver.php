<?php

/**
 *	REACT-PHP-CPP test file for the resolver
 * 
 *  @copyright 2014 Copernica BV
 */
 
// create the event loop
$loop = new Async\Loop();

// create a resolver
$resolver = new Async\Resolver($loop);

// fetch all IPs
$resolver->ip("www.copernica.com", function() {
	
	echo("IPs: ");
	
	return false;
});

// fetch all MX records
$resolver->mx("copernica.com", function() {
	
	echo("MX records:\n");
	
	return false;
});

// run the event loop
$loop->run();
