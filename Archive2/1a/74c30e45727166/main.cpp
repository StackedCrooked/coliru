#include <memory>
#include <set>
#include <utility>
#include <iostream>

struct foo
{
    foo() = default;
    foo(foo const&) = delete;
    foo(foo&&)      { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    bool operator<(foo const&) const {return false;}
};

bool operator<(std::unique_ptr<foo> const& l, std::unique_ptr<foo> const& r)
{ return *l < *r; }

int main()
{
    std::set<std::unique_ptr<foo>> s;
    s.emplace(std::unique_ptr<foo>(new foo()));

    foo f{std::move(**s.begin())};
    s.erase(s.begin());
}
