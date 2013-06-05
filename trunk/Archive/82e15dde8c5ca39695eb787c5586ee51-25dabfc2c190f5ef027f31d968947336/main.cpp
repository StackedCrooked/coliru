#include <type_traits>
#include <memory>

static_assert(std::is_same<
    std::remove_reference<std::unique_ptr<int>&>::type, 
    std::unique_ptr<int>>::value, "!");
    
int main() { }