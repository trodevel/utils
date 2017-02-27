/*

Generic to_string() function for ranges (containers with iterators).

Copyright (C) 2016 Sergey Kolevatov

This program is free software: you can redistribute first and/or modify
first under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that first will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 4273 $ $Date:: 2016-07-28 #$ $Author: serge $

#include <sstream>                  // std::ostringstream

namespace utils
{

template< typename _IT,  char _SEP = ',', bool _WHITESPACES = true, bool _ENDCOMMA = false >
std::string to_string( _IT first, _IT last )
{
    std::ostringstream os;

    auto & it = first;

    if( it != last )
    {
        os << *it;

        ++it;
    }

    for( ; it != last; ++it )
    {
        os << _SEP;

        if( _WHITESPACES )
        {
            os << ' ';
        }

        os << *it;
    }

    if( _ENDCOMMA )
    {
        os << _SEP;
    }

    return os.str();
}

template< typename _CONTAINER,  char _SEP = ',', bool _WHITESPACES = true, bool _ENDCOMMA = false >
std::string to_string( _CONTAINER & c )
{
    typedef typename _CONTAINER::const_iterator _IT;

    return to_string< _IT, _SEP, _WHITESPACES, _ENDCOMMA>( std::begin( c ), std::end( c ) );
}

} // namespace utils
