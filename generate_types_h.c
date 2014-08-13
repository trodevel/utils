/*

This tool generates a C/C++ header file containing platform independent types
like uint8, uint32, etc.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// $Id: generate_types_h.c 456 2014-04-29 18:03:42Z serge $

#include <stdio.h>

void print_type( const char *type, int size )
{
    printf(
    //"typedef signed %-9s    int%d;\n"
    "typedef %-16s    int%d;\n"
    "typedef unsigned %-9s  uint%d;\n",
        type, size ,
        type, size );
}

void print_error( const char *type, int size )
{
    printf( "#error weird '%s' size (%d)\n", type, size );
}

void gen_int8()
{
    if( sizeof( char ) == 1 )
        print_type( "char", 8 );
    else
        print_error( "char", sizeof( char ) );
}

void gen_int16()
{
    if( sizeof( short ) == 2 )
        print_type( "short", 16 );
    else
        print_error( "short", sizeof( short ) );
}

void gen_int32()
{
    if( sizeof( int ) == 4 )
        print_type( "int", 32 );
    else if( sizeof( long ) == 4 )
        print_type( "long", 32 );
    else
        print_error( "long", sizeof( long ) );
}

void gen_int64()
{
    if( sizeof( long ) == 8 )
        print_type( "long", 64 );
    else if( sizeof( long long ) == 8 )
        print_type( "long long", 64 );
    else
        print_error( "long long", sizeof( long long ) );
}

int main()
{
    printf(
        "// generated by generate_types_h.c\n\n"
        "#ifndef UTILS_TYPES_H\n"
        "#define UTILS_TYPES_H\n"
        "\n" );

    gen_int8();
    gen_int16();
    gen_int32();
    gen_int64();

    printf(
        "\n"
        "#endif // UTILS_TYPES_H\n" );

    return 0;
}
