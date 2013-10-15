#include<cassert>
#include <string>
    using std::string;
#include <boost/bimap.hpp>
    using boost::bimap;

#include <iostream>
#include <sstream>
    
int main() {
    typedef bimap<int, string> IntStringBiMap;
    IntStringBiMap m;
    
    assert(m.empty());
    assert(m.size() == 0);
    
    m.insert(IntStringBiMap::value_type(1, "one"));
    assert(!m.empty());
    assert(m.size() == 1);
    assert(m.left.at(1) == "one");
    assert(m.right.at("one") == 1);
    
    m.insert(IntStringBiMap::value_type(2, "two"));
    assert(!m.empty());
    assert(m.size() == 2);
    assert(m.left.at(1) == "one");
    assert(m.left.at(2) == "two");
    assert(m.right.at("one") == 1);
    assert(m.right.at("two") == 2);
    
    m.insert(IntStringBiMap::value_type(1000, "many"));
    assert(!m.empty());
    assert(m.size() == 3);
    assert(m.left.at(1) == "one");
    assert(m.left.at(2) == "two");
    assert(m.left.at(1000) == "many");
    assert(m.right.at("one") == 1);
    assert(m.right.at("two") == 2);
    assert(m.right.at("many") == 1000);
    
    std::ostringstream oss;
    for (auto v : m.left)
        oss << v.first << " -> " << v.second << "\n";
    for (auto v : m.right)
        oss << v.first << " -> " << v.second << "\n";
    assert(oss.str() == "1 -> one"      "\n"
                        "2 -> two"      "\n"
                        "1000 -> many"  "\n"
                        "many -> 1000"  "\n"
                        "one -> 1"      "\n"
                        "two -> 2"      "\n");
                        
    std::cout << "* all tests passed *" << std::endl;
}
