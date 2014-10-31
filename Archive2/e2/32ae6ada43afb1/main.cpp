#include <iostream>
#include <vector>
#include <set>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;

using boost::property_tree::ptree;

class Eric {
public:
    template <typename T> static std::vector<T> restore_vector(ptree const& pt, ptree::key_type const& key)
    {
        std::vector<T> r;
        BOOST_FOREACH (ptree::value_type const& item, pt.get_child(key)) {
            T s = item.second.get_value<T>();
            r.push_back(s);
        }
        return r;
    }
    template <typename T> static std::set<T> restore_set(ptree const& pt, ptree::key_type const& key)
    {
        std::set<T> r;
        BOOST_FOREACH (ptree::value_type const& item, pt.get_child(key)) {
            T s = item.second.get_value<T>();
            r.insert(s);
        }
        return r;
    }
};

int main()
{
    std::stringstream ss("{\"a\": [8, 7, 5, 6, 2], \"b\": [2, 2, 1]}");

    ptree pt;
    read_json(ss, pt);

    cout << "a: " << endl;
    BOOST_FOREACH (int i, Eric::restore_vector<int>(pt, "a")) std::cout << i << ' ';
    cout << "\n" << endl;
    std::cout << "b: " << endl;
    BOOST_FOREACH (int i, Eric::restore_set<int>(pt, "b")) std::cout << i << ' ';
}
