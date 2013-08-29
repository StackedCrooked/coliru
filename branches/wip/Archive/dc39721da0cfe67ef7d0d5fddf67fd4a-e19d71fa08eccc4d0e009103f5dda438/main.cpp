#include <boost/operators.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <cxxabi.h>


std::string demangle(const char * name);


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vec)
{
    os << "(";
    for (typename std::vector<T>::size_type idx = 0; idx != vec.size(); ++idx)
    {
        if (idx != 0)
        {
            os << " ";
        }
        os << vec[idx];
    }
    return os << ")";
}


std::stringstream ss;
template<unsigned N>
struct apply_tuple : apply_tuple<N - 1>
{
    template<typename F, typename ...Args>
    apply_tuple(const F & f, const std::tuple<Args...> & tup) : apply_tuple<N - 1>(f, tup)
    {
        enum { index = N - 1 };
        f(std::get<index>(tup));
    }
};

template<>
struct apply_tuple<0u>
{
    template<typename ...Args>
    apply_tuple(Args && ...) {}
};


struct print
{
    print(std::ostream & os) : os(os) {}
    
    template<typename T>
    void operator()(const T & t) const
    {
        os << "(" << demangle(typeid(T).name()) << " " << t << ") ";
    }
        
    std::ostream & os;
};


template<typename ...Tail>
std::ostream& operator<<(std::ostream& os, const std::tuple<Tail...> & tuple)
{
    apply_tuple<sizeof...(Tail)>(print(os), tuple);
    return os;
}


#define STRONG_TYPEDEF(T, Name) \
    struct Name : boost::operators<Name> { \
        Name() : t() {} \
        explicit Name(const T & t_) : t(t_) {} \
        operator const T & () const { return t; } \
        operator T & () { return t; } \
        bool operator==(const Name & rhs) const { return t == rhs.t; } \
        bool operator<(const Name & rhs) const { return t < rhs.t; } \
        T t; \
    }; \
    std::ostream& operator<<(std::ostream& os, const Name & name) { \
        return os << static_cast<T>(name); \
    }


template<typename>
struct Signature {};


template<typename T>
using Increment = Signature<T(const T&)>;


template<typename T>
using Sum = Signature<T(const T&, const T&)>;



STRONG_TYPEDEF(std::string, PersonId)
STRONG_TYPEDEF(std::string, FirstName)
STRONG_TYPEDEF(std::string, LastName)
STRONG_TYPEDEF(std::string, Address)
STRONG_TYPEDEF(std::string, Birthday)
STRONG_TYPEDEF(std::vector<PersonId>, Parents)
STRONG_TYPEDEF(std::vector<PersonId>, Children)


using Person = std::tuple<PersonId, FirstName, LastName, Address, Birthday, Children>;


std::string demangle(const char * name)
{
    int st;
    std::unique_ptr<char, decltype(&std::free)> p(abi::__cxa_demangle(name, 0, 0, &st), std::free);
    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }
    return std::string(p.get());
}


int main()
{    
    Person person(PersonId("1"), FirstName("John"), LastName("Smith"), Address("Sea"), Birthday("Easter"), Children({PersonId("2"), PersonId("3")}));
    std::cout << "Person: " << person << std::endl;
    std::cout << ss.str() << std::endl;
}
