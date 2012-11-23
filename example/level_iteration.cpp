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

#include <string>
#include <wiggly/log.hpp>
#include <wiggly/logger.hpp>
#include <iostream>

using namespace std;

int main( int argc, char ** argv )
{
    if( argc < 3 )
    {
        cerr << "please supply a number of iterations and a log level" << endl;
        return 0;
    }

    int num = atoi( argv[1] );

    string level( argv[2] );

    try
    {
        wiggly::log::initialise( "log4j.conf" );

        wiggly::log::logger &log = wiggly::log::logger::get_logger( "level_iteration" );

        if( level == "FATAL" )
        {
            log.level( wiggly::log::FATAL );
        }
        else if( level == "ERROR" )
        {
            log.level( wiggly::log::ERROR );
        }
        else if( level == "WARN" )
        {
            log.level( wiggly::log::WARN );
        }
        else if( level == "INFO" )
        {
            log.level( wiggly::log::INFO );
        }
        else if( level == "NOTICE" )
        {
            log.level( wiggly::log::NOTICE );
        }
        else if( level == "DEBUG" )
        {
            log.level( wiggly::log::DEBUG );
        }

        for( int i = 0; i < num; ++i )
        {        
            log.info( "start of iteration" );

            log.info( "a simple debugging message" );

            log.info( "a warning message" );

            log.info( "more information" );

            log.info( "a problem occured" );

            log.info( "halfway through iteration" );

            log.info( "more debugging" );

            log.info( "only two more messages left" );

            log.info( "nearly there" );

            log.info( "iteration complete" );
        }
    }
    catch( wiggly::log::log_exception& e )
    {
        cerr << "caught log exception : " << e.what() << endl;
        return 1;
    }

    return 0;
}
