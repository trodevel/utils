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

// $Revision: 8743 $ $Date:: 2018-03-12 #$ $Author: serge $

#include <vector>
#include <string>

#ifndef LIB_UTILS__READ_CONFIG_FILE_H
#define LIB_UTILS__READ_CONFIG_FILE_H

namespace utils
{

bool read_config_file(
        const std::string           & filename,
        std::vector<std::string>    & lines,
        const char                  comment_char = '#',
        bool                        throw_on_error = true );

}

#endif // LIB_UTILS__READ_CONFIG_FILE_H
