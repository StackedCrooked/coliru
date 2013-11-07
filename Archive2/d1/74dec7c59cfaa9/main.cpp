#include <iostream>
#include <deque>
#include <string>
#include <vector>


struct noncopyable // also non-movable
{
    noncopyable() {}
    
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};


int main()
{   
    std::deque<noncopyable> deq(1);
    deq.emplace_back();
    deq.pop_back();
    deq.pop_front();
    
    std::cout << "Everything is OK.";
}
