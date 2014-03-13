#include <iostream>
#include <type_traits>
#include <vector>

template
<
    class T, 
    class U = typename std::conditional<std::is_same<T, unsigned char>::value, int, T>::type
>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vals)
{
    for (auto v : vals) {
        os << U{v} << ' ';
    }

    return os;
}

int main()
{
    auto const vc = std::vector<unsigned char>{ 1, 2, 3 };
    auto const vi = std::vector<int>{ 4, 5, 6 };        
    
    std::cout << vc << "\n";
    std::cout << vi << "\n";
}
