#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <memory>
#include <map>
using namespace std;

struct result {
    atomic<bool> ready;
    string result;
};

map<int, result> tasks;
vector<shared_ptr<thread> > pool;

string GetUrl(string address) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return "data " + address;
}

int PushTask(function<string()> fun) {
    static int counter = 0;
    auto & res = tasks[counter++];
    
    function<void()> f = [&](){
        res.ready = false;
        res.result = fun();
        res.ready = true;
    };  
    
    pool.push_back(thread(f));
    return counter;
}

string WaitTaskResult(int taskId) {
    while(! tasks[taskId].ready ) {
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    return tasks[taskId].result;
}

void ClearTasksPool() {
    for(auto & t : pool) {
        t.join();
    }  
}

int main() {
    cout << 1;
    int id = PushTask([](){ 
        return GetUrl("Kaka Do!"); 
    });
    cout << 2;
    cout << WaitTaskResult(id);
    
    ClearTasksPool();
    return 0;
}