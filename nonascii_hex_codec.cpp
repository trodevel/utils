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

// $Revision: 8018 $ $Date:: 2017-10-11 #$ $Author: serge $

#include "nonascii_hex_codec.h"         // self

#include <boost/algorithm/hex.hpp>      // boost::unhex

namespace utils
{

namespace nonascii_hex_codec
{

std::string decode( const std::string & s )
{
    std::string res;

    auto size = s.size();

    if( size == 1 )
    {
        // empty string
        if( s == "=" )
            return res;
    }

    for( std::string::size_type i = 0; i < size; ++i )
    {
        auto c = s[i];

        if( c == '=' &&  ( i + 2 < size ) )
        {
            res += boost::algorithm::unhex( s.substr( i + 1, 2 ) );
            i += 2;
        }
        else
            res += c;
    }

    return res;

    return boost::algorithm::unhex( s );
}

std::string encode( const std::string & s )
{
    std::string res;

    if( s.empty() )
    {
        // empty string
        return std::string( "=" );
    }

    for( auto & c : s )
    {
        if( c < 33 || c > 126 || c == '=' )
        {
            res += "=";
#if BOOST_VERSION < 106501
            (void) boost::algorithm::detail::encode_one( c, std::back_inserter( res ) );
#else
            (void) boost::algorithm::detail::encode_one( c, std::back_inserter( res ), "0123456789ABCDEF" );
#endif
        }
        else
            res += c;
    }

    return res;
}

}

} // namespace utils
