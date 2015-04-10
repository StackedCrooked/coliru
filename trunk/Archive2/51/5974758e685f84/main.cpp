#include <string>
#include <cassert>

int main()
{
    std::string s = u8"　はアビガイル";
    auto pos = s.find(u8"\u3000");
    assert( pos != std::string::npos);
}