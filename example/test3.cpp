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

#include <string>
#include <wiggly/logger.hpp>
#include <wiggly/log.hpp>
#include <iostream>

#define WIGGLY_LOG_LEVEL WIGGLY_LOG_LEVEL_DEBUG

#include <wiggly/log_macro.hpp>

using namespace std;

int main( int argc, char ** argv )
{
    try
    {
        wiggly::log::initialise( "log4j.conf" );
        wiggly::log::logger &log = wiggly::log::logger::get_logger( "test3" );

        WIGGLY_LOG_STR_FATAL( log, "what the yak!?!" );

        WIGGLY_LOG_STR_ERROR( log, "this is an error" );

        WIGGLY_LOG_STR_WARN( log, "warning, danger Will Robinson!!!" );		

        WIGGLY_LOG_STR_INFO( log, "blah, blah, blah" );

        WIGGLY_LOG_STR_DEBUG( log, "I found a bug sir!" );

        WIGGLY_LOG_STR_ERROR( log, "last log line" );

        WIGGLY_LOG_STR_INFO( log, "last log line?" );
    }
    catch( wiggly::log::log_exception& e )
    {
        cerr << "caught log exception : " << e.what() << endl;
        return 1;
    }

    return 0;
}
