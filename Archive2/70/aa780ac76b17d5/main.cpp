#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
class remove_pointer_ {
    template <typename U=T>
    static auto test(int) -> std::remove_reference<decltype(*std::declval<U>())>;
    static auto test(...) -> std::remove_cv<T>;

public:
    using type = typename decltype(test(0))::type;
};

template <typename T>
using remove_pointer = typename remove_pointer_<T>::type;

int main() {
    static_assert(std::is_same<int,remove_pointer<int*>>::value, "");
    static_assert(std::is_same<int,remove_pointer<int* const volatile>>::value, "");
    static_assert(std::is_same<int,remove_pointer<int>>::value, "");
    static_assert(std::is_same<int,remove_pointer<std::unique_ptr<int>>>::value, "");
    static_assert(std::is_same<int,remove_pointer<std::shared_ptr<int>>>::value, "");
    static_assert(std::is_same<int[1],remove_pointer<int(*)[1]>>::value, "");
    static_assert(std::is_same<int(int),remove_pointer<int(*)(int)>>::value, "");
    static_assert(std::is_same<int(&(int))[1],remove_pointer<int(&(*)(int))[1]>>::value, "");
}
