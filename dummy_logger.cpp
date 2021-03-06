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

// $Revision: 6779 $ $Date:: 2017-04-28 #$ $Author: serge $


#include "dummy_logger.h"       // self

#include <functional>           // std::hash
#include <iostream>             // cout
#include <map>                  // std::map
//#include <unordered_map>
#include "vformat.h"            // vformat

#ifndef NOTHREAD
#include <mutex>                // std::mutex
#include "mutex_helper.h"       // MUTEX_SCOPE_LOCK
#endif

namespace dummy_logger {

#ifdef NOTHREAD
#define DL_SCOPE_LOCK(_x)
#define DL_LOCK(_x)
#define DL_UNLOCK(_x)
#else
#define DL_SCOPE_LOCK(_x)       MUTEX_SCOPE_LOCK(_x)
#define DL_LOCK(_x)             _x.lock()
#define DL_UNLOCK(_x)           _x.unlock()
#endif

class CoutWriter: public IWriter
{
public:

    void write( const log_levels_log4j level, const char *module_name, const std::string & msg )
    {
        std::cout << to_string( level ) << "|" << module_name << ": " << msg << "\n";
    }

    void write( const log_levels_log4j level, const char *module_name, unsigned int inst_id, const std::string & msg )
    {
        std::cout << to_string( level ) << "|" << module_name << "[" << inst_id << "]: " << msg << "\n";
    }

    void write( const char *module_name, const std::string & msg )
    {
        std::cout << module_name << ": " << msg << "\n";
    }

    void write( const char *module_name, unsigned int inst_id, const std::string & msg )
    {
        std::cout  << module_name << "[" << inst_id << "]: " << msg << "\n";
    }

};

const std::string & to_string( const log_levels_log4j level )
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


CoutWriter cout_writer;

struct State
{
    struct Module
    {
        log_levels_log4j    max_log_level;
        std::string         name;
        IWriter             * writer_;

        Module(
                log_levels_log4j    max_log_level,
                std::string         name,
                IWriter             * writer ):
                max_log_level( max_log_level ),
                name( name ),
                writer_( writer )
        {
        }

        bool can_log( log_levels_log4j level ) const
        {
            return level <= max_log_level;
        }
    };

    typedef std::map< unsigned int, Module >    MapModuleIdToModule;

    State();

    bool register_module( unsigned int module_id, const std::string & name, log_levels_log4j level );
    bool register_module( unsigned int module_id, const std::string & name );

    bool can_log( log_levels_log4j level ) const;
    void set_log_level( const log_levels_log4j level );
    void set_log_level( unsigned int module_id, const log_levels_log4j level );
    void set_level_output( bool b );
    void set_writer( IWriter * writer, unsigned int module_id );

    void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... );
    void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, va_list ap );
    void log( const log_levels_log4j level, unsigned int module_id, unsigned int inst_id, const char *fmt, va_list ap );
    void log( const log_levels_log4j level, const char *module_name, const char *fmt, ... );
    void log( const log_levels_log4j level, const char *module_name, const char *fmt, va_list ap );

private:

    bool can_log__( log_levels_log4j level ) const;

    void log_module( const log_levels_log4j level, const Module & m, const char *fmt, va_list ap );
    void log_module( const log_levels_log4j level, const Module & m, unsigned int inst_id, const char *fmt, va_list ap );
    void log_module_name( const log_levels_log4j level, const char * module_name, const char *fmt, va_list ap );

    void output__( const log_levels_log4j level, const Module & m, const std::string & msg );
    void output__( const log_levels_log4j level, const Module & m, unsigned int inst_id, const std::string & msg );

    void output__( const log_levels_log4j level, const char *module_name, const std::string & msg );

    void output_writer( IWriter & writer, const log_levels_log4j level, const Module & m, const std::string & msg );
    void output_writer( IWriter & writer, const log_levels_log4j level, const Module & m, unsigned int inst_id, const std::string & msg );
    void output_writer( IWriter & writer, const log_levels_log4j level, const char *module_name, const std::string & msg );

    const Module & get_module__( unsigned int module_id ) const;
    Module & get_module( unsigned int module_id );

public:
    static const Module         empty_mod_;
    static const Module         & empty_mod;

private:

#ifndef NOTHREAD
    mutable std::mutex          mutex_;
#endif // NOTHREAD

    log_levels_log4j            max_log_level_   = log_levels_log4j::INFO;

    MapModuleIdToModule         module_map_;
    bool                        must_print_level_;

    IWriter                     * writer_;
};

const State::Module    State::empty_mod_( log_levels_log4j::OFF, "", nullptr );
const State::Module    & State::empty_mod   = State::empty_mod_;

State::State():
        must_print_level_( true ),
        writer_( & cout_writer )
{
}

bool State::register_module( unsigned int module_id, const std::string & name, log_levels_log4j level )
{
    DL_SCOPE_LOCK( mutex_ );

    Module m( level, name, nullptr );

    module_map_.insert( MapModuleIdToModule::value_type( module_id, m ) );

    return true;
}

bool State::register_module( unsigned int module_id, const std::string & name )
{
    DL_SCOPE_LOCK( mutex_ );

    Module m( max_log_level_, name, nullptr );

    module_map_.insert( MapModuleIdToModule::value_type( module_id, m ) );

    return true;
}

