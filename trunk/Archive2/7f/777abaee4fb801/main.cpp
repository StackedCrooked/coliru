#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>


class ThreadPool
{
public:
    ThreadPool(std::size_t num_threads) : work_(ios_)
    {
        for (std::size_t i = 0; i != num_threads; ++i)
        {
            threads_.create_thread([this]{ ios_.run(); });
        }
    }

    template<typename F>
    void post(F&& f) { ios_.post(std::forward<F>(f)); }

    template<typename F>
    void dispatch(F&& f) { ios_.dispatch(std::forward<F>(f)); }

private:
    boost::asio::io_service ios_;
    boost::thread_group threads_;
    boost::asio::io_service::work work_;
};


int main()
{
    ThreadPool pool(4);
    usleep(100);
    for (int i = 0; i != 10; ++i)
    {
        pool.post([i]{ std::cout << '[' << i << ']'; });
    }
    usleep(100);    
}
