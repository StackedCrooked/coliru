#ifndef EXERCISE_2_1
#define EXERCISE_2_1

#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/type_traits/is_same.hpp>

#include <type_traits>

template <typename C, typename X, typename Y>
struct replace_type
{
    typedef C type;
    // If we missed a case, this should give an error about no "type"
};

template <typename C, typename X, typename Y, bool Same>
struct replace_type_dispatch
{
    // Really a forward declaration. "Same" specifications are given below.
};

template <typename C, typename Y>
struct replace_type<C, C, Y>
{
    typedef Y type;
};

template <typename C, typename X, typename Y>
struct replace_type<C*, X, Y>
{
    typedef
    typename boost::add_pointer<
    typename replace_type_dispatch<
    C,
    X,
    Y,
    boost::is_same<C, X>::value
    >::type
    >::type
    type;
};

template <typename C, typename X, typename Y>
struct replace_type<C&, X, Y>
{
    typedef
    typename boost::add_reference<
    typename replace_type_dispatch<
    C,
    X,
    Y,
    boost::is_same<C, X>::value
    >::type
    >::type
    type;
};

template <typename C, typename X, typename Y, size_t N>
struct replace_type<C[N], X, Y>
{
    typedef
    typename replace_type_dispatch<
    C,
    X,
    Y,
    boost::is_same<C, X>::value
    >::type
    type [N];
};

// Going to get tedious for multiple arguments... Could variadic templates help
// here?
template <typename Cr, typename X, typename Y>
struct replace_type<Cr(*)(), X, Y>
{
    typedef
    typename replace_type_dispatch<
    Cr,
    X,
    Y,
    boost::is_same<Cr, X>::value
    >::type
    (*type)();
};
template <typename Cr, typename C0, typename X, typename Y>
struct replace_type<Cr(*)(C0), X, Y>
{
    typedef
    typename replace_type_dispatch<
    Cr,
    X,
    Y,
    boost::is_same<Cr, X>::value
    >::type
    (*type)(
        typename replace_type_dispatch<
        C0,
        X,
        Y,
        boost::is_same<C0, X>::value
        >::type
    );
};
template <typename Cr, typename C0, typename C1, typename X, typename Y>
struct replace_type<Cr(*)(C0,C1), X, Y>
{
    typedef
    typename replace_type_dispatch<
    Cr,
    X,
    Y,
    boost::is_same<Cr, X>::value
    >::type
    (*type)(
        typename replace_type_dispatch<
        C0,
        X,
        Y,
        boost::is_same<C0, X>::value
        >::type,
        typename replace_type_dispatch<
        C1,
        X,
        Y,
        boost::is_same<C1, X>::value
        >::type
    );
};

template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, true>
{
    typedef Y type;
};
template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, false>
{
    typedef typename replace_type<C, X, Y>::type type;
};

namespace My
{
    template <typename T, typename From, typename To>
    struct ReplaceType
    {
        using type = typename std::conditional<std::is_same<T, From>::value,
        To, T>::type;
    };

    template <typename T, typename To>
    struct ReplaceType<const T, T, To>
    {
        using type = const To;
    };

    template <typename T, typename To>
    struct ReplaceType<T &, T, To>
    {
        using type = To &;
    };

    template <typename T, typename To>
    struct ReplaceType<const T &, T, To>
    {
        using type = const To &;
    };
}

#endif // EXERCISE_2_1


# include <type_traits>


namespace My
{
template <typename T>
struct AddConstReference
{
    using type = typename std::add_lvalue_reference<
    typename std::add_const<T>::type>::type;
};

template <typename T>
struct AddConstReferenceCustom
{
    using type = const T &;
};

template <typename T>
struct AddConstReferenceCustom<T &>
{
    using type = T &;
};

}


# include <type_traits>
# include <string>
# include <istream>


namespace My
{
template <typename T>
struct TypeDescriptor
{
    // empty general case!
};

template <>
struct TypeDescriptor<char>
{
    static std::string value() {
        return "char";
    }
};

template <>
struct TypeDescriptor<short>
{
    static std::string value() {
        return "short";
    }
};

template <>
struct TypeDescriptor<int>
{
    static std::string value() {
        return "int";
    }
};

template <>
struct TypeDescriptor<long>
{
    static std::string value() {
        return "long";
    }
};

template <typename T>
struct TypeDescriptor<T &>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " &";
    }
};

template <typename T>
struct TypeDescriptor<const T>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " const";
    }
};

template <typename T>
struct TypeDescriptor<volatile T>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " volatile";
    }
};

template <typename T>
struct TypeDescriptor<volatile const T>
{
    static std::string value() {
        return TypeDescriptor<volatile T>::value() + " const";
    }
};

template <typename T>
struct TypeDescriptor<T *>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " *";
    }
};

template <typename T, std::size_t N>
struct TypeDescriptor<T[N]>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " [" + std::to_string(N) + ']';
    }
};

template <typename T>
struct TypeDescriptor<T[]>
{
    static std::string value() {
        return TypeDescriptor<T>::value() + " []";
    }
};

}


template <typename T>
std::ostream & operator<<(std::ostream & is, My::TypeDescriptor<T>) {
    return is << My::TypeDescriptor<T>::value();
}




# include <iostream>


template <typename T>
void print(T t)
{
    std::cout << t << std::endl;
}

template <typename T, typename ... Args>
void print(T t, Args ... args)
{
    std::cout << t << "|";
    print(args ...);
}


int main(/*int argc, char * argv[]*/)
{
    using namespace My;
    using T =  char ;
    std::cout << std::boolalpha << std::is_same<AddConstReference<T>::type,
        AddConstReferenceCustom<T>::type>::value
        << std::endl;

    std::cout << std::boolalpha << std::is_same<const double &,
        AddConstReferenceCustom< double const &>::type>::value
        << std::endl;
    using U = int&;
    std::cout << std::is_same<U, ReplaceType< T , T, U>::type>::value << std::endl;


    std::cout << std::is_same<replace_type< const int, int, double>::type,
        const int>::value << std::endl;

//??<
const char * c = ":<??<";
//??/
std::cout << c << std::endl;
    print(TypeDescriptor<int volatile const * volatile * const volatile>(), TypeDescriptor<short>(), TypeDescriptor<int>(),
        TypeDescriptor< const char**const*[][2][5]>(), TypeDescriptor<long&>()
    );
}
