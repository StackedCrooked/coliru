#include <vector>
#include <atomic>
#include <cstdarg>
#include <fstream>
#include <ostream>
#include <type_traits>
#include <functional>
#include <iostream>
#include <mutex>

/* clang++ --std=c++11 log.cpp -DLOGGING_LEVEL=99 */

///------- snip logging header
namespace logging
{
#ifndef LOGGING_LEVEL
#define LOGGING_LEVEL 0xff
#endif

    constexpr int log_level = LOGGING_LEVEL;

    enum LogLevel
    {
        ALWAYS    = 0 , FATAL = 1 , ERROR     = 2 ,
        WARNING   = 3 , INFO  = 4 , RESERVED1 = 5 ,
        RESERVED2 = 6 , DEBUG = 7 , TRACE     = 8 ,
        LAST = TRACE,
    };

    namespace detail
    {
        using stream_t = 
            std::reference_wrapper<std::ostream>;

        struct log_discriptor
        {
            const char * prefix;
            stream_t stream;
            FILE * cstream;
        };

        class spinlock_mutex
        {
            std::atomic_flag flag;

        public:
            spinlock_mutex():
                flag(ATOMIC_FLAG_INIT)
            {}

            void lock()
            {
                while(flag.test_and_set(std::memory_order_acquire));
            }

            void unlock()
            {
                flag.clear(std::memory_order_release);
            }
        };

    } // end namespace detail

    std::vector<detail::log_discriptor> log_descriptors  = 
    {
        { "LOG       ==>  " , detail::stream_t(std::cerr) , stderr } ,
        { "FATAL     ==>  " , detail::stream_t(std::cerr) , stderr } ,
        { "ERROR     ==>  " , detail::stream_t(std::cerr) , stderr } ,
        { "WARNING   ==>  " , detail::stream_t(std::cout) , stdout } ,
        { "INFO      ==>  " , detail::stream_t(std::cout) , stdout } ,
        { "RESERVED1 ==>  " , detail::stream_t(std::cerr) , stderr } ,
        { "RESERVED2 ==>  " , detail::stream_t(std::cout) , stdout } ,
        { "DEBUG     ==>  " , detail::stream_t(std::cout) , stdout } ,
        { "TRACE     ==>  " , detail::stream_t(std::cerr) , stderr } ,
    };

    detail::spinlock_mutex log_mutex;

    //// For general case (things with operator<<(std::ostream...))
    template<enum LogLevel L, typename... Args>
        typename std::enable_if<(log_level >= L), void>::type 
        write_log(Args const & ... args)
        {   
            auto & stream = log_descriptors[L].stream.get();

            std::lock_guard<detail::spinlock_mutex> lock(log_mutex);

            stream << log_descriptors[L].prefix;
            (void)std::initializer_list<int> { (stream << args << ' ', 0)... };
            stream << std::endl;
        }

    //// with callback
    template<enum LogLevel L, typename F>
        typename std::enable_if<(log_level >= L), 
                 typename std::conditional<false, typename std::result_of<F()>::type, void>::type
                     >::type
        write_log(F && fn)
        { 
            fn();
        }
    
    //// printf...
    template<enum LogLevel L>
        typename std::enable_if<(log_level >= L), void>::type 
        write_log_fmt(const char * format, ...)
        {   
            auto _stream = log_descriptors[L].cstream;
            va_list args;
            va_start(args, format);

            std::lock_guard<detail::spinlock_mutex> lock(log_mutex);

            fprintf(_stream, "%s", log_descriptors[L].prefix);
            vfprintf(_stream, format, args);
            va_end(args);
        }

    //// SFINAE
    template<enum LogLevel L, typename F>
        typename std::enable_if<(log_level < L), 
                 typename std::conditional<false, typename std::result_of<F()>::type, void>::type
                     >::type
        write_log(F && fn)
        { /* intentionally empty for SFINAE */ }

    template<enum LogLevel L, typename... Args>
        typename std::enable_if<(log_level < L), void>::type
        write_log(Args const & ... args)
        { /* intentionally empty for SFINAE */ }

    template<enum LogLevel L>
        typename std::enable_if<(log_level < L), void>::type
        write_log_fmt(const char * format, ... )
        { /* intentionally empty for SFINAE */ }

#undef LOGGING_LEVEL

} // end namespace logging

///------ snip logging header



///------ snip main.cpp

using namespace logging;

//// acquires the lock manually
void external_logging()
{
    std::lock_guard<detail::spinlock_mutex> lk{log_mutex};
    std::cout << "some external message" << std::endl;
}

//// acquires the lock manually
struct external_logging_functor
{
    void operator()() const
    {
        std::lock_guard<detail::spinlock_mutex> lk{log_mutex};
        std::cout << "some external functor\n";
    }
};

int main(void)
{ 
    std::cout.sync_with_stdio(true);
    std::cerr.sync_with_stdio(true);

    write_log<ALWAYS>("hello, world!");
    write_log<INFO>("info");

    write_log<ERROR>(external_logging);
    write_log<TRACE>(external_logging_functor());

    write_log_fmt<DEBUG>("%s is a %s: %d\n",
                         "this", "test", 5);

    //// hmm change the streams ?
    //log_descriptors[DEBUG].cstream = fopen("test", "w");

    //write_log_fmt<DEBUG>("%s is a %s: %d\n",
    //                     "this", "test", 5);

    //fclose(log_descriptors[DEBUG].cstream);
}
