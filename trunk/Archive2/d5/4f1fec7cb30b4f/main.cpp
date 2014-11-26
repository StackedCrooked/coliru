#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (const auto & el : vec) {
        os << el << ' ';
    }
    return os;
}

int main() {
    int elemCount = 64;
    for (int stride = 1; stride < 9; ++stride) {
        std::cout << stride << ": ";
        std::vector<int> bla;
        for (int index = 0; index < elemCount; ++index) {
            auto trip = (index * stride) / elemCount;
            auto trip_offset = (stride - (trip * elemCount) % stride) % stride;
            auto z = (index * stride) % elemCount - trip_offset + trip;
            bla.push_back(z);
            if (z == 64 || (z == 0 && index == 53)) {
                //std::cout << index << ' ' << (index * stride) << ' ' << trip_offset << ' ' << trip << ' ' << z << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << bla << std::endl;
        std::sort(begin(bla), end(bla));
        //std::cout << " : " << bla << std::endl;
        (stride - (stride * elemCount) % stride) % stride
    }
}
