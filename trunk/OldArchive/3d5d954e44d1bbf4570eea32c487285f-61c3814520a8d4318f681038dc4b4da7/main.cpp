#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>


struct CacheNode {
  std::set<int> *value;
  int timestamp;
  CacheNode() : value(new std::set<int>()), timestamp(0) {}
};


int main() {
    std::vector<CacheNode> v;
    std::generate_n(std::back_inserter(v), 10u, [](){ return CacheNode{}; });
    
    v[0].value->insert(0);    
    std::cout << v[0].value->size() << std::endl;
    std::cout << v[1].value->size() << std::endl;
}