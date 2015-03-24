#include <iostream>

int main() {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer)), std::cin.gcount())
    {
        size_t got = std::cin.gcount();
        char* out = buffer;

        for (auto it = buffer; it < buffer+got; it += 4)
            *out++ = "0123456789abcdef"[
                    (it[0]!='0')*8 +
                    (it[1]!='0')*4 +
                    (it[2]!='0')*2 +
                    (it[3]!='0')*1
                ];

        std::cout.write(buffer, got/4);
    }
}
