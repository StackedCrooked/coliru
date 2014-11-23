#include <boost/variant.hpp>
#include <memory>
#include <utility>
#include <iostream>

struct IntList
{
    struct Empty {};
    using value_type = std::pair<int, std::unique_ptr<IntList>>;
    boost::variant< value_type, Empty > m;
    
    IntList(value_type v) : m(std::move(v)) {}
    IntList(int v, std::unique_ptr<IntList> n) : m(std::make_pair(v, std::move(n))) {}
    IntList(Empty e) : m(e) {}
    
    auto sum() -> int {
        struct visitor
        {
            using result_type = int;
            result_type operator()(value_type const& v) const { return v.first + v.second->sum(); }
            result_type operator()(Empty) const { return 0; }
        };
        auto v = visitor();
        return m.apply_visitor(v);
    }
    auto multiply_by(int n) -> std::unique_ptr<IntList> {
        struct visitor
        {
            using result_type = std::unique_ptr<IntList>;
            int n;
            result_type operator()(value_type const& v) { return std::make_unique<IntList>(v.first * n, v.second->multiply_by(n)); }
            result_type operator()(Empty) { return std::make_unique<IntList>(Empty{}); }
        };
        auto v = visitor{n};
        return m.apply_visitor(v);
    }
};

int main()
{
    using std::make_unique;
    auto list = make_unique<IntList>(1, make_unique<IntList>(2, make_unique<IntList>(3, make_unique<IntList>(IntList::Empty{}))));
    std::cout << "Sum of all values in the list: " << list->multiply_by(2)->sum();
}