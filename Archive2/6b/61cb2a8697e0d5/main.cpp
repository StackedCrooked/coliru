#include <iostream>
#include <functional>
#include <string>
 
struct S
{
    std::string first_name;
    std::string last_name;
};
 
template <class T>
class MyHash;
 
template<>
class MyHash<S>
{
public:
    std::size_t operator()(S const& s) const 
    {
        std::size_t h1 = std::hash<std::string>()(s.first_name);
        std::size_t h2 = std::hash<std::string>()(s.last_name);
        return h1 ^ (h2 << 1);
    }
};
 
int main()
{
    std::string s1 = "Hubert";
    std::string s2 = "Farnsworth";
    std::hash<std::string> h1;
 
    S n1;
    n1.first_name = s1;
    n1.last_name =  s2;
 
    std::cout << "hash(s1) = " << h1(s1) << "\n"
              << "hash(s2) = " << std::hash<std::string>()(s2) << "\n"
	      << "hash(n1) = " << MyHash<S>()(n1) << "\n";
 
}