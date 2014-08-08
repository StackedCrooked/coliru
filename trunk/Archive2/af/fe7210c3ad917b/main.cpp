#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <queue>
#include <random>

auto t0 = std::chrono::high_resolution_clock::now();
std::mutex cout_mutex;
void log(std::string s) {
    std::unique_lock<std::mutex> lck(cout_mutex);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "@" << ms << " ms: " << s << std::endl;
}

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

std::default_random_engine generator( std::time(0) );
size_t max_duration = 500;
std::uniform_int_distribution<size_t> distribution(0,max_duration);
std::chrono::milliseconds some_time() {
    auto unit = std::chrono::milliseconds(1);
    size_t duration = distribution(generator);
    return unit * duration;
}

typedef size_t Message;

Message produce() {
    std::this_thread::sleep_for( some_time() );
    return distribution(generator);
}

void consume(Message message) {
    std::this_thread::sleep_for( some_time()*2 );
}

size_t nMessages = 0;
size_t maxNMessages = 13;
std::queue<Message> mqueue; //the queue of messages

void producer()
{
    while(true) {
        log( "Producing..." );
        Message message = produce(); //... calculate the message ...
        std::unique_lock<std::mutex> lck {mtx};  //protect operations on mqueue
        mqueue.push(message);
        ++nMessages;
        cv.notify_one();
        log( "Produced. Size = " + std::to_string( mqueue.size() ) );
        if( nMessages == maxNMessages ) break;
    } //release lock (at end of scope)
}

void consumer()
{
    while(true) {
        std::unique_lock<std::mutex> lck{mtx};  //acquire mutex
        cv.wait(lck, []{return !mqueue.empty();}); //release lck and wait;
                            //re-acquire lck upon wakeup
        auto message = mqueue.front();  //get the message
        mqueue.pop();
        if( nMessages == maxNMessages ) break;
        log( "About to consume. Size = " + std::to_string( mqueue.size() ) );
        lck.unlock(); //release lck
        consume(message); // process message ...
        log( "Consumed." );
    }
}

int main ()
{
    std::thread thread1(producer);
    std::thread thread2(consumer);
    
    thread1.join();
    thread2.join();
    
    return EXIT_SUCCESS;
}