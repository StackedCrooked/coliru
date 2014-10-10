#include <type_traits>
#include <memory>

template <typename T>
class Foo
{
    void Release(std::true_type)
    {
        using U = typename std::remove_extent<T>::type;
        for (auto i = std::extent<T>::value; i-- > 0;) {
            reinterpret_cast<T&>(store)[i].~U();
        }
    }

    void Release(std::false_type)
    {
        reinterpret_cast<T&>(store).~T();
    }

public:
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type store;

    template <typename... Args>
    Foo(Args&&... args)
    {
        new (&store) T { std::forward<Args>(args)... };
    }

    void Release()
    {
        Release(std::is_array<T>());
    }
};

int main() {
    Foo<int[3]>{};
}
