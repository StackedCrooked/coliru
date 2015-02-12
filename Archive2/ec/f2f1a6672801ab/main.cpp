#include <iostream>

namespace detail {

    template <typename T>
    class moveable {
        // No copy constructor, and the move constructor will be 
        // defined as deleted if T doesn't have a move ctor
        struct Test : T { Test(Test&&) = default; };
    	
        // Can only be moved.
    	template <typename U>
    	static auto f(int) -> decltype(U(std::move(std::declval<U>())), 0) {}
        template <typename>
        static void f(...) {}
    	
    public:
    
    	static auto constexpr value = std::is_same<decltype(f<Test>(0)), int>{};
    };
}

// TODO: Implement unions
template <typename T>
using is_moveable = std::integral_constant<bool, 
    std::conditional_t<std::is_class<T>{}, detail::moveable<T>, std::is_arithmetic<T>>::value>;

class Moveable {};
class NotMoveable {NotMoveable(NotMoveable&&) = delete;};

static_assert( is_moveable<Moveable>::value, "" );
static_assert( !is_moveable<NotMoveable>::value, "" );
static_assert( is_moveable<int>::value, "" );
static_assert( !is_moveable<void>::value, "" );

int main() {}