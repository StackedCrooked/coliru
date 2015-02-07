#include <iostream>
#include <vector>

template <class T, template<class...> class Iterable>
void operator<<(std::ostream& s,const Iterable<T>& iter) {}

int main()
{
    std::cout << std::vector<int>();
}