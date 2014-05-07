
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <regex>
#include <deque>

#include <random>
#include <functional>
#include <chrono>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

#define MILION 100

class Randomizer {
    private:
    
    mt19937 engine;
    
    
    public:
    
    Randomizer()
    {
        engine.seed((unsigned int) chrono::system_clock::now().time_since_epoch().count());
    }
    
    int operator() (int min, int max)
    {
        uniform_int_distribution<int> distribution( min, max );
        return distribution(engine);
    }
};

atomic_int var;
mutex mtx;

void go_sleep(int id)
{
    Randomizer rand;
    int sleep_time = rand(1, 100);
    // std::cout << "go sleep " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

mutex chair_mtx;
mutex cut_mtx;
condition_variable chair_cv;
condition_variable cut_cv;

int current_client_id;
const int NONE = -1;

void client_thread(int id)
{
    while(true)
    {
        {
            unique_lock<mutex> lock(cut_mtx);
            cut_cv.wait(lock, [] { return current_client_id == NONE; });
            current_client_id = id;
            cut_cv.notify_all();
        }
        
        // cutting in progress...
        
        unique_lock<mutex> lock(chair_mtx);
        chair_cv.wait(lock, [] { return current_client_id == NONE; });

        // cutting finished

        {
            lock_guard<mutex> lock(mtx);
            std::cout << "client after cutting, id=" << id << std::endl;
        }
        
        go_sleep(id);
    }
}

void barber_thread()
{
    while(true)
    {  
        {
            lock_guard<mutex> lock(mtx);
            std::cout << "waiting for clients" << std::endl;
        }
        
        unique_lock<mutex> lock(chair_mtx);
        chair_cv.wait(lock, [] { return current_client_id != NONE; });
    
        {
            lock_guard<mutex> lock(mtx);
            std::cout << "CUTTING client=" << current_client_id  << std::endl;
        }
        
           // do cutting....
        
        {
            // after cutting 
            current_client_id = NONE;
            cut_cv.notify_one();
        }
        
        lock.unlock();
        chair_cv.notify_one();
    }
}

int main()
{   
    const int MAX_CLIENTS = 5;
    vector<thread> c_threads;
    c_threads.reserve(MAX_CLIENTS);
    current_client_id = NONE;
    
    thread barber(barber_thread);
    for(int i=0; i<MAX_CLIENTS; ++i)
    {
        c_threads.push_back(thread(client_thread, i));
    }
    
    for(int i=0; i<MAX_CLIENTS; ++i)
    {
        c_threads[i].join();
    }
    barber.join();
    
    return 0;
}
