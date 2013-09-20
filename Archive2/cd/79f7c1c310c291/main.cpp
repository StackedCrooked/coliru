#include <vector>
#include <cassert>

int main() {
    std::vector<int> some_vector { 1, 2, 3, 4, 5 };
    auto e = some_vector.end();
    assert(e == some_vector.end());
    assert(some_vector.size() > 0);
    e = some_vector.erase(e-1);
    assert(e == some_vector.end());
}