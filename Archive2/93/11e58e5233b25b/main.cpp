#include <iostream>
#include <cassert>

int main() {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer))) {
        auto got = std::cin.gcount();
        auto out = buffer;

        for (auto it = buffer; it < buffer + got; it+=4) {
            char digit = (it[0] == '0'
                          ? (it[1] == '0' ? (it[2] == '0' ? (it[3] == '0' ? '0' : '1') : (it[3] == '0' ? '2' : '3'))
                                          : (it[2] == '0' ? (it[3] == '0' ? '4' : '5') : (it[3] == '0' ? '6' : '7')))
                          : (it[1] == '0' ? (it[2] == '0' ? (it[3] == '0' ? '8' : '9') : (it[3] == '0' ? 'a' : 'b'))
                                          : (it[2] == '0' ? (it[3] == '0' ? 'c' : 'd') : (it[3] == '0' ? 'e' : 'f'))));
            *out++ = digit;
        }

        std::cout.write(buffer, got / 4);
    }
}
