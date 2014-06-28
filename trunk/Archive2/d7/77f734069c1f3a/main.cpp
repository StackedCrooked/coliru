#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

int main()
{
    std::unordered_multimap<int, std::string> 
        mymap{{4, "key 4"}, 
              {3, "key 3"}, 
              {3, "key 3"}, 
              {2, "key 2"}, 
              {2, "key 2"}, 
              {2, "key 2"},};
              
    for(auto const& kv : mymap) {
        std::cout << "key: " << kv.first << " value: " << kv.second << '\n';
    }
}

