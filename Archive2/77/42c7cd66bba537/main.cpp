#include <memory>
#include <type_traits>
#include <unordered_map>

static_assert(!std::is_copy_constructible<std::unordered_map<int,std::unique_ptr<int>>>::value,"Copyable");

int main () {   }