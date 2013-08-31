#include <utility>
#include <type_traits>


#define RETURNS(X) ->decltype(X) { return (X); } // C++11 lacks non-lambda return value deduction
#define OVERLOAD_SET(F) struct {\
  template<typename... Args>\
  auto operator()(Args&&...args)const\
    RETURNS( F( std::forward<Args>(args)... ) )\
  template<typename T,typename=typename std::enable_if<\
    std::is_same< decltype(static_cast<T>( F )), T >::value\
  >::type>\
  operator T() const { return F; }\
}

#include <iostream>

static OVERLOAD_SET(std::endl) endl_functor;

template<typename X>
void print(X&& x) {
    std::cout << x;
}
int main()
{
    print("hello");
    print(endl_functor);
    print("world");
    print(endl_functor);
}