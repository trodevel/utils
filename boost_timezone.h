// $Revision: 7960 $ $Date:: 2017-10-02 #$ $Author: serge $

#ifndef LIB_UTILS__BOOST_TIMEZONE_H
#define LIB_UTILS__BOOST_TIMEZONE_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime
#include <boost/date_time/local_time/local_time.hpp>    // boost::local_time::tz_database

namespace utils
{

class TimeZoneConverter
{
public:

    TimeZoneConverter();

    bool init( const std::string & filename );

    boost::posix_time::ptime local_to_utc( const boost::posix_time::ptime & t, const std::string & timezone );
    boost::posix_time::ptime utc_to_local( const boost::posix_time::ptime & t, const std::string & timezone );

private:

    boost::local_time::tz_database      tz_db_;
    boost::local_time::time_zone_ptr    tz_utc_;
};

} // namespace utils

#endif // LIB_UTILS__BOOST_TIMEZONE_H
