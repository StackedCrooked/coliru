#include <tuple>
#include <memory>
#include <utility>
#include <functional>

template<class T>
struct LazyConstruct {
   template<class... Args>
   LazyConstruct(Args&&... args)
   : holder([this, args = std::make_tuple(std::forward<Args>(args)...)]() {
            return create(std::index_sequence_for<Args...>(), std::move(args));
       })
   {
   }
   
   T& get() {
      if(!data) data = holder();
      return *data;
   }

   template<std::size_t... I, class Tuple>
   std::unique_ptr<T> create(std::index_sequence<I...>, Tuple args)
   {
      return std::unique_ptr<T>{new T(std::get<I>(args)...)};
   }
    
private:
   std::function<std::unique_ptr<T>()> holder;
   std::unique_ptr<T> data;
};

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
    
    auto f = LazyConstruct<foo>(std::ref(s), std::string("World"), 42, d);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f.get();
}
