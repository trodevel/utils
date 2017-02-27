/*

Logfile Writer.

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

// $Revision: 5850 $ $Date:: 2017-02-27 #$ $Author: serge $

#ifndef LIB_UTILS_LOGFILE_WRITER_H
#define LIB_UTILS_LOGFILE_WRITER_H

#include "dummy_logger.h"   // IWriter
#include "logfile.h"        // Logfile

class LogfileWriter: public dummy_logger::IWriter
{
public:
    LogfileWriter( const std::string & filename, uint32_t rotation_interval_min );
    virtual ~LogfileWriter() {};

    virtual void write( const log_levels_log4j level, const char *module_name, const std::string & msg );
    virtual void write( const log_levels_log4j level, const char *module_name, unsigned int inst_id, const std::string & msg );
    virtual void write( const char *module_name, const std::string & msg );
    virtual void write( const char *module_name, unsigned int inst_id, const std::string & msg );

private:
    Logfile     logfile_;
};

#endif // LIB_UTILS_LOGFILE_WRITER_H
