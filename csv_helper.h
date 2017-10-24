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

// $Revision: 8146 $ $Date:: 2017-10-24 #$ $Author: serge $

#ifndef LIB_UTILS_CSV_HELPER_H
#define LIB_UTILS_CSV_HELPER_H

#include <string>                   // std::string
#include <sstream>                  // std::ostringstream
#include <iterator>                 // std::distance

namespace utils
{

template< char _SEP = ';', bool LAST_SEP = true >
class CsvHelperT
{
public:

    template< typename ... Args >
    static std::ostream& write( std::ostream& os, const Args& ... args )
    {
        write_intern( os, args... );
        return os;
    }

    template< typename ... Args >
    static std::ostream& write_nl( std::ostream& os, const Args& ... args )
    {
        write_intern( os, args... );
        os << std::endl;
        return os;
    }

    template<bool BREAKLINE = false, typename IT>
    static std::ostream& write_array( std::ostream& os, IT first, IT last )
    {
        return write_user_array( os, first, last, write_elem<typename std::iterator_traits<IT>::value_type> );
    }

    template<bool BREAKLINE = false, typename IT, class Writer>
    static std::ostream& write_user_array( std::ostream& os, IT first, IT last, Writer writer )
    {
        auto size = std::distance( first, last );

        write_intern( os, size );

        if( BREAKLINE )
        {
            os << "\n";
        }

        auto & it = first;

        for( ; it != last; ++it )
        {
            if( it != first )
                os << _SEP;

            writer( os, *it );
        }

        if( LAST_SEP )
            os << _SEP;

        return os;
    }

    template< typename ... Args >
    static std::string to_csv( const Args& ... args )
    {
        std::ostringstream os;
        write_intern( os, args... );
        return os.str();
    }

    template< typename ... Args >
    static std::string to_csv_nl( const Args& ... args )
    {
        std::ostringstream os;
        write_intern( os, args... );
        os << std::endl;
        return os.str();
    }

    template<typename _IT>
    static std::string to_csv( _IT first, _IT last )
    {
        std::ostringstream os;

        auto it = first;

        for( ; it != last; ++it )
        {
            if( it != first )
                os << _SEP;

            os << *it;
        }

        if( LAST_SEP )
            os << _SEP;

        return os.str();
    }

protected:

    template< class T >
    static void write_elem( std::ostream& os, const T & e )
    {
        write_intern( os, e );
    }

    static void write_intern( std::ostream& )
    {
    }

    static void write_intern( std::ostream& os, const std::string& str )
    {
        os << str << _SEP;
    }

    template< class T1, typename ... Args >
    static void write_intern( std::ostream& os, const T1& t1, const Args& ... args )
    {
        os << t1 << _SEP;
        write_intern( os, args... );
    }

};

typedef CsvHelperT<';'> CsvHelper;

} // namespace utils

#endif // LIB_UTILS_CSV_HELPER_H
