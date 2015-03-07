#include <iostream>
#include <thread>
#include <vector>

struct guarded_thread : public std::thread {
    using std::thread::thread;
    
    guarded_thread(const guarded_thread&) = delete ;
    guarded_thread(guarded_thread&&) = default ;
    
    ~guarded_thread() { if (joinable()) join(); }
};

void f() { std::cerr << "f();" << std::endl; }

int main()
{
    std::vector<guarded_thread> t ;
    t.emplace_back(f);
}