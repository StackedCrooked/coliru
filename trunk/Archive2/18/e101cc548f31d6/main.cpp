#include <map>
#include <vector>
#include <algorithm>

template <class Map>
std::vector<typename Map::key_type> getKeys(Map const& m)
{
  typedef typename Map::key_type Key;
  std::vector<Key> result;
  result.reserve(m.size());
  for (auto const& keyValuePair : m) //foreach (Map::value_type const& keyValuePair, m)
  {
    result.push_back(keyValuePair.first);
  }
  return result;
}

#include <iostream>

int main()
{
    std::map<int, char const*> theMap = {{3, "meh"}, {5, "muh"}, {7, "meow"}};
    auto theKeys = getKeys(theMap);
    for (auto const& k : theKeys) std::cout << k << '\n';
}
