#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>
#include <ctime>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#define SIZE 10

class ActiveObject
{
public:
    ActiveObject()
        : service_(),
          work_(boost::asio::io_service::work(service_))
    {
        executionThread_.reset(new std::thread([&] { service_.run(); }));
    }

    virtual ~ActiveObject()
    {
        // execute all unfinished work in case this object is leaving scope.
        work_ = boost::none;
        executionThread_->join();
        std::cout << "active object thread exited" << std::endl;
    }

    void doSomething()
    {
        // post request the io_service to invoke someImpl method and return immediately
        service_.post([this] { someImpl();});
    }

protected:
    boost::asio::io_service service_;
    boost::optional<boost::asio::io_service::work> work_;

private:
    std::shared_ptr<std::thread> executionThread_;

    void someImpl()
    {
        std::chrono::milliseconds dura(200);
        std::this_thread::sleep_for(dura);
        std::cout << "poll thread id: " << std::this_thread::get_id() << std::endl;
    }

};

int main()
{
    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

    ActiveObject obj;
    std::chrono::milliseconds dura(200);
    std::this_thread::sleep_for(dura);

    for(int i=0; i < SIZE; ++i)
    {
        obj.doSomething(); // call is nonblocking
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout <<  "main thread exited " << std::endl;
}
