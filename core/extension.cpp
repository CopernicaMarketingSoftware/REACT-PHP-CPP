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
//#include "timer.h"

// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("REACT-PHP-CPP","0.1");
        
        // add the custom class ot the extension
        extension.add("React\\Loop", Php::Class<ReactPhp::Loop>({
            Php::Public("run", Php::Method<ReactPhp::Loop>(&ReactPhp::Loop::run)),
            Php::Public("step", Php::Method<ReactPhp::Loop>(&ReactPhp::Loop::step)),
            Php::Public("stop", Php::Method<ReactPhp::Loop>(&ReactPhp::Loop::stop)),
            Php::Public("onTimeout", Php::Method<ReactPhp::Loop>(&ReactPhp::Loop::onTimeout)),
            Php::Public("onInterval", Php::Method<ReactPhp::Loop>(&ReactPhp::Loop::onInterval)),
		}));
                
        // return the extension module
        return extension.module();
    }
}

