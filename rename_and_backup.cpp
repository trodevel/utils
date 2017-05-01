/*

Rename file and make a backup copy of the target file if it already exists.

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

// $Revision: 6791 $ $Date:: 2017-04-28 #$ $Author: serge $

#include "rename_and_backup.h"      // self

#include <cstdio>                   // std::rename

namespace utils
{

bool rename_and_backup( const std::string & old_name, const std::string & new_name )
{
    auto backup_name    = new_name + ".old";

    std::remove( backup_name.c_str() );

    std::rename( new_name.c_str(), backup_name.c_str() );

    std::remove( new_name.c_str() );

    std::rename( old_name.c_str(), new_name.c_str() );

    return true;
}

} // namespace utils
