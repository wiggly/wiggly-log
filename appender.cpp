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

#include "config.h"
#include "detail.hpp"

#ifndef HAVE_STRFTIME
#error "strftime required"
#endif

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#include <map>
#include <wiggly/log/appender.hpp>
#include <wiggly/log/simple_layout.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

using namespace std;

//
// anon namespace for file statics
//
namespace
{
#ifdef HAVE_PTHREAD
    pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

    typedef map< string, wiggly::log::appender_ptr > appender_map;

    appender_map appenders;

    bool initialised = false;
}

//! \class wiggly::log::appender
//! \brief Appender class.
//!
//! Appender class.
//!

void
wiggly::log::appender::initialise()
{
    if( not initialised )
    {
#ifndef NDEBUG
        cerr << "appender initialise\n";
#endif
        initialised = true;
    }
}

void
wiggly::log::appender::shutdown()
{
    if( initialised )
    {
#ifndef NDEBUG
        cerr << "appender shutdown\n";

        appender_map::iterator it;
        
        for( it = appenders.begin();
            it != appenders.end();
            ++it )
        {
            cerr << "app : " << (*it).first << " - count : " << (*it).second.use_count() << "\n";
        }
#endif

        appenders.clear();

#ifndef NDEBUG
        cerr << "appenders.size : " << appenders.size() << "\n";
#endif
    }
}

void
wiggly::log::appender::add_appender( const std::string& name, appender_ptr a )
{
    appenders[name] = a;
}

wiggly::log::appender_ptr
wiggly::log::appender::get_appender( const std::string& name )
{
    return appenders[name];
}

void
wiggly::log::appender::remove_appender( const std::string& name )
{
    appenders.erase( name );
}

//! \brief Default ctor.
//!
//! Creates an appender to stderr.
//!
wiggly::log::appender::appender()
:
layout_( new simple_layout() )
{}

//! \brief Destructor.
//!
wiggly::log::appender::~appender()
{
#ifndef NDEBUG
    cerr << "~appender\n";
#endif
}

//! \brief Set log layout.
//!
//! Sets the layout to use.
//!
//! \param layout log layout to use
//!
void
wiggly::log::appender::layout( wiggly::log::layout_ptr l )
{
    // FIXME - make this take a const param and use a clone method or
    // something to take a copy instead of simply taking the address of the
    // param.
    layout_ = l;
}

//! \brief Get log layout.
//!
//! \return log layout currently in use.
//!
wiggly::log::layout_ptr
wiggly::log::appender::layout() const
{
    return layout_;
}
