#include <cstdio>
#include <string>
#include <vector>

template<typename UnaryOperator, typename InputIterator>
void for_each_my(UnaryOperator&& uo, InputIterator&& begin, InputIterator&& end) {
    UnaryOperator uoo{std::forward(uo)};

    for (auto it = begin; it != end; ++it) {
        uoo(*it);   
    }
}

int main()
{
    auto v = std::vector<int> { 1, 2, 3, 4, 5 };
    for_each_my([](int i){ printf("Value: %i"); }, v.cbegin(), v.cend());
    return 0;
}