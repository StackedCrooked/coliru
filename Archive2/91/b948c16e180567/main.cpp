#include <memory>
#include <type_traits>
#include <unordered_map>

template<typename T>
class Container {
    T t;
public:
    Container() = default;
    ~Container() = default;
    
    template<typename U = T>
    Container(Container&& other) : t(std::move(other.t)) {}

    template<typename U = T>
    Container(const Container& other) : t(other.t) {}
};

static_assert(std::is_copy_constructible<Container<int>>::value, "Non-Copyable");
static_assert(!std::is_copy_constructible<Container<std::unique_ptr<int>>>::value, "Copyable");

Container<std::unique_ptr<int>> makeNonCopyableContainer() {
    return Container<std::unique_ptr<int>>();
}

int main () { 
    Container<int> c1;
    Container<int> c2(c1);
    Container<std::unique_ptr<int>> c3;
    // This would give compile error:
    // Container<std::unique_ptr<int>> c4(c3);
    Container<std::unique_ptr<int>> c5(makeNonCopyableContainer());
    return 0;
}