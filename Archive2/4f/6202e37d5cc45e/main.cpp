#include <iostream>

#include <sstream>
#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <random>

using namespace std;

mutex cout_mutex;
mutex processed_mutex;

std::condition_variable wait_for_other_tasks;
bool t1_processed = false;
bool t2_processed = false;

const int t1_max= 40;
const int t2_max = 60;
int t1_counter = 0;
int t2_counter = 0;
const string t1_name = "T1";
const string t2_name = "T2";

void printToCout(const string str)
{
    // w celu urealnienie przykładu
    // "zezwolenie" na uruchomienie innego wątku
    this_thread::yield();
    this_thread::yield();
    
    lock_guard<mutex> lock(cout_mutex);
    cout << str << endl;
}

void incrementer(bool &processed, const int max, int counter, const string threadName)
{
    stringstream ss;
    
    for (int i = 0; i < max; ++i)
    {
        ++counter;
        ss << threadName; ss << '\t'; ss << counter;
        
        printToCout(ss.str());
        ss.clear(); ss.str("");
    }
    
    {
        lock_guard<mutex> processed_lock(processed_mutex);
        processed = true;
    }
    
    wait_for_other_tasks.notify_all();
}

void external_event()
{
    random_device rd;
    default_random_engine e1(rd());
    uniform_int_distribution<int> uniform_dist(1, 100);
    
    int event;
    stringstream ss;
    
    for (int i = 0; i < 100; ++i)
    {        
        event = uniform_dist(e1);
        ss << "Event";  ss << '\t' << "#"; ss << event;
        
        printToCout(ss.str());
        
        ss.clear(); ss.str("");
    }
    
    // czekamy na t1 i t2...
    {
        unique_lock<mutex> processed_lock(processed_mutex);
        wait_for_other_tasks.wait(processed_lock, []{return t1_processed && t2_processed;});
    }
}

int main()
{   
    cout << "int main() START" << endl;
    
    thread externalEvent(external_event);
    
    thread t1(incrementer, ref(t1_processed), t1_max, t1_counter, t1_name);
    thread t2(incrementer, ref(t2_processed), t2_max, t2_counter, t2_name);
    
    // działąją sobie niezależnie od mainowego wątku
    t1.detach();
    t2.detach();
    
    // mainowy wątek czeka aż externalEvent zakończy działanie
    // a tak na prawde dopóki t1 i t2 nie zakończą processingu
    externalEvent.join();
    
    cout << "int main() END" << endl;
    
    return 0;
}
