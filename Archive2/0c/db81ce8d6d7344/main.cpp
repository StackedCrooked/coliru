#include <iostream>
using namespace std;

template<class T> void bar(T t)
{
    foo(t);
}

struct F {};

#if 1 // Change It
    typedef int T;
#else
    typedef F T;
#endif

void foo(T)
{
    cout << "foo(T)" << endl;
}

int main() {
    T f;
    bar(f);
}

