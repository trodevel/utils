#include <iostream>

#include "boost_timezone.h"     // self

boost::posix_time::ptime convert_utc_to_local( const std::string & time, const std::string & tz, utils::TimeZoneConverter & tzc )
{
    auto tm = boost::posix_time::time_from_string( time );

    auto res = tzc.utc_to_local( tm, tz );

    std::cout << "UTC: " << tm << " - LOC: " << res << " " << tz << "\n";

    return res;
}

boost::posix_time::ptime convert_local_to_utc( const std::string & time, const std::string & tz, utils::TimeZoneConverter & tzc )
{
    auto tm = boost::posix_time::time_from_string( time );

    auto res = tzc.local_to_utc( tm, tz );

    std::cout << "LOC: " << tm << " " << tz << " - UTC: " << res << "\n";

    return res;
}

void test_tz_cvt_01( utils::TimeZoneConverter & tzc )
{
    convert_utc_to_local( "2017-10-09 12:00:00", "Europe/Berlin", tzc );
}

void test_tz_cvt_02( utils::TimeZoneConverter & tzc )
{
    convert_utc_to_local( "2017-12-09 12:00:00", "Europe/Berlin", tzc );
}

void test_tz_cvt_03( utils::TimeZoneConverter & tzc )
{
    convert_utc_to_local( "2017-10-09 12:00:00", "Europe/Moscow", tzc );
}

void test_tz_cvt_04( utils::TimeZoneConverter & tzc )
{
    convert_utc_to_local( "2017-12-09 12:00:00", "Europe/Moscow", tzc );
}

void test_tz_cvt_05( utils::TimeZoneConverter & tzc )
{
    convert_local_to_utc( "2017-10-09 12:00:00", "Europe/Berlin", tzc );
}

void test_tz_cvt_06( utils::TimeZoneConverter & tzc )
{
    convert_local_to_utc( "2017-12-09 12:00:00", "Europe/Berlin", tzc );
}

void test_tz_cvt()
{
    utils::TimeZoneConverter tzc;

    tzc.init( "date_time_zonespec.csv" );

    test_tz_cvt_01( tzc );
    test_tz_cvt_02( tzc );
    test_tz_cvt_03( tzc );
    test_tz_cvt_04( tzc );
    test_tz_cvt_05( tzc );
    test_tz_cvt_06( tzc );
}

int main()
{
    test_tz_cvt();

    return 0;
}
