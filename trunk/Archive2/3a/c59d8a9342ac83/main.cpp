#include <type_traits>

template<typename ComponentType = int>
struct baz {
    template<typename T, typename std::enable_if<std::is_convertible<ComponentType, T>::value>::type>
    operator baz<T>() {
        return {};
    }
};

int main() {
    baz<> b = baz<float>();
}
