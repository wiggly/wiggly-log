#ifndef WIGGLY_LOG_EVENT_HPP
#define WIGGLY_LOG_EVENT_HPP
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
#include <ostream>
#include <ctime>
#include <wiggly/log_level.hpp>

namespace wiggly
{

namespace log
{

struct event
{
    event()
    :
        level( FATAL ),
        logger_name( "ROOT" ),
        thread_name( "MAIN" )
    {}

    log_level level;
    std::time_t time;
    std::string logger_name;
    std::string thread_name;
    std::string message;
};

inline std::ostream& operator<<( std::ostream& out, const event& value )
{
    out << "log event" << std::endl;
    out << "level : " << value.level << std::endl;
    out << "time : " << value.time << std::endl;
    out << "logger name : " << value.logger_name << std::endl;
    out << "thread name : " << value.thread_name << std::endl;
    out << "message : " << value.message << std::endl;
    return out;
}

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_EVENT_HPP
