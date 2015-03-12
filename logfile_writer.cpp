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

// $Revision: 1567 $ $Date:: 2015-03-11 #$ $Author: serge $

#include "logfile_writer.h" // self

LogfileWriter::LogfileWriter( const std::string & filename, uint32 rotation_interval_min ):
    logfile_( filename, rotation_interval_min )
{
}

void LogfileWriter::write( const std::string & s )
{
    logfile_.write( s );
}
LogfileWriter::IWriter & LogfileWriter::operator<<( const std::string & s )
{
    logfile_ << s;

    return *this;
}
LogfileWriter::IWriter & LogfileWriter::operator<<( const char * s )
{
    logfile_ << s;

    return *this;
}
