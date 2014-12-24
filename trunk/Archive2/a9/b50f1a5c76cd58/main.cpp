#include <iostream>
#include <type_traits>

template <class Type>
class my_traits
{
    //! Implements a type for "true"
    typedef struct { char value;    } true_class;
    //! Implements a type for "false"
    typedef struct { char value[2]; } false_class;

    //! This handy macro generates actual SFINAE class members for checking event callbacks
    #define MAKE_MEMBER(X) \
        public: \
            template <class T> \
            static true_class has_##X(decltype(&T::X)); \
        \
            template <class T> \
            static false_class has_##X(...); \
        public: \
            static constexpr bool call_##X = sizeof(has_##X<Type>(0)) == sizeof(true_class);

    MAKE_MEMBER(open_file)

public:

    /* SFINAE foo-has-correct-sig :) */
    template<class A>
    static std::true_type test(void (A::*)(int) const)
    {
        return std::true_type();
    }

    /* SFINAE game over :( */
    template<class A>
    static std::false_type test(...)
    {
        return std::false_type();
    }

    /* SFINAE foo-exists :) */
    template <class A>
    static decltype(test(&A::open_file)) test(decltype(&A::open_file), void *)
    {
        /* foo exists. What about sig? */
        typedef decltype(test(&A::open_file)) return_type;
        return return_type();
    }

    /* SFINAE foo-not-exists */
    template <class A>
    static std::false_type test(void*, ...)
    {
        return {};
    }

    /* This will be either `std::true_type` or `std::false_type` */
    typedef decltype(test<Type>(0, 0)) type;

    static const bool value = type::value; /* Which is it? */

    /*  `eval(T const &,std::true_type)`
     delegates to `T::foo()` when `type` == `std::true_type`
     */
    static void eval(Type const & t, std::true_type)
    {
        t.open_file(1);
    }
    /* `eval(...)` is a no-op for otherwise unmatched arguments */
    static void eval(...)
    {
        // This output for demo purposes. Delete
        std::cout << "open_file() not called" << std::endl;
    }

    /* `eval(T const & t)` delegates to :-
     - `eval(t,type()` when `type` == `std::true_type`
     - `eval(...)` otherwise
     */
    static void eval(Type const &t)
    {
        eval(t, type());
    }

};

class does_match
{
public:
    void open_file(int i) const { std::cout << "MATCHES!" << std::endl; };
};

class doesnt_match
{
public:
    void open_file() const { std::cout << "DOESN'T!" << std::endl; };
};

int main()
{
    does_match   it_does;
    doesnt_match it_doesnt;

    my_traits<decltype(it_does)>::eval(it_does);
    my_traits<decltype(it_doesnt)>::eval(it_doesnt);
}
