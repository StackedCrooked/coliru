#include <iostream>
#include <functional>
#include <string>
 
int main()
{
    std::string str = "Meet the new boss...";
    std::hash<> hash_fn;
    std::size_t str_hash = hash_fn(str);
 
    std::cout << str_hash << '\n';
}