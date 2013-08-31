#include <string>
#include <stack>

namespace exprtemplates
{
    template <typename T> struct stack_indexer_expr
    {
        typedef std::stack<T> S;
        S& s;
        std::size_t n;
        stack_indexer_expr(S& s, std::size_t n) : s(s), n(n) {}

        operator T() const {
            auto i = s.size()-n;
            for (auto clone = s; !clone.empty(); clone.pop())
                if (0 == --i) return clone.top();
        }

        operator std::string() const {
            return std::to_string(this->operator T());
        }
    };

    template <typename T> struct stack_expr
    {
        typedef std::stack<T> S;
        S& s;
        stack_expr(S& s) : s(s) {}

        stack_indexer_expr<T> operator[](std::size_t n) const {
            return { s, n };
        }
    };
}

template <typename T> 
exprtemplates::stack_expr<T> extend(std::stack<T>& s) {
    return { s };
}

#include <iostream>
int main()
{
    std::stack<double> s;
    s.push(0.5);
    s.push(0.6);
    s.push(0.7);
    s.push(0.8);

    std::string demo = extend(s)[3];
    std::cout << demo << "\n";

    // some more usage:
    auto magic_stack = extend(s);
    std::cout << magic_stack[0] << "\n";
    std::cout << magic_stack[1] << "\n";
    std::cout << magic_stack[2] << "\n";
    std::cout << magic_stack[3] << "\n";

    double      as_double = magic_stack[0];
    std::string as_string = magic_stack[0];
}
