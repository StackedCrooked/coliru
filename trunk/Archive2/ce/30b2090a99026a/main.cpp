#include <tuple>

template<typename ... Args>
struct foo
{
    typedef std::tuple<Args ..., int> myTuple;
};

int main() {}
