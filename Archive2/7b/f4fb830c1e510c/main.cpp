#include <iostream>
#include <memory>
#include <set>
#include <string>

struct foo
{
    foo() = default;
    foo(foo const& rhs) = delete;
    foo(foo&&rhs) :value(std::move(rhs.value)) { std::cerr << __PRETTY_FUNCTION__ << '\n'; }
    explicit foo(std::string v) : value(v) {};
    
    bool operator<(foo const& rhs) const {return value<rhs.value;}    
    std::string value;
};

bool is_in_set(foo* ptr);

int main()
{
    foo* p1 = new foo();
    std::cerr << is_in_set(p1);
}



/*module 2*/

bool operator<(std::unique_ptr<foo> const& l, std::unique_ptr<foo> const& r)
{ return *l < *r; }

std::set<std::unique_ptr<foo>> s_ctor() {
    std::set<std::unique_ptr<foo>> s;
    s.emplace(new foo());
    return s;
}
std::set<std::unique_ptr<foo>> s = s_ctor();

bool is_in_set(foo* ptr) {
    std::cerr << "entering is_in_set\n";
    auto it = s.find(std::unique_ptr<foo>(ptr));
    bool result =  it != s.end();
    std::cerr << "holds: " << ptr->value << '\n';
    return result;
}