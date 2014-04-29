/*

String tokenizer supporting quotes.

Inspired by stackoverflow:
http://stackoverflow.com/questions/18675364/c-tokenize-a-string-with-spaces-and-quotes

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

// $Id: tokenizer.h 359 2014-04-10 17:01:58Z serge $

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

inline void tokenize_to_vector( std::vector<std::string> & res, const std::string & str, const char * delimeter )
{
    std::string temp;

    const char quote = '"';

    for( size_t i = 0; i < str.length(); i++ )
    {
        char c = str[i];
        if( c == delimeter[0] )
        {
            if( !temp.empty() )
            {
                res.push_back( temp );
                temp.clear();
            }
        }
        else if( c == quote )
        {
            i++;
            while( str[i] != quote )
            {
                temp.append( 1, str[i] );
                i++;
            }
        }
        else
        {
            temp.append( 1, c );
        }
    }

    if( !temp.empty() )
    {
        res.push_back( temp );
    }
}


#endif // TOKENIZER_H
