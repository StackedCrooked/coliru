#include <iostream>
#include <string>
#include <array>
#include <memory>

struct mydata {
    uint32_t data[8] = {0x00000001, 0x00020003, 0x00040005, 0x00060007, 0x00080009, 0x000A000B, 0x000C000D, 0x000E000F};
    
    auto begin() -> decltype(&data[0]) {
        return &data[1];
    }
    
    auto end() -> decltype(&data[0]) {
        return &data[6];
    }
    
    uint16_t* begin2() {
        return reinterpret_cast<uint16_t*>(&data[2]);
    }
    
    uint16_t* end2() {
        return reinterpret_cast<uint16_t*>(&data[5]);
    }
};

int main()
{
    mydata md;
    
    std::array<uint16_t, 4> &data = *reinterpret_cast<std::array<uint16_t, 4>*>(&md.data[4]);
    
    for (auto val : data) std::cout << val << " "; // undefined behavior
    std::cout << std::endl;
    
    for (auto val : md.data) std::cout << val << " ";
    std::cout << std::endl;
    
    for (auto val : md) std::cout << val << " ";
    std::cout << std::endl;
    
    for (auto val = md.begin2(); val != md.end2(); val++) {
        std::cout << *val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
