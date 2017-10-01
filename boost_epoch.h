/*

how-do-i-convert-boostposix-timeptime-to-time-t

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/4461586/how-do-i-convert-boostposix-timeptime-to-time-t
author: http://stackoverflow.com/users/277176/ybungalobill

*/

#ifndef LIB_UTILS_BOOST_EPOCH_H
#define LIB_UTILS_BOOST_EPOCH_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime

#include <cstdint>                      // uint32_t, int64_t

namespace utils
{

uint32_t to_epoch( const boost::posix_time::ptime & t );

int64_t to_epoch_microsec( const boost::posix_time::ptime & t );

boost::posix_time::ptime from_epoch_sec( uint32_t sec );

boost::posix_time::ptime from_epoch_millisec( uint64_t millis );

} // namespace utils

#endif // LIB_UTILS_BOOST_EPOCH_H
