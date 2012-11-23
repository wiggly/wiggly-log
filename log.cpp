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

//! \file

//! \mainpage Wiggly-Log
//!
//! \section Introduction
//!
//! This is my logging package! There are many like it, but this one is
//! mine...
//!       
//! Whilst playing with graphics I found I needed a simple and fast logging
//! implementation that I could improve as I needed.
//!
//! I wanted to be able to use standard C++ features like streams for
//! outputting user-defined datatypes instead of having to bother with
//! C-style printf or other variadic functions.
//!
//! I also wanted to be able to remove logging from certain very time
//! sensitive parts completely at compile-time.
//!
//! I had tried to find a logging package in C++ that was stable on both
//! Linux and Windows but failed. Log4cpp looks to be orphaned and the code
//! wasn't inspiring enough for me to want to try and mess with it.
//!
//! \section Caveats
//!
//! Yes. I know it isn't fast yet, the point right now is that I have
//! something with an interface I like (streams), it's simple (only took me
//! a few days to put together), runs on Linux and Windows, and I can
//! eliminate the overhead entirely at compile time if I wish to.
//!
//! The code has lots of FIXME and TODOs, this is a Good Thing(tm) 'cos you
//! can see what I'm thinking. More importantly it reminds me what I was
//! thinking when I come back to the code.
//!
//! There is very limited support for using this in a multithreaded
//! environment. The configure script accepts a --with-pthread option that
//! will make the logger serialise all logging operations. Nothing else is
//! thread-safe though so operations that modify the logging level, change
//! the log format etc are still prone to race conditions. This will change
//! as and when it becomes more important.
//!
//! There aren't currently any real tests or examples. There are a bunch of
//! programs that get built in the example directory that you can run to see
//! if things are working and as inspiration for you own code...
//!
//! \section Future
//!
//! I'm heading toward a library that is as close to Log4J as possible. To
//! that end everything is now configured through a properties file.
//!
//! There are only two different kinds of appender, console and file. Log
//! levels and appenders are inherited, but right now only from the root
//! logger.
//!
//!
//! Once I've gone and spent a bit more time using it I'll revisit it, but
//! the following will probably be at the top of the list:
//!
//! - Sinks
//! - More Formatting Classes
//! - Speed
//!
//! Speed and tuning will probably come once I've done the first three as
//! they will change the way the guts work anyway.
//!

#include "config.h"
#include "detail.hpp"

#include <wiggly/log/appender_factory.hpp>
#include <wiggly/log_exc.hpp>
#include <wiggly/log.hpp>
#include <wiggly/log/properties.hpp>

#ifndef NDEBUG
#include <iostream>
#include <fstream>
#endif

using namespace std;

namespace
{
    bool initialised = false;
}

// internal
wiggly::log::appender_ptr
create_appender(
    const string& name,
    const wiggly::log::Properties& props )
{
    string prefix = "log4j.appender." + name;  

    string type = props.get( prefix );

    return wiggly::log::appender_factory::singleton()->construct( type, name, props );
}

//! \brief Initialise library
//!
//! Initialise the logging library.
//!
void
wiggly::log::initialise()
{
#ifndef NDEBUG
    cerr << "log initialise\n";
#endif

    if( not initialised )
    {
        atexit( wiggly::log::shutdown );
        wiggly::log::appender::initialise();
        wiggly::log::logger::initialise();
        initialised = true;
    }
    else
    {
        throw wiggly::log::log_exception( "library already initialised" );
    }
}

//! \brief Initialise library and configure it
//!
//! Initialise the logging library with a configuration file.
//!
void
wiggly::log::initialise( const std::string& config )
{
#ifndef NDEBUG
    cerr << "log initialise\n";
#endif
    initialise();
    configure( config );
}

