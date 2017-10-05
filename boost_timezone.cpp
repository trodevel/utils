// $Revision: 7966 $ $Date:: 2017-10-04 #$ $Author: serge $

#include "boost_timezone.h"     // self

namespace utils
{

TimeZoneConverter::TimeZoneConverter()
{
}

bool TimeZoneConverter::init( const std::string & filename )
{
    tz_db_.load_from_file( filename );

    tz_utc_.reset( new boost::local_time::posix_time_zone( "UTC" ) );

    return true;
}

boost::posix_time::ptime TimeZoneConverter::local_to_utc( const boost::posix_time::ptime & t, const std::string & timezone )
{
    boost::local_time::time_zone_ptr tz = tz_db_.time_zone_from_region( timezone );

    boost::local_time::local_date_time tm( t, tz );

    boost::posix_time::ptime res = tm.utc_time();

    return res;
}

boost::posix_time::ptime TimeZoneConverter::utc_to_local( const boost::posix_time::ptime & t, const std::string & timezone )
{
    boost::local_time::local_date_time t_utc( t, tz_utc_ );

    boost::local_time::time_zone_ptr tz = tz_db_.time_zone_from_region( timezone );

    auto res = t_utc.local_time_in( tz ).local_time();

    return res;
}

} // namespace utils
