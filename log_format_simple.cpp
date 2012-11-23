// wiggly-log C++ Logging Library
// Copyright (C) 2007 Nigel A. Rantor
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

#ifndef HAVE_STRFTIME
#error "strftime required"
#endif

#include <ctime>
#include <cstring>
#include <wiggly/log_exc.hpp>
#include <wiggly/log_format_simple.hpp>

using namespace std;

//! \class wiggly::log::log_format_simple
//! \brief Simple formatter class.
//!
//! Formatter class that accepts a printf-like string that is used to format
//! the available fields.
//!
//!
//! The available format specifiers are as follows.
//!
//! \li %%m - log message
//! \li %%l - log level name
//! \li %%c - logger name
//! \li %%t - thread name
//! \li %%d - passthrough date formatting to strftime
//! \li %%n - newline
//!    \li %% - literal % sign
//!
//! Message (%%m)
//!
//! This is the message that the user requested to be logged.
//! 
//! Note that this format class is very simplistic, as a side effect any
//! format specifiers present in the log message *will also* be replaced.
//!
//! Level Name (%%l)
//!
//! This is the name of the level that this message was logged at.
//!
//! Logger Name (%%n) 
//!
//! When the system provides the ability to create named loggers this will
//! provide the name of the logger this message was logged through.
//!
//! Thread (%%t)
//!
//! The name of the thread calling the log method.
//!
//! Date Passthrough (%%d)
//!
//! Any format specifier starting with %d is assumed to be a valid strftime
//! format specifier, the d is stripped and the resulting format specifier
//! is passed through strftime to provide date/time formatting.
//!
//! For example %%dY is converted to %%Y which strftime will expand into the
//! year including century.
//!
//! Newline (%%n)
//!
//! Insert a newline. By default the format does not include newlines so if
//! you want your log lines seperated you'll need %%n on the end.
//!
//! Example
//!
//! If a format class is not provided the logger currently falls back to
//! using the time_format string and it's static method of printing log
//! lines. An example of that output follows:
//!
//! \verbinclude default_output_sample.log
//! 
//! To make the simple log format class produce this output you would need
//! to provide the following format string:
//!
//! %%dY-%%dm-%%dd %%dH:%%dM:%%dS %%l %%m%%n
//!
//!

wiggly::log::log_format_simple::log_format_simple( const std::string& format_string )
:
format_string_( format_string )
{}
    
wiggly::log::log_format_simple::~log_format_simple()
{}

void
wiggly::log::log_format_simple::format(
    std::ostream& out,
    const wiggly::log::event& rec ) const
{
    //
    // initial simple implementation, takes format string, replaces any of our
    // own format specifiers and then runs the entire thing through a
    // strftime-like filter to add time information.
    //

    string buf;    
    string::size_type last_pos = 0;
    string::size_type pos;

    do
    {
        // find the next format specifier
        pos = format_string_.find( '%', last_pos );

        // pass through any characters up until the format specifier
        buf.append( format_string_, last_pos, pos - last_pos );

        if( pos != string::npos )
        {
            ++pos;

            switch( format_string_[ pos++ ] )
            {

                case 'l' :
                    buf.append( rec.level.name() );
                    break;

                case 'c' :
                    buf.append( rec.logger_name );
                    break;

                case 't' :
                    buf.append( rec.thread_name );
                    break;

                case 'm' :
                    buf.append( rec.message );
                    break;

                case 'd' :
                    buf.append( "%" );
                    break;

                case '%' :
                    buf.append( "%%" );
                    break;

                case 'n' :
                    buf.append( "\n" );
                    break;
            }
        }
        
        last_pos = pos;
    }
    while( pos != string::npos );

    out << format_time( buf, rec );

    return;
}

std::string
wiggly::log::log_format_simple::format_time(
    const std::string& s,
    const wiggly::log::event& rec ) const
{
    //
    // FIXME
    //
    // - localtime will need to be changed to localtime_r or whatever if we are
    // going to be mt safe eventually
    //
    // - add strftime and localtime tests to configure.ac
    //
    // - see how slow it isand speed it up
    //

    //cerr << "timestamp" << endl;

    size_t buf_len = s.length();
    char* buf = 0;
    int max_tries = 5;
    int written = 0;
    struct tm* now_tm = localtime( &rec.time );

    do
    {
        //cerr << "timestamp iteration " << max_tries << endl << endl;

        buf_len *= 2;

        if( buf )
        {
            delete[] buf;
        }        

        buf = new char[ buf_len ];

        memset( buf, 0, buf_len );

        written = strftime( buf, buf_len-1, s.c_str(), now_tm );

        if( written )
        {
            string ret( buf );
            delete[] buf;
            return ret;
        }
    }
    while( max_tries-- );

    if( buf )
    {
        delete[] buf;
    }

    throw log_exception( "Could not format time, strftime error" );
}
