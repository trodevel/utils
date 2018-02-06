/*

Logfile.

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

// $Revision: 8694 $ $Date:: 2018-02-06 #$ $Author: serge $

#ifndef LIB_UTILS_LOGFILE_H
#define LIB_UTILS_LOGFILE_H

#include <boost/date_time/posix_time/posix_time_types.hpp>    // boost::posix_time::ptime
#include <fstream>      // std::ofstream

#include <cstdint>      // uint32_t

namespace utils
{

class Logfile
{
public:

    class OneLiner
    {
    public:

        OneLiner( Logfile & parent );
        ~OneLiner();

        std::ofstream & get();

        void* operator new (std::size_t size) throw (std::bad_alloc) = delete;
        void* operator new[] (std::size_t size) throw (std::bad_alloc) = delete;

    private:

        Logfile         & parent_;
    };

    friend OneLiner;

public:
    Logfile();
    Logfile( const std::string & filename, uint32_t rotation_interval_min );
    ~Logfile();

    bool init( const std::string & filename, uint32_t rotation_interval_min );

    void write( const std::string & s );

private:

    std::ofstream  & get_stream_for_oneliner();
    void flush();

    static std::string create_interval_filename(
            const std::string                       & filename_mask,
            const boost::posix_time::time_duration  & rotation_interval,
            const boost::posix_time::ptime          & time );

    void check_interval();

    static boost::posix_time::ptime get_now();

    bool is_interval_ended( const boost::posix_time::ptime & now );
    void switch_to_next( const boost::posix_time::ptime & now );
    boost::posix_time::ptime rotate_to_time( const boost::posix_time::ptime & now );
    bool create_filename_and_open_file( const boost::posix_time::ptime & current_interval_start, bool throw_on_error );
    boost::posix_time::time_duration calc_delta( const boost::posix_time::ptime & current_time ) const;

private:

    std::string                 filename_mask_;

    boost::posix_time::time_duration    rotation_interval_;
    boost::posix_time::ptime            current_interval_end_;

    std::string                 current_filename_;
    std::ofstream               ofs_;
};

} // namespace utils

#endif // LIB_UTILS_LOGFILE_H
