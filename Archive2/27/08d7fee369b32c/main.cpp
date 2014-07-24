#include <memory>
#include <iostream>

template<typename A, typename B>
struct helper {

    std::shared_ptr<A> _a;

    B* _b;

    helper(std::shared_ptr<A> a) : _a(a), _b(nullptr) {}

    virtual ~helper() {
        std::cout << "value was " << *_a << std::endl;
        }

    void test(B& b) {}
};

int main()
{
    helper<int, float>(std::make_shared<int>());
    std::cout << "all done!" << std::endl;
}
