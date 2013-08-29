#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/noncopyable.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
 
#include <iostream>
 
class ThreadPool;
 
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
//	const uint8_t &getWorkersCount() const;
	template<class F>
	void enqueue(F f);
	~ThreadPool();
private:

	/* The actual io_service we are wrapping */
//	boost::atomic<uint8_t> workers_count_;
	boost::asio::io_service service_;
	typedef boost::interprocess::unique_ptr<boost::asio::io_service::work, UniquePtrDefaultDeleter<boost::asio::io_service::work> > asio_worker;
	asio_worker working_;
	bool is_initialized_;
	/* Need to keep track of threads so we can join them */
	boost::ptr_vector<boost::thread> workers_;

};

ThreadPool::ThreadPool() :
		service_(),
		working_(new asio_worker::element_type(service_)),
		is_initialized_(false)//,		workers_count_(0)
		{
}

/**
 * \brief	Constructor just launches some amount of workers
 */
ThreadPool::ThreadPool(size_t threads) :
		service_(),
		working_(new asio_worker::element_type(service_)),
		is_initialized_(false) {
	init(threads);
}

void ThreadPool::init(std::size_t threads) {
	if(!is_initialized_) {
		for ( std::size_t i = 0; i < threads; ++i ) {
			workers_.push_back(new boost::thread(service_.run()));
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
 
struct WorkerFixture : boost::noncopyable {
private:
    WorkerFixture();

	static boost::atomic<uint16_t> counter_;
public:
    static void run() {
        uint16_t runner_id = ++counter_;
        for (int cnt =0; cnt < 3 ; ++cnt) {
            std::cout << "hello from " <<runner_id << " "<< cnt<< std::endl;
        }
    }
};

boost::atomic<uint16_t> WorkerFixture::counter_(0);
 
int main(int argc, char** argv) {
    ThreadPool* tp = new ThreadPool(2);
    for(int i = 0; i <2 ; ++i) {
        tp->enqueue(&WorkerFixture::run);
    }
}

