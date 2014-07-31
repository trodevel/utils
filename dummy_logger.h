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

// $Id: dummy_logger.h 853 2014-07-30 17:09:52Z serge $

#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H

enum class log_levels_log4j
{
    OFF     = 0,
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE
};

void dummy_log( const int level, const char *module_name, const char *fmt, ... );

void dummy_log_set_log_level( const log_levels_log4j level );

#define dummy_log_fatal( _mod, _fmt, ... )      ::dummy_log( ( int ) log_levels_log4j::FATAL, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_error( _mod, _fmt, ... )      ::dummy_log( ( int ) log_levels_log4j::ERROR, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_warn( _mod, _fmt, ... )       ::dummy_log( ( int ) log_levels_log4j::WARN,  _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_info( _mod, _fmt, ... )       ::dummy_log( ( int ) log_levels_log4j::INFO,  _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_debug( _mod, _fmt, ... )      ::dummy_log( ( int ) log_levels_log4j::DEBUG, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_trace( _mod, _fmt, ... )      ::dummy_log( ( int ) log_levels_log4j::TRACE, _mod, _fmt, ##__VA_ARGS__ )

#endif // DUMMY_LOGGER_H
