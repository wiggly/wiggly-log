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

#include <wiggly/log_exc.hpp>

using namespace std;

wiggly::log::log_exception::log_exception( const std::string& msg ) throw()
: exception(), msg_( msg )
{}
    
wiggly::log::log_exception::~log_exception() throw()
{}

const char*
wiggly::log::log_exception::what() const throw()
{
    return msg_.c_str();
}

wiggly::log::file_access_exception::file_access_exception( const std::string& msg ) throw()
: log_exception( msg )
{}

wiggly::log::file_access_exception::~file_access_exception() throw()
{}
