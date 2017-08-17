/*

to_value() wrappers.

Copyright (C) 2017 Sergey Kolevatov

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

// $Revision: 7629 $ $Date:: 2017-08-16 #$ $Author: serge $

#ifndef LIB_UTILS__TO_VALUE_H
#define LIB_UTILS__TO_VALUE_H

#include <string>                   // std::string

namespace utils
{

void to_value( bool * res, const std::string & val_str );
void to_value( std::int8_t * res, const std::string & val_str );
void to_value( std::int16_t * res, const std::string & val_str );
void to_value( std::int32_t * res, const std::string & val_str );
void to_value( std::int64_t * res, const std::string & val_str );
void to_value( std::uint8_t * res, const std::string & val_str );
void to_value( std::uint16_t * res, const std::string & val_str );
void to_value( std::uint32_t * res, const std::string & val_str );
void to_value( std::uint64_t * res, const std::string & val_str );
void to_value( float * res, const std::string & val_str );
void to_value( double * res, const std::string & val_str );

} // namespace utils

#endif // LIB_UTILS__TO_VALUE_H
