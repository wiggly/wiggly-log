#ifndef WIGGLY_LOG_EXC_HPP
#define WIGGLY_LOG_EXC_HPP
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

#include <exception>
#include <string>

namespace wiggly
{

namespace log
{

//
// general logging exception
//
class log_exception : public std::exception
{
    public:

    log_exception( const std::string& msg ) throw();
    
    virtual ~log_exception() throw();

    virtual const char* what() const throw();
    
    private:
    
    std::string msg_;

}; // class log_exception

//
// file access problems
//
class file_access_exception : public log_exception
{
    public:

    file_access_exception( const std::string& msg ) throw();
    
    virtual ~file_access_exception() throw();

}; // class file_access_exception

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_EXC_HPP
