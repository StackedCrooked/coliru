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
    packaged_task<string()> getResource([]{
        return GetUrl("bla-bla");
    });   
    auto result = getResource.get_future();
    
    packaged_task<string()> getResource2( bind(GetUrl, "bla-bla"));   
    auto result2 = getResource2.get_future();

    pool.push_back(make_shared<thread>(move(getResource)));
    pool.push_back(make_shared<thread>(move(getResource2)));

    cout << result.get() << endl 
    << result2.get() << endl;
    
    ClearTasksPool();
    return 0;
}