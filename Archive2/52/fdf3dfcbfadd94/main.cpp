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
        typedef S argument_type;
        typedef std::size_t result_type;
 
        result_type operator()(argument_type const& s) const
        {
            result_type const h1 ( std::hash<std::string>()(s.first_name) );
            result_type const h2 ( std::hash<std::string>()(s.last_name) );
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