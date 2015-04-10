#include <string>
#include <cassert>

int main()
{
    std::string s = u8"　はアビガイル";
    auto pos = s.find(u8"\u3000");
    assert( pos != std::string::npos);
    pos = s.find("\xe3\x80\x80"); // \u3000 as individual bytes
    assert( pos != std::string::npos);
}