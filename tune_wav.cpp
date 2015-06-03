/*

Adjust WAV file header in order to let Skype correctly read it.

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

// $Revision: 1812 $ $Date:: 2015-06-03 #$ $Author: serge $

#include "tune_wav.h"       // self

#include <iostream>         // cout
#include <fstream>          // std::ifstream

#include "dummy_logger.h"   // dummy_log_debug
#include "types.h"          // uint8

#define MODULENAME "tune_wav"

bool tune_wav( const std::string & filename, const std::string & outp )
{
    std::ifstream  src( filename.c_str(), std::ios::binary );

    if( !src.is_open() )
    {
        dummy_log_error( MODULENAME, "cannot open input file '%s'", filename.c_str() );
        return false;
    }

    src.seekg( 17 );

    uint8 val = src.get();

    if( val == 0x12 )
    {
        dummy_log_debug( MODULENAME, "field contains correct value - no transformation is needed" );
        return true;
    }

    dummy_log_debug( MODULENAME, "patching file '%s'", filename.c_str() );

    std::ofstream dst( outp.c_str(), std::ios::binary | std::ios::out );

    if( !dst.is_open() )
    {
        dummy_log_error( MODULENAME, "cannot open temp output file '%s'", outp.c_str() );
        return false;
    }

    src.seekg( 0, std::ios::beg );

    int8 buf[ 256 ];

    // read header (including size field) and write it without size field
    src.read( buf, 17 );
    dst.write( buf, 16 );

    // write new size
    dst.put( 0x12 );

    // read and write the rest
    src.read( buf, 19 );
    dst.write( buf, 19 );

    // put 2 extra zero bytes
    dst.put( 0 );
    dst.put( 0 );

    dst << src.rdbuf();

    return true;
}
