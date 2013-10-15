#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>



using namespace std;
using namespace std::chrono;

//classic message q or a light weight message q to
//share data between producers and consumers (which are different threads)

//make this template class to accept any data type
template<class T>
class threadq
{
    public:
        //push an item to thread q, this is thread safe
        void push(T data)
        {
            //guard insertion through mutex
            unique_lock<mutex> lck{m}; //unique lock uses RTTI to unlock mutex

            q.push_back(data);
            
            //notify all threads waiting for this data
            //that there is some data 
            cv.notify_all();
        }
        
        T pop()
        {
            //guard removal of data
            unique_lock<mutex> lck{m}; //unique lock ensures mutex gets unlocked automatically when the scope is out
            
            //wait until some data comes into q and this thread
            //is notified
            while(q.empty() == true) //check emptiness before popping
            {
                cv.wait(lck); //someone notified this thread
            }
            
            
            T data = q.front(); //take the first one from queue/take last one to inverse priority
            q.pop_front(); //remove the taken one
            
            return data; //return
        }
    
    private:
        list<T> q; //use linked list, as we dont want random access
        
        mutex m;
        condition_variable cv; //this is the key to notify other threads, do not use boolean flag
};


class ProducerAndConsumer
{
    public:
        
        void consume()
        {
            if(dispatch == nullptr)
            {
                //call cosumedispatch to do the q operations on this object, pass child object reference to ensure the proper overridden is called, just in case
                dispatch = new thread(&ProducerAndConsumer::consumedispatch, this);
            }
        }
        
        virtual ~ProducerAndConsumer()
        {
            //ensure dispatcher thread blocks main thread to ensure proper delivery of the produced
            if(dispatch != nullptr)
            {
                dispatch->join();
                
                delete dispatch;
                
                dispatch = nullptr;
            }
        }
    
        //real consume
        virtual void consumedispatch()
        {
            while(true)
            {
                string data = q.pop();
                
                if(data == "end$$")
                {
                    cout << endl;
                    break;
                }

                cout << data << "\t";
                
                //make thread wait for some milliseconds
                this_thread::sleep_for(milliseconds(100));
                
            }
                
        }
    
    
        //real produce
        virtual void produce(string data)
        {
            q.push(data);
        }
    
    private:
        threadq<string> q;
        thread* dispatch{nullptr}; //this is the dispatcher thread, called when consume is called
};




int main()
{
    ProducerAndConsumer pc;
    
    pc.consume(); //call this first to make the thread wait for data to arrive, :D, just checking
    
    
    //add whatever into q and the thread receives it!!
    pc.produce("Hello");
    pc.produce("from");
    pc.produce("GCC");
    pc.produce(__VERSION__);
    pc.produce("!");
    pc.produce("end$$"); //ensure proper termination of thread


    return 0;
}
