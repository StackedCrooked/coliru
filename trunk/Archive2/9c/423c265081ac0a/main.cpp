struct test {
    int x;
    int y;
};

#include <iostream>
#include <string>
#include <sstream>

int main() {
    test t;
    char bin[] = { 0x30, 0x39, 0x00, 0x00, 0x14, 0x15, 0x00, 0x00 };
    std::string data(bin, sizeof(bin));
    std::istringstream ss(data, std::ios_base::binary);
    ss.read(reinterpret_cast<char*>(&t), sizeof(t));
    static_assert(sizeof(bin) == sizeof(test), "..");
    std::cout << t.x << '\n' << t.y;
}