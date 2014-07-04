/*

Dummy logger.

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

// $Id: dummy_logger.cpp 709 2014-07-03 17:52:00Z serge $


#include "dummy_logger.h"       // self
#include "vformat.h"            // vformat
#include <iostream>             // cout

#ifndef NOTHREAD
#include <boost/thread.hpp>     // boost::mutex
#include "wrap_mutex.h"         // SCOPE_LOCK
#endif

struct DummyLoggerState
{
    log_levels_log4j max_log_level;
};

DummyLoggerState    gl_dummy_logger_state   = { log_levels_log4j::INFO };

void dummy_log_core( const char *module_name, const std::string & msg )
{
#ifndef NOTHREAD

    static boost::mutex mutex;

    SCOPE_LOCK( mutex );

#endif // NOTHREAD

    std::cout << module_name << ": " << msg << std::endl;
}

void dummy_log( const int level, const char *module_name, const char *fmt, ... )
{
    if( level > ( int ) gl_dummy_logger_state.max_log_level )
        return;

    std::string res;
    va_list ap;
    va_start( ap, fmt );

    res = vformat( fmt, ap );
    va_end( ap );

    dummy_log_core( module_name, res );
}

void dummy_log_set_log_level( const log_levels_log4j level )
{
    gl_dummy_logger_state.max_log_level = level;
}
