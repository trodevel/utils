/*

Request ID generator interface.

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

#ifndef UTILS__I_REQUEST_ID_GEN_H
#define UTILS__I_REQUEST_ID_GEN_H

#include <cstdint>      // uint32_t

namespace utils {

class IRequestIdGen
{
public:

    virtual ~IRequestIdGen() {};

    virtual uint32_t get_next_request_id()  = 0;
};

} // namespace utils

#endif // UTILS__I_REQUEST_ID_GEN_H
