#include <iostream>

int main(int argc, char** argv) {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer)), std::cin.gcount() > 0) {
        size_t got = std::cin.gcount();
        char* out = buffer;

        for (auto it = buffer; it < buffer + got; it += 4) {
            unsigned long r = it[3] + (it[2] * 2) + (it[1] * 4) + (it[0] * 8) - 672;
            if (r > 57) r += 39;
            *out++ = r;
        }

        std::cout.write(buffer, got / 4);
    }
}

