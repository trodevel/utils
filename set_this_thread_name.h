/*

Set name of current thread.

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

// $Revision: 5792 $ $Date:: 2017-02-20 #$ $Author: serge $

#ifndef UTILS_SET_THIS_THREAD_NAME_H
#define UTILS_SET_THIS_THREAD_NAME_H

#include <string>   // std::string

namespace utils
{

void set_this_thread_name( const std::string & name );
void set_this_thread_name( const char * name );

} // namespace utils

#endif // UTILS_SET_THIS_THREAD_NAME_H
