/*

Pretty printer of test results.

Copyright (C) 2019 Sergey Kolevatov

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

// $Revision: 12061 $ $Date:: 2019-09-27 #$ $Author: serge $

#include <iostream>
#include <string>

inline void log_test(
        const std::string   & test_name,
        bool                res,
        bool                expected_res,
        const std::string   & exp_msg,
        const std::string   & not_exp_msg,
        const std::string   & error_msg )
{
    std::cout << "log_test: "<< test_name << " - ";

    if( res == expected_res )
    {
        std::cout << "OK: " << exp_msg;
    }
    else
    {
        std::cout << "ERROR: " << not_exp_msg;
    }

    if( ! error_msg.empty() )
    {
        std::cout << ": " << error_msg;
    }

    std::cout << std::endl;
}
