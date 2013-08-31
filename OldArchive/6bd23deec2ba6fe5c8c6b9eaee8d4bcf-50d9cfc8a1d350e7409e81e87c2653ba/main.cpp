#include <type_traits>

  template<typename Base, typename Class> struct is_base_of
  {
    static void foo(Base*);
    template<class F>
    static auto test(int) -> decltype(foo(std::declval<F*>()), std::true_type{});
    template<class>
    static auto test(...) -> std::false_type;

    static constexpr bool value = decltype(test<Class>(0))();
    constexpr operator bool() { return value; }
  };

class A {};
class B : private A {};
class C : virtual A {};

static_assert(std::is_base_of<B,A>(), "B is a private base of A");
static_assert(std::is_base_of<C,A>(), "C is a virtual base of A");

static_assert(is_base_of<B,A>(), "B is a private base of A");
static_assert(is_base_of<C,A>(), "C is a virtual base of A");

int main(){}
