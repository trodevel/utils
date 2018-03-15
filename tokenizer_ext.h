/*

Extended tokenizer and converter.

Copyright (C) 2018 Sergey Kolevatov

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

// $Revision: 8753 $ $Date:: 2018-03-13 #$ $Author: serge $

#ifndef LIB_UTILS__TOKENIZER_EXT_H
#define LIB_UTILS__TOKENIZER_EXT_H

#include "tokenizer.h"
#include "to_value.h"       // to_value()

namespace utils
{

template <class T>
void tokenize_and_convert( std::vector<T> & res, const std::string & str, const char * delimeter )
{
    std::vector<std::string> temp;

    ::tokenize_to_vector( temp, str, delimeter, true );

    res.reserve( temp.size() );

    for( auto & e : temp )
    {
        T v;

        to_value( & v, e );

        res.push_back( v );
    }
}

} // namespace utils

#endif // LIB_UTILS__TOKENIZER_EXT_H
