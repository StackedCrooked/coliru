#include <boost/asio.hpp>
#include <boost/atomic.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/move/utility.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <sstream>
#include <string>

class Log {
  public:
    Log(std::string const &logFileName, int32_t queueSize, std::vector<int32_t> const &pushCores)
      : fp(stderr),
        flag(false),
        thrd(&Log::pop, this),
        _queue(queueSize),
        _service(),
        _work(_service)
    {
        fp = stderr; // std::fopen(logFileName.c_str(),"w");
        flag = true;

        for (auto& c:pushCores) {
            thread_pool.create_thread([&] { (void) c; _service.run(); });
        }
    }

    void pop() {
        std::string s;
        s.reserve(1000);

        struct timeval ts;
        while (flag) {
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

    template <typename T> std::string stringer(T const &t) {
        return boost::lexical_cast<std::string>(t);
    }

    template <typename T, typename... Args>
    std::string stringer(T const &t, Args const &... args) {
        return stringer(t) + stringer(args...);
    }

    template <typename T, typename... Args> void enqueue(T &t, Args const&... args) {
        _service.post([=]{ 
                    push(stringer(t, args...));
                });
    }

    void push(std::string const &s) {
        while (!_queue.push(s));
    }

    ~Log() {
        _service.stop();
        thread_pool.join_all();

        flag = false;
        thrd.join();

        std::fflush(fp);
        std::fclose(fp);

        fp = NULL;
    }

  private:
    FILE *fp;
    boost::atomic<bool> flag;

    boost::thread thrd;
    boost::lockfree::spsc_queue<std::string> _queue;

    boost::asio::io_service _service;
    boost::optional<boost::asio::io_service::work> _work;
    boost::thread_group thread_pool;
};


int main() {
    std::vector<int32_t> pushCores;
    for (int i = 0; i < 10; ++i) {
        pushCores.push_back(i);
        pushCores.push_back(i);
    }

    Log l("/tmp/junk.log", 1024, pushCores);
    struct timeval ts_1, ts_2;
    gettimeofday(&ts_1, NULL);
    gettimeofday(&ts_2, NULL);

    for (int64_t i = 0; i < 10; ++i) {
        l.enqueue("hello", " world");
    }
    std::fprintf(stderr, "%li microsec\n", (ts_2.tv_sec - ts_1.tv_sec) * 1000000 + (ts_2.tv_usec - ts_1.tv_usec));
}
