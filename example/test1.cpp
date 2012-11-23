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
#include <wiggly/log.hpp>
#include <wiggly/logger.hpp>
#include <iostream>

using namespace std;


void funny()
{
    wiggly::log::logger &log = wiggly::log::logger::get_logger( "test1" );    
    log.error() << "funny logging message";
}

int main( int argc, char ** argv )
{
    try
    {
        wiggly::log::initialise( "log4j.conf" );

        wiggly::log::logger &log = wiggly::log::logger::get_logger( "test1" );
        
        log.info() << "first logging message";

        log.log( wiggly::log::WARN ) << "testy testy";

        funny();

        log.warn() << "another logging message";

        log.info() << "about to open logfile";

        log.debug() << "yikes";

        log.fatal() << "blergle...";
    }
    catch( wiggly::log::log_exception& e )
    {
        cerr << "caught log exception : " << e.what() << endl;
        return 1;
    }

    return 0;
}
