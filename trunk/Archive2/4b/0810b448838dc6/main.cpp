#include <iostream>
using namespace std;

template <class X>
struct s1
{
    template <class Y>
    struct s2
    {
        Y y;
    };
    X x;
};
template <class X, class Y>
void test1(Y y)
{
    typename s1<X>::template s2<Y> temp; // G++/Clang protestano qui
    temp.y = y;
}


int main(int argc, char *argv[])
{
   test1<double, int>(2);
}