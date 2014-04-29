/*

printf for std::string.

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/69738/c-how-to-get-fprintf-results-as-a-stdstring-w-o-sprintf#69911
author: http://stackoverflow.com/users/3832/larry-gritz

*/

#ifndef VFORMAT_H
#define VFORMAT_H

#include <string>               // std::string
#include <stdarg.h>             // va_list stuff

std::string vformat( const char *fmt, va_list ap );
std::string vformat_2( const char* fmt, ... );

#endif // VFORMAT_H
