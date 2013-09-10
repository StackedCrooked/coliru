#include <iostream>
#include <tuple>

using namespace std;

struct test {
  explicit test() { cout << "constructor" << endl; }
  explicit test(test const&) = delete;
  explicit test(test &&) { cout << "move constructor" << endl; }
  test & operator =(test const&) { cout << "copy assignment" << endl; return *this; }
  test & operator =(test &&) { cout << "move assignment" << endl; return *this; }
  ~test() { cout << "destructor" << endl; }
};

int main() {
 make_tuple(test());
  return 0;
}
