#include "EMailSender.h"    // EMailSender

#include "log_test.h"       // log_test

#include <fstream>

bool send_email(
        std::string         * error_msg,
        const std::string   & from,
        const std::string   & to,
        const std::string   & cc,
        const std::string   & subject,
        const std::string   & body,
        const std::string   & host_name,
        uint32_t            port,
        const std::string   & user_name,
        const std::string   & password
        )
{
    utils::EMailSender s( host_name, port, user_name, password );

    return s.send( error_msg, from, to, cc, subject, body );
}

bool read_config(
        std::string         * from,
        std::string         * to,
        std::string         * cc,
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

        std::getline( file, * from );
        std::getline( file, * to );
        std::getline( file, * cc );
        std::getline( file, * host_name );
        std::getline( file, l );
        * port    = stoi( l );
        std::getline( file, * user_name );
        std::getline( file, * password );

        std::cerr << "DEBUG:" << "\n"
                << "from      = " << * from << "\n"
                << "to        = " << * to << "\n"
                << "cc        = " << * cc << "\n"
                << "host_name = " << * host_name << "\n"
                << "port      = " << * port << "\n"
                << "user_name = " << * user_name << "\n"
                << "password  = " << * password << "\n"
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
    std::string from;
    std::string to;
    std::string cc;
    std::string host_name;
    uint32_t    port;
    std::string user_name;
    std::string password;

    auto b = read_config( & from, & to, & cc, & host_name, & port, & user_name, & password, filename );

    if( b == false )
    {
        log_test( name, b, true, "config loaded", "cannot load config file", filename );
        return;
    }

    std::string error_msg;

    b = send_email( & error_msg, from, to, cc, name, body, host_name, port, user_name, password );

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

void test_send_mail()
{
    test_send_mail_01();
    test_send_mail_02();
}
