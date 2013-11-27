#include <iostream>
#include <functional>
#include <string>
 
struct S
{
    std::string first_name;
    std::string last_name;
};
 
namespace std
{
    template<>
    struct hash<S>
    {
    public:
        std::size_t operator()(S const& s) const 
        {
            std::size_t h1 = std::hash<std::string>()(s.first_name);
            std::size_t h2 = std::hash<std::string>()(s.last_name);
            return h1 ^ (h2 << 1);
        }
    };
}
 
int main()
{
    S s;
    s.first_name = "Bender";
    s.last_name =  "Rodriguez";
    std::hash<S> hash_fn;
 
    std::cout << "hash(s) = " << hash_fn(s) << "\n";
}