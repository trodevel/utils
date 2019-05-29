/*

Convenience wrapper for boost assert.

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
// $Revision: 10640 $ $Date:: 2019-03-13 #$ $Author: serge $

#ifndef UTILS_ASSERT_H
#define UTILS_ASSERT_H

#include <cassert>      // assert

#ifndef ASSERT
#define ASSERT(_x)  assert(_x)
#endif

#endif // UTILS_ASSERT_H
