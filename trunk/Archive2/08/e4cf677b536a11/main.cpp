#include <boost/variant.hpp>
#include <iostream>

struct s_node;

typedef boost::variant<
        int,
        boost::recursive_wrapper<s_node>
    > expr;

struct s_node
{
    expr oper1, oper2;
    double value;

    explicit s_node(const expr& l, const expr& r)
        : oper1(l), oper2(r), value(-1) { }

    friend std::ostream& operator<<(std::ostream& os, s_node const& n) {
        return os << "s_node {" << n.oper1 << ", " << n.oper2 << " /*value: " << n.value << "*/}";
    }
};

struct Traversal : boost::static_visitor<void>
{
    void operator()(int) const { }

    void operator()(s_node& b) const {
        b.value = 10.0;
    }
};

int main()
{
    expr x = s_node(5, s_node(7, 42));

    std::cout << "Before: " << x << "\n";

    boost::apply_visitor(Traversal(), x);

    std::cout << "After:  " << x << "\n";
}
