/*

Remove extra spaces from the string.

LICENSE: cc by-sa 3.0 with attribution required

source: stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
author: http://stackoverflow.com/users/440119/benjamin-lindley

*/

// $Revision: 1404 $ $Date:: 2015-01-16 #$ $Author: serge $

#include "remove_extra_spaces.h"        // self

#include <algorithm>                // std::unique

bool BothAreSpaces( char lhs, char rhs )
{
    return ( lhs == rhs ) && ( lhs == ' ' );
}

void remove_extra_spaces( std::string & s )
{
    std::string::iterator new_end = std::unique( s.begin(), s.end(), BothAreSpaces );
    s.erase( new_end, s.end() );
}

