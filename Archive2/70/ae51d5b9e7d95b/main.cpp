#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << "gcc version " << __VERSION__ << "\n";
    std::vector<std::vector<int> > aanXY;
    aanXY.emplace_back(std::vector<int>{0,1,2,3});
    std::cout << aanXY[0][0] << std::endl;
    std::cout << aanXY[0][1] << std::endl;
    std::cout << aanXY[0][2] << std::endl;
    std::cout << aanXY[0][3] << std::endl;
    std::cout << aanXY.size() << std::endl;
}
