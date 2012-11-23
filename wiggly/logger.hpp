#ifndef WIGGLY_LOGGER_HPP
#define WIGGLY_LOGGER_HPP
// wiggly-log C++ Logging Library
// Copyright (C) 2006 Nigel A. Rantor
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

#include <iosfwd>
#include <string>
#include <memory>
#include <sstream>
#include <vector>

#include <wiggly/log_exc.hpp>
#include <wiggly/log_level.hpp>
#include <wiggly/log_format.hpp>
#include <wiggly/log/appender.hpp>

#include <boost/utility.hpp>

namespace wiggly
{

namespace log
{

class logger : boost::noncopyable
{
    private:

    class stream
    {
        public:
        
        stream();

        stream( logger* parent, const log_level& l );

        ~stream();
        
        stream( const stream& rhs );
        
        stream& operator=( const stream& rhs );

        template< typename T > stream& operator<<( const T& value );

        private:

        bool is_null() const { return parent_ == 0; }

        logger* parent_;
        log_level level_;
        mutable std::auto_ptr< std::ostringstream > str_;
    }; // class stream

    public:

    static void initialise();

    static void shutdown();

    static logger& get_root_logger();

    static logger& get_logger( const std::string& name );

    static logger& create_logger( const std::string& name );

    ~logger();

//    logger( const logger& rhs );
    
//    logger& operator=( const logger& rhs );

    std::string name() const;

    void level( const log_level& lvl );
    
    log_level level() const;

    void add_appender( appender_ptr app );
    
    std::vector<appender_ptr> appenders() const;

    void log( const log_level& lvl, const std::string& message );

    stream log( const log_level& lvl );

    void fatal( const std::string& message );

    stream fatal();
  
    void panic( const std::string& message );

    stream panic();
  
    void error( const std::string& message );

    stream error();
  
    void warn( const std::string& message );

    stream warn();
  
    void info( const std::string& message );

    stream info();
  
    void notice( const std::string& message );

    stream notice();
  
    void debug( const std::string& message );

    stream debug();
    
    private:
    
    logger( const std::string& name );

    std::string name_;

    log_level level_;

    std::vector<appender_ptr> app_;
}; // class logger


template< typename T >
wiggly::log::logger::stream&
wiggly::log::logger::stream::operator<<( const T& value )
{
    if( ! is_null() )
    {
        (*str_) << value;
    }
    return *this;
}

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOGGER_HPP
