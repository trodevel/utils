/*

Adjust WAV file header in order to let Skype correctly read it.

Copyright (C) 2014 Sergey Kolevatov

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

// $Id: tune_wav.h 467 2014-05-02 17:42:09Z serge $

#ifndef UTILS_TUNE_WAV_H
#define UTILS_TUNE_WAV_H

#include <string>

bool tune_wav( const std::string & filename, const std::string & outp );

#endif // UTILS_TUNE_WAV_H
