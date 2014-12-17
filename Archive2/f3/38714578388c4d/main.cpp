#include <iostream>
#include <string>

#include <boost/variant.hpp>

using namespace std;

using FuncInt = std::function<int()>;
using VaryInt = boost::variant<int, FuncInt>;

struct VaryIntVisitor : public boost::static_visitor<int> {
  int operator()(int i) const { return i; }
  int operator()(FuncInt f) const { return f(); }
};

template <bool>
struct Log;

template <>
struct Log<true> {
  static void print_int(VaryInt f) {
    cout << boost::apply_visitor(VaryIntVisitor(), f) << endl;
  };
};

template <>
struct Log<false> {
  static void print_int(VaryInt) {};
};

#ifdef LOG_DEBUG
using LOG = Log<true>;
#else
using LOG = Log<false>;
#endif

int main(void) {
  LOG::print_int([] { int i = 0; /* do expensive computation */ i = 42; return i; });
  LOG::print_int(52);
  return 0;
};
