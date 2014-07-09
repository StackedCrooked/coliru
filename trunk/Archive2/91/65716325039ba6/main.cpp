#include <memory>
#include <cstdio>

struct test
{
    int a;
    char b[1];
};


int main()
{
    auto a = std::shared_ptr<test[]>(new test[10]);
    
    a[0].a = 10;

    printf("%d", a[0].a);

    return 0;
}