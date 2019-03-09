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

// $Revision: 9939 $ $Date:: 2018-11-02 #$ $Author: serge $


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

std::ostream & write_year(
        std::ostream                    & os,
        const boost::gregorian::date    & date )
{
    os << std::setfill( '0' ) << std::setw( 4 ) << date.year();
    return os;
}

std::ostream & write_month(
        std::ostream                    & os,
        const boost::gregorian::date    & date )
{
    os << std::setfill( '0' ) << std::setw( 2 ) << date.month().as_number();
    return os;
}

std::ostream & write_week(
        std::ostream                    & os,
        const boost::gregorian::date    & date )
{
    os << "_wk_" << std::setfill( '0' ) << std::setw( 2 ) << date.week_number();
    return os;
}

std::ostream & write_day(
        std::ostream                    & os,
        const boost::gregorian::date    & date )
{
    os << std::setfill( '0' ) << std::setw( 2 ) << date.day();

    return os;
}

std::ostream & write_hours(
        std::ostream                    & os,
        const boost::posix_time::ptime  & time )
{
    os << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().hours();

    return os;
}

std::ostream & write_minutes(
        std::ostream                    & os,
        const boost::posix_time::ptime  & time )
{
    os << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().minutes();

    return os;
}

std::string create_interval_filename(
    const boost::posix_time::time_duration  & rotation_interval,
    const boost::posix_time::ptime          & time,
    bool                                    need_dash )
{
    const std::string & sep = make_dash( need_dash );

    uint32_t  mins  = rotation_interval.minutes();
    uint32_t  hours = rotation_interval.hours();

    uint32_t  days      = 0;
    uint32_t  weeks     = 0;
    uint32_t  months    = 0;

    if( hours > 0 && ( ( hours % 24 ) == 0 ) )
    {
        days    = hours / 24;
        hours   = 0;
    }

    if( days > 0 && ( ( days % 7 ) == 0 ) )
    {
        weeks   = days / 7;
        days    = 0;
    }

    if( days > 0 && ( ( days % 30 ) == 0 ) )
    {
        months  = days / 30;
        days    = 0;
    }

    std::ostringstream os;

    boost::gregorian::date date = time.date();

    write_year( os, date );

    if( mins > 0 )
    {
        os << sep;
        write_month( os, date );
        os << sep;
        write_day( os, date ) << "_";
        write_hours( os, time );
        write_minutes( os, time );
    }
    else if( hours > 0 )
    {
        os << sep;
        write_month( os, date );
        os << sep;
        write_day( os, date ) << "_";
        write_hours( os, time );
    }
    else if( days > 0 )
    {
        os << sep;
        write_month( os, date );
        os << sep;
        write_day( os, date );
    }
    else if( weeks > 0 )
    {
        write_week( os, date );
    }
    else if( months > 0 )
    {
        os << sep;
        write_month( os, date );
    }

    //os << "_debug_hours_" << hours << "_minutes_" << mins;    // DEBUG

    return os.str();
}

} // namespace logfile

} // namespace utils
