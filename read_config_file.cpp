/*

Read config file.

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

// $Revision: 8843 $ $Date:: 2018-03-28 #$ $Author: serge $

#include "read_config_file.h"       // self

#include <stdexcept>                // std::runtime_error
#include <fstream>                  // std::ifstream

#include "trim.h"                   // trim

namespace utils
{

bool read_config_file( const std::string & filename, std::vector<std::string> & lines, const char comment_char, bool throw_on_error )
{
    std::ifstream inp( filename.c_str() );
    std::string line;

    if( inp.is_open() == false )
    {
        if( throw_on_error )
            throw std::runtime_error( "read_config_file: cannot open '" + filename + "'" );

        return false;
    }

    while( inp.good() )
    {
        getline( inp, line );

        std::string clean_line = trim( line );

        if( clean_line.empty() )
            continue;

        if( clean_line.at( 0 ) == comment_char )
            continue;

        lines.push_back( clean_line );
    }

    inp.close();

    return true;
}

} // namespace utils
