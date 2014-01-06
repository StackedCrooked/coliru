#include <cstdint>
#include <iostream>
using namespace std;

static struct { } s;
struct t1 { }; 
struct t2 { };

template <typename T>
inline uintptr_t unique_id() {
    static char dummy;
    return reinterpret_cast<uintptr_t>(&dummy);
}

int main() {
  cout << unique_id<int          >() << endl;
  cout << unique_id<double       >() << endl;
  cout << unique_id<decltype(s)  >() << endl;
  cout << unique_id<size_t       >() << endl;
  cout << unique_id<unsigned long>() << endl;
  cout << unique_id<t1           >() << endl;
  cout << unique_id<t2           >() << endl;
}