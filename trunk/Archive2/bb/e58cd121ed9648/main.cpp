/*
 工行有30万个员工，其工卡号码分别是1~30万，有接下来的某天他们将举行年会，需要抽出10万个员工发奖品。

 我们有一个随机数生成函数rand()能够随机均匀生成[0, 65535]的整数，请写一个抽奖程序，输出这10万个员工的工卡号码。
*/

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
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
