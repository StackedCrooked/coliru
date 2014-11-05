#include <iostream>
using namespace std;

struct Echo{
  Echo(){std::cout << "construct\n";}
};

template<typename T>
struct Test{
  static Echo i;
};

template<typename T>
Echo Test<T>::i;

Test<int> t1;

int main()
{
    t1.i;
}
