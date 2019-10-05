/*

Simple EMail Sender.

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

// $Revision: 12104 $ $Date:: 2019-10-04 #$ $Author: serge $

#ifndef UTILS__EMAIL_SENDER_H
#define UTILS__EMAIL_SENDER_H

#include <string>
#include <vector>

// A non-threadsafe simple libcURL e-mail sender

class EMailSender
{
public:
    EMailSender(
            const std::string   & host_name,
            unsigned            port,
            const std::string   & username,
            const std::string   & secret);

    ~EMailSender();

    // @return true - ok, false - error
    bool send(
            std::string         * error_msg,
            const std::string   & from,
            const std::string   & to,
            const std::string   & cc,
            const std::string   & subject,
            const std::string   & body );
public:

    struct Context
    {
        std::vector<std::string>    lines;
        std::size_t                 current_line;
    };

private:

    static std::string add_angle_brackets( const std::string & s );

    static Context to_context(
            const std::string   & from,
            const std::string   & to,
            const std::string   & cc,
            const std::string   & subject,
            const std::string   & body );

private:
    void        *curl_;

    std::string smtp_server_;
    std::string username_;
    std::string secret_;
};

#endif  // UTILS__EMAIL_SENDER_H
