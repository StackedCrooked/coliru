#include <vector>

template <typename... Args>
    void foo(Args... args)
{
    static_assert(sizeof...(Args) == 7, "unexpected number of arguments");
    std::vector<int> v { args... };
}


int main(int argc, char* argv[])
{
    foo(1,2,3,4,5,6,7);
    foo(1,2,3,4,5,6,7,8); // oops
}

