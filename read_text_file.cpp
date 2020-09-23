/*

Read text file.

Copyright (C) 2020 Sergey Kolevatov

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

// $Revision: 13826 $ $Date:: 2020-09-23 #$ $Author: serge $

#include "read_text_file.h"       // self

#include <stdexcept>                // std::runtime_error
#include <fstream>                  // std::ifstream
#include <sstream>

namespace utils
{

std::string read_text_file(
        const std::string           & filename,
        bool                        throw_on_error )
{
    std::ifstream inp( filename );

    if( inp.is_open() == false )
    {
        if( throw_on_error )
            throw std::runtime_error( "read_text_file: cannot open '" + filename + "'" );

        return std::string();
    }

    std::stringstream buffer;

    buffer << inp.rdbuf();

    return buffer.str();
}

} // namespace utils
