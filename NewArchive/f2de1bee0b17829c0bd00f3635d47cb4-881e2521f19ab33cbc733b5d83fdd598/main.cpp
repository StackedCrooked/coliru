#include <stdio.h>

template<typename T, int N>
class A
{
public:
    void func();
};

template<int N>
class A<int,N>
{
public:
  void func();
};

template<int N>
void A<int,N>::func()
{
    printf("%d\n",3);
}
int main()
{
    A<int, 3> a;
    a.func();
    return 0;
}
