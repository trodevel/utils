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

// $Revision: 1738 $ $Date:: 2015-04-26 #$ $Author: serge $


#include "logfile.h"      // self

Logfile::Logfile( const std::string & filename, uint32 rotation_interval_min ):
    filename_mask_( filename )
{
    rotation_interval_      = boost::posix_time::minutes( rotation_interval_min );
    current_interval_end_   = get_now(); // initialize with current time

    create_filename_and_open_file( current_interval_end_ );

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
    boost::posix_time::ptime now = get_now();

    if( is_interval_ended( now ) )
    {
        switch_to_next( now );
    }

    ofs_ << s;
    ofs_.flush();
}

boost::posix_time::ptime Logfile::get_now()
{
    return boost::posix_time::second_clock::universal_time();
}

bool Logfile::is_interval_ended( const boost::posix_time::ptime & now )
{
    if( now > current_interval_end_ )
        return true;

    return false;
}

void Logfile::switch_to_next( const boost::posix_time::ptime & now )
{
    ofs_.close();

    boost::posix_time::ptime interval_start = rotate_to_time( now );

    create_filename_and_open_file( interval_start );

    current_interval_end_   = interval_start + rotation_interval_;
}

boost::posix_time::ptime Logfile::rotate_to_time( const boost::posix_time::ptime & now )
{
    boost::posix_time::ptime res    = current_interval_end_;

    while( res + rotation_interval_ < now )
    {
        res += rotation_interval_;
    }

    return res;
}

void Logfile::create_filename_and_open_file( const boost::posix_time::ptime & current_interval_start )
{
    current_filename_   = create_interval_filename( filename_mask_, rotation_interval_, current_interval_start );

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

    os << std::setfill( '0' );

    os << std::setw( 4 ) << date.year() << std::setw( 2 ) << date.month().as_number() << std::setw( 2 ) << date.day();

    if( mins > 0 )
    {
        os << "_" << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().hours()
                << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().minutes();
    }
    else if( hours > 0 )
    {
        os << "_" << std::setfill( '0' ) << std::setw( 2 ) << time.time_of_day().hours();
    }

    return os.str();
}
