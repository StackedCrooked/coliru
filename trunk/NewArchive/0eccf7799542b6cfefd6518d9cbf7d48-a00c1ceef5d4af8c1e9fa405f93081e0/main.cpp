#include <type_traits>
#include <vector>
#include <memory>

static_assert(std::is_constructible<std::vector<std::unique_ptr<void>>>(), ":(");

int main() {}
