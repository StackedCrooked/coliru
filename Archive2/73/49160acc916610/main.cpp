#include <memory>
#include <set>
#include <utility>
#include <iostream>

struct foo
{
    foo(int i) : i{i} {}
    foo(foo const&) = delete;
    foo(foo&& other) : i{other.i} { std::cout << __PRETTY_FUNCTION__ << ' ' << i << '\n'; }
    bool operator<(foo const& other) const {return i < other.i;}
    
    int i = 0;
};

bool operator<(std::unique_ptr<foo> const& l, std::unique_ptr<foo> const& r)
{ return *l < *r; }

int main()
{
    std::set<std::unique_ptr<foo>> s;
    s.emplace(std::unique_ptr<foo>(new foo(10)));
    s.emplace(std::unique_ptr<foo>(new foo(10)));
    s.emplace(std::unique_ptr<foo>(new foo(20)));

    std::cout << s.size() << std::endl;
    std::cout << s.count(std::unique_ptr<foo>(new foo(20))) << std::endl;
    
    foo f{std::move(**s.begin())};
    s.erase(s.begin());
}
