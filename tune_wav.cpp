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

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#include "tune_wav.h"       // self

#include <iostream>         // cout
#include <fstream>          // std::ifstream

#include "types.h"          // uint8

bool tune_wav( const std::string & filename, const std::string & outp )
{
    std::ifstream  src( filename.c_str(), std::ios::binary );

    if( !src.is_open() )
    {
        std::cout << "ERROR: cannot open input file '" << filename << "'" << std::endl;
        return false;
    }

    src.seekg( 17 );

    uint8 val = src.get();

    if( val == 0x12 )
    {
        std::cout << "DBG: field contains correct value - no transformation is needed" << std::endl;
        return true;
    }

    std::cout << "DBG: patching file '" << filename << "'" << std::endl;

    std::ofstream dst( outp.c_str(), std::ios::binary | std::ios::out );

    if( !dst.is_open() )
    {
        std::cout << "ERROR: cannot open temp output file '" << outp << "'" << std::endl;
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
