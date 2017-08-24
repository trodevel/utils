/*

Wrapper for boost::regex_match()

Copyright (C) 2016 Sergey Kolevatov

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

// $Revision: 7694 $ $Date:: 2017-08-22 #$ $Author: serge $

#ifndef LIB_UTILS_REGEX_MATCH_H
#define LIB_UTILS_REGEX_MATCH_H

#include <string>           // std::string

namespace utils
{

bool regex_match( const std::string & s, const std::string & regex );

bool regex_match_i( const std::string & s, const std::string & regex );

} // namespace utils

#endif // LIB_UTILS_REGEX_MATCH_H
