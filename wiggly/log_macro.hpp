#ifndef WIGGLY_LOG_MACRO_HPP
#define WIGGLY_LOG_MACRO_HPP
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

#include <wiggly/logger.hpp>
#include <string>

//
// if we have not had the global level set then set it low enough that we
// output nothing
//
#ifndef WIGGLY_LOG_LEVEL
#define WIGGLY_LOG_LEVEL (-1)
#endif

//
// logging macros
//
// these either get generated as inline functions that can accept a log
// object by pointer/reference if the log level they log for is less than or
// equal to the WIGGLY_LOG_LEVEL preprocessor symbol or they get output as
// nop loops
//
// there may be a better way of doing this using TMP but quite frankly it's
// not worth the hassle to figure out right now since this works, and will
// work on a vast number of systems.
//

#if( WIGGLY_LOG_LEVEL_FATAL <= WIGGLY_LOG_LEVEL )

#define WIGGLY_LOG_FATAL( log, stream_commands ) { log.fatal() stream_commands; }

inline void WIGGLY_LOG_STR_FATAL( wiggly::log::logger& log, const std::string& message )
{
    log.fatal( message );
}

inline void WIGGLY_LOG_STR_FATAL( wiggly::log::logger* log, const std::string& message )
{
    log->fatal( message );
}

#define WIGGLY_LOG_GET_LOGGER( log, name ) wiggly::log::logger&log = wiggly::log::logger::get_logger( name );

#else

#define WIGGLY_LOG_FATAL( log, stream_commands ) { while(0) {}; }

#define WIGGLY_LOG_STR_FATAL( log, message ) { while(0) {}; }

#define WIGGLY_LOG_GET_LOGGER( log, name ) { while(0) {}; }

#endif

#if( WIGGLY_LOG_LEVEL_ERROR <= WIGGLY_LOG_LEVEL )

#define WIGGLY_LOG_ERROR( log, stream_commands ) { log.error() stream_commands; }

inline void WIGGLY_LOG_STR_ERROR( wiggly::log::logger& log, const std::string& message )
{
    log.error( message );
}

inline void WIGGLY_LOG_STR_ERROR( wiggly::log::logger* log, const std::string& message )
{
    log->error( message );
}

#else

#define WIGGLY_LOG_ERROR( log, message ) { while(0) {}; }

#define WIGGLY_LOG_STR_ERROR( log, message ) { while(0) {}; }

#endif

#if( WIGGLY_LOG_LEVEL_WARN <= WIGGLY_LOG_LEVEL )

#define WIGGLY_LOG_WARN( log, stream_commands ) { log.warn() stream_commands; }

inline void WIGGLY_LOG_STR_WARN( wiggly::log::logger& log, const std::string& message )
{
    log.warn( message );
}

inline void WIGGLY_LOG_STR_WARN( wiggly::log::logger* log, const std::string& message )
{
    log->warn( message );
}

#else

#define WIGGLY_LOG_WARN( log, message ) { while(0) {}; }

#define WIGGLY_LOG_STR_WARN( log, message ) { while(0) {}; }

#endif

#if( WIGGLY_LOG_LEVEL_INFO <= WIGGLY_LOG_LEVEL )

#define WIGGLY_LOG_INFO( log, stream_commands ) { log.info() stream_commands; }

inline void WIGGLY_LOG_STR_INFO( wiggly::log::logger& log, const std::string& message )
{
    log.info( message );
}

inline void WIGGLY_LOG_STR_INFO( wiggly::log::logger* log, const std::string& message )
{
    log->info( message );
}

#else

#define WIGGLY_LOG_INFO( log, message ) { while(0) {}; }

#define WIGGLY_LOG_STR_INFO( log, message ) { while(0) {}; }

#endif

#if( WIGGLY_LOG_LEVEL_DEBUG <= WIGGLY_LOG_LEVEL )

#define WIGGLY_LOG_DEBUG( log, stream_commands ) { log.debug() stream_commands; }

inline void WIGGLY_LOG_STR_DEBUG( wiggly::log::logger& log, const std::string& message )
{
    log.debug( message );
}

inline void WIGGLY_LOG_STR_DEBUG( wiggly::log::logger* log, const std::string& message )
{
    log->debug( message );
}

#else

#define WIGGLY_LOG_DEBUG( log, message ) { while(0) {}; }

#define WIGGLY_LOG_STR_DEBUG( log, message ) { while(0) {}; }

#endif

#endif // WIGGLY_LOG_MACRO_HPP
