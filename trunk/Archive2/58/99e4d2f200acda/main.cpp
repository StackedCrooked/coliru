#include <memory>
#include <cstdio>

struct test
{
    int a;
    char b[1];
};

int main()
{
    auto a = std::shared_ptr<test>(
        (test*)malloc(sizeof(test)+10),
        [](test* ptr) { free(ptr); }
    );
    
    a->a = 10;

    printf("%d", a->a);

    return 0;
}