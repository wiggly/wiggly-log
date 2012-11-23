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

#include "config.h"
#include "detail.hpp"

#include <wiggly/log/appender_factory.hpp>
#include <wiggly/log_exc.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

using namespace std;

// factory singleton
wiggly::log::appender_factory_ptr
wiggly::log::appender_factory::singleton()
{
    static wiggly::log::appender_factory_ptr singleton( new wiggly::log::appender_factory() );
    return singleton;
}

wiggly::log::appender_factory::~appender_factory() {}

// used by concrete types to add their constructors to the set the
// factory knows about 
void
wiggly::log::appender_factory::add_constructor(
    const std::string& type,
    appender_ctor ctor )
{
#ifndef NDEBUG
    cerr << "registering appender constructor for : " << type << "\n";
#endif
    constructors.insert( make_pair( type, ctor ) );
}

// construct a new appender of a certain type
wiggly::log::appender_ptr
wiggly::log::appender_factory::construct( const std::string& type, const std::string& name, const Properties& props )
{
    ctor_map::iterator it = constructors.find( type );
    
    if( it != constructors.end() )
    {
        return (*it).second( name, props );
    }
    else
    {
        throw log_exception( "no constructor found for : " + type + " ( " + name + " )" );
    }
}

wiggly::log::appender_factory::appender_factory() {}
