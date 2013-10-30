#include <iostream>
#include <functional>

//////////////////////////////////////////

template<typename Object, typename R, typename ...Args>
struct smart_fun
{
    Object & obj;
    R (Object::*fun)(Args...);
    
    R operator()(Args... args)
    {
        return (obj.*fun)(args...);
    }
};


template<typename C, typename R, typename ...Args>
auto smart_bind(C & c, R (C::*fun)(Args...)) -> smart_fun<C, R, Args...>
{
    return smart_fun<C, R, Args...>{c, fun};
}
//////////////////////////////////////////

struct Foo
{
  int bar(int i,float f,bool b) { return b ? i : f; }
};


int main() {
  Foo object;
  std::function<int(int,float,bool)> fun = smart_bind(object, &Foo::bar);
  
  std::cout << fun(100, 150.32, true) << std::endl;
  std::cout << fun(100, 150.32, false) << std::endl;
}