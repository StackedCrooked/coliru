#include <map>
#include <vector>
#include <algorithm>

template <class Map>
std::vector<typename Map::key_type> getKeys(Map const& m)
{
  typedef typename Map::key_type Key;
  std::vector<Key> result;
  result.reserve(m.size());
  
  std::transform(begin(m), end(m), std::back_inserter(result), [](typename Map::value_type const& value) {return value.first;});
  return result;
}

#include <iostream>

int main()
{
    std::map<int, char const*> theMap = {{3, "meh"}, {5, "muh"}, {7, "meow"}};
    auto theKeys = getKeys(theMap);
    for (auto const& k : theKeys) std::cout << k << '\n';
}
