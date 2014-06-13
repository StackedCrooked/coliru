#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void func(int n){
    std::cout<<n<<std::endl;
    func(n);   
}
int main()
{
    
    func(5);
    return 0;
}
