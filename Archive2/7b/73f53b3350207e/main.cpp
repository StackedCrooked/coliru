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


class xxx
{
    public:
    
    int **triangle;
    
    
    xxx(int n){
        triangle = new int *[n+1];
        for(int i=0;i<=n; i++) triangle[i]=new int[i+1];
    }
    
};


int main()
{
    xxx x(10);
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
