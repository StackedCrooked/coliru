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

int main()
{
    packaged_task<string()> tsk ([](){
        return GetUrl("bla-bla-bla");
    });
    
    auto result = tsk.get_future();
    auto t = make_shared<thread>(move(tsk));
    pool.push_back( t );
    
    cout << result.get() << endl;
    
    CleanPool();
    return 0;
}
