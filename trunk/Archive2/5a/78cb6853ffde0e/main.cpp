#include <iostream>
#include <map>
#include <unordered_map>
#include <cassert>

namespace util {
    
template <typename Container>
bool insert(Container& container,
            typename Container::key_type const& key,
            typename Container::mapped_type&& mapped)
{
  return std::get<1>(container.insert({key, mapped}));
}

template <typename Container>
bool replace(Container& container,
             typename Container::key_type const& key,
             typename Container::mapped_type&& mapped)
{
  auto p = container.find(key);
  if (end(container) == p)
    return false;

  p->second = std::move(mapped);
  return true;
}

template <typename Container>
void insert_or_replace(Container& container,
                       typename Container::key_type const& key,
                       typename Container::mapped_type&& mapped)
{
  container[key] = std::move(mapped);
}

}

int main()
{
  std::map<int, std::string> m;
  assert(true == util::insert(m, 1, "abc"));
  assert(1 == m.size());
  assert(m[1] == "abc");

  assert(false == util::insert(m, 1, "abc"));
  assert(1 == m.size());
  assert(m[1] == "abc");

  assert(false == util::replace(m, 2, "def"));
  assert(1 == m.size());
  assert(m[1] == "abc");

  assert(true == util::replace(m, 1, "def"));
  assert(1 == m.size());
  assert(m[1] == "def");

  util::insert_or_replace(m, 1, "ghi");
  assert(1 == m.size());
  assert(m[1] == "ghi");

  util::insert_or_replace(m, 2, "jkl");
  assert(2 == m.size());
  assert(m[2] == "jkl");

  std::unordered_map<int, std::string> um;
  assert(true == util::insert(um, 1, "abc"));
  assert(1 == um.size());
  assert(um[1] == "abc");

  assert(false == util::insert(um, 1, "abc"));
  assert(1 == um.size());
  assert(um[1] == "abc");

  assert(false == util::replace(um, 2, "def"));
  assert(1 == um.size());
  assert(um[1] == "abc");

  assert(true == util::replace(um, 1, "def"));
  assert(1 == um.size());
  assert(um[1] == "def");

  util::insert_or_replace(um, 1, "ghi");
  assert(1 == um.size());
  assert(um[1] == "ghi");

  util::insert_or_replace(um, 2, "jkl");
  assert(2 == um.size());
  assert(um[2] == "jkl");

  return 0;
}
