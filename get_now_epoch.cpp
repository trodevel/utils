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

// $Revision: 11734 $ $Date:: 2019-06-13 #$ $Author: serge $

#include "get_now_epoch.h"      // self

#include <chrono>           // std::chrono

#include "chrono_epoch.h"   // to_epoch()

namespace utils
{

epoch32_t get_now_epoch()
{
    return to_epoch( std::chrono::system_clock::now() );
}

epoch64_t get_now_epoch_microsec()
{
    return to_epoch_microsec( std::chrono::system_clock::now() );
}

} // namespace utils
