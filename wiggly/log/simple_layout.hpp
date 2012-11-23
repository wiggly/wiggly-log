#ifndef WIGGLY_LOG_SIMPLE_LAYOUT_HPP
#define WIGGLY_LOG_SIMPLE_LAYOUT_HPP
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

#include <iosfwd>
#include <wiggly/log/layout.hpp>

namespace wiggly
{

namespace log
{

class simple_layout : public layout
{
    public:

    simple_layout();
    
    virtual ~simple_layout();
    
    virtual void format(
        std::ostream& out,
        const wiggly::log::event& e ) const;
}; // simple_layout

} // namespace log

} // namespace wiggly

#endif // WIGGLY_LOG_SIMPLE_LAYOUT_HPP
