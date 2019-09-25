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

// $Revision: 12036 $ $Date:: 2019-09-25 #$ $Author: serge $

#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H

#include <string>           // std::string

enum class log_levels_log4j
{
    OFF     = 0,
    FATAL,
    ERROR,
    WARN,
    INFO,
    Debug,
    TRACE
};

#define dummy_log_fatal( _mod,  _fmt, ... )     dummy_logger::log( log_levels_log4j::FATAL, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_error( _mod,  _fmt, ... )     dummy_logger::log( log_levels_log4j::ERROR, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_warn( _mod,   _fmt, ... )     dummy_logger::log( log_levels_log4j::WARN,  _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_info( _mod,   _fmt, ... )     dummy_logger::log( log_levels_log4j::INFO,  _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_debug( _mod,  _fmt, ... )     dummy_logger::log( log_levels_log4j::Debug, _mod, _fmt, ##__VA_ARGS__ )
#define dummy_log_trace( _mod,  _fmt, ... )     dummy_logger::log( log_levels_log4j::TRACE, _mod, _fmt, ##__VA_ARGS__ )

#define dummy_logi_fatal( _mod, _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::FATAL, _mod, _inst, _fmt, ##__VA_ARGS__ )
#define dummy_logi_error( _mod, _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::ERROR, _mod, _inst, _fmt, ##__VA_ARGS__ )
#define dummy_logi_warn( _mod,  _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::WARN,  _mod, _inst, _fmt, ##__VA_ARGS__ )
#define dummy_logi_info( _mod,  _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::INFO,  _mod, _inst, _fmt, ##__VA_ARGS__ )
#define dummy_logi_debug( _mod, _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::Debug, _mod, _inst, _fmt, ##__VA_ARGS__ )
#define dummy_logi_trace( _mod, _inst, _fmt, ... )      dummy_logger::log( log_levels_log4j::TRACE, _mod, _inst, _fmt, ##__VA_ARGS__ )

namespace dummy_logger {

class IWriter
{
public:
    virtual ~IWriter() {};

    virtual void write( const log_levels_log4j level, const char *module_name, const std::string & msg ) = 0;
    virtual void write( const log_levels_log4j level, const char *module_name, unsigned int inst_id, const std::string & msg ) = 0;
    virtual void write( const char *module_name, const std::string & msg ) = 0;
    virtual void write( const char *module_name, unsigned int inst_id, const std::string & msg ) = 0;
};

void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... );
void log( const log_levels_log4j level, unsigned int module_id, unsigned int inst_id, const char *fmt, ... );
void log( const log_levels_log4j level, const char *module_name, const char *fmt, ... );
unsigned int register_module( const char *module_name );
void set_log_level( const log_levels_log4j level );
void set_log_level( unsigned int module_id, const log_levels_log4j level );
void set_level_output( bool b );
void set_writer( IWriter * writer, unsigned int module_id = 0 );

const std::string & to_string( const log_levels_log4j level );

} // namespace dummy_logger

#endif // DUMMY_LOGGER_H
