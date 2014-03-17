/**
 *	Extension.cpp
 *
 *	Starting point for the event loop extension. In this file all
 *	classes and methods that are defined by the extension are
 *	registered to PHP
 *
 * 	@copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include "loop.h"
#include "timeoutwatcher.h"
#include "intervalwatcher.h"
#include "readwatcher.h"
#include "writewatcher.h"
#include "synchronizewatcher.h"

//using namespace std;
//using namespace ReactPhp;

// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("REACT-PHP-CPP","0.1");
        
        // create a namespace
        Php::Namespace async("Async");
        
        // the loop class
        Php::Class<ReactPhp::Loop> loop("Loop");
        loop.method("now", &ReactPhp::Loop::now);
        loop.method("run", &ReactPhp::Loop::run);
        loop.method("step", &ReactPhp::Loop::step);
        loop.method("stop", &ReactPhp::Loop::stop);
        loop.method("resume", &ReactPhp::Loop::resume);
        loop.method("suspendmak", &ReactPhp::Loop::suspend);
        loop.method("onTimeout", &ReactPhp::Loop::onTimeout);
        loop.method("onInterval", &ReactPhp::Loop::onInterval);
        loop.method("onReadable", &ReactPhp::Loop::onReadable);
        loop.method("onWritable", &ReactPhp::Loop::onWritable);
        loop.method("onSynchronize", &ReactPhp::Loop::onSynchronize);
      //  loop.method("database", &ReactPhp::Loop::database);
      //  loop.method("query", &ReactPhp::Loop::query);

        // the timer watcher class
        Php::Class<ReactPhp::TimeoutWatcher> timeoutWatcher("TimeoutWatcher");
        timeoutWatcher.method("__construct", &ReactPhp::TimeoutWatcher::__construct);
        timeoutWatcher.method("start", &ReactPhp::TimeoutWatcher::start);
        timeoutWatcher.method("cancel", &ReactPhp::TimeoutWatcher::cancel);
        timeoutWatcher.method("set", &ReactPhp::TimeoutWatcher::set);
      
		// the read watcher class
		Php::Class<ReactPhp::ReadWatcher> readWatcher("ReadWatcher");
		readWatcher.method("__construct", &ReactPhp::ReadWatcher::__construct);
		readWatcher.method("cancel", &ReactPhp::ReadWatcher::cancel);
		readWatcher.method("resume", &ReactPhp::ReadWatcher::resume);
		
		// the write watcher class
		Php::Class<ReactPhp::WriteWatcher> writeWatcher("WriteWatcher");
		writeWatcher.method("__construct", &ReactPhp::WriteWatcher::__construct);
		writeWatcher.method("cancel", &ReactPhp::WriteWatcher::cancel);
		writeWatcher.method("resume", &ReactPhp::WriteWatcher::resume);
		
		// the interval watcher class
		Php::Class<ReactPhp::IntervalWatcher> intervalWatcher("IntervalWatcher");
		intervalWatcher.method("__construct", &ReactPhp::IntervalWatcher::__construct);
		intervalWatcher.method("___construct", &ReactPhp::IntervalWatcher::___construct);
		intervalWatcher.method("start", &ReactPhp::IntervalWatcher::start);
        intervalWatcher.method("cancel", &ReactPhp::IntervalWatcher::cancel);
        intervalWatcher.method("set", &ReactPhp::IntervalWatcher::set);
        
		// the synchronize watcher class
		Php::Class<ReactPhp::SynchronizeWatcher> synchronizeWatcher("SynchronizeWatcher");
		synchronizeWatcher.method("__construct", &ReactPhp::SynchronizeWatcher::__construct);
		synchronizeWatcher.method("synchronize", &ReactPhp::SynchronizeWatcher::synchronize);
		synchronizeWatcher.method("cancel", &ReactPhp::SynchronizeWatcher::cancel);
		
        // add all classes to the namespace
        async.add(loop);
        async.add(timeoutWatcher);
        async.add(readWatcher);
        async.add(writeWatcher);
        async.add(intervalWatcher);
        async.add(synchronizeWatcher);
        
		// add the namespace to the extension
        extension.add(async);
        
        // return the extension module
        return extension.module();
    }
}


