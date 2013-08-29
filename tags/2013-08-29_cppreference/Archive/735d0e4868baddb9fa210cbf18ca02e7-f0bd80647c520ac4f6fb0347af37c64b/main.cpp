#include <type_traits>
#include <vector>
#include <memory>

static_assert(std::is_copy_constructible<std::vector<std::unique_ptr<void>>>(), ":(");

int main() {}
