/*

printf for std::string.

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/69738/c-how-to-get-fprintf-results-as-a-stdstring-w-o-sprintf#69911
author: http://stackoverflow.com/users/3832/larry-gritz

*/

#include "vformat.h"    // self

#include <vector>

std::string vformat( const char *fmt, va_list ap )
{
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    size_t size = 1024;
    char stackbuf[1024];
    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];
    va_list ap_copy;

    while( true )
    {
        // Try to vsnprintf into our buffer.
        va_copy( ap_copy, ap );
        int needed = vsnprintf( buf, size, fmt, ap_copy );
        va_end( ap_copy );
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if( needed <= (int)size && needed >= 0 )
        {
            // It fit fine so we're done.
            return std::string( buf, (size_t)needed );
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        size = ( needed > 0 ) ? ( needed + 1 ) : ( size * 2 );
        dynamicbuf.resize( size );
        buf = &dynamicbuf[0];
    }

    return std::string();   // never reached, only to avoid warning
}


std::string vformat_2( const char* fmt, ... )
{
    std::string m;

    if( fmt != 0 )
    {
        va_list ap;

        va_start( ap, fmt );

        m   = vformat( fmt, ap );

        va_end( ap );
    }

    return m;
}
