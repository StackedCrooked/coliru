#include <iostream>
#include <type_traits>
#include <tuple>

template<typename... Args>
struct windst
{
    template<class Tuple, class Callback, unsigned Index = std::tuple_size<typename std::decay<Tuple>::type>::value>
    typename std::enable_if<Index != 0>::type 
    wind(Tuple&& tuple, Callback&& callback)
    {   
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        using elementT = decltype(std::get<Index - 1>(std::forward<Tuple>(tuple)));
        
        callback.template operator()(std::get<Index - 1>(std::forward<Tuple>(tuple)));              // std::get automatically return &/&&
    
       // recursivly call wind until the end
       wind<Tuple, Callback, Index - 1>( std::forward<Tuple>(tuple), std::forward<Callback>(callback));
    }
    
    template<class Tuple, class Callback, unsigned Index = std::tuple_size<typename std::decay<Tuple>::type>::value>
    typename std::enable_if<Index == 0>::type 
    wind(Tuple&& tuple, Callback&& callback)
    {   
    }
};

// callback looks like:
template<typename... Args>
struct CallMe
{   
  // Args provide type info. No function arguments here.
  template<class Data>
  void operator()(Data &&data)
  {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};
   
int main()
{
    CallMe<short, unsigned short> callback;
    windst<short, unsigned short> w;
    
    auto tup = std::make_tuple(true, 1, 1L, 1LL);
    w.wind(tup, callback);
    
    w.wind(std::make_tuple(true, 1, 1L, 1LL), callback);
}
