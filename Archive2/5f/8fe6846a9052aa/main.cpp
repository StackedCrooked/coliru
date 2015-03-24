#include <iostream>

int main(int argc, char** argv) {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer))) {
        size_t got = std::cin.gcount();
        char* out = buffer;

        for (auto it = buffer; it < buffer + got; it += 4) {
            unsigned long r = 0;
            for (int i = 0; i < 4; ++i) {
                r <<= 1;
                r += it[i] - '0';
            }
            
            *out++ = '0' + r + (r > 9) * ('a' - '0' - 10);
        }

        std::cout.write(buffer, got / 4);
    }
}
