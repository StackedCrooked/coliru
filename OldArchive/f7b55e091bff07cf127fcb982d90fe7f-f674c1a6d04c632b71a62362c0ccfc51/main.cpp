#include <iostream>
#include <initializer_list>



template<typename T>
std::ostream& operator<<(std::ostream& os,   std::initializer_list<T> c)
{
    for (const auto& el : c)
    {
        os << el << ' ';
    }
    return os;
}


int main()
{
    const auto words= {"Hello", "from", "GCC", __VERSION__, "!" };
    
    std::cout << words << std::endl;
}
