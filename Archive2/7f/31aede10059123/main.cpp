#include <utility>
#include <type_traits>
#include <iostream>

namespace unittest_op {
    class access {
        template<typename T, typename Enable = void> class impl;

        template<typename T>
            class impl<T, typename std::enable_if<std::is_arithmetic<T>::value, void>::type>
        {
          public: typedef T result_type;
            static T            & call(T& v) { return v; }
            static T const& call(T const& v) { return v; }
        };

      public:
        template<typename T>
        static typename impl<T>::result_type do_access(T const& v) { return impl<T>::call(v); }

        template<typename T> static constexpr bool can_access(decltype(do_access(std::declval<T>()))*) { return true; }
        template<typename T> static constexpr bool can_access(...) { return false; }
    };

    template<typename T>
        typename std::enable_if<access::can_access<T>(nullptr) && not std::is_arithmetic<T>::value, std::ostream&>::type
            operator<<(std::ostream& os, T const& v) { return os << "{" << access::do_access(v) << "}"; }

    template <typename T, typename Enable=decltype(access::do_access(std::declval<T>())) >
        static T operator-(T const& lhs) { return - access::do_access(lhs); }

    template <typename T, typename Enable=decltype(access::do_access(std::declval<T>())) >
        static T operator+(T const& lhs) { return + access::do_access(lhs); }

#define UNITTEST_OP_BINOP(OP) \
    template <typename T1, typename T2> \
        static decltype(access::do_access(std::declval<T1>()) OP access::do_access(std::declval<T2>()))  \
            operator OP(T1 const& lhs, T2 const& rhs) { return access::do_access(lhs) OP access::do_access(rhs); } \
    using ::unittest_op::operator OP;

    UNITTEST_OP_BINOP(==)
    UNITTEST_OP_BINOP(!=)

    UNITTEST_OP_BINOP(< )
    UNITTEST_OP_BINOP(> )
    UNITTEST_OP_BINOP(<=)
    UNITTEST_OP_BINOP(>=)

    UNITTEST_OP_BINOP(+ )
    UNITTEST_OP_BINOP(- )
    UNITTEST_OP_BINOP(% )
    UNITTEST_OP_BINOP(* )
    UNITTEST_OP_BINOP(/ )

    // assign-ops only for lvalue types (i.e. identity `access::impl<T>`)
    UNITTEST_OP_BINOP(+=)
    UNITTEST_OP_BINOP(-=)
    UNITTEST_OP_BINOP(%=)
    UNITTEST_OP_BINOP(*=)
    UNITTEST_OP_BINOP(/=)

#undef UNITTEST_OP_BINOP
}

namespace boost { namespace test_tools {

    using unittest_op::operator ==;
    using unittest_op::operator !=;

    using unittest_op::operator < ;
    using unittest_op::operator > ;
    using unittest_op::operator <=;
    using unittest_op::operator >=;

    using unittest_op::operator + ;
    using unittest_op::operator - ;
    using unittest_op::operator % ;
    using unittest_op::operator * ;
    using unittest_op::operator / ;

    using unittest_op::operator +=;
    using unittest_op::operator -=;
    using unittest_op::operator %=;
    using unittest_op::operator *=;
    using unittest_op::operator /=;

    using unittest_op::operator <<;

} }

class MyTypeWithDouble
{
    public:
      constexpr MyTypeWithDouble(double v = 0) : m(v) {}
      MyTypeWithDouble& operator=(MyTypeWithDouble const&) noexcept = default;
      constexpr MyTypeWithDouble(MyTypeWithDouble const&) noexcept = default;
    private:
      friend class unittest_op::access;
      double m;
};

namespace unittest_op {
    template<> class access::impl<MyTypeWithDouble> {
      public:
        typedef double result_type;
        static result_type call(MyTypeWithDouble const& v) { return v.m; }
    };
}

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(my_test)
{
    MyTypeWithDouble v(4);

    BOOST_CHECK_CLOSE(3.99, v, MyTypeWithDouble(0.1));
}

BOOST_AUTO_TEST_CASE(general_operator_invocations) // just a testbed to see the overloads are found and compile
{
    MyTypeWithDouble v(4);

    using namespace unittest_op; // we're not using the test_tools here

    BOOST_CHECK(4.00000000000000001 == v);
    BOOST_CHECK(4.000000000000001   != v);

#define UNITTEST_OP_BINOP(OP) { \
    auto x = v OP static_cast<MyTypeWithDouble>(0.01); \
    x = static_cast<MyTypeWithDouble>(0.01) OP v; \
    x = v OP v; \
    (void) x; \
}

    UNITTEST_OP_BINOP(==)
    UNITTEST_OP_BINOP(!=)
    UNITTEST_OP_BINOP(+ )
    UNITTEST_OP_BINOP(- )
    //UNITTEST_OP_BINOP(% )
    UNITTEST_OP_BINOP(* )
    UNITTEST_OP_BINOP(/ )

    UNITTEST_OP_BINOP(< )
    UNITTEST_OP_BINOP(> )
    UNITTEST_OP_BINOP(<=)
    UNITTEST_OP_BINOP(>=)

    -v == -v;
    +v == +v;
}
