#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>

 
void worker_thread(std::condition_variable *cv, std::mutex *m, std::string *data)
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(*m);
    cv->wait(lk);
 
    //after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    *data += " after processing";
 
    // Send data back to main()
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid
    // that the waiting thread gets blocked again.
    lk.unlock();
    cv->notify_one();
}
 
int main()
{
    std::condition_variable cv;
    std::mutex m;
    std::string data;
    std::thread worker(worker_thread, &cv, &m, &data);
 
    data = "mydata";
    // send data to the worker thread

    std::cout << "main() signals data ready for processing\n";

    //wait 2s
    //std::chrono::milliseconds dura( 2000 );
    //std::this_thread::sleep_for( dura );
    
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk);
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}