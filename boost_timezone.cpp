// $Revision: 7949 $ $Date:: 2017-09-29 #$ $Author: serge $

#include "boost_timezone.h"     // self

#include <boost/date_time/local_time/local_time.hpp>

namespace utils
{

boost::posix_time::ptime convert_tz_to_utc( const boost::posix_time::ptime & t, const std::string & timezone )
{
    boost::local_time::tz_database tz_db;

    tz_db.load_from_file( "date_time_zonespec.csv" );

    boost::local_time::time_zone_ptr tz = tz_db.time_zone_from_region( timezone );

    boost::local_time::local_date_time tm( t, tz );

    boost::posix_time::ptime tm_utc = tm.utc_time();

    return tm_utc;
}

boost::posix_time::ptime convert_utc_to_tz( const boost::posix_time::ptime & t, const std::string & timezone )
{
    return t;
}

} // namespace utils
