#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class container
{
    public:
    
    container()
    {
        std::cout << "default constructor\n";    
    }

    container(const container & a)
    {
        std::cout << "copy constructor\n" ;
    }
    
    container(container && a)
    {
        std::cout << "move constructor\n";
        std::cout << "size of data before move " << a.data.size() << "\n";
        data = (std::move(a.data));
        std::cout << "size of data after move " << a.data.size() << "\n";
    }
    
    container& operator=(const container&) 
    { 
        std::cout << "copy assigned\n"; 
        return *this; 
    }

    container& operator=(container&& a) {
        std::cout << "move assigned\n";
        std::cout << "size of data before move " << a.data.size() << "\n";
        data = (std::move(a.data));
        std::cout << "size of data after move " << a.data.size() << "\n";
        return *this;
    }
    
    std::vector<int> data;
    
};



container get_container()
{
    container blah ;
    blah.data = {1,2,3};   
    return blah;
}

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

    
    container one = get_container() ;
    
    std::cout <<"size of one " << one.data.size() << "\n";
    
    std::cout <<"done\n";
}
