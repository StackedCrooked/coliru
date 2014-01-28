#include <type_traits>

template <class T>
struct __has_allocate
{
private:
    template <class U> static std::false_type test(...);
    template <class U> static std::true_type test(decltype(std::declval<U>().allocate(0)));
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

#include <memory>

static_assert(!__has_allocate<int>::value, "int has allocate?!?");
static_assert(__has_allocate<std::allocator<int>>::value, "std::allocator<int> has allocate.");
