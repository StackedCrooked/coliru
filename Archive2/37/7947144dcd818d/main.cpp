#include <tuple>
#include <memory>
#include <utility>
#include <type_traits>

template<class T, class... Args>
struct LazyConstruct {
   // accept any number of arguments, 
   // which would later be used to construct T
   template<class... U>
   LazyConstruct(U&&... u)
   : args(std::make_tuple(std::forward<U>(u)...))
   {
   }
   
   T& get() {
      if(!data) data = create(std::index_sequence_for<Args...>());
      return *data;
   }
   
   template<std::size_t... I>
   std::unique_ptr<T> create(std::index_sequence<I...>)
   {
      return std::unique_ptr<T>{new T(std::get<I>(args)...)};
   }
    
private:
   std::tuple<typename std::decay<Args>::type...> args;
   std::unique_ptr<T> data;
};

template<class T, class... Args>
LazyConstruct<T, Args...> make_LazyConstruct(Args&&... args)
{
    return LazyConstruct<T, Args...>{std::forward<Args>(args)...};
}

#include <iostream>
#include <string>

struct foo
{
    foo(std::string s1, std::string s2, int i, double d)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << s1 << ' ' << s2 << ' ' << i << ' ' << d << std::endl;
    }
};

int main() 
{
    double d = 10.1;
    auto s = std::string("Hello");
    
    auto f = make_LazyConstruct<foo>(std::move(s), "World", 42, d);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f.get();
}
