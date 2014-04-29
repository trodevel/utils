/*

Random string generator.

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
author: http://stackoverflow.com/users/13760/carl

*/

// $Id: gen_random_string.cpp 441 2014-04-23 23:10:16Z serge $

#include "gen_random_string.h"  // self

#include <iostream>
#include <vector>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

std::string gen_random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
