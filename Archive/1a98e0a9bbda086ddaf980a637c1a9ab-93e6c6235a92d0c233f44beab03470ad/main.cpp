#include <iostream>
#include <string>
#include <boost/regex/pending/unicode_iterator.hpp>

using namespace std;

template <typename C>
std::string to_utf8(C const& in)
{
    std::string result;
    auto out = std::back_inserter(result);
    auto utf8out = boost::utf8_output_iterator<decltype(out)>(out);

    std::copy(begin(in), end(in), utf8out);
    return result;
}

int main()
{
    wstring s = L"سلام hello";

    auto first  = s.substr(0,3);
    auto second = s.substr(4,5);

    cout << to_utf8(first)  << endl;
    cout << to_utf8(second) << endl;
}
