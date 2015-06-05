/*

Logfile Writer with Timestamp.

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

// $Revision: 1824 $ $Date:: 2015-06-05 #$ $Author: serge $

#include "logfile_time_writer.h"    // self

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime

LogfileTimeWriter::LogfileTimeWriter( const std::string & filename, uint32 rotation_interval_min ):
    logfile_( filename, rotation_interval_min )
{
}

void LogfileTimeWriter::write( const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    std::string s;

    logfile_ << get_current_timestamp( s ) << " " << dummy_logger::to_string( level ) << "|" << module_name << ": " << msg << "\n";
}

void LogfileTimeWriter::write( const char *module_name, const std::string & msg )
{
    std::string s;

    logfile_ << get_current_timestamp( s ) << " " << module_name << ": " << msg << "\n";
}

const std::string & LogfileTimeWriter::get_current_timestamp( std::string & s )
{
    s = to_iso_extended_string( boost::posix_time::microsec_clock::universal_time() );

    return s;
}
