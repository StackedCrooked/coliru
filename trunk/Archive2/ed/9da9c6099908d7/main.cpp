#include <cstdio>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class A
{
public:
    A(void)
    {
    }
    A(const A &)
    {
    }
    A &operator=(const A &)
    {
        return *this;
    }
    A(const unordered_map<int, A> &)
    {
    }
};

int main(void)
{
    A a;
    unordered_map<wstring, A> m;
    printf("Hello, World!");
    return 0;
}