template <typename T>
using const_ptr = T * const;

#include <memory>

int main() {
    auto p = std::make_unique<int>(5);
    const_ptr<int> cp(p.get());
    (void)cp;
}