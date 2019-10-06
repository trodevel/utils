#include "EMailSender.h"    // EMailSender

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

        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }
}
