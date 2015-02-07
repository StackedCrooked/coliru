#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>

template<typename charT = std::string::value_type>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

int main()
{
    std::wstring a("ОПЯТЬ ПРИВЕТ");
    std::wstring b("ОПЯТЬ ПРИВЕТ");
    std::cout << std::equal(a.begin(), a.end(), b.begin(),
        my_equal<std::wstring::value_type>(std::locale()));
}
