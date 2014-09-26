#include <vector>

void foo(std::vector<int>);
void foo(std::vector<int> &);

int main() {
    std::vector<int> v;
    foo(v);
}