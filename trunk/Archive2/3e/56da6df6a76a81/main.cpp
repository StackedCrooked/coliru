#include <cstdint>

constexpr const std::uint8_t major = 1;
constexpr const std::uint8_t minor = 10;
constexpr const std::uint8_t bugfix = 0;

constexpr class VersionStr
{
public:
    constexpr VersionStr()
        : ofs{sizeof(value) - 1}, value{}
    {
        predend_int(bugfix);
        push_front('.');
        predend_int(minor);
        push_front('.');
        predend_int(major);
    }

    constexpr const char* c_str() const { return value + ofs; }

private:
    constexpr void push_front(char c) { value[--ofs] = c; }

    constexpr void predend_int(int x)
    {
        do
        {
            auto digit = x % 10;
            x = x / 10;
            push_front(digit + '0');
        }
        while (x);
    }

    int ofs;
    char value[16]; // big enough to hold an 'xxx.xxx.xxx' string
} version_str{};

#include <iostream>
int main()
{
    std::cout << version_str.c_str() << '\n';
}