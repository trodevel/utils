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

// $Revision: 13835 $ $Date:: 2020-09-25 #$ $Author: serge $

#include "EMailSender.h"    // self
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>          // memcpy
#include <ctime>            // strftime

#include "gen_uuid.h"       // utils::gen_uuid

#ifdef EMAIL_SENDER_DEBUG
#include <iostream>
#include "../hexdump/Hexdump.hpp"
#endif // EMAIL_SENDER_DEBUG

namespace utils
{

EMailSender::EMailSender(
        const std::string   & host_name,
        unsigned            port,
        const std::string   & username,
        const std::string   & password ):
                username_( username ),
                password_( password )
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

    if( context->current_offset < context->content.size() )
    {
        auto block_size = size;

        if( context->current_offset + block_size >= context->content.size() )
        {
            block_size = context->content.size() - context->current_offset;
        }

#ifdef EMAIL_SENDER_DEBUG
        std::cerr << "content " << block_size << ":" << context->content.substr( context->current_offset, block_size ) << "\n";
#endif

        context->content.copy( reinterpret_cast<char*>( ptr ), block_size, context->current_offset );
        context->current_offset += block_size;

        return block_size;
    }

    return 0;
}

// @return true - ok, false - error
bool EMailSender::send(
        std::string         * error_msg,
        const std::string   & from,
        const std::string   & to,
        const std::string   & cc,
        const std::string   & bcc,
        const std::string   & subject,
        const std::string   & body )
{
    return send( error_msg, { from, "" }, { to, "" }, { cc, "" }, { bcc, "" }, subject, body );
}

// @return true - ok, false - error
bool EMailSender::send(
        std::string         * error_msg,
        const EMailWithName & from,
        const EMailWithName & to,
        const EMailWithName & cc,
        const EMailWithName & bcc,
        const std::string   & subject,
        const std::string   & body )
{
    if( curl_ == nullptr )
    {
        * error_msg = "failed to initialize curl";
        return false;
    }

    curl_easy_setopt( curl_, CURLOPT_USERNAME, username_.c_str() );
    curl_easy_setopt( curl_, CURLOPT_PASSWORD, password_.c_str() );

    curl_easy_setopt( curl_, CURLOPT_URL, smtp_server_.c_str() );

    curl_easy_setopt( curl_, CURLOPT_USE_SSL, (long )CURLUSESSL_ALL );

    curl_easy_setopt( curl_, CURLOPT_MAIL_FROM, add_angle_brackets( from.email ).c_str() );

    struct curl_slist *recipients = nullptr;

    if( to.email.empty() == false )
        recipients = curl_slist_append( recipients, add_angle_brackets( to.email ).c_str() );

    if( cc.email.empty() == false )
        recipients = curl_slist_append( recipients, add_angle_brackets( cc.email ).c_str() );

    if( bcc.email.empty() == false )
        recipients = curl_slist_append( recipients, add_angle_brackets( bcc.email ).c_str() );

    curl_easy_setopt( curl_, CURLOPT_MAIL_RCPT, recipients );

    auto context = to_context( from, to, cc, bcc, subject, body );

#ifdef EMAIL_SENDER_DEBUG
    std::cerr << "context:\n" << Hexdump( context.content.c_str(), context.content.size() ) << "\n";
#endif // EMAIL_SENDER_DEBUG

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

std::string EMailSender::to_string( const EMailWithName & s )
{
    std::string res;

    if( s.name.empty() == false )
        res += s.name + " ";

    res += add_angle_brackets( s.email );

    return res;
}

std::string EMailSender::get_date()
{
    const int RFC5322_TIME_LEN = 32;
    time_t t;
    struct tm *tm;

    std::string res;
    res.resize( RFC5322_TIME_LEN );

    time( &t );
    tm = localtime( &t );

    auto size = std::strftime( &res[0], RFC5322_TIME_LEN, "%a, %d %b %Y %H:%M:%S %z", tm );

    res.resize( size );

    return res;
}

std::string EMailSender::generate_message_id( const std::string & from )
{
    auto id = utils::gen_uuid();

    auto pos = from.find( '@' );

    if( pos != from.npos )
    {
        id += from.substr( pos );
    }

    return id;
}

void EMailSender::append(
        Context             * res,
        const std::string   & line )
{
    res->content.append( line );
    res->content.append( "\r\n" );
}

void EMailSender::append_header(
        Context             * res,
        const EMailWithName & from,
        const EMailWithName & to,
        const EMailWithName & cc,
        const EMailWithName & bcc,
        const std::string   & subject,
        const std::string   & date,
        const std::string   & message_id )
{
    append( res, "Date: " + date );
    append( res, "From: " + to_string( from ) );

    if( to.email.empty() == false )
        append( res, "To: " + to_string( to ) );

    if( cc.email.empty() == false )
        append( res, "Cc: " + to_string( cc ) );

    if( bcc.email.empty() == false )
        append( res, "Bcc: " + to_string( bcc ) );

    append( res, "Message-ID: " + add_angle_brackets( message_id ) );
    append( res, "Subject: " + subject );
    append( res, "" );  // empty line to divide headers from body, see RFC5322
}

EMailSender::Context EMailSender::to_context(
        const EMailWithName & from,
        const EMailWithName & to,
        const EMailWithName & cc,
        const EMailWithName & bcc,
        const std::string   & subject,
        const std::string   & body )
{
    Context res;

    res.current_offset    = 0;

    auto date       = get_date();
    auto message_id = generate_message_id( from.email );

    append_header( & res,
            from,
            to,
            cc,
            bcc,
            subject,
            date,
            message_id );

    append( & res, body );

    return res;
}

} // namespace utils
