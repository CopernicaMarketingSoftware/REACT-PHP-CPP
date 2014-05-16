/**
 * Resolver.cpp
 *
 * @copyright 2014 Copernica BV
 */
 
/**
 *  Dependencies
 */
#include "resolver.h"
#include "resolverresult.h"
#include "loop.h"
#include <iostream>

/**
 *	Set up namespace
 */
namespace ReactPhp {
	
/**
 *  Alternative constructor
 *  @param	loop
 */
void Resolver::__construct(Php::Parameters &params)
{
	// retrieve the parameters
	Php::Value loopParam = params[0];
	
	// get the actual base object
	Loop *loop = (Loop *)loopParam.implementation();
		
	// create the actual timer-watcher
	_resolver = std::make_shared<React::Dns::Resolver>(loop->loop());
}

/**
 * Find all IP addresses for a certain domain
 * @param domain The domain to fetch the IPs for
 * @param version IP version, can be 4 or 6
 * @param callback
 * @return bool
 */
void Resolver::ip(Php::Parameters &params)
{
	// retrieve the parameters
	Php::Value domain = params[0];
	Php::Value version = params[1];
	Php::Value callback = params[2];
	
	// call the React::Dns::Resolver::ip function
	_resolver->ip(domain, version, [callback](React::Dns::IpResult &&ips, const char *error) {
		
		// check for error
		if (error) throw Php::Exception(error);
		
		// call the PHP callback
		callback();
		
		// fetch all IPs
		for (auto &ip : ips) std::cout << ip << std::endl;
	});
	
	
}

/**
 * Find all MX records for a certain domain
 * @param domain The domain name to search MX records for
 * @param callback Callback that is called when found
 * @return bool
 */
Php::Value Resolver::mx(Php::Parameters &params)
{
	// retrieve the parameters
	Php::Value domain = params[0];
	Php::Value callback = params[1];
	
	// call the React::Dns::Resolver::mx function
	_resolver->mx(domain, [callback](React::Dns::MxResult &&mxs, const char *error) {
		
		// check for error
		if (error) throw Php::Exception(error);
		
		ResolverResult *object = new ResolverResult(std::move(mxs));

		// call the PHP callback
		callback(Php::Object("Async\\ResolverResult", object));
	});
	
	return true;
}

/**
 * 	End of namespace
 */
}
