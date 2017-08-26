// https://stackoverflow.com/questions/3152241/case-insensitive-stdstring-find/19839371#19839371

#include <algorithm>
#include <string>
#include <cctype>

namespace utils
{

/// Try to find in the Haystack the Needle - ignore case
bool findStringIC(const std::string & strHaystack, const std::string & strNeedle)
{
  auto it = std::search(
    strHaystack.begin(), strHaystack.end(),
    strNeedle.begin(),   strNeedle.end(),
    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
  );
  return (it != strHaystack.end() );
}

} // namespace utils
