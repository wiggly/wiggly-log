// wiggly-log C++ Logging Library
// Copyright (C) 2009 Nigel A. Rantor
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

// FIXME - rewrite this to use a vector of vecotrs, or list of vectors or
// something else, get rid of the new calls to create property vectors...

#include "config.h"
#include "detail.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <wiggly/log/properties.hpp>

using namespace std;

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

wiggly::log::Properties::Properties()
: p_( properties_map() )
{}

wiggly::log::Properties::Properties( const Properties& obj )
: p_( obj.p_ )
{}

wiggly::log::Properties::~Properties()
{
// FIXME - this is SEGFAULTING on exit now...possibly becasue it wasn't
// being called until I wrapped the props object in a smart pointer...
/*
	properties_map::iterator it;
	for( it = _p.begin(); it != _p.end(); it++ )
	{
		delete &(it->second);
	}
*/
}

wiggly::log::Properties&
wiggly::log::Properties::operator=( const Properties& rhs )
{
	if( this == &rhs ) return *this;

	// We want a COPY of the map, not a reference to it
	// XXX - check this
	p_ = rhs.p_;

	return *this;
}


// load properties from file into this object, any existing properties
// remain or are overwritten if they exist in the file to be loaded
void
wiggly::log::Properties::load( const std::string& file )
{
	ifstream in( file.c_str() );
	load( in );
	in.close();
}

// load properties from a stream
void
wiggly::log::Properties::load( std::istream& in )
{
	property_vector * pv;

	string line;

	string k;
	string v;

	std::string::size_type pos;
	std::string::size_type epos;

	while( in.good() && ( ! in.eof() ) )
	{
		getline( in, line );

		// find first position that isn't horizontal space
		pos = line.find_first_not_of( "\t " );

		// discard blank lines
		if( pos == string::npos ) continue;
		
		// discard comments
		if( line.at( pos ) == '#' ) continue;

		// create vector for our properties
		pv = new property_vector();
		
		// get key
		epos = line.find_first_of( "\t =" );
		k = line.substr( pos, epos );

		// start searching from the end of the key
		pos = epos;

		epos = line.find_first_of( "=", pos );
		
		// if we have no value then just set the value to be true
		if( epos == string::npos )
		{
			v = "true";
			pv->push_back( v );			
		}
		else
		{
			pos = epos;
			epos = line.find_first_not_of( "\t =", pos );
			pos = epos;
			line = line.erase( 0, pos );

			pos = line.find_first_of( "," );

			if( pos == string::npos )
			{
				// single valued property
				v = line;
				pv->push_back( boost::trim_copy( v ) );
			}
			else
			{
				// multi valued property
				boost::char_separator<char> sep( "," );
				tokenizer tokens( line , sep );
				tokenizer::iterator tit;
				for( tit = tokens.begin(); tit != tokens.end(); tit++ )
				{
					pv->push_back( boost::trim_copy( *tit ) );
				}
			}
		}
		
		p_[k] = *pv;
		// put here after valgrinding....maybe pv should go into an
		// auto_ptr while we play with it
		delete pv;
	}

	return;
}

// save properties to a file
void
wiggly::log::Properties::save( const string& file ) const
{
	ofstream out( file.c_str() );
	save( out );
	out.close();
}

// save properties to a stream
void
wiggly::log::Properties::save( ostream& out ) const
{
	properties_map::const_iterator it;
	property_vector::const_iterator pit;

	for( it = p_.begin(); it != p_.end(); it++ )
	{
		out << it->first << " = ";
		
		pit = it->second.begin();
		
		do
		{
			out << *pit;
			pit++;
			if( pit != it->second.end() )
			{
				out << ",";
			}
		}
		while( pit != it->second.end() );

		out << endl;
	}	
}

// clear all properties
void
wiggly::log::Properties::clear()
{
	p_.clear();
}

bool
wiggly::log::Properties::exists( const string& name ) const
{
	return ( p_.find( name ) != p_.end() );
}

std::vector<std::string>
wiggly::log::Properties::keys() const
{
    std::vector<std::string> keys;

    properties_map::const_iterator it;
    
    for( it = p_.begin();
        it != p_.end();
        ++it )
    {
        keys.push_back( it->first );
    }

    return keys;
}

string
wiggly::log::Properties::get( const string& name, unsigned int index ) const
{
	return get( name, string(""), index );
}

string
wiggly::log::Properties::get( const string& name, const string& default_val, unsigned int index ) const
{
	if( exists( name ) )
	{
		if( p_[name].size() > index )
		{
			return p_[name][index];
		}
	}
	return default_val;
}

void
wiggly::log::Properties::put( const string& name, const string& value, unsigned int index )
{
	p_[name][index] = value;
}

istream&
wiggly::log::operator>>( istream& in, Properties& p )
{
	p.load( in );
	return in;
}

ostream&
wiggly::log::operator<<( ostream& out, const Properties& p )
{
	p.save( out );
	return out;
}

