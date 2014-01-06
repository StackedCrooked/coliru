#include <cstdint>
#include <iostream>
using namespace std;

static struct { } s;
struct t1 { }; 
struct t2 { };

template <typename T>
class unique_id {
  static char dummy;
public:
  const static uintptr_t value = reinterpret_cast<uintptr_t>(&dummy);
};

template <typename T>
char unique_id<T>::dummy;

template <typename T>
const uintptr_t unique_id<T>::value;

int main() {
  cout << unique_id<int          >::value << endl;
  cout << unique_id<double       >::value << endl;
  cout << unique_id<decltype(s)  >::value << endl;
  cout << unique_id<size_t       >::value << endl;
  cout << unique_id<unsigned long>::value << endl;
  cout << unique_id<t1           >::value << endl;
  cout << unique_id<t2           >::value << endl;
}