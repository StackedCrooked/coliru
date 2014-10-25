#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

using namespace std;

struct Person
{
    std::string first_name;
    std::string last_name;
    
    bool operator==(const Person & rhs) const {
        return first_name == rhs.first_name && last_name == rhs.last_name;
    }
};

namespace std
{
    template<>
    struct hash<Person>
    {
        size_t operator()(Person const& s) const
        {
            static std::hash<std::string> hf;
            const size_t h1 ( hf(s.first_name) );
            const size_t h2 ( hf(s.last_name) );
            return h1 ^ (h2 << 1); // h1 XOR (h2 shifted left by 1)
        }
    };
}

int main()
{
    Person p;
    p.first_name = "Bender";
    p.last_name =  "Rodriguez";
    std::hash<Person> hash_fn;
 
    std::cout << "hash(p) = " << hash_fn(p) << "\n";

    std::unordered_map<Person, int> salary;
    salary[p] = 50000;

    std::cout << p.first_name << " earns " << salary[p] << "\n";
}