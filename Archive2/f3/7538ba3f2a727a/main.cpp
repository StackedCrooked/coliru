#include <memory>
#include <cstdio>

struct foo
{
    foo()
    {
        puts(__FUNCTION__);
    }

    ~foo()
    {
        puts(__FUNCTION__);
    }
};

void useRawFooPointer()
{
    puts(__FUNCTION__);
    auto ptr = new foo();

    // TON OF CODE
    return; // or throw
    // TON OF CODE

    delete ptr;
}

void useUniqueFooPointer()
{
    puts(__FUNCTION__);
    std::unique_ptr<foo> ptr(new foo());

    // TON OF CODE
    return; // or throw
    // TON OF CODE
}

int main(int, char**)
{
    useRawFooPointer();
    puts("");
    useUniqueFooPointer();
}
