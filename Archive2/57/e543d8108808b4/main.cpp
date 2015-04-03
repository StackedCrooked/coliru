#include <vector>

namespace my_ns {
 
 template<class T>
 auto begin(T & t) -> decltype(t.begin()) { return t.begin(); }
    
 template<class T>
 auto foo(T&& f) -> decltype(begin(f)) { return begin(f); }
}

int main()
{
   std::vector<int> a;
   my_ns::foo(a);
}