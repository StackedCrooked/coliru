#include <vector>

namespace my_ns {
 
 struct begin_t
 {
     template<typename T>
     auto operator () (T& t) -> decltype(t.begin()) { return t.begin(); }
 } begin;
     
 template<class T>
 auto foo(T&& f) -> decltype(begin(f)) { return begin(f); }
}

int main()
{
   std::vector<int> a;
   my_ns::foo(a);
}