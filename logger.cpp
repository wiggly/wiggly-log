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

#include <map>
#include <wiggly/logger.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

using namespace std;

namespace
{
    typedef map< string, wiggly::log::logger* > logger_map;

    wiggly::log::logger* root_logger;

    logger_map loggers;

    bool initialised = false;
}

//! \class wiggly::log::logger
//! \brief Logging class.
//!
//! Logging class.
//!

// TODO - doc
void wiggly::log::logger::initialise()
{
    if( not initialised )
    {
#ifndef NDEBUG
        cerr << "logger initialise\n";
#endif
        root_logger = new logger( "ROOT" );

        initialised = true;
    }
}

// TODO - doc
void wiggly::log::logger::shutdown()
{
    if( initialised )
    {
#ifndef NDEBUG
        cerr << "logger shutdown\n";
#endif
        delete root_logger;
        
        logger_map::iterator it;
        
        for( it = loggers.begin();
            it != loggers.end();
            ++it )
        {
            delete (*it).second;
        }
        
        loggers.clear();
    }
}

//! \brief Get root logging object.
//!
wiggly::log::logger&
wiggly::log::logger::get_root_logger()
{
    return (*root_logger);
}

//! \brief Get logging object by name.
//!
//! \param name The name of the logger to get.
//!
wiggly::log::logger&
wiggly::log::logger::get_logger( const std::string& name )
{
    logger_map::iterator it;

    it = loggers.find( name );

    // FIXME - this needs to actually take it's config from any loggers
    // closer to it up the hierarchy onstead of always using the root
    if( it == loggers.end() )
    {
#ifndef NDEBUG
        cerr << "logger not found : " << name << "\n";
        for( it = loggers.begin();
            it != loggers.end();
            ++it )
        {
            cerr << "logger: " << (*it).first << "\n";
        }
#endif

        logger* obj = new logger(
            name );

        obj->level( get_root_logger().level() );

        vector<appender_ptr> app = get_root_logger().appenders();
        
        vector<appender_ptr>::iterator appit;
        
        for( appit = app.begin();
            appit != app.end();
            ++appit )
        {
            obj->add_appender( *appit );
        }

        loggers[name] = obj;
        
        return (*obj);
    }

    return (*(*it).second);
}

//! \brief Get logging object by name.
//!
//! \param name The name of the logger to get.
//!
wiggly::log::logger&
wiggly::log::logger::create_logger( const std::string& name )
{
    logger_map::iterator it;

    it = loggers.find( name );

    // FIXME - this needs to actually take it's config from any loggers
    // closer to it up the hierarchy onstead of always using the root
    if( it == loggers.end() )
    {
#ifndef NDEBUG
        cerr << "logger not found : " << name << "\n";
        for( it = loggers.begin();
            it != loggers.end();
            ++it )
        {
            cerr << "logger: " << (*it).first << "\n";
        }
#endif

        logger* obj = new logger(
            name );

        loggers[name] = obj;

        return (*obj);
    }

    return (*(*it).second);
}


//! \brief Default ctor.
//!
//! Creates a logger.
//!
//! \param app The appender object for log messages to be sent to.
//!
wiggly::log::logger::logger( const std::string& name )
:
name_( name ),
level_( wiggly::log::INFO ),
app_()
{
#ifndef NDEBUG
    cerr << "logger ctor : " << this->name() << "\n";
#endif
}

//! \brief Destructor
//!
wiggly::log::logger::~logger()
{
#ifndef NDEBUG
    cerr << "logger dtor : " << this->name() << "\n";
#endif
}

//! \brief Category name.
//!
//! \return Category name.
//!
std::string
wiggly::log::logger::name() const
{
    return name_;
}

//! \brief Set logging level.
//!
//! \param level Level to log at from now on.
//!
void
wiggly::log::logger::level( const log_level& level )
{
    level_ = level;
}

//! \brief Get logging level.
//!
//! \return Current logging level.
//!
wiggly::log::log_level
wiggly::log::logger::level() const
{
    return level_;
}

//! \brief Add appender.
//!
//! \param app Appender to add to set we should emit log events to.
//!
void
wiggly::log::logger::add_appender( appender_ptr app )
{
    app_.push_back( app );
}

//! \brief Get appenders
//!
//! \return Current set of appenders.
//!
std::vector<wiggly::log::appender_ptr>
wiggly::log::logger::appenders() const
{
    return app_;
}

