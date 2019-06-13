/*

how-do-i-convert-boostposix-timeptime-to-time-t

LICENSE: cc by-sa 3.0 with attribution required

source: http://stackoverflow.com/questions/4461586/how-do-i-convert-boostposix-timeptime-to-time-t
author: http://stackoverflow.com/users/277176/ybungalobill

*/

#ifndef LIB_UTILS_BOOST_EPOCH_H
#define LIB_UTILS_BOOST_EPOCH_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime

#include "epoch32_t.h"              // epoch32_t

namespace utils
{

epoch32_t to_epoch( const boost::posix_time::ptime & t );

int64_t to_epoch_microsec( const boost::posix_time::ptime & t );

boost::posix_time::ptime from_epoch_sec( epoch32_t sec );

boost::posix_time::ptime from_epoch_millisec( epoch64_t millis );

} // namespace utils

#endif // LIB_UTILS_BOOST_EPOCH_H
