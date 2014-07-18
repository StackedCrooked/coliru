#include <iostream>
#include <string>
#include <utility>

struct A {
  std::string abc = "abc";
  std::string& get() & {
    std::cout << "get() &" << std::endl;
    return abc;
  }
  std::string get() && {
    std::cout << "get() &&" << std::endl;
    return std::move(abc);
  }
  std::string const& get() const & {
    std::cout << "get() const &" << std::endl;
    return abc;
  }
  std::string get() const && {
    std::cout << "get() const &&" << std::endl;
    return abc;
  }
};

int main()
{
  A a1;
  a1.get();
  const A a2{};
  a2.get();
  A().get();
  const A a3{};
  std::move(a3).get();
}
