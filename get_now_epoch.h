/*

Get now epoch.

Copyright (C) 2019 Sergey Kolevatov

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

#ifndef LIB_UTILS__GET_NOW_EPOCH_H
#define LIB_UTILS__GET_NOW_EPOCH_H

#include "epoch32_t.h"  // epoch32_t

namespace utils
{

epoch32_t get_now_epoch();

epoch64_t get_now_epoch_microsec();

} // namespace utils

#endif // LIB_UTILS__GET_NOW_EPOCH_H
