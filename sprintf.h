/*

stdstring-formatting-like-sprintf

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
author: http://stackoverflow.com/users/627042

*/

#ifndef SPRINTF_H
#define SPRINTF_H

#include <string>               // std::string
#include <stdarg.h>             // va_list stuff

void spf( std::string &s, const char *fmt, ... );
void spf_2( std::string &s, const char *fmt, va_list ap );

#endif // SPRINTF_H
