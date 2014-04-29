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

// $Id: HTTPDownloader.hpp 400 2014-04-16 17:12:30Z serge $

#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP

#include <string>

/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 */
class HTTPDownloader
{
public:
    HTTPDownloader();
    ~HTTPDownloader();
    /**
     * Download a file using HTTP GET and store in in a std::string
     * @param url The URL to download
     * @return The download result
     */
    std::string download( const std::string& url );

    /**
     * @return true - ok, false - error
     */
    bool download_file( const std::string& url, const std::string & file );

private:
    void* curl;
};

#endif  /* HTTPDOWNLOADER_HPP */
