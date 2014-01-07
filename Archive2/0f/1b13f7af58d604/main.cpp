#include <iostream>
#include <memory>
#include <unordered_map>
#include <cstdlib>

struct foo 
{
    foo(unsigned i) : i(i) {}
    unsigned i;
};

namespace std {

template<>
struct hash<foo *>
{
    size_t operator()(foo const *f) const
    {
        std::cout << "Hashing foo: " << f->i << '\n';
        return f->i;;
    }
};

}

int main()
{
    std::unordered_map<std::unique_ptr<foo>, int> m;
    m.insert(std::make_pair(std::unique_ptr<foo>(new foo(10)), 100));
    m.insert(std::make_pair(std::unique_ptr<foo>(new foo(20)), 200));
}