//! \brief General logging method.
//!
//! This accepts a log \a level and a \a message. The message will be logged
//! if the \a level is less than or equal to the log level this logger is
//! set to.
//!
//! For example if the logger has had its level set to wiggly::log::ERROR
//! and wiggly::log::FATAL is passed as \a level then the message will be
//! logged.
//!
//!
//! \param level The level this message should be logged at or beyond.
//! \param message The message to be logged.
//!
void
wiggly::log::logger::log( const log_level& level, const std::string& message )
{
    if( level <= level_ )
    {
        vector<appender_ptr>::iterator it;

#ifndef NDEBUG
        cerr << "log : " << message << "\n";
#endif

        for( it = app_.begin();
            it != app_.end();
            ++it )
        {
            event e; 
            e.level = level;
            e.time = time( 0 );
            e.logger_name = this->name(); 
            //e.thread_name = ???
            e.message = message;
        
            (*it)->log( e );
        }
    }
}

//! \brief General log stream creation.
//!
//! This accepts a log \a level. The data output to the returned stream will
//! be logged if the \a level is less than or equal to the log level this
//! logger is set to.
//!
//! The stream returned should not be stored, saved or played with other
//! than to output data. Currentlt behaviour is undefined if you do. You'll
//! most likely either lose logging information or wind up dumping core.
//!
//! \param level The level the returned stream will log at.
//! \return A stream to log a \a level message to.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
wiggly::log::logger::stream
wiggly::log::logger::log( const log_level& level )
{
    // if we need to log this level then return a stream capable of it
    if( level <= level_ )
    {
        return stream( this, level );
    }
    // otherwise return a null stream
    else
    {
        return stream();
    }
}

//! \brief FATAL logging method.
//!
//! Logs a FATAL message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::fatal( const std::string& message )
{
    log( FATAL, message );
}

//! \brief FATAL log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::fatal()
{
    return log( FATAL );
}

//! \brief PANIC logging method.
//!
//! Logs a PANIC message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::panic( const std::string& message )
{
    log( PANIC, message );
}

//! \brief PANIC log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::panic()
{
    return log( PANIC );
}

//! \brief ERROR logging method.
//!
//! Logs a ERROR message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::error( const std::string& message )
{
    log( ERROR, message );
}

//! \brief ERROR log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::error()
{
    return log( ERROR );
}

//! \brief WARN logging method.
//!
//! Logs a WARN message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::warn( const std::string& message )
{
    log( WARN, message );
}

//! \brief WARN log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::warn()
{
    return log( WARN );
}

//! \brief INFO logging method.
//!
//! Logs a INFO message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::info( const std::string& message )
{
    log( INFO, message );
}

//! \brief INFO log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::info()
{
    return log( INFO );
}

//! \brief NOTICE logging method.
//!
//! Logs a NOTICE message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::notice( const std::string& message )
{
    log( NOTICE, message );
}

//! \brief NOTICE log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::notice()
{
    return log( NOTICE );
}

//! \brief DEBUG logging method.
//!
//! Logs a DEBUG message.
//!
//! \param message The message to be logged.
//! \sa wiggly::log::logger::log( const log_level& level, const std::string& message )
//!
void
wiggly::log::logger::debug( const std::string& message )
{
    log( DEBUG, message );
}

//! \brief DEBUG log stream creation.
//!
//! \return A stream to log a FATAL message to. 
//! \sa wiggly::log::logger::log( const log_level& level )
//!
wiggly::log::logger::stream
wiggly::log::logger::debug()
{
    return log( DEBUG );
}

//! \class wiggly::log::logger::stream
//! \brief Log stream proxy class.
//!
//! A simple proxy class returned by the logger's stream methods. These
//! proxy streams are used to collect all of the items to be logged into a
//! stringstream, when the stream proxy is destroyed the string it has
//! collected is logged via the logger it was created from.
//!
//! Objects of this type returned by wiggly::log::logger should not be held
//! on to by clients because of the way in which it is designed, it
//! transfers ownership of its internal state on copy rather than actually
//! copying anything. If you hold on to it or copy it then weird things
//! could happen.
//!

wiggly::log::logger::stream::stream()
:
parent_( 0 ),
level_( FATAL ),
str_( 0 )
{
#ifndef NDEBUG
    cerr << "stream ctor\n";
#endif
}

wiggly::log::logger::stream::stream( logger* parent, const log_level& l )
:
parent_( parent ),
level_( l ),
str_( new ostringstream() )
{
#ifndef NDEBUG
    cerr << "stream ctor\n";
#endif
}

wiggly::log::logger::stream::~stream()
{
#ifndef NDEBUG
    cerr << "stream dtor\n";
#endif

    // if we are not a null stream
    if( ! is_null() )
    {
        // and we have some data
        if( str_.get() )
        {
            // log it
            parent_->log( level_, str_->str() );
        }
    }
}
