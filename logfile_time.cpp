/*

Logfile with Timestamp.

Copyright (C) 2018 Sergey Kolevatov

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

#include "logfile_time.h"       // self

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime

namespace utils
{

LogfileTime::LogfileTime( const std::string & filename, uint32_t rotation_interval_min ):
    logfile_( filename, rotation_interval_min )
{
}

void LogfileTime::write( const std::string & msg )
{
    std::string s;

    Logfile::OneLiner( logfile_ ).get() << get_current_timestamp( s ) << " " << msg << "\n";
}

const std::string & LogfileTime::get_current_timestamp( std::string & s )
{
    s = to_iso_extended_string( boost::posix_time::microsec_clock::universal_time() );

    return s;
}

} // namespace utils
