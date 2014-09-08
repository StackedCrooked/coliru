#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

int main()
{
    std::vector <int> v {1, 2, 3, 4};
    std::vector <int> x;
    std::for_each (v.begin (), v.end (), [] (int const &i) { std::cerr << i; });
    std::cerr << "|";
    std::transform (v.begin (), v.end (), std::back_inserter (x), [](int const &i) { return i + 1; });
    std::copy (x.begin (), x.end (), std::ostream_iterator <int> (std::cerr, ","));    
    std::cerr << "|";
    std::cerr << std::count (x.begin (), x.end (), 2);
    std::cerr << "|min=" << *std::min_element (x.begin (), x.end ()) << "|max=" << *std::max_element (x.begin (), x.end ());
    std::cerr << "|" << std::distance (x.begin (), std::find (x.begin (), x.end (), 5)) << "|";
    x.erase (std::remove (x.begin (), x.end (), 3), x.end ());
    std::copy (x.begin (), x.end (), std::ostream_iterator <int> (std::cerr, ","));
    
    typedef std::unordered_map <std::string, std::string> MyMap;
    MyMap map { {"a", "A"}, {"b", "B"} };
    auto func = std::bind (&MyMap::value_type::second, std::placeholders::_1);
    std::cerr << "|" << func (*map.begin ());
    
}
