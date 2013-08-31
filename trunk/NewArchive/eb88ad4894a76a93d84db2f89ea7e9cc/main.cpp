#include <iostream>
#include <utility>
#include <type_traits>

struct foo
{
    int operator()() {
        return 0;
    }
};

template<typename T>
void check(T)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    typedef std::result_of<foo()>::type result_type;
    check(result_type{});
}