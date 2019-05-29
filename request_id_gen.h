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

// $Revision: 11688 $ $Date:: 2019-05-30 #$ $Author: serge $

#ifndef UTILS__REQUEST_ID_GEN_H
#define UTILS__REQUEST_ID_GEN_H

#include "i_request_id_gen.h"

#include <atomic>           // std::atomic

namespace utils {

class RequestIdGen: public IRequestIdGen
{
public:

    RequestIdGen();

    void init( uint32_t first, uint32_t step );

    virtual uint32_t get_next_request_id() override;

    uint32_t get_last_request_id() const;

private:

    std::atomic<uint32_t>   last_id_;

    uint32_t                step_;
};

} // namespace utils

#endif // UTILS__REQUEST_ID_GEN_H
