
struct A {
    template <typename T>
    void operator=(T&&) && = delete; // no op= for rvalues

    // generate other special members normally
    A() = default;
    A(A const&) = default;
    A(A&&) = default;
    ~A() = default;
    // op= only for lvalues
    A& operator=(A&&) & = default;
    A& operator=(A const&) & = default;
};

int main() {
 A a;
 a = A(); // fine
 //A() = A(); // error
 return 0; 
}

// Coliru does not have clang properly configured with a standard library so I need
// to reinvent std::is_assignable to write some assertions... :(
namespace my {
    template <typename T> T&& declval();
    template <bool B, typename... Dummies>
    struct bool_ { constexpr operator bool() const { return B; } };

    struct is_assignable_test {
        template <typename T, typename U>
        bool_<true, decltype(declval<T>() = declval<U>())> static test(int);
        template <typename...>
        bool_<false> static test(...);
    };
    template <typename T, typename U>
    struct is_assignable : decltype(is_assignable_test::test<T, U>(0)) {};
}

static_assert(my::is_assignable<A&, A&>(), "can assign A lvalues to A lvalues");
static_assert(my::is_assignable<A&, A&&>(), "can assign A rvalues to A lvalues");
static_assert(not my::is_assignable<A&&, A&>(), "cannot assign A lvalues to A rvalues");
static_assert(not my::is_assignable<A&&, A&&>(), "cannot assign A lvalues to A rvalues");
