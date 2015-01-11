#include <iostream>
using namespace std;

template <typename T>
class bar
{
 public:
 bar(){cout << "bar" <<"\n";}
};

template <typename T, typename ctor = bar<T>>
class foo
{
 T i;
public:
 explicit foo(const ctor& c = ctor());
private:
 ctor mctor;


};

template <typename T, typename ctor>
foo<T,ctor>::foo(const ctor& c):mctor(c)
{
 cout << "foo" <<"\n";
}

int main()
{
 foo<int> f;
 return 0;
}