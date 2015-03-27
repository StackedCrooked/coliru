#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <future>


class ThreadPool
{
public:
    ThreadPool(std::size_t num_threads) : work(ios)
    {
        for (std::size_t i = 0; i != num_threads; ++i)
        {
            tg.create_thread([this]{ ios.run(); });
        }
    }

    template<typename F>
    void post(F&& f) { ios.post(std::forward<F>(f)); }

    template<typename F>
    void dispatch(F&& f) { ios.dispatch(std::forward<F>(f)); }

private:
    boost::asio::io_service ios;
    boost::thread_group tg;
    boost::asio::io_service::work work;
};


int main()
{
    ThreadPool pool(4);
    usleep(1);
    for (int i = 0; i != 10; ++i)
    {
        pool.post([i]{ std::cout << '[' << i << ']'; });
    }
    usleep(1);    
}
