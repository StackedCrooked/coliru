#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
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
    
    std::multimap<std::size_t, double> d;
    
    std::cout << __LINE__ << std::endl;
    
    std::multiset<std::size_t> e;
    
    std::cout << __LINE__ << std::endl;
    
    std::forward_list<std::size_t> f;
    
    std::cout << __LINE__ << std::endl;
    
    std::unordered_map<std::size_t, double> g;
    
    std::cout << __LINE__ << std::endl;
    
    std::unordered_set<std::size_t> h;
    
    std::cout << __LINE__ << std::endl;
}

/* OUTPUT FROM MSVC !!!

     allocation of size: 32
23
     allocation of size: 20
27
     allocation of size: 12
31
     allocation of size: 32
35
     allocation of size: 20
39
43
     allocation of size: 24
     allocation of size: 64
47
     allocation of size: 12
	 allocation of size: 64
51

*/
