#ifndef WIGGLY_LOG_APPENDER_FACTORY_HPP
#define WIGGLY_LOG_APPENDER_FACTORY_HPP
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

#include <string>

#include <wiggly/log/properties.hpp>
#include <wiggly/log/appender.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <map>

namespace wiggly
{

namespace log
{

class appender_factory;

typedef boost::shared_ptr<appender_factory> appender_factory_ptr;

class appender_factory : boost::noncopyable
{
    public:

    // constructor function type
    typedef boost::function<appender_ptr ( const std::string&, const Properties& )> appender_ctor;

    // factory singleton
    static appender_factory_ptr singleton();

    ~appender_factory();

    // used by concrete types to add their constructors to the set the
    // factory knows about 
    void add_constructor( const std::string& type, appender_ctor ctor );

    // construct a new appender of a certain type
    appender_ptr construct( const std::string& type, const std::string& name, const Properties& props );
    
    private:

    appender_factory();

    typedef std::map< std::string, appender_ctor > ctor_map;

    ctor_map constructors;

}; // class appender_factory

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_APPENDER_FACTORY_HPP
