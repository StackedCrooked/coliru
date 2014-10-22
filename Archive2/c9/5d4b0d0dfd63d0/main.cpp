#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <sstream>

namespace bip = boost::interprocess;

template <class T> class SynchronizedQueue {

  public:
    typedef bip::allocator<T, bip::managed_shared_memory::segment_manager> allocator_type;
  private:
    bip::deque<T, allocator_type> sQueue;
    mutable bip::interprocess_mutex io_mutex_;
    mutable bip::interprocess_condition waitCondition;
  public:
    SynchronizedQueue(allocator_type alloc) : sQueue(alloc) {} 

    void push(T element) {
        boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);
        sQueue.push_back(element);
        waitCondition.notify_one();
    }
    bool empty() const {
        boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);
        return sQueue.empty();
    }
    bool pop(T &element) {
        boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);

        if (sQueue.empty()) {
            return false;
        }

        element = sQueue.front();
        sQueue.pop_front();

        return true;
    }
    unsigned int sizeOfQueue() const {
        // try to lock the mutex
        boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);
        return sQueue.size();
    }
    void waitAndPop(T &element) {
        boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);

        while (sQueue.empty()) {
            waitCondition.wait(lock);
        }

        element = sQueue.front();
        sQueue.pop();
    }

    std::string toString() const {
        bip::deque<T> copy;
        // make a copy of the class queue, to reduce time locked
        {
            boost::lock_guard<bip::interprocess_mutex> lock(io_mutex_);
            copy.insert(copy.end(), sQueue.begin(), sQueue.end());
        }

        if (copy.empty()) {
            return "Queue is empty";
        } else {
            std::stringstream os;
            int counter = 0;

            os << "Elements in the Synchronized queue are as follows:" << std::endl;
            os << "**************************************************" << std::endl;

            while (!copy.empty()) {
                T object = copy.front();
                copy.pop_front();
                os << "Element at position " << counter << " is: [" << typeid(object).name()  << "]\n";
            }
            return os.str();
        }
    }
};

struct gps_position {
    int degrees;
    int minutes;
    float seconds;

    gps_position(int d=0, int m=0, float s=0) : degrees(d), minutes(m), seconds(s) {}
};

static char const *SHARED_MEMORY_NAME = "MySharedMemory";
static char const *SHARED_QUEUE_NAME  =  "MyQueue";
typedef SynchronizedQueue<gps_position> MySynchronisedQueue;

#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>

void consumer()
{
    bip::managed_shared_memory openedSegment(bip::open_only, SHARED_MEMORY_NAME);

    MySynchronisedQueue *openedQueue = openedSegment.find<MySynchronisedQueue>(SHARED_QUEUE_NAME).first;
    gps_position position;

    while (openedQueue->pop(position)) {
        std::cout << "Degrees= " << position.degrees << " Minutes= " << position.minutes << " Seconds= " << position.seconds;
        std::cout << "\n";
    }
}

void producer() {
    bip::shared_memory_object::remove(SHARED_MEMORY_NAME);

    bip::managed_shared_memory mysegment(bip::create_only,SHARED_MEMORY_NAME, 65536);

    MySynchronisedQueue::allocator_type alloc(mysegment.get_segment_manager());
    MySynchronisedQueue *myQueue = mysegment.construct<MySynchronisedQueue>(SHARED_QUEUE_NAME)(alloc);

    for(int i = 0; i < 100; ++i)          
        myQueue->push(gps_position(i, 2, 3));

    // Wait until the queue is empty: has been processed by client(s)
    while(myQueue->sizeOfQueue() > 0) 
        continue;
}

int main() {
    producer();
    consumer();
}
