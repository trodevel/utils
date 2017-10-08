// $Revision: 7972 $ $Date:: 2017-10-06 #$ $Author: serge $

#include "boost_timezone.h"     // self

//#include <iostream>

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
    // @descr: https://stackoverflow.com/a/6300087

    if( t.is_not_a_date_time() )
        return t;

    boost::local_time::time_zone_ptr tz = tz_db_.time_zone_from_region( timezone );

    boost::local_time::local_date_time tm( t.date(), t.time_of_day(), tz, boost::local_time::local_date_time::NOT_DATE_TIME_ON_ERROR );

    //std::cout << "DEBUG: local_to_utc: " << t << " " << timezone << " - " << tm << "\n";

    auto res = tm.utc_time();

    return res;
}

boost::posix_time::ptime TimeZoneConverter::utc_to_local( const boost::posix_time::ptime & t, const std::string & timezone )
{
    if( t.is_not_a_date_time() )
        return t;

    boost::local_time::local_date_time t_utc( t, tz_utc_ );

    boost::local_time::time_zone_ptr tz = tz_db_.time_zone_from_region( timezone );

    auto res = t_utc.local_time_in( tz ).local_time();

    return res;
}

} // namespace utils
