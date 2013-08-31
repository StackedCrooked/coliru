#include <thread>
#include <unordered_map>
#include <iostream>
#include <vector>

using thread_names = std::unordered_map<std::thread::id,const char*>;

namespace {
    thread_names names;
}

void namethread(const char* name) {
    names[std::this_thread::get_id()] = name;
    std::cout << "Hello from thread named " << names.at(std::this_thread::get_id()) << '\n';
}

int main() {
    std::vector<std::thread> threads;
    for(auto&& i : {"thread1","thread2","thread3","thread4","thread5"}) {
        threads.push_back(std::thread(namethread,i));
    }
    for(auto&& thread : threads) {
        thread.join();
    }
}