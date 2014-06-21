#include <memory>
#include <cstdio>

struct test
{
    int a;
    char b[1];
};

struct deleter_using_free
{
    void operator()(void* ptr)
    {
        free(ptr);
    }
};

int main()
{
    auto a = std::shared_ptr<test>(
        (test*)malloc(sizeof(test)+10),
        deleter_using_free()
    );
    
    a->a = 10;

    printf("%d", a->a);

    return 0;
}