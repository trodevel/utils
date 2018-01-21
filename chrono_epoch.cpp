/*

C++ std::chrono to epoch converter

https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back

*/

// $Revision: 8542 $ $Date:: 2018-01-18 #$ $Author: serge $

#include "chrono_epoch.h"       // self

namespace utils
{

uint32_t to_epoch( const std::chrono::system_clock::time_point & tp )
{
    auto tp_casted = std::chrono::time_point_cast<std::chrono::seconds>( tp );

    auto epoch = tp_casted.time_since_epoch();

    auto value = std::chrono::duration_cast<std::chrono::seconds>( epoch );

    uint32_t duration = value.count();

    return duration;
}

uint64_t to_epoch_microsec( const std::chrono::system_clock::time_point & tp )
{
    auto tp_casted = std::chrono::time_point_cast<std::chrono::microseconds>( tp );

    auto epoch = tp_casted.time_since_epoch();

    auto value = std::chrono::duration_cast<std::chrono::microseconds>( epoch );

    uint64_t duration = value.count();

    return duration;
}

} // namespace utils
