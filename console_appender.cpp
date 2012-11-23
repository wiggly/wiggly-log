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

// TODO - ensure we need all these includes

#include "config.h"
#include "detail.hpp"

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#include <wiggly/log/console_appender.hpp>
#include <wiggly/log/appender_factory.hpp>

using namespace std;

//
// anon namespace for file statics
//
namespace
{
#ifdef HAVE_PTHREAD
    pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

    wiggly::log::console_appender::console_appender_init initialiser;
}

//! \class wiggly::log::console_appender
//! \brief Console appender class.
//!
//! Console appender class.
//!

// TODO - doc
wiggly::log::appender_ptr
wiggly::log::console_appender::construct( const std::string& name, const Properties& props )
{
#ifndef NDEBUG
    cerr << "console_appender construct\n";
#endif
    appender_ptr a( new console_appender() );
    return a;
}

//! \brief Default ctor.
//!
//! Creates an appender to stderr.
//!
wiggly::log::console_appender::console_appender()
:
out_( new ostream( cerr.rdbuf() ) ) 
{
#ifndef NDEBUG
    cerr << "console_appender\n";
#endif
}

//! \brief Destructor.
//!
wiggly::log::console_appender::~console_appender()
{
#ifndef NDEBUG
    cerr << "~console_appender\n";
#endif
}

//! \brief General logging method.
//!
//! This accepts a log \a level and a \a message. The message will be logged,
//! the \a level is passed in so that it can be formatted appropriately.
//!
//! \param level The level this message was logged at.
//! \param message The message to be logged.
//!
void
wiggly::log::console_appender::log( const event& e )
{
#ifdef HAVE_PTHREAD
    pthread_mutex_lock( &log_mutex );
#endif

    layout()->format( *out_, e );

#ifdef HAVE_PTHREAD
    pthread_mutex_unlock( &log_mutex );
#endif
}

// TODO - doc
wiggly::log::console_appender::console_appender_init::console_appender_init()
{
    wiggly::log::appender_factory::singleton()->add_constructor(
        "wiggly.log.console_appender",
        wiggly::log::console_appender::construct );

    wiggly::log::appender_factory::singleton()->add_constructor(
        "wiggly::log::console_appender",
        wiggly::log::console_appender::construct );
}
