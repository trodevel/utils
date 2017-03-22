/*

HEX codec.

Copyright (C) 2015 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 6125 $ $Date:: 2017-03-20 #$ $Author: serge $

#include "hex_codec.h"                  // self

#include <boost/algorithm/hex.hpp>      // boost::unhex

namespace utils
{

std::string unhex_string( const std::string & s )
{
    return boost::algorithm::unhex( s );
}

std::string hex_string( const std::string & s )
{
    return boost::algorithm::hex( s );
}

} // namespace utils