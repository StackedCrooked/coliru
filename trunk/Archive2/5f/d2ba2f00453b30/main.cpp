#include<iostream>
#include<set>
#include<memory>
#include<functional>

template <typename Comparator = std::less<void>>
struct indirect_compare
{
    Comparator C;
    explicit indirect_compare(const Comparator& x = Comparator()) : C(x) {}
    template<typename T>
    bool operator()(const T& lhs, const T& rhs)
    { return C(*lhs, *rhs); }
};

int main()
{
    std::set<std::shared_ptr<std::string>, indirect_compare<>> mySet;
    mySet.insert(std::make_shared<std::string>("foo"));
    mySet.insert(std::make_shared<std::string>("baz"));
    mySet.insert(std::make_shared<std::string>("bar"));
    mySet.insert(std::make_shared<std::string>("last"));
    for(const auto& s: mySet)
        std::cout << *s << '\n';
}
