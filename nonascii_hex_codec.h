/*

NON-ASCII HEX codec.

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

// $Revision: 6192 $ $Date:: 2017-03-22 #$ $Author: serge $

#ifndef LIB_UTILS_NONASCII_HEX_CODEC_H
#define LIB_UTILS_NONASCII_HEX_CODEC_H

#include <string>

namespace utils
{

namespace nonascii_hex_codec
{

std::string decode( const std::string & s );
std::string encode( const std::string & s );

}

} // namespace utils

#endif // LIB_UTILS_NONASCII_HEX_CODEC_H
