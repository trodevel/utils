/*

create_interval_filename().

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

// $Revision: 8710 $ $Date:: 2018-02-09 #$ $Author: serge $

#ifndef LIB_UTILS__CREATE_INTERVAL_FILENAME_H
#define LIB_UTILS__CREATE_INTERVAL_FILENAME_H

#include <boost/date_time/posix_time/posix_time_types.hpp>    // boost::posix_time::ptime

namespace utils
{

namespace logfile
{

std::string create_interval_filename(
        const boost::posix_time::time_duration  & rotation_interval,
        const boost::posix_time::ptime          & time,
        bool                                    need_dash );

} // namespace logfile

} // namespace utils

#endif // LIB_UTILS__CREATE_INTERVAL_FILENAME_H
