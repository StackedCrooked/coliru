#include <iostream>
#include <vector>
#include <stack>

template<typename T, template <typename, typename> class Cont>
std::ostream& operator<<(std::ostream& os, Cont<T, std::allocator<T>> cont)
{
    for (const auto& el : cont)
        std::cout << el << "\n";
    return os;
}


int main()
{
    std::vector<int> v{1, 2, 3};
    std::stack<int> s;
    s.push(1); s.push(2); s.push(3);
    std::cout << v << "\n"
              << s;
}
