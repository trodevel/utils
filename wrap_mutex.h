/*

Convenience wrapper for boost mutexes.

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

// $Id: wrap_mutex.h 930 2014-08-14 09:46:41Z serge $

#ifndef _WRAP_MUTEX_H_
#define _WRAP_MUTEX_H_

#define CPP_MUTEX(_x)           boost::mutex _x
#define CPP_COND(_x)
#define CPP_INIT_COND(_x)
#define CPP_BROADCAST_COND(_x)
#define SCOPE_LOCK(_x)          boost::mutex::scoped_lock _scoped_lock##_x(_x)
#define THREAD_SLEEP_MS(_x)     boost::this_thread::sleep( boost::posix_time::milliseconds( _x ) )
#define THREAD_SLEEP_SEC(_x)    boost::this_thread::sleep( boost::posix_time::seconds( _x ) )

#endif // _WRAP_MUTEX_H_
