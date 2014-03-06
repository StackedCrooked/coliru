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


template<typename kernelEntryT, size_t kernelRowSize, size_t kernelColSize>
class Kernel {
    kernelEntryT kernelMatrix[kernelRowSize][kernelColSize];
};

int main(){
    Kernel<int,3,3> k = {{0,0,0},{0,1,0},{0,0,0}};
}
