#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>

#include <boost/atomic.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/thread/thread.hpp>

/*
 * safe for use from a single thread only
 */
template <unsigned line_maxchars = 1000>
class Log {
  public:
    Log(std::string const &logFileName, int32_t queueSize)
      : fp(stderr), // std::fopen(logFileName.c_str(),"w")
        _shutdown(false),
        thrd(&Log::pop, this),
        _queue(queueSize)
    { }

    void pop() {
        std::string s;
        s.reserve(line_maxchars);

        struct timeval ts;
        while (!_shutdown) {
            while (_queue.pop(s)) {
                gettimeofday(&ts, NULL);
                std::fprintf(fp, "%li.%06li %s\n", ts.tv_sec, ts.tv_usec, s.c_str());
            }
            std::fflush(fp); // RECONSIDER HERE?
        }

        while (_queue.pop(s)) {
            gettimeofday(&ts, NULL);
            std::fprintf(fp, "%li.%06li %s\n", ts.tv_sec, ts.tv_usec, s.c_str());
        }
    }

    template <typename S, typename T> void stringer(S& stream, T const &t) {
        stream << t;
    }

    template <typename S, typename T, typename... Args>
    void stringer(S& stream, T const &t, Args const &... args) {
        stringer(stream, t);
        stringer(stream, args...);
    }

    template <typename T, typename... Args> void enqueue(T &t, Args const&... args) {
        thread_local char buffer[line_maxchars] = {};
        boost::iostreams::array_sink as(buffer);
        boost::iostreams::stream<boost::iostreams::array_sink> stream(as);

        stringer(stream, t, args...);

        auto output = as.output_sequence();
        push(std::string(output.first, output.second));
    }

    void push(std::string const &s) {
        while (!_queue.push(s));
    }

    ~Log() {
        _shutdown = true;
        thrd.join();

        assert(_queue.empty());
        std::fflush(fp);
        std::fclose(fp);

        fp = NULL;
    }

  private:
    FILE *fp;
    boost::atomic_bool _shutdown;

    boost::thread thrd;
    boost::lockfree::spsc_queue<std::string> _queue;
};

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    {
        Log<> l("/tmp/junk.log", 1024);

        for (int64_t i = 0; i < 10; ++i) {
            l.enqueue("hello", " world ", boost::gregorian::day_clock::local_day());
        }
    }

    std::cout << duration_cast<microseconds>(high_resolution_clock::now() - start).count() << "μs\n";
}
