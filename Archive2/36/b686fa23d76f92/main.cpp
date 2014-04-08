template<typename T>
struct value_setter
{
  value_setter(const T& t):t(t){}
  
  template<typename Q>
  void operator()(Q& q){q=t;}
  
  const T& t;
};

template<typename T>
value_setter<T> set_value(const T& t){return value_setter<T>(t);}

// testing

#include <iostream>

int main()
{
  int x=0;
  set_value(10)(x);
  std::cout<<x<<"\n";
  set_value('a')(x);
  std::cout<<x<<"\n";
}