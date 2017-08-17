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

#include "to_value.h"               // self

#include <stdexcept>                // std::invalid_argument

namespace utils
{

void to_value( bool * res, const std::string & val_str )
{
    static const std::string true_1( "true" );
    static const std::string true_2( "yes" );
    static const std::string true_3( "on" );

    static const std::string false_1( "false" );
    static const std::string false_2( "no" );
    static const std::string false_3( "off" );

    if( val_str == true_1 || val_str == true_2 || val_str == true_3 )
    {
        * res = true;
        return;
    }

    if( val_str == false_1 || val_str == false_2 || val_str == false_3 )
    {
        * res = false;
        return;
    }

    std::uint16_t t;

    to_value( & t, val_str );

    if( t == 0 )
    {
        * res = false;
        return;
    }

    if( t == 1 )
    {
        * res = true;
        return;
    }

    throw std::invalid_argument( "invalid value" );
}

void to_value( std::int8_t * res, const std::string & val_str )
{
    * res   = static_cast<std::int8_t>( std::stoi( val_str ) );
}
void to_value( std::int16_t * res, const std::string & val_str )
{
    * res   = static_cast<std::int16_t>( std::stoi( val_str ) );
}
void to_value( std::int32_t * res, const std::string & val_str )
{
    * res   = static_cast<std::int32_t>( std::stol( val_str ) );
}
void to_value( std::int64_t * res, const std::string & val_str )
{
    * res   = static_cast<std::int64_t>( std::stoll( val_str ) );
}
void to_value( std::uint8_t * res, const std::string & val_str )
{
    * res   = static_cast<std::uint8_t>( std::stoul( val_str ) );
}
void to_value( std::uint16_t * res, const std::string & val_str )
{
    * res   = static_cast<std::uint16_t>( std::stoul( val_str ) );
}
void to_value( std::uint32_t * res, const std::string & val_str )
{
    * res   = static_cast<std::uint32_t>( std::stoul( val_str ) );
}
void to_value( std::uint64_t * res, const std::string & val_str )
{
    * res   = static_cast<std::uint64_t>( std::stoull( val_str ) );
}
void to_value( float * res, const std::string & val_str )
{
    * res   = std::stof( val_str );
}
void to_value( double * res, const std::string & val_str )
{
    * res   = std::stod( val_str );
}

} //namespace utils
