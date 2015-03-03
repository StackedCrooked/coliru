#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>
#include <atomic>
#include <future>

using namespace std;

vector<shared_ptr<thread> > pool;

void CleanPool() {
    for(auto t : pool) {
        t->join();
    }
}

string GetUrl(string url) {
    string result = "Data " + url;
    this_thread::sleep_for(chrono::milliseconds(100));
    return result;
}

template<typename T>
void PushTask(T && tsk) {
    auto t = make_shared<thread>( move(tsk) );
    pool.push_back( t );
}

int main()
{
    packaged_task<string()> tsk ([](){
        return GetUrl("bla-bla-bla");
    });
    
    auto result = tsk.get_future();
    PushTask(tsk);
    
    cout << result.get() << endl;
    
    CleanPool();
    return 0;
}
