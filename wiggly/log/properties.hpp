#ifndef WIGGLY_LOG_PROPERTIES_HPP
#define WIGGLY_LOG_PROPERTIES_HPP

#include "config.h"
#include <tr1/unordered_map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

typedef std::vector<std::string> property_vector;
typedef std::tr1::unordered_map<std::string,property_vector> properties_map;

namespace wiggly
{

namespace log
{

/**
 * property object
 *
 * FIXME - add operations to egt values as specific types
 * FIXME - copy ctor
 * FIXME - add decorators to provide subset of the properties tree
 * FIXME - copy op
 *
 *
 */
class Properties
{
	public:

	Properties();
	
	Properties( const Properties& obj );
	
	~Properties();

	Properties& operator=( const Properties& rhs );

	// load properties from file into this object, any existing properties
	// remain or are overwritten if they exist in the file to be loaded
	void load( const std::string& file );

	// load properties from a stream
	void load( std::istream& in );

	// save properties to a file
	void save( const std::string& file ) const;
	
	// save properties to a stream
	void save( std::ostream& out ) const;
	
	// clear all properties
	void clear();	

	bool exists( const std::string& name ) const;

	std::vector<std::string> keys() const;

	std::string get( const std::string& name, unsigned int index = 0 ) const;
		
	std::string get( const std::string& name, const std::string& default_val ) const;
	
	std::string get( const std::string& name, const std::string& default_val, unsigned int index = 0 ) const;
	
	void put( const std::string& name, const std::string& value, unsigned int index = 0 );

	private:

	mutable properties_map p_;
};

std::istream& operator>>( std::istream& in, Properties& p );

std::ostream& operator<<( std::ostream& out, const Properties& p );

typedef boost::shared_ptr<Properties> Properties_ptr;

} // log

} // wiggly

#endif // WIGGLY_LOG_PROPERTIES_HPP
