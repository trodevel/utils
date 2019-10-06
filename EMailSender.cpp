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

// $Revision: 12106 $ $Date:: 2019-10-05 #$ $Author: serge $

#include "EMailSender.h"    // self
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>          // memcpy

namespace utils
{

EMailSender::EMailSender(
        const std::string   & host_name,
        unsigned            port,
        const std::string   & username,
        const std::string   & secret)
{
    curl_ = curl_easy_init();

    smtp_server_  = "smtp://" + host_name + ":" + std::to_string( port );
}

EMailSender::~EMailSender()
{
    curl_easy_cleanup( curl_ );
}

static size_t data_getter( void *ptr, size_t size, size_t nmemb, void *userp )
{
    auto * context = (EMailSender::Context *)userp;

    if( ( size == 0 ) || ( nmemb == 0 ) || ( ( size * nmemb ) < 1 ) )
    {
        return 0;
    }

    if( context->current_line < context->lines.size() )
    {
        auto & line = context->lines[context->current_line];

        size_t len = line.size();
        memcpy( ptr, line.c_str(), len );
        context->current_line++;

        return len;
    }

    return 0;
}

// @return true - ok, false - error
bool EMailSender::send(
        std::string         * error_msg,
        const std::string   & from,
        const std::string   & to,
        const std::string   & cc,
        const std::string   & subject,
        const std::string   & body )
{
    if( curl_ == nullptr )
    {
        * error_msg = "failed to initialize curl";
        return false;
    }

    curl_easy_setopt( curl_, CURLOPT_USERNAME, username_.c_str() );
    curl_easy_setopt( curl_, CURLOPT_PASSWORD, secret_.c_str() );

    curl_easy_setopt( curl_, CURLOPT_URL, smtp_server_.c_str() );

    curl_easy_setopt( curl_, CURLOPT_USE_SSL, (long )CURLUSESSL_ALL );

    curl_easy_setopt( curl_, CURLOPT_MAIL_FROM, add_angle_brackets( from ).c_str() );

    struct curl_slist *recipients = nullptr;

    if( to.empty() == false )
        recipients = curl_slist_append( recipients, add_angle_brackets( to ).c_str() );

    if( cc.empty() == false )
        recipients = curl_slist_append( recipients, add_angle_brackets( cc ).c_str() );

    curl_easy_setopt( curl_, CURLOPT_MAIL_RCPT, recipients );

    auto context = to_context( from, to, cc, subject, body );

    curl_easy_setopt( curl_, CURLOPT_READFUNCTION, data_getter );
    curl_easy_setopt( curl_, CURLOPT_READDATA, & context );
    curl_easy_setopt( curl_, CURLOPT_UPLOAD, 1L );

    curl_easy_setopt( curl_, CURLOPT_VERBOSE, 1L ); // DEBUG

    CURLcode res = curl_easy_perform( curl_ );

    if( res != CURLE_OK )
    {
        * error_msg = "curl_easy_perform() failed: " + std::string( curl_easy_strerror( res ) );
        return false;
    }

    curl_slist_free_all( recipients );

    return true;
}

std::string EMailSender::add_angle_brackets( const std::string & s )
{
    return "<" + s + ">";
}

EMailSender::Context EMailSender::to_context(
        const std::string   & from,
        const std::string   & to,
        const std::string   & cc,
        const std::string   & subject,
        const std::string   & body )
{
    Context res;

    res.current_line    = 0;

    return res;
}

} // namespace utils
