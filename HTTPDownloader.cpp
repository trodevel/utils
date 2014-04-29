/*

http://techoverflow.net/blog/2013/03/15/c-simple-http-download-using-libcurl-easy-api/

Code License.

As you might have noticed, most code on this blog is licensed as Apache
License v2.0. If a code snippet published on this domain does not
contain a license statement, you are allowed to use it under Apache
License v2.0.

This includes you won't held me liable for any damage done, directly or
indirectly, with my code. Also, I won't

However, there's a special exception: I hereby grant the special
permission to all readers of this blog to skip section 4 a), b), c) and
d) for all code published on the domain techoverflow.net or any of its
subdomains marked with 'Uli Köhler' as author and licensed under Apache
License v2.0

In other words, you don't have to include neither the original author (=
me) nor a copy of the Apache License when redistributing derivate works.
I'd still prefer if you mentioned me as original author, but you don't
have to.

Note that this special exception only applies to code published on this
blog, and not my GitHub account or other projects.

Why? Because on TechOverflow, we publish short- to medium-sized snippets
and we want to make it as easy as possible for anyone to reuse those
snippets in commercial or non-commercial projects. Of course, Open
Source is preferred!

Please contact me (see Impressum page) for questions or requests
regarding licensing.

*/

// $Id: HTTPDownloader.cpp 400 2014-04-16 17:12:30Z serge $
#include "HTTPDownloader.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

size_t write_data( void *ptr, size_t size, size_t nmemb, void *stream )
{
    string data( (const char*)ptr, (size_t)size * nmemb );
    *( (stringstream*)stream ) << data << endl;
    return size * nmemb;
}

size_t write_data_file( void *ptr, size_t size, size_t nmemb, void *stream )
{
    string data( (const char*)ptr, (size_t)size * nmemb );
    *( (ofstream*)stream ) << data;
    return size * nmemb;
}


HTTPDownloader::HTTPDownloader()
{
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader()
{
    curl_easy_cleanup( curl );
}

string HTTPDownloader::download( const std::string& url )
{
    curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
    curl_easy_setopt( curl, CURLOPT_NOSIGNAL, 1 ); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt( curl, CURLOPT_ACCEPT_ENCODING, "deflate" );
    std::stringstream out;
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, &out );
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform( curl );
    /* Check for errors */
    if( res != CURLE_OK )
    {
        fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( res ) );
    }
    return out.str();
}

bool HTTPDownloader::download_file( const std::string& url, const std::string & file )
{
    curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
    curl_easy_setopt( curl, CURLOPT_NOSIGNAL, 1 ); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt( curl, CURLOPT_ACCEPT_ENCODING, "deflate" );

    std::ofstream out( file.c_str() );

    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data_file );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, &out );
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform( curl );
    /* Check for errors */
    if( res != CURLE_OK )
    {
        fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( res ) );
        return false;
    }
    return true;
}

