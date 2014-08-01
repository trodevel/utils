/*

how-do-i-convert-boostposix-timeptime-to-time-t

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/4461586/how-do-i-convert-boostposix-timeptime-to-time-t
author: http://stackoverflow.com/users/277176/ybungalobill

*/

#ifndef LIB_UTILS_BOOST_EPOCH_H
#define LIB_UTILS_BOOST_EPOCH_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime
#include <boost/date_time/gregorian/gregorian.hpp>      // boost::gregorian::date

#include "types.h"      // uint32

inline uint32 to_epoch( const boost::posix_time::ptime & t )
{
    static const boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );

    boost::posix_time::time_duration::sec_type x = ( t - epoch ).total_seconds();

    return x;
}

inline int64 to_epoch_microsec( const boost::posix_time::ptime & t )
{
    static const boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );

    if( t.is_special() )
        return -1;

    boost::posix_time::time_duration::tick_type x = ( t - epoch ).total_microseconds();

    return x;
}

#endif // LIB_UTILS_BOOST_EPOCH_H
