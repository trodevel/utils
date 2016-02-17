/*

BOOST date to string.

Copyright (C) 2015 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 2867 $ $Date:: 2015-11-30 #$ $Author: serge $

#include "boost_date_to_string.h"       // self

#include <locale>                       // std::locale
#include <sstream>                      // std::ostringstream
#include <boost/date_time/gregorian/gregorian.hpp>      // boost::gregorian::date
#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::time_duration

namespace utils
{

const std::locale * get_locale( date_to_string_e fmt )
{
    typedef std::map<date_to_string_e, std::locale> Map;

    static const Map map =
    {
        Map::value_type( date_to_string_e::YYYYMMDD,      std::locale( std::locale::classic(), new boost::gregorian::date_facet( "%Y%m%d" ) ) ),
        Map::value_type( date_to_string_e::YYYY_MM_DD,    std::locale( std::locale::classic(), new boost::gregorian::date_facet( "%Y-%m-%d" ) ) ),
        Map::value_type( date_to_string_e::MM_DD_YYYY,    std::locale( std::locale::classic(), new boost::gregorian::date_facet( "%m/%d/%Y" ) ) ),
        Map::value_type( date_to_string_e::DD_MM_YYYY,    std::locale( std::locale::classic(), new boost::gregorian::date_facet( "%d.%m.%Y" ) ) )
    };

    Map::const_iterator it = map.find( fmt );

    return ( it != map.end() ) ? ( & it->second ) : ( & map.begin()->second );
}

std::string to_string( const boost::gregorian::date& date, date_to_string_e fmt )
{
    const std::locale * loc = get_locale( fmt );

    std::ostringstream os;
    os.imbue( *loc );
    os << date;
    return os.str();
}

std::string to_string( const boost::posix_time::time_duration& time )
{
    std::ostringstream os;

    os << time;

    return os.str();
}

} // namespace utils
