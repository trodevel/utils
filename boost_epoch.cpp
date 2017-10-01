/*

how-do-i-convert-boostposix-timeptime-to-time-t

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/4461586/how-do-i-convert-boostposix-timeptime-to-time-t
author: http://stackoverflow.com/users/277176/ybungalobill

*/

#include "boost_epoch.h"    // self

#include <boost/date_time/posix_time/posix_time_duration.hpp>   // boost::posix_time::millisec
#include <boost/date_time/posix_time/conversion.hpp>    // boost::posix_time::from_time_t
#include <boost/date_time/gregorian/gregorian.hpp>      // boost::gregorian::date

namespace utils
{

uint32_t to_epoch( const boost::posix_time::ptime & t )
{
    static const boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );

    boost::posix_time::time_duration::sec_type x = ( t - epoch ).total_seconds();

    return x;
}

int64_t to_epoch_microsec( const boost::posix_time::ptime & t )
{
    static const boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );

    if( t.is_special() )
        return -1;

    boost::posix_time::time_duration::tick_type x = ( t - epoch ).total_microseconds();

    return x;
}

boost::posix_time::ptime from_epoch_sec( uint32_t sec )
{
    return boost::posix_time::from_time_t( sec );
}

boost::posix_time::ptime from_epoch_millisec( uint64_t millis )
{
    return boost::posix_time::from_time_t( millis / 1000 ) + boost::posix_time::millisec( millis % 1000 );
}

} // namespace utils
