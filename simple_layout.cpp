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

#include "config.h"
#include "detail.hpp"

#include <wiggly/log/simple_layout.hpp>

//! \class wiggly::log::simple_layout
//! \brief Simple layout class.
//!

wiggly::log::simple_layout::simple_layout()
{}
    
wiggly::log::simple_layout::~simple_layout()
{}

void
wiggly::log::simple_layout::format(
    std::ostream& out,
    const wiggly::log::event& e ) const
{
    out << e.time << " " <<
    e.level << " " <<
    "[" << e.thread_name << "] " <<
    e.logger_name << " " <<
    e.message << "\n";
    return;
}
