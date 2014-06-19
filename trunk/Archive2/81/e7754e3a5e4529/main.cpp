#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
class remove_pointer_ {
    template <typename U>
    struct helper {
        typedef U type;
    };

    template <typename U>
    using pointee = typename std::remove_reference<decltype(*std::declval<U>())>::type;

    template <typename U = T>
    static helper<pointee<U>> is_pointer(int);

    static helper<T> is_pointer(...);

  public:
    typedef typename decltype(is_pointer(0))::type type;
};

template <typename T>
using remove_pointer = typename remove_pointer_<T>::type;

int main() {
    static_assert(std::is_same<int,remove_pointer<int*>>::value, "");
    static_assert(std::is_same<int,remove_pointer<int>>::value, "");
    static_assert(std::is_same<int,remove_pointer<std::unique_ptr<int>>>::value, "");
    static_assert(std::is_same<int,remove_pointer<std::shared_ptr<int>>>::value, "");
    static_assert(std::is_same<int[1],remove_pointer<int(*)[1]>>::value, "");
    static_assert(std::is_same<void(),remove_pointer<void(*)()>>::value, "");
}
