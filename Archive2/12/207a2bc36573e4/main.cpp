// g++ -std=c++11 Pipeline.cpp 
#include <iostream>
#include <type_traits>
#include <vector>

// ..............................................................
// ..............................................................
std::string dup (std::string s) {
  return s + s;
}

// ..............................................................
// ..............................................................
template <typename TI, typename F>
auto operator | (const std::vector<TI> & in, F f) -> std::vector<typename std::decay<decltype(f(in[0]))>::type> {
  std::vector<typename std::decay<decltype(f(in[0]))>::type> out;
  for (auto i : in) {
    out.push_back ( f(i) );
  }
  return out;
}

// ..............................................................
// ..............................................................
int main () {
  std::cout << " hello " << std::endl;

  std::vector<std::string> vs = {"one", "two", "three", "four", "five"};

  auto res = vs | dup;
  // OK: vector<string> res = operator|<string,string> (vs, dup);

  for (auto s : res) { std::cout << s << std::endl; }

}