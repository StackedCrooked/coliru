#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <list>
#include <iostream>
// for refcounting:
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

namespace asio = boost::asio;

class AsyncBuffer {
    friend class MyClass;
  protected:
    AsyncBuffer(boost::asio::io_service &io_service) : write_event_(io_service) {
        write_event_.expires_at(boost::posix_time::pos_infin);
    }

    void Write(uint32_t data) {
        buffer_.push_back(data);
        write_event_.cancel();
    }

    uint32_t Read(boost::asio::yield_context context) {
        if (buffer_.empty()) {
            boost::system::error_code ec;
            write_event_.async_wait(context[ec]);

            if (ec != boost::asio::error::operation_aborted || write_event_.expires_from_now().is_negative())
            {
                if (context.ec_)
                    *context.ec_ = boost::asio::error::operation_aborted;
                return 0;
            }
        }

        uint32_t data = buffer_.front();
        buffer_.pop_front();
        return data;
    }

    void Stop() {
        write_event_.expires_from_now(boost::posix_time::seconds(-1));
    }

  private:
    boost::asio::deadline_timer write_event_;
    std::list<uint32_t> buffer_;
};

class MyClass : public boost::enable_shared_from_this<MyClass> {
    bool stopped_;
  public:
    MyClass(boost::asio::io_service &io_service) : stopped_(false), buffer_(io_service), strand_(io_service) {}

    void Run(boost::asio::yield_context context) {
        while (!stopped_) {
            boost::system::error_code ec;

            uint32_t data = buffer_.Read(context[ec]);

            if (ec == boost::asio::error::operation_aborted)
                break;

            // do something with data
            std::cout << data << " " << std::flush;
        }
        std::cout << "EOF\n";
    }

    bool Write(uint32_t data) { 
        if (!stopped_) {
            strand_.post(boost::bind(&AsyncBuffer::Write, &buffer_, data));
        }
        return !stopped_;
    }

    void Start() {
        stopped_ = false;
        boost::asio::spawn(strand_, boost::bind(&MyClass::Run, shared_from_this(), _1));
    }

    void Stop() {
        stopped_ = true;
        strand_.post(boost::bind(&AsyncBuffer::Stop, &buffer_));
    }

    ~MyClass() { 
        std::cout << "MyClass destructed because no coroutines hold a reference to it anymore\n";
    }

  protected:
    AsyncBuffer buffer_;
    boost::asio::strand strand_;
};

int main()
{
    boost::thread_group tg;
    asio::io_service svc;

    {
        // Start the consumer:
        auto instance = boost::make_shared<MyClass>(svc); 
        instance->Start();

        // Sniper in 2 seconds :)
        boost::thread([instance]{ 
                boost::this_thread::sleep_for(boost::chrono::seconds(2));
                instance->Stop();
                }).detach();

        // Start the producer:
        auto producer_coro = [instance, &svc](asio::yield_context c) { // a bound function/function object in C++03
            asio::deadline_timer tim(svc);

            while (instance->Write(rand())) {
                tim.expires_from_now(boost::posix_time::milliseconds(200));
                tim.async_wait(c);
            }
        };

        asio::spawn(svc, producer_coro);

        // Start the service threads:
        for(size_t i=0; i < boost::thread::hardware_concurrency(); ++i)
            tg.create_thread(boost::bind(&asio::io_service::run, &svc));
    }

    // now `instance` is out of scope, it will selfdestruct after the snipe
    // completed
    boost::this_thread::sleep_for(boost::chrono::seconds(3)); // wait longer than the snipe
    std::cout << "This is the main thread _after_ MyClass self-destructed correctly\n";

    // cleanup service threads
    tg.join_all();
}
