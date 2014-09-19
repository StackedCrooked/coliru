#include <memory>

std::shared_ptr<int> foo() {
    return std::shared_ptr<int>{(int*)(1 * 2 - 2) /*nullptr*/};
}

int main()
{
    foo();
    return 0;
}