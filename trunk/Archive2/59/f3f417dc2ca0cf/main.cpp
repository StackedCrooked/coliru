#include <iostream>
#include <string>
using namespace std;

template <class T>
struct Foo
{
    template <class S>
    void print(const T& t, const S& s);
};

template <>
struct Foo<int>
{
    template <class S>
    void print(const int& t, const S& s);
};

template <class S>
void Foo<int>::print(const int& t, const S& s)
{
    cout << s << " " << t << endl;
}
int main(void)
{
    string str("hello");
    Foo<int> foo;
    foo.print(7, str);
    return 0;
}