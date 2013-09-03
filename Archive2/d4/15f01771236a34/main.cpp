#include <algorithm>
#include <cctype>
#include <map>
#include <iostream>
#include <vector>
#include <boost/iterator/transform_iterator.hpp>

std::pair<std::string, int> make_lower(std::pair<std::string, int> x) {
    std::transform(x.first.begin(), x.first.end(), x.first.begin(), ::tolower);
    return x;
}

int main() {
    std::vector<std::pair<std::string, int>> myvector;
    myvector.push_back(std::make_pair("HELLO", 42));
    
    std::map<std::string, int> mymap(
        boost::make_transform_iterator(myvector.begin(), make_lower),
        boost::make_transform_iterator(myvector.end(), make_lower));
    
    std::cout << mymap["hello"] << '\n';
}