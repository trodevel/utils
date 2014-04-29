/*

Detects format of numbers in strings.

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

// $Id: number_format.cpp 376 2014-04-14 23:01:06Z serge $


// E110

#include "number_format.h"  // self

bool is_number_int( const std::string & arg )
{
    int sign_corr = 0;

    // check if sign is present
    if( arg.compare( 0, 1, "-" ) == 0 )
    {
        sign_corr = 1;
    }

    // check if hex number
    if( arg.compare( 0 + sign_corr, 2, "0x" ) == 0 )
    {
        for( int i = 2 + sign_corr; i < ( int )arg.length(); ++i )
            {
                int c = arg.at( i );
                if( ( c < '0' || c > '9' ) && ( c < 'a' || c > 'f' ) )
                    return false;
            }
    }
    else
    {
        // check if a decimal number
        for( int i = 0 + sign_corr; i < ( int )arg.length(); ++i )
        {
            int c = arg.at( i );
            if( c < '0' || c > '9')
                return false;
        }
    }
    return true;
}

bool is_number_float( const std::string & arg )
{
    // check if a floating point number
    for( int i = 0; i < ( int )arg.length(); ++i )
    {
        int c = arg.at( i );
        if( c != '-' && c != '.' && ( c < '0' || c > '9' ) )
            return false;
    }

    return true;
}
