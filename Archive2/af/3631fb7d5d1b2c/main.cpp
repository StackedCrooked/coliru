#include <iostream>

int main(int argc, char** argv) {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer))) {
        size_t got = std::cin.gcount();
        char* out = buffer;

        for (auto it = buffer; it < buffer + got; it += 4) {
            unsigned long r = it[0] + (it[1] * 2) + (it[2] * 4) + (it[3] * 8) - 672;
            if (r > 57) r += 39;
            *out++ = r;
        }

        std::cout.write(buffer, got / 4);
    }
}

