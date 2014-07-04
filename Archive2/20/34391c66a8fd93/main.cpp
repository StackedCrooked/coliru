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

int main()
{
    std::vector<std::string> words = {
        "Hello","DDD" , "GCC", __VERSION__, "!"
    };
    for(int j=0;j<10;j++)   //打印的函数
    {
        for(int i=0;i<j;i++)  //打印的 * 个数
        {
            std::cout << '*';  //打印 *
        }
        std::cout << std::endl;  //回车
    }