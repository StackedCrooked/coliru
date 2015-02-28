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

int PushTask(function<string()> fun) {
    static int counter = 0;
    auto & res = tasks[++counter];
    
    
    function<void()> f = [&](){
        res.ready = false;
        res.result = fun();
        res.ready = true;
    };  
    pool.push_back(make_shared<thread>(f));

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
        t->join();
    }  
}

string GetUrl(string address) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return "data " + address;
}

int main() {
    cout << 1 << endl;
    int id = PushTask([](){ 
        return GetUrl("Kaka Do!"); 
    });
    
    int id2 = PushTask([](){ 
        return GetUrl("Haloha!"); 
    });
    
    int id3 = PushTask([](){ 
        return GetUrl("Bla-bla-bla!"); 
    });
    cout << 2 << endl;
    
    cout << WaitTaskResult(id) << endl 
    << WaitTaskResult(id2) << endl 
    << WaitTaskResult(id3) << endl;
    
    ClearTasksPool();
    return 0;
}