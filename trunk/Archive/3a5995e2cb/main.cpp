#include <iostream>
#include <functional>
#include <string>
 
int main()
{
    std::string str = "Meet 啊啊飞大叔";
    std::hash<std::string> hash_fn;
    std::size_t str_hash = hash_fn(str);
 
    std::cout << str_hash << '\n';
}