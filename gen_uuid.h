/*

UUID generator.

Copyright (C) 2016 Sergey Kolevatov

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

// $Revision: 12061 $ $Date:: 2019-09-27 #$ $Author: serge $

#ifndef UTILS__GEN_UUID_H
#define UTILS__GEN_UUID_H

#include <string>       // std::string

namespace utils
{
std::string gen_uuid();
}

#endif // UTILS__GEN_UUID_H
