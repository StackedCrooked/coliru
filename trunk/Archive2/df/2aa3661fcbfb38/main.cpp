#include <type_traits>
#include <utility>

namespace xxx
{
    using std::swap;

    template<class T, class U>
    auto adl_swap(T& t, U& u) noexcept(noexcept(swap(t, u)))
    {
        return swap(t, u);
    }
}

struct X;
void swap(X&, X&) noexcept;

struct Y
{
    Y(Y&&) noexcept;
    Y& operator =(Y&&) noexcept;
};

struct Z
{
    Z(Z const&);
    Z& operator =(Z const&);
};

int main()
{
    using xxx::adl_swap;
    
    static_assert( noexcept(adl_swap(std::declval<X&>(), std::declval<X&>())), "" );
    static_assert( noexcept(adl_swap(std::declval<Y&>(), std::declval<Y&>())), "" );
    static_assert(!noexcept(adl_swap(std::declval<Z&>(), std::declval<Z&>())), "" );
}
