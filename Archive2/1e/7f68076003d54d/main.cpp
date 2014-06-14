#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class container
{
    public:
    
    container(){}
    container(container && a)
    {
        std::cout << "size of data before move " << a.data.size() << "\n";
        data = std::move(a.data);
        std::cout << "size of data after move " << a.data.size() << "\n";
    }
    std::vector<int> data;
    
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    container one;
    one.data = {1,2,3,4,5};
    
    container two ( std::move(one) );
    
    std::cout <<"size of one " << one.data.size() << "\n";
    std::cout <<"size of two " << two.data.size() << "\n";
    
    std::cout <<"done\n";
}
