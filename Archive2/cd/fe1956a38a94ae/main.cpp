#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::placeholders;

int main()
{
    typedef pair<string, string> MyElem;
    vector <MyElem> vec { {"a", "b" }, {"c", "d"} };
    map <string, string> map { vec.begin (), vec.end () };
    transform (map.begin (), map.end (), ostream_iterator <string> (cout, "\n"), bind (&decltype (map)::value_type::second, _1));
}
