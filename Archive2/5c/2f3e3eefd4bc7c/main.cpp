#include <iostream>
#include <string>

//#define TEMPLATED //comment this eventually

struct my_str {
  std::string s;

  my_str(): s("") { std::cout << "my_str default ctor" << std::endl; }
  my_str(const std::string & str): s(str) { std::cout << "my_str parameter ctor" << std::endl; }
  my_str(const my_str & o): s(o.s) { std::cout << "my_str copy ctor" << std::endl; }
  my_str(my_str && o): s(std::move(o.s)) { std::cout << "my_str move ctor" << std::endl; }
};
std::ostream & operator<<(std::ostream & o, const my_str & i) {
  return (o << i.s);
}

#ifdef TEMPLATED
template <typename T>
    my_str build(T && s) {
      return my_str(std::forward<T>(s));
    }
#else
    my_str build(my_str s) {
      return my_str(std::move(s)); 
    }
#endif

int main() {
  my_str s("hello");
  std::cout << "s: " << s << std::endl;
  build(s);
  std::cout << "s: " << s << std::endl;
  build(std::move(s));
  std::cout << "s: " << s << std::endl;  
  return 0;
}