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

// $Revision: 8700 $ $Date:: 2018-02-07 #$ $Author: serge $


#include "logfile.h"        // self

#include "create_interval_filename.h"       // create_interval_filename()

namespace utils
{

Logfile::Logfile( const std::string & filename, uint32_t rotation_interval_min ):
    filename_mask_( filename )
{
    rotation_interval_      = boost::posix_time::time_duration( rotation_interval_min / 60, rotation_interval_min % 60, 0 );
    boost::posix_time::ptime current_time   = get_now(); // initialize with current time

    create_filename_and_open_file( current_time, true );

    current_interval_end_   = current_time + calc_delta( current_time );
}

Logfile::~Logfile()
{
    if( ofs_.is_open() )
        ofs_.close();
}

void Logfile::write( const std::string & s )
{
    check_interval();

    ofs_ << s;
    ofs_.flush();
}

void Logfile::check_interval()
{
    boost::posix_time::ptime now = get_now();

    if( is_interval_ended( now ) )
    {
        switch_to_next( now );
    }
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

    create_filename_and_open_file( interval_start, true );

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

bool Logfile::create_filename_and_open_file( const boost::posix_time::ptime & current_interval_start, bool throw_on_error )
{
    current_filename_   = create_interval_filename( filename_mask_, rotation_interval_, current_interval_start );

    ofs_.open( current_filename_.c_str(), std::ios::out | std::ios::app );

    if( ofs_.fail() )
    {
        if( throw_on_error )
            throw std::runtime_error( ( "cannot open file '" + current_filename_ + "'" ).c_str() );
        else
            return false;
    }

    return true;
}

boost::posix_time::time_duration Logfile::calc_delta( const boost::posix_time::ptime & current_time ) const
{
//    unsigned int ms     = rotation_interval_.fractional_seconds();
//    unsigned int s      = rotation_interval_.seconds();
    unsigned int m      = rotation_interval_.minutes();
    unsigned int h      = rotation_interval_.hours();
    unsigned int d      = h / 24;

    unsigned int cms    = current_time.time_of_day().fractional_seconds();
    unsigned int cs     = current_time.time_of_day().seconds();
    unsigned int cm     = current_time.time_of_day().minutes();
    unsigned int ch     = current_time.time_of_day().hours();

    boost::posix_time::time_duration delta;

    if( d > 0 )
    {
        delta   = boost::posix_time::time_duration( d * 24, 0, 0 ) - boost::posix_time::time_duration( ch, cm, cs, cms );
    }
    else if( h > 0 )
    {
        delta   = boost::posix_time::time_duration( h, 0, 0 ) - boost::posix_time::time_duration( 0, cm, cs, cms );
    }
    else /* if( m > 0 ) */
    {
        delta   = boost::posix_time::time_duration( 0, m, 0 ) - boost::posix_time::time_duration( 0, 0, cs, cms );
    }

    return delta;
}

std::ofstream  & Logfile::get_stream_for_oneliner()
{
    check_interval();

    return ofs_;
}

void Logfile::flush()
{
    ofs_.flush();
}

std::string Logfile::create_interval_filename(
    const std::string                       & filename_mask,
    const boost::posix_time::time_duration  & rotation_interval,
    const boost::posix_time::ptime          & time )
{
    return filename_mask + "_" + utils::logfile::create_interval_filename( rotation_interval, time, false );
}

Logfile::OneLiner::OneLiner( Logfile & parent ):
        parent_( parent )
{
}

Logfile::OneLiner::~OneLiner()
{
    parent_.flush();
}

std::ofstream & Logfile::OneLiner::get()
{
    return parent_.get_stream_for_oneliner();
}


} // namespace utils
