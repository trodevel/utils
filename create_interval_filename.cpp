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

// $Revision: 8684 $ $Date:: 2018-02-05 #$ $Author: serge $


#include "create_interval_filename.h"   // self

#include <fstream>          // std::ofstream
#include <iomanip>          // std::setfill

namespace utils
{

namespace logfile
{

const std::string & make_dash(
    bool                                    need_dash )
{
    static const std::string dash( "-" );
    static const std::string nodash;

    return need_dash ? dash : nodash;
}


std::string create_interval_filename(
    const boost::posix_time::time_duration  & rotation_interval,
    const boost::posix_time::ptime          & time,
    bool                                    need_dash )
{
    const std::string & sep = make_dash( need_dash );

    uint32_t  mins  = rotation_interval.minutes();
    uint32_t  hours = rotation_interval.hours();

    std::ostringstream os;

    boost::gregorian::date date = time.date();

    os << std::setfill( '0' );

    os << std::setw( 4 ) << date.year() << sep << std::setw( 2 ) << date.month().as_number() << sep << std::setw( 2 ) << date.day();

    if( mins > 0 )
    {
        os << "_" << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().hours()
                << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().minutes();
    }
    else if( hours > 0 && hours != 24 )
    {
        os << "_" << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().hours();
    }

    //os << "_debug_hours_" << hours << "_minutes_" << mins;    // DEBUG

    return os.str();
}

} // namespace logfile

} // namespace utils
