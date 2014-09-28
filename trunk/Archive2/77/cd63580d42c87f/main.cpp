#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <vector>
#include <list>
#include <map>
#include <set>

void* operator new(size_t n)
{
    std::cout << "\t allocation of size: " << n << std::endl;
    return malloc(n);
}
void operator delete(void* ptr)
{
    free(ptr);
}
int main()
{
    std::map<std::size_t, double> a;

    std::cout << __LINE__ << std::endl;
    
    std::set<std::size_t> b;
    
    std::cout << __LINE__ << std::endl;
    
    std::list<std::size_t> c;
    
    std::cout << __LINE__ << std::endl;
    
    std::vector<std::size_t> d;
    
    std::cout << __LINE__ << std::endl;
    
    std::multimap<std::size_t, double> e;
    
    std::cout << __LINE__ << std::endl;
    
    std::multiset<std::size_t> f;
    
    std::cout << __LINE__ << std::endl;
    
    std::forward_list<std::size_t> g;
    
    std::cout << __LINE__ << std::endl;
    
    std::unordered_map<std::size_t, double> h;
    
    std::cout << __LINE__ << std::endl;
    
    std::unordered_set<std::size_t> i;
    
    std::cout << __LINE__ << std::endl;
}

/* OUTPUT FROM MSVC !!!

     allocation of size: 32
24
     allocation of size: 20
28
     allocation of size: 12
32
36
     allocation of size: 32
40
     allocation of size: 20
44
48
     allocation of size: 24
     allocation of size: 64
52
     allocation of size: 12
	 allocation of size: 64
56

*/
