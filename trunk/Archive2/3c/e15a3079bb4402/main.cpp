#include <iostream>
#include <map>
#include <set>

template<typename C>
class X
{
public:
  void foo(typename C::value_type vt)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    bar(vt);
  }
  
  void bar(typename C::key_type kt)
  {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  
private:
  template<typename T = C>
  void bar(typename T::value_type kt)
  {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
     bar(kt.first);
  }
};


int main()
{
    {
        std::map<int, long> m;
        X<decltype(m)> x;
        x.foo(decltype(m)::value_type{});
    }
    {
        std::set<int> s;
        X<decltype(s)> x;
        x.foo(decltype(s)::value_type{});
    }
}
