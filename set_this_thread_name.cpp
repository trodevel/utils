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

#include "set_this_thread_name.h"   // self

#include <sys/prctl.h>              // prctl

namespace utils
{

void set_this_thread_name( const std::string & name )
{
    set_this_thread_name( name.c_str() );
}

// http://stackoverflow.com/questions/778085/how-to-name-a-thread-in-linux
void set_this_thread_name( const char * name )
{
#ifdef __linux__
#if defined( PR_SET_NAME )

    prctl( PR_SET_NAME, (unsigned long) name, 0, 0, 0 );

#endif
#endif
}

} // namespace utils
