/*

stdstring-formatting-like-sprintf

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
author: http://stackoverflow.com/users/627042

*/

#include "sprintf.h"    // self

void spf( std::string &s, const char *fmt, ... )
{
    int n, size = 100;
    bool b = false;
    va_list ap;

    while( !b )
    {
        s.resize( size );
        va_start( ap, fmt );
        n = vsnprintf( (char*)s.c_str(), size, fmt, ap );
        va_end( ap );
        if( ( n > 0 ) && ( ( b = ( n < size ) ) == true ) )
            s.resize( n );
        else
            size *= 2;
    }
}

void spf_2( std::string &s, const char *fmt, va_list ap )
{
    int n, size = 100;
    bool b = false;

    while( !b )
    {
        s.resize( size );

        n = vsnprintf( (char*)s.c_str(), size, fmt, ap );

        if( ( n > 0 ) && ( ( b = ( n < size ) ) == true ) )
            s.resize( n );
        else
            size *= 2;
    }
}
