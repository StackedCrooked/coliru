#include <vector>

const std::vector<int>& foo() {
    static const std::vector<int> x;
    return x;
}

int main()
{
    foo();
}
