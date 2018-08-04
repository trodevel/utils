/*

Request ID generator.

Copyright (C) 2018 Sergey Kolevatov

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

// $Revision: 9588 $ $Date:: 2018-08-03 #$ $Author: serge $

#include "request_id_gen.h"     // self

namespace utils {

RequestIdGen::RequestIdGen():
    last_id_( 0 ),
    first_( 1 ),
    step_( 1 )
{
}

void RequestIdGen::init( uint32_t first, uint32_t step )
{
    first_      = first;
    step_       = step;
}

uint32_t RequestIdGen::get_next_request_id()
{
    auto    res = last_id_++;

    return first_ + ( res * step_ );
}

} // namespace utils
