#include <memory>

std::shared_ptr<int> foo() {
    return {1 * 2 - 2};
}

int main()
{
    foo();
    return 0;
}
