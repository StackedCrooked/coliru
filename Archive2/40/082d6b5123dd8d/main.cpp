#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;

template <typename T>
std::vector<T> as_vector(ptree const& pt, ptree::key_type const& key)
{
    std::vector<T> r;
    BOOST_FOREACH (ptree::value_type const& item, pt.get_child(key))
        r.push_back(item.second.get_value<T>());
    return r;
}

int main()
{
    std::stringstream ss("{\"a\": [8, 6, 2], \"b\": [2, 2, 1]}");

    ptree pt;
    read_json(ss, pt);

    BOOST_FOREACH (int i, as_vector<int>(pt, "a")) std::cout << i << ' ';
    std::cout << '\n';
    BOOST_FOREACH (int i, as_vector<int>(pt, "b")) std::cout << i << ' ';
}
