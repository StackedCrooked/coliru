#include <iostream>
#include <type_traits>
 
namespace bw
{
    struct __static_castable
    {
        template<typename Src, typename Dest,
            typename = decltype(
                static_cast<Dest>(
                std::declval<Src>()))>
        static char __test(int);
 
        template<typename, typename>
        static int __test(...);
    };
 
    struct __has_equal_operator_impl
    {
        template<typename TA, typename TB>
        using __implicit_conv =
            decltype(
                __static_castable::__test<
                    decltype(
                        std::declval<TA>()
                     == std::declval<TB>()
                ), bool>(0)
            );
 
        template<typename TA, typename TB,
            typename = decltype(
                std::declval<TA>()
             == std::declval<TB>())>
        static __implicit_conv<TA, TB> __test(int);
 
        template<typename, typename>
        static int __test(...);
    };
 
    template<typename A, typename B>
    using has_equal_operator = std::is_same<char,
        decltype(__has_equal_operator_impl::__test<A, B>(0))>;
}
 
template<typename A, typename B>
void output_result()
{
    std::cout << std::boolalpha
        << bw::has_equal_operator<A, B>::value << std::endl;
}
 
struct A;
struct B;
struct C;
struct D
{
    operator bool();
};
bool operator == (const A&, const B&);
A operator == (const A&, const C&);
D operator == (const B&, const C&);
 
int main()
{
    // true，因为重载有 operator == (const A&, const B&)
    output_result<A, B>();
    // false，因为没有重载 operator == (const B&, const A&)
    output_result<B, A>();
    // false，因为 A() == C() 返回值类型是 A，A 无法转换为 bool
    output_result<A, C>();
    // true，因为返回类型 D 可以转换为 bool
    output_result<B, C>();
    // true
    output_result<int, int>();
    // true
    output_result<double, int>();
    // false
    output_result<void, int>();
    // false
    output_result<decltype(std::cout), int>();
    return 0;
}