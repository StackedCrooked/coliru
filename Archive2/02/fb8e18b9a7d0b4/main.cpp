#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <memory>
#include <map>
#include <future>
using namespace std;

vector<shared_ptr<thread> > pool;

void PushTask(function<void()> fun) {
    pool.push_back(make_shared<thread>(fun));
}

void ClearTasksPool() {
    for(auto & t : pool) {
        t->join();
    }  
}

string GetUrl(string address) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return "data " + address;
}

int main() {
    std::packaged_task<string()> getResource([]{
        return GetUrl("bla-bla");
    }); 
    auto result = getResource.get_future();
    
    PushTask([&](){
        getResource();
    });
    
    cout << result.get() << endl ;
    
    ClearTasksPool();
    return 0;
}