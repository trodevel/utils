/*

Dummy logger.

Copyright (C) 2014 Sergey Kolevatov

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

// $Id: dummy_logger.h 386 2014-04-15 16:26:53Z serge $

#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H

void dummy_log( const int level, const char *module_name, const char *fmt, ... );

#endif // DUMMY_LOGGER_H
