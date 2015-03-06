#include <vector>

template<typename Container>
struct container_type_aliases {
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;
    
protected:
    ~container_type_aliases() = default;
};

struct MyContainer : container_type_aliases<std::vector<int>> {
    reference foo();
};

int main() {
    
}