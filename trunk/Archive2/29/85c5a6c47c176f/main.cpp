#include <memory>
#include <utility>
#include <iostream>

struct IntList
{
    using Node = std::pair<int, IntList>;
    std::unique_ptr<Node> m;
    
    IntList(std::unique_ptr<Node> v) : m(std::move(v)) {}
    IntList(std::nullptr_t) : m() {}
    
    auto sum() -> int {
        if(m) {
            return m->first + m->second.sum();
        }else {
            return 0;
        }
    }
    auto multiply_by(int n) -> IntList {
        if(m) {
            return std::make_unique<Node>(m->first * n, m->second.multiply_by(n));
        }else {
            return IntList(nullptr);
        }
    }
};

int main()
{
    using std::make_unique;
    using Node = IntList::Node;
    auto list = IntList{make_unique<Node>(1, make_unique<Node>(2, make_unique<Node>(3, nullptr)))};
    std::cout << "Sum of all values in the list: " << list.multiply_by(2).sum();
}