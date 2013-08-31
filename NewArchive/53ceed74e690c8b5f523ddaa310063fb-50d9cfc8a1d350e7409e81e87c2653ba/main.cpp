#include <iostream>
#include <cstddef>

struct mystruct {
  std::string key;
  
  // lots of stuff
};

int main()
{
    my::map<mystruct> map;
    map.add(mystruct("abc"));
    map.add(mystruct("def"));
    map.add(mystruct("ghi"));
    
    std::cout << map["abc"].myfield << '\n';
}
