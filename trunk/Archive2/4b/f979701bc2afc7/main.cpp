#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <boost/optional.hpp>

template <typename Key, typename Value, 
          template <typename, typename, typename...> class C, 
          typename... Args>
boost::optional<Value> search(const C<Key, Value, Args...>& dict,
                              const Key& key)
{
  auto it = dict.find(key);

  if (it != dict.end()) {
    return it->second;
  } else {
    return boost::none;
  }
}

int main()
{
    std::map<std::string, int> m1;
    std::cout << search(m1, std::string("Foo")) << std::endl;
    
    std::unordered_map<std::string, int> m2;
    std::cout << search(m2, std::string("Foo")) << std::endl;
    
    std::unordered_multimap<std::string, int> m3;
    std::cout << search(m3, std::string("Foo")) << std::endl;
}
