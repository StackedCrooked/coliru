
#include <iostream>
#include <algorithm>
#include <functional>

template<typename C>
  struct adjacent_pairs {
      typedef typename C::const_iterator const_iterator;
      typedef typename C::const_reference const_reference;
      typedef std::pair<const_reference, const_reference> ref_pair;
      struct adjacent_pairs_iterator {
          const_iterator i, e;
          adjacent_pairs_iterator(const_iterator _i, const_iterator _e): i(_i), e(_e) { i = std::adjacent_find(i, e); }
          adjacent_pairs_iterator operator++() { if( i == e ) return *this; i = std::adjacent_find(i+2, e); return *this; };
          ref_pair operator*() { return ref_pair(i[0], i[1]); }
          adjacent_pairs_iterator end() { return adjacent_pairs_iterator(e, e); }
          bool operator!=(const adjacent_pairs_iterator& ii) const { return i != ii.i; }
      } i;
      adjacent_pairs(const C& c): i(c.cbegin(), c.cend()) {}
      adjacent_pairs_iterator begin() { return i; }
      adjacent_pairs_iterator end() { return i.end(); }
  };
  
template<typename C>
  adjacent_pairs<C> make_adjacent_pairs(const C& c) { return adjacent_pairs<C>(c); }
      
  
struct employee {
    int id, salary;
    bool operator<(const employee& e) const { return id < e.id; }
    bool operator==(const employee& e) const { return id == e.id; }
};

int main() {
    std::vector<employee> v1 { { 1, 1500 }, { 10, 2000 }, { 15, 2500 }, { 16, 1000 } };
    std::vector<employee> v2 { { 10, 1500 }, { 13, 2000 }, { 15, 500 }, { 19, 1300 } };
    std::vector<employee> v3; v3.reserve(v1.size()+v2.size());
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
    for( auto a: make_adjacent_pairs(v3) ) {
      std::cout << a.first.id << ' ' << a.first.salary << ' ';
      std::cout << a.second.id << ' ' << a.second.salary << '\n';
    }
}
