/*

Some string utils.

Copyright (C) 2014 Sergey Kolevatov

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

// $Id: string_utils.h 376 2014-04-14 23:01:06Z serge $


// DC18

#include <string>

#include "../utils/trim.h"      // trim
/**
 * @descr remove comments starting with '#'
 */
std::string remove_comments( const std::string & str, const std::string::value_type c = '#' )
{
    std::string::size_type hash_pos = str.find( c );

    if( std::string::npos == hash_pos )
        return str;

    std::string res = str.substr( 0, hash_pos );

    return trim( res );
}

// @descr removes first and last symbol from a string
std::string remove_quotes( const std::string & str, const std::string::value_type = '#' )
{
    if( str.length() <= 2 )
        return str;

    return str.substr( 1, str.length() - 2 );
}

