#include <iostream>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using namespace boost::property_tree;

int main()
{
    ptree pt;

    pt.add("foo","bar");
    pt.add("bar","baz");
    pt.add("baz","foo");
    pt.add("book","title1");
    pt.add("book","title2");
    pt.add("book","title3");
    pt.add("baz2","foo3");

    std::pair < ptree::const_assoc_iterator, ptree::const_assoc_iterator> bounds = pt.equal_range("book");
    
    for (ptree::const_assoc_iterator it = bounds.first; it != bounds.second ; ++it)
    {
        cout << it->second.data() << endl;
    }

    return 0;
}
