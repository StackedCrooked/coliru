#include <thread>

struct Bar {};

template<class T>
void foo()
{
  // do something
}

int main()
{
    std::thread t{foo<Bar>}; // Not compiling neither.
    t.join();
}
