#include <iostream>
#include <string>
#include <iomanip>
#include <map>
 
// helper function templates for printing each element
template<typename CharT, typename Traits, typename T>
void print_item(std::basic_ostream<CharT, Traits>& stream, const T& item)
{
  stream << item;
}
 
template<typename CharT, typename Traits, typename Alloc>
void print_item(std::basic_ostream<CharT, Traits>& stream,
    const std::basic_string<CharT, Traits, Alloc>& item)
{
  stream << std::quoted(item);
}
 
// A printer for unordered maps
template<typename Key, typename T, typename Compare, typename Allocator>
std::ostream& operator<<(std::ostream& stream,
    const std::map<Key, T, Compare, Allocator>& map)
{
  stream << '{';
  char comma[3] = {'\0', ' ', '\0'};
  for (const auto& pair : map) {
    stream << comma;
    print_item(stream, pair.first);
    stream << ':';
    print_item(stream, pair.second);
    comma[0] = ',';
  }
  stream << '}';
  return stream;
}
 
int main()
{
  // (1) Default constructor
  std::map<std::string, int> map1;
  map1["something"] = 69;
  map1["anything"] = 199;
  map1["that thing"] = 50;
  std::cout << std::string(80, '-') << '\n';
  std::cout << "map1 = " << map1 << '\n';
 
  // (2) Iterator constructor
  std::map<std::string, int> iter(map1.find("anything"), map1.end());
  std::cout << std::string(80, '-') << '\n';
  std::cout << "iter = " << iter << '\n';
  std::cout << "map1 = " << map1 << '\n';
 
  // (3) Copy constructor
  std::map<std::string, int> copied(map1);
  std::cout << std::string(80, '-') << '\n';
  std::cout << "copied = " << copied << '\n';
  std::cout << "map1 = " << map1 << '\n';
 
  // (4) Move constructor
  std::map<std::string, int> moved(std::move(map1));
  std::cout << std::string(80, '-') << '\n';
  std::cout << "moved = " << moved << '\n';
  std::cout << "map1 = " << map1 << '\n';
 
  // (5) Initializer list constructor
  const std::map<std::string, int> init {
    {"this", 100},
    {"can", 100},
    {"be", 100},
    {"const", 100},
  };
  std::cout << std::string(80, '-') << '\n';
  std::cout << "init = " << init << '\n';
}