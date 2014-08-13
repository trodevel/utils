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

// $Id: dummy_logger.cpp 914 2014-08-13 17:29:04Z serge $


#include "dummy_logger.h"       // self

#include <functional>           // std::hash
#include <iostream>             // cout
#include <map>                  // std::map
//#include <unordered_map>
#include "vformat.h"            // vformat

#ifndef NOTHREAD
#include <boost/thread.hpp>     // boost::mutex
#include "wrap_mutex.h"         // SCOPE_LOCK
#endif

namespace dummy_logger {

#ifdef NOTHREAD
#define DL_SCOPE_LOCK(_x)
#define DL_LOCK(_x)
#define DL_UNLOCK(_x)
#else
#define DL_SCOPE_LOCK(_x)       SCOPE_LOCK(_x)
#define DL_LOCK(_x)             _x.lock()
#define DL_UNLOCK(_x)           _x.unlock()
#endif

struct State
{
    struct Module
    {
        log_levels_log4j    max_log_level;
        std::string         name;

        bool can_log( log_levels_log4j level ) const
        {
            return level <= max_log_level;
        }
    };

    typedef std::map< unsigned int, Module >    MapModuleIdToModule;

    State();

    bool register_module( unsigned int module_id, const std::string & name, log_levels_log4j level );

    bool can_log( log_levels_log4j level ) const;
    void set_log_level( const log_levels_log4j level );
    void set_log_level( unsigned int module_id, const log_levels_log4j level );
    void set_level_output( bool b );

    const Module & get_module_and_lock( unsigned int module_id ) const;

    void unlock() const;

    void log__no_lock( const log_levels_log4j level, const Module & m , const char *fmt, va_list ap );

    void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... );
    void log( const log_levels_log4j level, const char *module_name, const std::string & msg );
private:

    void output__( const log_levels_log4j level, const Module & m, const std::string & msg );

    void output__( const log_levels_log4j level, const char *module_name, const std::string & msg );

    const Module & get_module__( unsigned int module_id ) const;

    static const std::string & to_string( const log_levels_log4j level );

public:
    static const Module         empty_mod_;
    static const Module         & empty_mod;

private:

#ifndef NOTHREAD
    mutable boost::mutex        mutex_;
#endif // NOTHREAD

    log_levels_log4j            max_log_level_   = log_levels_log4j::INFO;

    MapModuleIdToModule         module_map_;
    bool                        must_print_level_;
};

const State::Module    State::empty_mod_    = { log_levels_log4j::OFF };
const State::Module    & State::empty_mod   = State::empty_mod_;

State::State():
        must_print_level_( true )
{
}

bool State::register_module( unsigned int module_id, const std::string & name, log_levels_log4j level )
{
    DL_SCOPE_LOCK( mutex_ );

    Module m = { level, name };

    module_map_[ module_id ] = m;

    return true;
}

bool State::can_log( log_levels_log4j level ) const
{
    DL_SCOPE_LOCK( mutex_ );

    return level <= max_log_level_;
}

void State::set_log_level( const log_levels_log4j level )
{
    DL_SCOPE_LOCK( mutex_ );

    max_log_level_   = level;

}
void State::set_log_level( unsigned int module_id, const log_levels_log4j level )
{
    DL_SCOPE_LOCK( mutex_ );

    module_map_[ module_id ].max_log_level = level;
}

void State::set_level_output( bool b )
{
    DL_SCOPE_LOCK( mutex_ );

    must_print_level_   = b;
}

const State::Module & State::get_module_and_lock( unsigned int module_id ) const
{
    DL_LOCK( mutex_ );

    MapModuleIdToModule::const_iterator it = module_map_.find( module_id );

    if( it == module_map_.end() )
    {
        DL_UNLOCK( mutex_ );

        return empty_mod;
    }

    return ( *it ).second;
}

void State::unlock() const
{
    DL_UNLOCK( mutex_ );
}


