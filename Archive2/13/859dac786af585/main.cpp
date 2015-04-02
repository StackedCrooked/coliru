#include <iostream>
#include <functional>
#include <string>
 
int main()
{
    std::hash<int64_t> hash_fn;
    std::size_t h = hash_fn(42);
 
    std::cout << h << '\n';
}