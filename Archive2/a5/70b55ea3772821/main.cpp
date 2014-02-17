#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <algorithm>

template< class T, class... Args >
std::unique_ptr<T> make_unique( Args&&... args )
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct Entry
{
    Entry(std::string const& s): s_(s) {}
    std::string s_;    
};

struct Catalogue
{
    void populate(std::vector<std::string> const& names)
    {
        decltype(vec_) tmp;
        tmp.reserve(names.size());
                
        transform(begin(names), end(names), std::back_inserter(tmp),
            [](auto const& s) 
        { 
            return make_unique<Entry>(s);
        });
            
        swap(tmp, vec_);
    }

    std::vector<std::unique_ptr<Entry>> vec_;
};

int main()
{
    auto n = std::vector<std::string>{ "a", "b", "c", "d" };
    Catalogue c;
    c.populate(n);
    for (auto&& p : c.vec_)
        std::cout << p->s_ << ",";
}
