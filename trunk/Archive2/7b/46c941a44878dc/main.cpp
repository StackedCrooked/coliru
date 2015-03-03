#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>
#include <atomic>

using namespace std;

vector<shared_ptr<thread> > pool;

struct task {
    atomic<bool> ready;
    string result;
};

map<int, task> tasks;

int PushTask(function<string()> f){
    int id = rand();

    auto action = [=]() {
        auto & t = tasks[id];
        t.ready = false;
        t.result = f();
        t.ready = true;
    };
    auto executor = make_shared<thread>(action);
    pool.push_back(executor);
    
    return id;
}

void CleanPool() {
    for(auto t : pool) {
        t->join();
    }
}

string WaitTask(int id) {
    auto & t = tasks[id];
    while(!t.ready) {
        this_thread::sleep_for(chrono::milliseconds(1)); 
    }
    return t.result;
}

string GetUrl(string url) {
    string result = "Data " + url;
    this_thread::sleep_for(chrono::milliseconds(100));
    return result;
}

int main()
{
    int id = PushTask([](){
        return GetUrl("bla-bla-bla");
    });
    
    int id2 = PushTask([](){
        return GetUrl("Kitty");
    });
    
    int id3 = PushTask([](){
        return GetUrl("YouTube");
    });
    
    cout << WaitTask(id) << endl
    <<  WaitTask(id2) << endl
    <<  WaitTask(id3) << endl;
    
    CleanPool();
    return 0;
}
