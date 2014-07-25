#include <memory>
#include <iostream>

template<typename A>
struct helper {

    std::shared_ptr<A> _a;

    helper(std::shared_ptr<A> a) : _a(a) {}

    virtual ~helper() {
        std::cout << "value was " << *_a << std::endl;
        }
};

int main()
{
    helper<int>(std::make_shared<int>());
    std::cout << "all done!" << std::endl;
}
