#include <iostream>
#include <vector>

template <class T, template<class...> class Iterable>
void operator<<(std::ostream&, const Iterable<T>&) {}

int main()
{
    std::cout << std::vector<int>();
}