void State::log__no_lock( const log_levels_log4j level, const Module & m , const char *fmt, va_list ap )
{
    if( m.can_log( level ) == false )
        return;

    std::string res = vformat( fmt, ap );

    output__( level, m, res );
}

void State::log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... )
{
    DL_SCOPE_LOCK( mutex_ );

    const Module & m = get_module__( module_id );

    if( & m == & empty_mod )
        return;

    va_list ap;
    va_start( ap, fmt );

    log__no_lock( level, m, fmt, ap );

    va_end( ap );
}

void State::log( const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    DL_SCOPE_LOCK( mutex_ );

    output__( level, module_name, msg );
}
// private:

void State::output__( const log_levels_log4j level, const Module & m, const std::string & msg )
{
    if( must_print_level_ )
        //std::cout << to_string( level ) << " " << m.name << ": " << msg << std::endl;
        std::cout << to_string( level ) << "|" << m.name << ": " << msg << std::endl;
    else
        std::cout << m.name << ": " << msg << std::endl;
}

void State::output__( const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    if( must_print_level_ )
        //std::cout << to_string( level ) << " " << module_name << ": " << msg << std::endl;
        std::cout << to_string( level ) << "|" << module_name << ": " << msg << std::endl;
    else
        std::cout << module_name << ": " << msg << std::endl;
}


const State::Module & State::get_module__( unsigned int module_id ) const
{
    MapModuleIdToModule::const_iterator it = module_map_.find( module_id );

    if( it == module_map_.end() )
        return empty_mod;

    return ( *it ).second;
}

const std::string & State::to_string( const log_levels_log4j level )
{
    static const std::string names[]   =
    {
    "     ",
    "FATAL",
    "ERROR",
    " WARN",
    " INFO",
    "DEBUG",
    "TRACE",
    };

    if( level < log_levels_log4j::OFF || level > log_levels_log4j::TRACE )
        return names[0];

    return names[ static_cast<unsigned int>( level ) ];
}

// ***********************************************************************************

State    state;

void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... )
{
    const State::Module & m = state.get_module_and_lock( module_id );

    if( & m == & State::empty_mod )
        return;

    va_list ap;
    va_start( ap, fmt );

    state.log__no_lock( level, m, fmt, ap );

    va_end( ap );

    state.unlock();
}

// old version for macro compatibility
void log( const log_levels_log4j level, const char *module_name, const char *fmt, ... )
{
    if( state.can_log( level ) == false )
        return;

    std::string res;
    va_list ap;
    va_start( ap, fmt );

    res = vformat( fmt, ap );
    va_end( ap );

    state.log( level, module_name, res );
}



unsigned int get_hash( const std::string & module_name )
{
    size_t hash = std::hash<std::string>()( module_name );
    return ( unsigned int ) hash;
}

unsigned int register_module( const std::string & module_name )
{
    unsigned int hash = get_hash( module_name );

    bool b = state.register_module( hash, module_name, log_levels_log4j::INFO );

    return b ? hash : 0;
}

unsigned int register_module( const char *module_name )
{
    return register_module( std::string ( module_name ) );
}

void set_log_level( const log_levels_log4j level )
{
    state.set_log_level( level );
}

void set_log_level( unsigned int module_id, const log_levels_log4j level )
{
    state.set_log_level( module_id, level );
}

void set_level_output( bool b )
{
    state.set_level_output( b );
}


} // namespace dummy_logger

void dummy_log( const int level, const char *module_name, const char *fmt, ... )
{
    if( dummy_logger::state.can_log( ( log_levels_log4j )level ) == false )
        return;

    std::string res;
    va_list ap;
    va_start( ap, fmt );

    res = vformat( fmt, ap );
    va_end( ap );

    dummy_logger::state.log( ( log_levels_log4j )level, module_name, res );
}

void dummy_log_set_log_level( const log_levels_log4j level )
{
    dummy_logger::set_log_level( level );
}
