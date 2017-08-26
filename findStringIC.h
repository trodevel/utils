// https://stackoverflow.com/questions/3152241/case-insensitive-stdstring-find/19839371#19839371

#ifndef LIB_UTILS__FIND_STRING_IC_H
#define LIB_UTILS__FIND_STRING_IC_H

#include <string>

namespace utils
{

/// Try to find in the Haystack the Needle - ignore case
bool findStringIC(const std::string & strHaystack, const std::string & strNeedle);

} // namespace utils

#endif // LIB_UTILS__FIND_STRING_IC_H
