
#include <iostream>
#include <map>

struct Key {
  Key() :m(0) { std::cout << "key: 0"; }
  Key(int i) : m(i) { std::cout << "key: " << i; }
  Key(const Key& k) : m(k.m) { std::cout << "key&: " << m; }
  Key(Key&& k) : m(k.m) { std::cout << "key&&: " << m; }

  struct less {
    bool operator() (const Key& that, const Key& other) { return that.m < other.m; }
  };

  int m;
};


struct Value {
  Value() : m(0)  { std::cout << ", value: " << 0 << std::endl; }
  Value(int i) : m(i)  { std::cout << ", value: " << i << std::endl; }
  Value(const Value& v) : m(v.m)  { std::cout << ", value&: " << m << std::endl; }
  Value(Value&& v) : m(v.m)  { std::cout << ", value&&: " << m << std::endl; }

  int m;
};

int main() {
  std::map<Key, Value, Key::less> map;

  map.insert(std::pair<Key, Value>(1, 2));
  map.insert(std::pair<const Key, Value>(3, 4));
  map.insert(std::make_pair(5, 6));
  map.emplace(7, 8);

  return 0;
}