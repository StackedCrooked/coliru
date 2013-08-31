#include <iostream>
#include <cstdint>

uint32_t htonl(uint32_t hostlong) {
    return hostlong; // example impl
}

int32_t hton(int32_t hostlong) {
    return reinterpret_cast<int32_t>(htonl(reinterpret_cast<uint32_t>(hostlong)));
}

int main() {
    int myi = 100;
    std::cout << hton(myi) << "\n";
    return 0;
}