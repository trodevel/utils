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

#include <string>

#ifndef LIB_UTILS__READ_TEXT_FILE_H
#define LIB_UTILS__READ_TEXT_FILE_H

namespace utils
{

std::string read_text_file(
        const std::string           & filename,
        bool                        throw_on_error = true );

}

#endif // LIB_UTILS__READ_TEXT_FILE_H
