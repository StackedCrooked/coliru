#include <iostream>
#include <type_traits>

    template <typename T>
    class HasValidLifetime final {
      private:
        /* Differently sized types represent Yes/No. */
        using Yes = uint8_t;
        using No = uint16_t;
        static_assert(sizeof(Yes) != sizeof(No), "Yes and No must be different");

        /* If T has a member named 'm_lifetime', there will be an ambiguity
         * here that will cause problems later. We'll take advantage of this. */
        struct Base
        { int m_lifetime; };
        struct Derived : T, Base
        { };

        /* M::m_lifetime will be a controlled ambiguity if M has two members,
         * causing substitution to fail here. We'll instead go to the Yes func. */
        template <typename M>
        static No& test(decltype(M::m_lifetime) const * const);
        template <typename M>
        static Yes& test(...);

      public:
        static bool constexpr const value
        { sizeof(test<Derived>(nullptr)) == sizeof(Yes) };
        static bool constexpr const multiple
        { value && (sizeof(test<T>(nullptr)) == sizeof(Yes)) };
    }; 

struct test1
{ int m_lifetime{}; };
struct test2
{};

struct base
{ int m_lifetime{}; };
struct derived : public base
{ int m_lifetime{}; };

int main() 
{
    std::cout << "test1: (" << HasValidLifetime<test1>::value << " "
              << HasValidLifetime<test1>::multiple << ")" << std::endl;
    std::cout << "test2: (" << HasValidLifetime<test2>::value << " "
              << HasValidLifetime<test2>::multiple << ")" << std::endl;
    std::cout << "derived: (" << HasValidLifetime<derived>::value << " "
              << HasValidLifetime<derived>::multiple << ")" << std::endl;  
}
