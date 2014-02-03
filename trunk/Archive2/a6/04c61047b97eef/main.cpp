struct A
{
    alignas(2) char byte;
};

#include <type_traits>

int main()
{
    static_assert(std::is_standard_layout<A>::value, "is not standard-layout");
    static_assert(sizeof(A) == sizeof(A::byte), "is not the same size as its member");
}