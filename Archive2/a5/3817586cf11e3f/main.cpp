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

int solution(int N)
{
    int largest = N;
    int shift = 0;
    int temp = N;
    
    for (int i = 1; i < 30; ++i) {
        // int index = (temp & 1);
        // temp = ((temp >> 1) | (index << 29));
        int index = (N << (30 - i)) & 0x3fffffff;
        temp = ((N >> i) | (index));
        
        if (temp > largest) {
            largest = temp;
            shift = i;
        }
    }
    return shift;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::cout << solution(1073741822) << std::endl;
}

/*
simple_result_zero N = 110..000, 110..010 and 110..001
0.008 s
WRONG ANSWER
got 29, but 805306368 >> 29 == 536870913, w hereas 805306368 >> 0 == 805306368
*/
