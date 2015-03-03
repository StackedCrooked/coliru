#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T>& vec)
{
    for (auto&& el : vec)
    {
        os << el << ' ';
        el += "_x";
    }
    return os;
}

void fun(int x)
{
    std::cout << "last " << x << std::endl;
}

void fun(char x)
{
    std::cout << "last " << x << std::endl;
}
template <class... Targs>
void fun(int x, Targs... args)
{
    std::cout << x << " , sizeof...(args)="<< sizeof...(args) << std::endl;
    fun(++args...);
}
int main()
{
    std::vector<std::string> words = {
        "Hello1", "from", "GCC", __VERSION__, "!"
    };
    for( auto& a : words)
    {
       std::cout << a << " -- " << words << std::endl;
    }
    
    fun(10,1,2,3,4,5,6,7,8,'A');

}
