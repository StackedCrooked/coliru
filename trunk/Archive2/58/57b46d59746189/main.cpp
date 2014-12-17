#include <iostream>
#include <string>
#include <functional>

using namespace std;

static const bool LOG_DEBUG = false;


int int_generator() {
    cout << "I was called!" << endl;
    return 42;
}

template <bool dbg = LOG_DEBUG, std::enable_if_t<dbg>* = nullptr>
inline void dbg_call(std::function<void(void)> f) { f(); }
template <bool dbg = LOG_DEBUG, std::enable_if_t<!dbg>* = nullptr>
inline void dbg_call(std::function<void(void)>) {}

int main(void) {
  printf("%d\n", int_generator());
  dbg_call([] { printf("%d\n", int_generator()); });
  return 0;
}