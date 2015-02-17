#include <vector>
#include <memory>
#include <algorithm>

template<typename T, typename Container>
auto any_of_type(Container&& container) -> bool {
    return std::any_of(
        std::forward<Container&&>(container).begin(),
        std::forward<Container&&>(container).end(),
        [](typename Container::value_type&& value) -> bool {
            return dynamic_cast<T*>(value.get()) != nullptr;
        });
}

int main() {
}
