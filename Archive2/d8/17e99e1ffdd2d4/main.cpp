#include <fstream>

template<typename CharT, typename Traits>
void foo(std::basic_ostream<CharT, Traits>&) {}

int main()
{
    std::ofstream f;
    foo(f);
}