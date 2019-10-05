/*

Simple Epoch to String converter.

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

// $Revision: 12013 $ $Date:: 2019-09-19 #$ $Author: serge $


#include "epoch_to_string.h"    // self

#include "boost_epoch.h"        // utils::from_epoch_sec

namespace utils
{

std::string epoch_to_string( epoch32_t epoch )
{
    return boost::posix_time::to_simple_string( from_epoch_sec( epoch ) );
}

} // namespace utils