bool State::can_log( log_levels_log4j level ) const
{
    DL_SCOPE_LOCK( mutex_ );

    return can_log__( level );
}

bool State::can_log__( log_levels_log4j level ) const
{
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

    get_module( module_id ).max_log_level = level;
}

void State::set_level_output( bool b )
{
    DL_SCOPE_LOCK( mutex_ );

    must_print_level_   = b;
}

void State::set_writer( IWriter * writer, unsigned int module_id )
{
    DL_SCOPE_LOCK( mutex_ );

    if( module_id == 0 )
        writer_ = writer;
    else
    {
        get_module( module_id ).writer_   = writer;
    }
}

void State::log_module( const log_levels_log4j level, const Module & m , const char *fmt, va_list ap )
{
    if( m.can_log( level ) == false )
        return;

    std::string res = vformat( fmt, ap );

    output__( level, m, res );
}

void State::log_module( const log_levels_log4j level, const Module & m, unsigned int inst_id, const char *fmt, va_list ap )
{
    if( m.can_log( level ) == false )
        return;

    std::string res = vformat( fmt, ap );

    output__( level, m, inst_id, res );
}

void State::log_module_name( const log_levels_log4j level, const char * module_name, const char *fmt, va_list ap )
{
    if( can_log__( level ) == false )
        return;

    std::string res = vformat( fmt, ap );

    output__( level, module_name, res );
}

void State::log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );

    log( level, module_id, fmt, ap );

    va_end( ap );
}

void State::log( const log_levels_log4j level, unsigned int module_id, const char *fmt, va_list ap )
{
    DL_SCOPE_LOCK( mutex_ );

    const Module & m = get_module__( module_id );

    if( & m == & empty_mod )
        return;

    log_module( level, m, fmt, ap );
}

void State::log( const log_levels_log4j level, unsigned int module_id, unsigned int inst_id, const char *fmt, va_list ap )
{
    DL_SCOPE_LOCK( mutex_ );

    const Module & m = get_module__( module_id );

    if( & m == & empty_mod )
        return;

    log_module( level, m, inst_id, fmt, ap );
}

void State::log( const log_levels_log4j level, const char *module_name, const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );

    log( level, module_name, fmt, ap );

    va_end( ap );
}

void State::log( const log_levels_log4j level, const char *module_name, const char *fmt, va_list ap )
{
    DL_SCOPE_LOCK( mutex_ );

    log_module_name( level, module_name, fmt, ap );
}

// private:

void State::output__( const log_levels_log4j level, const Module & m, const std::string & msg )
{
    output_writer( *writer_, level, m, msg );
    if( m.writer_ )
        output_writer( *m.writer_, level, m, msg );
}

void State::output__( const log_levels_log4j level, const Module & m, unsigned int inst_id, const std::string & msg )
{
    output_writer( *writer_, level, m, inst_id, msg );
    if( m.writer_ )
        output_writer( *m.writer_, level, m, inst_id, msg );
}

void State::output__( const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    output_writer( *writer_, level, module_name, msg );
}

void State::output_writer( IWriter & writer, const log_levels_log4j level, const Module & m, const std::string & msg )
{
    if( must_print_level_ )
        writer.write( level, m.name.c_str(), msg );
    else
        writer.write( m.name.c_str(), msg );
}

void State::output_writer( IWriter & writer, const log_levels_log4j level, const Module & m, unsigned int inst_id, const std::string & msg )
{
    if( must_print_level_ )
        writer.write( level, m.name.c_str(), inst_id, msg );
    else
        writer.write( m.name.c_str(), inst_id, msg );
}

void State::output_writer( IWriter & writer, const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    if( must_print_level_ )
        writer.write( level, module_name, msg );
    else
        writer.write( module_name, msg );
}

const State::Module & State::get_module__( unsigned int module_id ) const
{
    MapModuleIdToModule::const_iterator it = module_map_.find( module_id );

    if( it == module_map_.end() )
        return empty_mod;

    return ( *it ).second;
}

State::Module & State::get_module( unsigned int module_id )
{
    MapModuleIdToModule::iterator it = module_map_.find( module_id );

    if( it == module_map_.end() )
        throw std::runtime_error( ( "cannot find module '" + std::to_string( module_id ) + "'" ).c_str() );

    return ( *it ).second;
}

// ***********************************************************************************

State    state;

void log( const log_levels_log4j level, unsigned int module_id, const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );

    state.log( level, module_id, fmt, ap );

    va_end( ap );
}

void log( const log_levels_log4j level, unsigned int module_id, unsigned int inst_id, const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );

    state.log( level, module_id, inst_id, fmt, ap );

    va_end( ap );
}

// old version for macro compatibility
void log( const log_levels_log4j level, const char *module_name, const char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );

    state.log( level, module_name, fmt, ap );

    va_end( ap );
}

unsigned int get_hash( const std::string & module_name )
{
    size_t hash = std::hash<std::string>()( module_name );
    return ( unsigned int ) hash;
}

unsigned int register_module( const std::string & module_name )
{
    unsigned int hash = get_hash( module_name );

    bool b = state.register_module( hash, module_name );

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

void set_writer( IWriter * writer, unsigned int module_id )
{
    state.set_writer( writer, module_id );
}

} // namespace dummy_logger
