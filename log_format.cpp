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

#include <wiggly/log_format.hpp>

//! \class wiggly::log::log_format
//! \brief Base formatter class.
//!
//! Base for classes wishing to provide formatting for logging records.
//!
//! Currently this class is not meant to be used to create your own format
//! classes, the current way in which log records are represented is
//! simplistic and liable to change. However, having said that, if you're
//! after both speed and flexibility then you may want to.
//!
//! There are a small number of concrete format classes, have a look at
//! their own documentation to find out more about their charactersitics.
