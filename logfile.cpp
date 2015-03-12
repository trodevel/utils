/*

Logfile.

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

// $Revision: 1565 $ $Date:: 2015-03-10 #$ $Author: serge $


#include "logfile.h"      // self

Logfile::Logfile( const std::string & filename, uint32 rotation_interval_min ):
    filename_mask_( filename )
{
    rotation_interval_      = boost::posix_time::minutes( rotation_interval_min );
    current_interval_end_   = boost::posix_time::second_clock::universal_time(); // initialize with current time

    create_filename_and_open_file();

    current_interval_end_   += rotation_interval_;
}

Logfile::~Logfile()
{
    ofs_.close();
}

Logfile& Logfile::operator <<( const char * s )
{
    write__( s );

    return *this;
}

Logfile& Logfile::operator <<( const std::string & s )
{
    write__( s );

    return *this;
}

void Logfile::write( const std::string & s )
{
    write__( s );
}
void Logfile::write__( const std::string & s )
{
    if( is_interval_ended() )
    {
        switch_to_next();
    }

    ofs_ << s;
}

bool Logfile::is_interval_ended()
{
    boost::posix_time::ptime    now( boost::posix_time::second_clock::universal_time() );

    if( now > current_interval_end_ )
        return true;

    return false;
}

void Logfile::switch_to_next()
{
    ofs_.close();

    create_filename_and_open_file();

    current_interval_end_   += rotation_interval_;
}

void Logfile::create_filename_and_open_file()
{
    current_filename_   = create_interval_filename( filename_mask_, rotation_interval_, current_interval_end_ );

    ofs_.open( current_filename_.c_str() );

    if( ofs_.fail() )
        throw std::runtime_error( ( "cannot open file '" + current_filename_ + "'" ).c_str() );
}


std::string Logfile::create_interval_filename(
    const std::string                       & filename_mask,
    const boost::posix_time::time_duration  & rotation_interval,
    const boost::posix_time::ptime          & time )
{
    uint32  mins    = rotation_interval.minutes();
    uint32  hours   = rotation_interval.hours();

    std::ostringstream os;

    boost::gregorian::date date = time.date();

    os << filename_mask << "_";

    os << date.year() << date.month() << date.day();

    if( mins > 0 )
    {
        os << time.time_of_day().hours() << time.time_of_day().minutes();
    }
    else if( hours > 0 )
    {
        os << time.time_of_day().hours();
    }

    return os.str();
}
