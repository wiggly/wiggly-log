#ifndef WIGGLY_LOG_APPENDER_HPP
#define WIGGLY_LOG_APPENDER_HPP
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

//#include <iosfwd>
#include <string>
//#include <memory>
//#include <sstream>

//#include <wiggly/log_exc.hpp>
//#include <wiggly/log_level.hpp>
#include <wiggly/log/layout.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

namespace wiggly
{

namespace log
{

class appender;

typedef boost::shared_ptr<appender> appender_ptr;

class appender : boost::noncopyable
{
    public:

    static void initialise();

    static void shutdown();

    // FIXME
    static void add_appender( const std::string& name, appender_ptr a );

    // FIXME
    static appender_ptr get_appender( const std::string& name );

    // FIXME
    static void remove_appender( const std::string& name );

    appender();
    
    virtual ~appender();

    void layout( wiggly::log::layout_ptr l );
    
    wiggly::log::layout_ptr layout() const;

    virtual void log( const event& e ) = 0;
    
    private:
    
    wiggly::log::layout_ptr layout_;
}; // class appender

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_APPENDER_HPP
