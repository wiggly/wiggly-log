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

#include <fstream>
#include <wiggly/log/appender_factory.hpp>
#include <wiggly/log/file_appender.hpp>

using namespace std;

//
// anon namespace for file statics
//
namespace
{
//
// we really don't need one of these per-appender...although I suppose it
// does decrease the chance that different threads will block one another
//
#ifdef HAVE_PTHREAD
    pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

    wiggly::log::file_appender::file_appender_init initialiser;
}

//! \class wiggly::log::file_appender
//! \brief File appender class.
//!
//! File appender class.
//!

// TODO - doc
wiggly::log::appender_ptr
wiggly::log::file_appender::construct( const std::string& name, const Properties& props )
{
#ifndef NDEBUG
    cerr << "file_appender construct\n";
#endif
    appender_ptr a( new file_appender( name, props ) );
    return a;
}

//! \brief Default ctor.
//!
//! Creates an appender to stderr.
//!
wiggly::log::file_appender::file_appender( const std::string& name, const Properties& props )
:
out_( 0 )
{
#ifndef NDEBUG
    cerr << "file_appender\n";
#endif
    std::string prefix = "log4j.appender." + name + ".filename";
    std::string filename = props.get( prefix );
#ifndef NDEBUG
    cerr << "file : " << filename << "\n";
#endif
    out_ = new ofstream( filename.c_str(), ios::app );
}

//! \brief Destructor.
//!
wiggly::log::file_appender::~file_appender()
{
#ifndef NDEBUG
    cerr << "~file_appender\n";
#endif
    if( out_ && out_->good() )
    {
        out_->flush();
    }
    delete out_;
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
wiggly::log::file_appender::log( const event& e )
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
wiggly::log::file_appender::file_appender_init::file_appender_init()
{
    wiggly::log::appender_factory::singleton()->add_constructor(
        "wiggly.log.file_appender",
        wiggly::log::file_appender::construct );

    wiggly::log::appender_factory::singleton()->add_constructor(
        "wiggly::log::file_appender",
        wiggly::log::file_appender::construct );
}
