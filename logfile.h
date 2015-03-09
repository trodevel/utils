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

// $Revision: 1561 $ $Date:: 2015-03-05 #$ $Author: serge $

#ifndef LIB_UTILS_LOGFILE_H
#define LIB_UTILS_LOGFILE_H

#include <boost/date_time/posix_time/posix_time.hpp>    // boost::posix_time::ptime
#include <fstream>      // std::ofstream

#include "types.h"      // uint32

class Logfile
{
public:
    Logfile( const std::string & filename, uint32 rotation_interval_min );
    ~Logfile();

    Logfile& operator <<( const char * s );
    Logfile& operator <<( const std::string & s );

    void write( const std::string & s );

private:

    static std::string create_interval_filename(
            const std::string                       & filename_mask,
            const boost::posix_time::time_duration  & rotation_interval,
            const boost::posix_time::ptime          & time );

    void write__( const std::string & s );

    bool is_interval_ended();
    void switch_to_next();
    void create_filename_and_open_file();

private:

    std::string                 filename_mask_;

    boost::posix_time::time_duration    rotation_interval_;
    boost::posix_time::ptime            current_interval_end_;

    std::string                 current_filename_;
    std::ofstream               ofs_;
};


#endif // LIB_UTILS_LOGFILE_H
