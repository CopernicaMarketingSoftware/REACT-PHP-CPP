/**
* Resolver.h
*
* Class for resolving domain names
*/

/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <reactcpp.h>

/**
* Set up namespace
*/
namespace ReactPhp {

/**
 *	Class definition
 */
class Resolver : public Php::Base
{
private:
	/**
	 *  The actual resolver object
	 * 	@var	std::shared_ptr
	 */
	std::shared_ptr<React::Dns::Resolver> _resolver;
	
public:
	/**
	 * 	Constructor
	 */
	Resolver() {}
	
	/**
	 *  Alternative constructor
	 *  @param	loop
	 */
	void __construct(Php::Parameters &params);
	
	/**
	 * Destructor
	 */
    virtual ~Resolver() {}
    
    /**
	 * Find all IP addresses for a certain domain
	 * @param domain The domain to fetch the IPs for
	 * @param version IP version, can be 4 or 6
	 * @param callback
	 * @return bool
	 */
    void ip(Php::Parameters &params);

    /**
	 * Find all MX records for a certain domain
	 * @param domain The domain name to search MX records for
	 * @param callback Callback that is called when found
	 * @return bool
	 */
    Php::Value mx(Php::Parameters &params);
	
};
	
/**
 * 	End of namespace
 */
}