//! \brief Initialise library
//!
//! Initialise the logging library with a configuration file
//!
void
wiggly::log::configure( const std::string& config )
{
    using namespace std;

#ifndef NDEBUG
    cerr << "log configure\n";
#endif

    if( not initialised )
    {
        throw wiggly::log::log_exception( "library not initialised" );
    }

    Properties prop;
    
    prop.load( config );

    vector<string> k = prop.keys();
    vector<string>::iterator it;

#ifndef NDEBUG
    for( it = k.begin();
        it != k.end();
        ++it )
    {
        cerr << "prop : " << *it << "\n";
    }
    cerr << "\n";
#endif

    // create appenders
    for( it = k.begin();
        it != k.end();
        ++it )
    {
        if( (*it).find( "log4j.appender.", 0 ) == 0 )
        {
            string name = (*it).erase( 0, string("log4j.appender.").length() );

            if( name.find( ".", 0 ) == string::npos )
            {
#ifndef NDEBUG
                cerr << "appender : " << name << "\n";
#endif
                appender_ptr ap = create_appender( name, prop );
                wiggly::log::appender::add_appender( name, ap );
            }
        }
    }

    // set up root logger
    if( prop.exists( "log4j.rootLogger" ) )
    {
#ifndef NDEBUG
        cerr << "got root logger key\n";
#endif

        wiggly::log::logger& root = wiggly::log::logger::get_root_logger();

        string root_level = prop.get( "log4j.rootLogger" );

#ifndef NDEBUG
        cerr << "root level : " << root_level << "\n";
#endif

        if( root_level == "FATAL" )
        {
            root.level( FATAL );
        }
        else if( root_level == "ERROR" )
        {
            root.level( ERROR );
        }
        else if( root_level == "WARN" )
        {
            root.level( WARN );
        }
        else if( root_level == "INFO" )
        {
            root.level( INFO );
        }
        else if( root_level == "DEBUG" )
        {
            root.level( DEBUG );
        }
        
        int rooti;
        
        for( rooti = 1; rooti > 0; ++rooti )
        {
            string appender_name = prop.get( "log4j.rootLogger", rooti );

            if( appender_name.length() )
            {
#ifndef NDEBUG
                cerr << "root appender : " << appender_name << "\n";                
#endif
                root.add_appender( wiggly::log::appender::get_appender( appender_name ) );
            }
            else
            {
#ifndef NDEBUG
                cerr << "no more appenders for root logger\n";
#endif
                rooti = -1;
            }
        }
    }


    for( it = k.begin();
        it != k.end();
        ++it )
    {
        if( (*it).find( "log4j.logger.", 0 ) == 0 )
        {
#ifndef NDEBUG
            cerr << "\n";
#endif

            string name = *it;
            name.erase( 0, string("log4j.logger.").length() );

#ifndef NDEBUG
            cerr << "got logger " << name << " (" << *it << ")\n";
#endif

            wiggly::log::logger& log = wiggly::log::logger::create_logger( name );

            string logger_level = prop.get( *it );

#ifndef NDEBUG
            cerr << "logger level : " << logger_level << "\n";
#endif

            if( logger_level == "FATAL" )
            {
#ifndef NDEBUG
                cerr << "setting log level to fatal\n";
#endif
                log.level( FATAL );
            }
            else if( logger_level == "ERROR" )
            {
#ifndef NDEBUG
                cerr << "setting log level to error\n";
#endif
                log.level( ERROR );
            }
            else if( logger_level == "WARN" )
            {
#ifndef NDEBUG
                cerr << "setting log level to warn\n";
#endif
                log.level( WARN );
            }
            else if( logger_level == "INFO" )
            {
#ifndef NDEBUG
                cerr << "setting log level to info\n";
#endif
                log.level( INFO );
            }
            else if( logger_level == "DEBUG" )
            {
#ifndef NDEBUG
                cerr << "setting log level to debug\n";
#endif
                log.level( DEBUG );
            }
        
            int i;
            
            for( i = 1; i > 0; ++i )
            {
                string appender_name = prop.get( *it, i );

                if( appender_name.length() )
                {
#ifndef NDEBUG
                    cerr << "appender : " << appender_name << "\n";
#endif
                    log.add_appender( wiggly::log::appender::get_appender( appender_name ) );
                }
                else
                {
#ifndef NDEBUG
                    cerr << "no more appenders for logger\n";
#endif
                    i = -1;
                }
            }
            
            if( log.appenders().size() == 0 )
            {
                vector<appender_ptr> app = wiggly::log::logger::get_root_logger().appenders();
                vector<appender_ptr>::iterator appit;
                
                for( appit = app.begin();
                    appit != app.end();
                    ++appit )
                {
                    log.add_appender( *appit );
                }            
            }
        }
    }
}

//! \brief Cleanup library
//!
//! Perform any cleanup required, including destroying all objects created.
//!
//! This should not need to be called by users as it will automatically be
//! put into an atexit hook on initialise. If for some reason however you
//! want to cleanup the library and remove objects it has created from
//! memory then feel free.
//!
void
wiggly::log::shutdown()
{
#ifndef NDEBUG
    cerr << "log shutdown\n";
#endif
    if( initialised )
    {
        wiggly::log::logger::shutdown();
        wiggly::log::appender::shutdown();
    }
}
