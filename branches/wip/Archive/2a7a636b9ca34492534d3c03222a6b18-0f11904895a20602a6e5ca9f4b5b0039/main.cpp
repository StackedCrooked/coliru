#include <cassert> 
#include <iostream>

struct no_max_clamp_type {} no_max_clamp;
struct no_min_clamp_type {} no_min_clamp;
template<class L, class T, class R>
T clamp(L l, T t, R r) {return ((l<t)==false)?T(l):t<r?t:T(r);}
template<class L, class T>
T clamp(L l, T t, no_max_clamp_type) {return ((l<t)==false)?T(l):t;}
template<class T, class R>
T clamp(no_min_clamp_type, T t, R r) {return (t<r)?t:T(r);}


#define ASSERT(statement) std::cout << #statement << std::flush; assert(statement); std::cout << " => PASS " << std::endl;
int main()
{   
    ASSERT(clamp(2,1,4)==2);
    ASSERT(clamp(2,2,4)==2);
    ASSERT(clamp(2,3,4)==3);
    ASSERT(clamp(2,4,4)==4);
    ASSERT(clamp(2,5,4)==4);
    
    ASSERT(clamp("B",std::string("A"),"D")=="B");
    ASSERT(clamp("B",std::string("B"),"D")=="B");
    ASSERT(clamp("B",std::string("C"),"D")=="C");
    ASSERT(clamp("B",std::string("D"),"D")=="D");
    ASSERT(clamp("B",std::string("E"),"D")=="D");
}




