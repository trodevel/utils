/*

C++ std::chrono to epoch converter

https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back

*/

// $Revision: 8542 $ $Date:: 2018-01-18 #$ $Author: serge $

#ifndef LIB_UTILS_CHRONO_EPOCH_H
#define LIB_UTILS_CHRONO_EPOCH_H

#include <chrono>       // std::chrono
#include <cstdint>      // uint32_t, uint64_t

namespace utils
{

uint32_t to_epoch( const std::chrono::system_clock::time_point & tp );

uint64_t to_epoch_microsec( const std::chrono::system_clock::time_point & tp );

} // namespace utils

#endif // LIB_UTILS_CHRONO_EPOCH_H
