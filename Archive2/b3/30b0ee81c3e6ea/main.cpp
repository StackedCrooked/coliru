#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

using namespace std;

int product = 0;
boost::mutex mutex;
boost::condition_variable cv;
boost::condition_variable pv;
bool done = false;

void consumer(){
    boost::mutex::scoped_lock lock(mutex);
    while(done==false){
        //cout << "start c" << endl
        cv.wait(lock);
        //cout << "wakeup c" << endl;
        if (done==false)
        {
            cout << product << endl;
            //cout << "notify c" << endl;
            pv.notify_one();
        }
        //cout << "end c" << endl;
    }
}

void producer(){
    boost::mutex::scoped_lock lock(mutex);
    for(int i=0;i<10;i++){
        //cout << "start p" << endl;
        // boost::this_thread::sleep(boost::posix_time::microseconds(50000));
        ++product;
        //cout << "notify p" << endl;
        cv.notify_one();
        pv.wait(lock);
        //cout << "wakeup p" << endl;
    }
    //cout << "end p" << endl;
    cv.notify_one();
    done = true;
}

int main()
{
    int t = 1000;
    while(t--){
        /*
        This is not perfect, and is prone to a subtle issue called the lost wakeup (for example, producer calls notify() 
        on the condition, but client hasn't really called wait() yet, then both will wait() indefinitely.) 
        */
        boost::thread consumerThread(&consumer);    
        boost::thread producerThread(&producer);

        producerThread.join();
        consumerThread.join();
        done =false;
        //cout << "process end" << endl;
    }
    cout << "done" << endl;
    getchar();
    return 0;
}
