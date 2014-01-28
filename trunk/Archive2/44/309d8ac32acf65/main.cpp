#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::placeholders;

int main()
{
    multimap <string, string> map = { {"key", "Ala"}, {"key", "ma"}, {"key", "kota"} };
    
    //         source begin  source end  destination                             unary function OP (gets called for each source element).
    transform (map.begin (), map.end (), ostream_iterator <string> (cout, ", "), bind (&multimap <string, string>::value_type::second, _1));
}
