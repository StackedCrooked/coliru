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

    template <typename T> static void restore_vector(ptree const& pt, ptree::key_type const& key, std::vector<T>& coll)
    {
        coll.clear();
        BOOST_FOREACH(ptree::value_type const& item, pt.get_child(key)) {
            T s = item.second.get_value<T>();
            coll.push_back(s);
        }
    }
    
    template <typename T> void save_vector(ptree const& pt, ptree::key_type const& key, std::vector<T>& coll)
    {
        return;
    }
    
    template <typename T> static void restore_set(ptree const& pt, ptree::key_type const& key, std::set<T>& coll)
    {
        coll.clear();
        BOOST_FOREACH(ptree::value_type const& item, pt.get_child(key)) {
            T s = item.second.get_value<T>();
            coll.insert(s);
        }
    }

    template <typename T> void save_set(ptree const& pt, ptree::key_type const& key, std::set<T>& coll)
    {
        return;
    }
};

int main()
{
    std::stringstream ss("{\"a\": [8, 7, 5, 6, 2], \"b\": [2, 2, 1]}");

    ptree pt;
    read_json(ss, pt);

    cout << "a: " << endl;
    vector<int> a;
    Eric::restore_vector<int>(pt, "a", a);
    BOOST_FOREACH (int i, a) std::cout << i << ' ';
    
    cout << "\n" << endl;
    
    std::cout << "b: " << endl;
    set<int> b;
    Eric::restore_set<int>(pt, "b", b);
    BOOST_FOREACH (int i, b) std::cout << i << ' ';
}
