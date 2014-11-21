#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

using namespace boost;

struct MySessionThing : enable_shared_from_this<MySessionThing> {

    MySessionThing(asio::io_service& svc) 
        : svc_(svc), tim(svc)
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }

    ~MySessionThing() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

    void start() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        tim.expires_from_now(posix_time::seconds(2));
        tim.async_wait(bind(&MySessionThing::callback, shared_from_this(), asio::placeholders::error));

        thread(bind(&MySessionThing::teardown, shared_from_this())).detach();
    }

  private:
    void callback(system::error_code ec) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        if (ec != asio::error::operation_aborted) {
            std::cout << " - continuing wait - keeps the object alive (as it should)\n";
            tim.expires_from_now(posix_time::seconds(2));
            tim.async_wait(bind(&MySessionThing::callback, shared_from_this(), asio::placeholders::error));
        }

        std::cout << " - " << ec.message() << ": exiting handler - also implicitly releases the lock on MySessionThing\n";
        // only if the new async_wait has *not* been posted, this will cause the destructor to run
    }

    void teardown() {
        this_thread::sleep_for(chrono::seconds(3));
        svc_.post([=] { tim.cancel(); }); // the tim object itself is not threadsafe
    }
    
    asio::io_service& svc_;
    asio::deadline_timer tim;
};

int main()
{
    asio::io_service svc;
    { // inner scope
        auto session = make_shared<MySessionThing>(svc);
        session->start();
    } // release our lock on the session

    svc.run();
}
