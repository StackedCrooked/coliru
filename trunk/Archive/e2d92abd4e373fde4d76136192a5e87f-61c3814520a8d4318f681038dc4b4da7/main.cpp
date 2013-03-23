#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>


struct CacheNode {
  std::set<int> *value;
  int timestamp;
  CacheNode() : value(new std::set<int>()), timestamp(0) {}
};


template<typename T>
struct vextor : std::vector<T> {
    using typename std::vector<T>::size_type;    
    vextor(size_type s) {
        this->reserve(s);
        std::generate_n(std::back_inserter(*this), s, [](){ return T(); });
    }
};


int main() {
    vextor<CacheNode> v(10);
}