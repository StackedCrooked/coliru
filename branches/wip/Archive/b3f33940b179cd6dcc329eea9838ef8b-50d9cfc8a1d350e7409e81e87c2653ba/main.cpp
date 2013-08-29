#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
 
#include <iostream>
 
template<typename T>
struct UniquePtrDefaultDeleter {
    void operator()(T *p) {
		delete p;
	}
};
 
class ThreadPool {
public:
        ThreadPool();
        ThreadPool(std::size_t);
        void init(std::size_t);
 
        template<class F>
        void enqueue(F f);
        ~ThreadPool();
private:
 
        /* The actual io_service we are wrapping */
        boost::asio::io_service service_;
        typedef boost::interprocess::unique_ptr<boost::asio::io_service::work, UniquePtrDefaultDeleter<boost::asio::io_service::work> > asio_worker;
        asio_worker working_;
        bool is_initialized_;
        /* Need to keep track of threads so we can join them */
        std::vector<boost::interprocess::unique_ptr<boost::thread, UniquePtrDefaultDeleter<boost::thread> > > workers_;
 
};
 
ThreadPool::ThreadPool() :
                service_(),
                working_(new asio_worker::element_type(service_)),
                is_initialized_(false) {
}
 
ThreadPool::ThreadPool(size_t threads) :
                service_(),
                working_(new asio_worker::element_type(service_)),
                is_initialized_(false) {
        init(threads);
}
 
void ThreadPool::init(std::size_t threads) {
        if(!is_initialized_) {
                for ( std::size_t i = 0; i < threads; ++i ) {
                        workers_.push_back(
                                        boost::interprocess::unique_ptr<boost::thread,UniquePtrDefaultDeleter<boost::thread> >(
                                                        new boost::thread([i]{
                                                                service_.run();
                                                        })
                                        )
                        );
                }
                is_initialized_ = true;
        }
}
 
template<class F>
void ThreadPool::enqueue(F f) {
        service_.post(f);
}
 
ThreadPool::~ThreadPool() {
        //service.stop();
        //for ( std::size_t i = 0; i < workers.size(); ++i )
        //   workers[i]->join();
        working_.reset();
        service_.run();
}
 
int main(int argc, char** argv) {
    ThreadPool tp = new ThreadPool(2);
    for(int i = 0; i <2 ; ++i) {
        tp->enqueue([i]{
        std::cout << "hello " << i << std::endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        std::cout << "world " << i << std::endl;           
            })
    }
}