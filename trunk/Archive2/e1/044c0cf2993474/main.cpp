#include <iostream>
#include <string>
#include <functional>
#include <map>

class A {
public:
  static void f(const std::string &s) { std::cout << s; }
  static void f(const std::string &s, char c) { std::cout << s << ' ' << c; }
};

std::map<std::string, std::function<void(std::string const &)>> fs;

template <typename... Exact>
struct funptr
{
    template <typename R>
	constexpr auto operator()(R(*p)(Exact...)) -> decltype(p)
	{ return p; }
};

int main() {
  fs["f"] = funptr<std::string const&>()(&A::f);
  fs["f"]("hello");
}
