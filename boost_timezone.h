// $Revision: 7948 $ $Date:: 2017-09-29 #$ $Author: serge $

#ifndef LIB_UTILS__BOOST_TIMEZONE_H
#define LIB_UTILS__BOOST_TIMEZONE_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime

namespace utils
{

boost::posix_time::ptime convert_tz_to_utc( const boost::posix_time::ptime & t, const std::string & timezone );

boost::posix_time::ptime convert_utc_to_tz( const boost::posix_time::ptime & t, const std::string & timezone );

} // namespace utils

#endif // LIB_UTILS__BOOST_TIMEZONE_H
