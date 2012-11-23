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

#include <wiggly/log_level.hpp>

using namespace std;

//
// anon namespace for file statics
//
namespace
{
    const string FATAL_STR( "FATAL" );
    const string PANIC_STR( "PANIC" );
    const string ERROR_STR( "ERROR" );
    const string WARN_STR( "WARN" );
    const string INFO_STR( "INFO" );
    const string NOTICE_STR( "NOTICE" );
    const string DEBUG_STR( "DEBUG" );    
}

//! \class wiggly::log::log_level
//! \brief Logging level.
//!
//! This class represents logging levels. A logging level has a name and a
//! number. Logging levels names are used to describe them, their numbers
//! are used to determine whether or not a logging event should be recorded.
//!
//! A logger object will have a level associated with it, logging events
//! whose numbers are less than or equal to this levels number will be
//! logged.
//!
//! Seven logging levels are provided as standard, you are free to use
//! whatever mixture of logging levels suits you though, you don't have to
//! use the ones provided. (TODO - make an example program showing
//! completely different logging levels )

//! \brief FATAL level
//!
//! Events that cannot be reasonably recovered from that are going to cause
//! us to try and stop execution as soon as possible.
//!
const wiggly::log::log_level wiggly::log::FATAL( FATAL_NUM, FATAL_STR );

//! \brief PANIC level
//!
//! Events that cannot be reasonably recovered from that we are going to
//! ignore and attempt to carry on anyway, despite the fact that the system
//! is now probably hopelesley corrupted.
//!
const wiggly::log::log_level wiggly::log::PANIC( PANIC_NUM, PANIC_STR );

//! \brief ERROR level
//!
//! Something went badly wrong and we are going to do our best to recover
//! from it.
//!
const wiggly::log::log_level wiggly::log::ERROR( ERROR_NUM, ERROR_STR );

//! \brief WARN level
//!
//! Something didn't quite work, failed transiently or unexpectedly and we
//! are going to recover from it.
//!
const wiggly::log::log_level wiggly::log::WARN( WARN_NUM, WARN_STR );

//! \brief INFO level
//!
//! Something fairly interesting happened and we're letting you know.
//!
const wiggly::log::log_level wiggly::log::INFO( INFO_NUM, INFO_STR );

//! \brief NOTICE level
//!
//! Something fairly banal happened and we're letting you know.
//!
const wiggly::log::log_level wiggly::log::NOTICE( NOTICE_NUM, NOTICE_STR );

//! \brief DEBUG level
//!
//! Lots of trivial information about the internal state of the system only
//! useful to programmers trying to debug the system.
//!
const wiggly::log::log_level wiggly::log::DEBUG( DEBUG_NUM, DEBUG_STR );

//! \brief Default ctor.
//!
//! Creates a log level.
//!
wiggly::log::log_level::log_level( int num, const std::string& name )
:
num_( num ),
name_( name )
{}
    
wiggly::log::log_level::~log_level()
{}

wiggly::log::log_level::log_level( const log_level& rhs )
:
num_( rhs.num_ ),
name_( rhs.name_ )
{}
    
wiggly::log::log_level&
wiggly::log::log_level::operator=( const log_level& rhs )
{
    if( this != &rhs )
    {
        num_ = rhs.num_;
        name_ = rhs.name_;
    }
    return *this;
}
    
//! \brief Get level name.
//!
string
wiggly::log::log_level::name() const
{
    return name_;
}
    
//! \brief Get level number.
//!
int
wiggly::log::log_level::num() const
{
    return num_;
}
