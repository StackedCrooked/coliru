#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/range.hpp>
#include <iterator>
#include <iostream>
#include <ostream>
#include <cstdint>
#include <vector>

int main()
{
    using namespace boost;
    using namespace spirit::qi;
    using namespace std;

    auto &&utf8_text=u8"你好，世界！";
    u8_to_u32_iterator<const char*>
        tbegin(begin(utf8_text)), tend(end(utf8_text));

    vector<uint32_t> result;
    parse(tbegin, tend, *standard_wide::char_, result);
    for(auto &&code_point : result)
        cout /*<< "&#"*/ << code_point << ";";
    cout << endl;
}