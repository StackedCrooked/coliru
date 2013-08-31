#include <type_traits>

template<class U, class S,
    typename std::enable_if<std::is_unsigned<U>::value &&
                            std::is_signed  <S>::value
        >::type* = nullptr>
inline U add(U a, S b)
{
    return a + b;
}

int main(int argc, const char * argv[], const char * envp[])
{
    unsigned int ui = 0;
    int i = 0;
    auto a = add(ui, i);
    static_assert(std::is_same<decltype(a), unsigned int>::value, "!");
    return 0;
}
