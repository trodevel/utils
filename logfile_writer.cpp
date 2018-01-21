/*

Logfile Writer.

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

// $Revision: 8576 $ $Date:: 2018-01-19 #$ $Author: serge $

#include "logfile_writer.h" // self

namespace utils
{

LogfileWriter::LogfileWriter( const std::string & filename, uint32_t rotation_interval_min ):
    logfile_( filename, rotation_interval_min )
{
}

void LogfileWriter::write( const log_levels_log4j level, const char *module_name, const std::string & msg )
{
    logfile_ << dummy_logger::to_string( level ) << "|" << module_name << ": " << msg << "\n";
}

void LogfileWriter::write( const log_levels_log4j level, const char *module_name, unsigned int inst_id, const std::string & msg )
{
    logfile_ << dummy_logger::to_string( level ) << "|" << module_name << "[" << inst_id << "]: " << msg << "\n";
}

void LogfileWriter::write( const char *module_name, const std::string & msg )
{
    logfile_ << module_name << ": " << msg << "\n";
}

void LogfileWriter::write( const char *module_name, unsigned int inst_id, const std::string & msg )
{
    logfile_ << module_name << "[" << inst_id << "]: " << msg << "\n";
}

} // namespace utils
