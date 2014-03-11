#include    <boost/algorithm/string/split.hpp>
#include    <vector>
#include    <string>

constexpr char separator = '.';     // This is how it's declared in some header file

int main()
{
    std::wstring text( L"This.is.a.test" );

    std::vector<std::wstring> result;
    // can't use is_any_of() unless i convert it to a wstring first.
    boost::algorithm::split( result, text, [](wchar_t ch) -> bool { return ch == (wchar_t) separator; });

    return 0;
}