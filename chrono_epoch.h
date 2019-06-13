/*

C++ std::chrono to epoch converter

https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back

*/

// $Revision: 11731 $ $Date:: 2019-06-13 #$ $Author: serge $

#ifndef LIB_UTILS_CHRONO_EPOCH_H
#define LIB_UTILS_CHRONO_EPOCH_H

#include <chrono>       // std::chrono
#include "epoch32_t.h"  // epoch32_t

namespace utils
{

epoch32_t to_epoch( const std::chrono::system_clock::time_point & tp );

epoch64_t to_epoch_microsec( const std::chrono::system_clock::time_point & tp );

} // namespace utils

#endif // LIB_UTILS_CHRONO_EPOCH_H
