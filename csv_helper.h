/*

CSV helper.

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

#ifndef LIB_UTILS_CSV_HELPER_H
#define LIB_UTILS_CSV_HELPER_H

#include <string>                   // std::string
#include <sstream>                  // std::ostringstream

namespace utils
{

class CsvHelper
{
public:

    template< typename ... Args >
    static std::string to_csv( const Args& ... args )
    {
        std::ostringstream os;
        to_csv_( os, args... );
        return os.str();
    }

    template< typename ... Args >
    static std::string to_csv_nl( const Args& ... args )
    {
        std::ostringstream os;
        to_csv_( os, args... );
        os << std::endl;
        return os.str();
    }

protected:

    static void to_csv_( std::ostringstream& )
    {
    }

    static void to_csv_( std::ostringstream& os, const std::string& str )
    {
        os << str << ";";
    }

    template< class T1, typename ... Args >
    static void to_csv_( std::ostringstream& os, const T1& t1, const Args& ... args )
    {
        os << t1 << ";";
        to_csv_( os, args... );
    }

};

} // namespace utils

#endif // LIB_UTILS_CSV_HELPER_H
