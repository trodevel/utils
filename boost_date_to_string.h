/*

BOOST date to string.

Copyright (C) 2015 Sergey Kolevatov

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

// $Revision: 2867 $ $Date:: 2015-11-30 #$ $Author: serge $

#ifndef LIB_UTILS_BOOST_DATE_TO_STRING_H
#define LIB_UTILS_BOOST_DATE_TO_STRING_H

#include <string>                       // string

namespace boost {
namespace gregorian {
class date;
}
}

namespace boost {
namespace posix_time {
class time_duration;
}
}

namespace utils
{

enum class date_to_string_e
{
    YYYYMMDD,
    YYYY_MM_DD,
    MM_DD_YYYY,
    DD_MM_YYYY,
};

std::string to_string( const boost::gregorian::date& date, date_to_string_e fmt = date_to_string_e::YYYYMMDD );
std::string to_string( const boost::posix_time::time_duration& time );

} // namespace utils

#endif // LIB_UTILS_BOOST_DATE_TO_STRING_H
