#include <iostream>
#include <type_traits>
#include <vector>

template<class T, class = typename std::enable_if<std::is_convertible<T, int>::value>::type>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vals)
{
    for (auto v : vals) {
        os << static_cast<int>(v) << ' '; // Warns on narrowing conversion.
    }

    return os;
}

int main()
{
    auto vc = vector<unsigned char>{ 65, 66, 67 };
    auto vi = vector<int>{ 4, 5, 6 };        
    
    std::cout << vc << "\n";
    std::cout << vi << "\n";
}
