#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

boost::asio::io_service io_service;

/////////////////////////////////////////////////////////////////////////
// I love stubbing out stuff I don't want to install just to help others
enum { ZMQ_PULL };
static void* zmq_ctx_new()         { return nullptr; }
static void* zmq_socket(void*,int) { return nullptr; }
static void  zmq_bind(void*,char const*) {}
static void  zmq_recv(void*,int*data,size_t,int) 
{ 
    boost::this_thread::sleep_for(boost::chrono::milliseconds(rand()%1000));
    *data = 2;
}
// End of stubs :)
/////////////////////////////////////////////////////////////////////////

void* context  = zmq_ctx_new();
void* sock_pull = zmq_socket(context, ZMQ_PULL);

struct session : boost::enable_shared_from_this<session> {
    session(boost::asio::io_service& svc, int N) :
        timer(svc, boost::posix_time::seconds(N)) 
    {
        // Note: shared_from_this is not allowed from ctor
    }

    void start() {
        // it's critical that the completion handler is bound to a shared
        // pointer so the handler keeps the session alive:
        timer.async_wait(boost::bind(&session::handler, shared_from_this(), boost::asio::placeholders::error));
    }

    ~session() {
        std::cout << "bye (session end)\n";
    }

  private:
    void handler(const boost::system::error_code &ec) {
        std::cout << "hello, world" << "\t" << ec.message() << std::endl;
    }

    boost::asio::deadline_timer timer;
};

void run() {
    io_service.run();
}

void thread_listener() {
    int nRecv = 0;
    for(int n=0; n<4; ++n) {
        zmq_recv(sock_pull, &nRecv, sizeof(nRecv), 0);
        std::cout << nRecv << std::endl;

        boost::make_shared<session>(io_service, nRecv)->start();
    }
}

int main() {
    auto work = boost::make_shared<boost::asio::io_service::work>(io_service);

    zmq_bind(sock_pull, "tcp://*:60000");
    boost::thread tThread(thread_listener);
    boost::thread tThreadRun(run);

    tThread.join();
    work.reset();

    tThreadRun.join();
}
