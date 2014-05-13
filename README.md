REACT-PHP-CPP
=============

Event loop library for PHP implemented in C++. Support for asynchronous non-blocking sockets, DNS lookups and database connections.

REACT-PHP-CPP utilizes the features of the PHP-CPP library and is a wrapper around the REACT-CPP and REACT-CPP-MYSQL libraries. Thus, it depends on the aforementioned libraries.


Event Loop
==========

The ReactPhp::Loop class is wrapped around the React::Loop class of the REACT-CPP library and runs the main PHP event loop. It contains methods to set timers, while it also utilizes callback functions which will be called whenever a filedescriptor becomes readable or writable.

Below is a typical application, where an instance of the event loop is created, which can then be used to register timers and filedescriptors that will be checked for readability:

```php

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

```

After the instance of the event loop is created, it should be run in order for everything to register the timers and filedescriptors.


Connection class
================

The ReactPhp::Connection class is wrapped around the React::MySQL::Connection class of the REACT-CPP-MYSQL library and it can be used to establish a connection to a MySQL daemon, as the following script illustrates: 

```php

// create the event loop
$loop = new Async\Loop();

// establish a connection to MySQL
$connection = new Async\Connection($loop, "mysql.example.org", "example user", "example password", "example database", function() {
	
	echo("Connection established\n");
	
	return false;
});

// run the event loop
$loop->run();

```

Again, an instance of the event loop needs to be created, so that the connection class can be used, whilst the callback function notifies us when the connection is established.


Statements
==========


