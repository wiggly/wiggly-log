// wiggly-log C++ Logging Library
// Copyright (C) 2007 Nigel A. Rantor
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

#include <wiggly/log_format_xml.hpp>

using namespace std;


//! \class wiggly::log::log_format_xml
//! \brief Basic XML formatter class.
//!
//! Formatter class that simply dumps the available fields into an XML
//! record with no particular formatting of those values.
//!
    
wiggly::log::log_format_xml::~log_format_xml()
{}

void
wiggly::log::log_format_xml::format(
    std::ostream& out,
    const wiggly::log::event& rec ) const
{

    out << "<event>" << endl;
    out << "\t<level>" << endl;
    out << "\t\t<name>" << rec.level.name() << "</name>" << endl;
    out << "\t\t<number>" << rec.level.num() << "</number>" << endl;
    out << "\t</level>" << endl;
    out << "\t<time>" << rec.time << "</time>" << endl;
    out << "\t<logger>" << rec.logger_name << "</logger>" << endl;
    out << "\t<thread>" << rec.thread_name << "</thread>" << endl;
    out << "\t<message>" << rec.message << "</message>" << endl;
    out << "</event>" << endl;
    return;
}
