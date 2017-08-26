/*

Simple string match filter.

Copyright (C) 2017 Sergey Kolevatov

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

// $Revision: 7746 $ $Date:: 2017-08-25 #$ $Author: serge $

#include "match_filter.h"       // self

#include "findStringIC.h"       // findStringIC

namespace utils
{

bool match_filter( const std::string & s, const std::string & filter, bool case_insensitive )
{
    if( case_insensitive )
    {
        return findStringIC( s, filter );
    }
    else
    {
        return s.find( filter ) != s.npos;
    }
}

} // namespace utils
