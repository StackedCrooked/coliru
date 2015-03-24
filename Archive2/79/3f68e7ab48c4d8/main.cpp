#include <iostream>

int main() {
    char buffer[4096];
    while (std::cin.read(buffer, sizeof(buffer)))
    {
        auto out = buffer;

        auto got = std::cin.gcount() / 4;
        auto b = reinterpret_cast<uint32_t const*>(buffer),
             e = b+got;

        for (auto ptr = b; ptr < e; ++ptr) {
            switch (*ptr) {
                case 0x30303030: *out++ = '0'; break;
                case 0x31303030: *out++ = '1'; break;
                case 0x30313030: *out++ = '2'; break;
                case 0x31313030: *out++ = '3'; break;
                case 0x30303130: *out++ = '4'; break;
                case 0x31303130: *out++ = '5'; break;
                case 0x30313130: *out++ = '6'; break;
                case 0x31313130: *out++ = '7'; break;
                case 0x30303031: *out++ = '8'; break;
                case 0x31303031: *out++ = '9'; break;
                case 0x30313031: *out++ = 'a'; break;
                case 0x31313031: *out++ = 'b'; break;
                case 0x30303131: *out++ = 'c'; break;
                case 0x31303131: *out++ = 'd'; break;
                case 0x30313131: *out++ = 'e'; break;
                case 0x31313131: *out++ = 'f'; break;
                default: *out++ = '?';
            }
        }

        std::cout.write(buffer, got);
    }
}
