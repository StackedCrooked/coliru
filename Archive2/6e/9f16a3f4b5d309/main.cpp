#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // Wait until main() sends data
    std::cout << "I Wanna lock the m " << std::endl;
    std::unique_lock<std::mutex> lk(m);
    std::cout << "m has been locked " << lk.owns_lock() << std::endl;
    cv.wait(lk, []{std::cout << lk.owns_lock() << ready << std::endl; return ready;});
    std::cout << "I also passed the wait" << std::endl;
 
    //after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid
    // that the waiting thread gets blocked again.
    lk.unlock();
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    data = "Example data";
    // send data to the worker thread
    {  
        std::cout << "Do you think I'm the first one!" << std::endl;
        std::unique_lock<std::mutex> lk(m);
        std::cout << "The lock status: " << lk.owns_lock() << std::endl;
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}