#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <thread>
#include <chrono>
 
void f(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "thread " << n << " ended" << '\n';
}
 
std::vector<std::thread> move_test()
{
    std::vector<std::thread> v;
    v.emplace_back(f, 1);
    v.emplace_back(f, 2);
    v.emplace_back(f, 3);
        
    // auto t = std::thread(f,4);
    // v.emplace_back(t);    
    return v;
}

int main() 
{
    auto v = move_test(); 
    auto v1 = std::move(v);
    v = std::move(v1);
    std::list<std::thread> l;
    
    // copy() would not compile, because std::thread is noncopyable
   
    std::move(v.begin(), v.end(), std::back_inserter(l)); 
    for (auto& t : l) t.join();
}