#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <unordered_map>
 
namespace N {
 
typedef std::tuple<int, char, char> key_t;
 
struct key_hash : public std::unary_function<key_t, std::size_t>
{
std::size_t operator()(const key_t& k) const
{
return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
}
};
 
struct key_equal : public std::binary_function<key_t, key_t, bool>
{
bool operator()(const key_t& v0, const key_t& v1) const
{
return (
std::get<0>(v0) == std::get<0>(v1) &&
std::get<1>(v0) == std::get<1>(v1) &&
std::get<2>(v0) == std::get<2>(v1)
);
}
};
 
struct data
{
std::string x;
};
 
typedef std::unordered_map<const key_t,data,key_hash,key_equal> map_t;
 
}
 
int main()
{
using namespace N;
 
map_t m;
data d;
d.x = "test data";
m[std::make_tuple(1, 'a', 'b')] = d;
auto itr = m.find(std::make_tuple(1, 'a', 'b'));
if (m.end() != itr)
{
std::cout << "x: " << itr->second.x;
}
return 0;
}
 