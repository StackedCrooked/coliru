#include <map>
#include <functional>
#include <memory>
#include <iostream>

struct my_allocator : std::allocator<int> {};

typedef std::map<int, int,   std::less<int>, my_allocator> Inner;
typedef std::map<int, Inner, std::less<int>, my_allocator> Outer;

int main()
{
    my_allocator alloc;
    Outer o(std::less<int>(), alloc);
    
    o[0] = Inner(std::less<int>(), alloc);
    o[0][0] = 10;
    o[0][1] = 20;
    
    o[1] = Inner(std::less<int>(), alloc);
    o[1][0] = 30;
    o[1][1] = 40;
    
    for(Outer::const_iterator oiter = o.begin(); oiter != o.end(); ++oiter) {
        for(Inner::const_iterator iiter = oiter->second.begin(); iiter != oiter->second.end(); ++iiter) {
            std::cout << oiter->first << ": (" << iiter->first << "," << iiter->second << ")\n";
        }
    }
}
