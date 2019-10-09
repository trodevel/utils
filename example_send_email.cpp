#include "EMailSender.h"    // EMailSender

#include "log_test.h"       // log_test

#include <fstream>

void to_EmailWithName(
        utils::EMailSender::EMailWithName   * res,
        const std::string                   & l )
{
    auto pos = l.find( ' ' );

    if( pos == std::string::npos )
    {
        res->email  = l;
        res->name   = "";

        return;
    }

    res->email  = l.substr( 0, pos );
    res->name   = l.substr( pos + 1 );
}

std::string to_string( const utils::EMailSender::EMailWithName & s )
{
    auto res = s.email;

    if( s.name.empty() == false )
        res += " " + s.name;

    return res;
}

bool read_config(
        utils::EMailSender::EMailWithName   * from,
        utils::EMailSender::EMailWithName   * to,
        utils::EMailSender::EMailWithName   * cc,
        utils::EMailSender::EMailWithName   * bcc,
        std::string         * host_name,
        uint32_t            * port,
        std::string         * user_name,
        std::string         * password,
        const std::string   & filename )
{
    try
    {
        std::ifstream file( filename );
        std::string l;

        std::getline( file, l );
        to_EmailWithName( from, l );

        std::getline( file, l );
        to_EmailWithName( to, l );

        std::getline( file, l );
        to_EmailWithName( cc, l );

        std::getline( file, l );
        to_EmailWithName( bcc, l );

        std::getline( file, * host_name );
        std::getline( file, l );
        * port    = stoi( l );
        std::getline( file, * user_name );
        std::getline( file, * password );

        std::cerr << "DEBUG:" << "\n"
                << "filename  = " << filename << "\n"
                << "from      = " << to_string( * from ) << "\n"
                << "to        = " << to_string( * to ) << "\n"
                << "cc        = " << to_string( * cc ) << "\n"
                << "bcc       = " << to_string( * bcc ) << "\n"
                << "host_name = " << * host_name << "\n"
                << "port      = " << * port << "\n"
                << "user_name = " << * user_name << "\n"
                << "password  = " << "..." << "\n"
                << std::endl;

        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }
}

void test_send_mail_kernel(
        const std::string & name,
        const std::string & filename,
        const std::string & body )
{
    utils::EMailSender::EMailWithName from;
    utils::EMailSender::EMailWithName to;
    utils::EMailSender::EMailWithName cc;
    utils::EMailSender::EMailWithName bcc;

    std::string host_name;
    uint32_t    port;
    std::string user_name;
    std::string password;

    auto b = read_config( & from, & to, & cc, & bcc, & host_name, & port, & user_name, & password, filename );

    if( b == false )
    {
        log_test( name, b, true, "config loaded", "cannot load config file", filename );
        return;
    }

    utils::EMailSender s( host_name, port, user_name, password );

    std::string error_msg;

    b = s.send( & error_msg, from, to, cc, bcc, name, body );

    log_test( name, b, true, "sent email", "cannot send email", error_msg );
}


void test_send_mail_01()
{
    test_send_mail_kernel( "test_send_mail_01", "send_mail_01.cfg", "one-liner" );
}

void test_send_mail_02()
{
    static const std::string body =
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\n"
            "sed do eiusmod tempor incididunt ut labore et dolore magna\n"
            "aliqua. Ut enim ad minim veniam, quis nostrud exercitation\n"
            "ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
            "Duis aute irure dolor in reprehenderit in voluptate velit\n"
            "esse cillum dolore eu fugiat nulla pariatur. Excepteur sint\n";

    test_send_mail_kernel( "test_send_mail_02", "send_mail_01.cfg", body );
}

void test_send_mail_03()
{
    static const std::string body =
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\n"
            "sed do eiusmod tempor incididunt ut labore et dolore magna\n"
            "aliqua. Ut enim ad minim veniam, quis nostrud exercitation\n"
            "ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
            "Duis aute irure dolor in reprehenderit in voluptate velit\n"
            "esse cillum dolore eu fugiat nulla pariatur. Excepteur sint\n";

    test_send_mail_kernel( "test_send_mail_03", "send_mail_02.cfg", body );
}

void test_send_mail_04()
{
    test_send_mail_kernel( "test_send_mail_04", "send_mail_03.cfg", "one-liner" );
}

void test_send_mail_05()
{
    test_send_mail_kernel( "test_send_mail_05", "send_mail_04.cfg", "one-liner" );
}

void test_send_mail_06()
{
    test_send_mail_kernel( "test_send_mail_06", "send_mail_05.cfg", "one-liner" );
}

void test_send_mail()
{
    test_send_mail_01();
    test_send_mail_02();
    test_send_mail_03();
    test_send_mail_04();
    test_send_mail_05();
    test_send_mail_06();
}
