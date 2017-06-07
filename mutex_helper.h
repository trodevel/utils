// LICENSE: Creative Commons Attribution-Sharealike 3.0 Unported License (CC-BY-SA) and by the GNU Free Documentation License (GFDL)
// http://en.cppreference.com/w/cpp/thread/sleep_for

#ifndef MUTEX_HELPER_H
#define MUTEX_HELPER_H

#include <chrono>
#include <thread>

#define MUTEX_SCOPE_LOCK(_x)        std::lock_guard<std::mutex> _(_x)
#define MUTEX_LOCK(_x)              _x.lock();
#define MUTEX_UNLOCK(_x)            _x.unlock();
#define THIS_THREAD_SLEEP(_x)       std::this_thread::sleep_for( _x )
#define THIS_THREAD_SLEEP_MS(_x)    std::this_thread::sleep_for( std::chrono::milliseconds( _x ) )
#define THIS_THREAD_SLEEP_SEC(_x)   std::this_thread::sleep_for( std::chrono::seconds( _x ) )

#endif // MUTEX_HELPER_H
