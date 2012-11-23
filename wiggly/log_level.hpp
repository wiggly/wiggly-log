#ifndef WIGGLY_LOG_LEVEL_HPP
#define WIGGLY_LOG_LEVEL_HPP
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
#include <iosfwd>

namespace wiggly
{

namespace log
{

//
// level of logging
//
class log_level
{
    public:
    
    log_level( int num, const std::string& name );
    
    ~log_level();

    log_level( const log_level& rhs );
    
    log_level& operator=( const log_level& rhs );
    
    std::string name() const;
    
    int num() const;

    private:
    
    int num_;
    std::string name_;
};


#define WIGGLY_LOG_LEVEL_FATAL (0)

const int FATAL_NUM = WIGGLY_LOG_LEVEL_FATAL;

extern const log_level FATAL;

#define WIGGLY_LOG_LEVEL_PANIC (10000)

const int PANIC_NUM = WIGGLY_LOG_LEVEL_PANIC;

extern const log_level PANIC;

#define WIGGLY_LOG_LEVEL_ERROR (20000)

const int ERROR_NUM = WIGGLY_LOG_LEVEL_ERROR;

extern const log_level ERROR;

#define WIGGLY_LOG_LEVEL_WARN (30000)

const int WARN_NUM = WIGGLY_LOG_LEVEL_WARN;

extern const log_level WARN;

#define WIGGLY_LOG_LEVEL_INFO (40000)

const int INFO_NUM = WIGGLY_LOG_LEVEL_INFO;

extern const log_level INFO;

#define WIGGLY_LOG_LEVEL_NOTICE (50000)

const int NOTICE_NUM = WIGGLY_LOG_LEVEL_NOTICE;

extern const log_level NOTICE;

#define WIGGLY_LOG_LEVEL_DEBUG (60000)

const int DEBUG_NUM = WIGGLY_LOG_LEVEL_DEBUG;

extern const log_level DEBUG;


//
// TODO : can we get rid of these by using rel_ops?
//
inline bool operator==( const log_level& a, const log_level& b )
{
    return a.num() == b.num();
}

inline bool operator!=( const log_level& a, const log_level& b )
{
    return a.num() != b.num();
}

inline bool operator<( const log_level& a, const log_level& b )
{
    return a.num() < b.num();
}

inline bool operator<=( const log_level& a, const log_level& b )
{
    return a.num() <= b.num();
}

inline bool operator>( const log_level& a, const log_level& b )
{
    return a.num() > b.num();
}

inline bool operator>=( const log_level& a, const log_level& b )
{
    return a.num() >= b.num();
}

inline std::ostream& operator<<( std::ostream& out, const log_level& value )
{
    out << value.name();
    return out;
}

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_LEVEL_HPP
