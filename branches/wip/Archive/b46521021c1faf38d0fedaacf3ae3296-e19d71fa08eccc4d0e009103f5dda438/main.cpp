#include <boost/operators.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vec)
{
    for (const auto & t : vec) os << vec << " ";
    return os;
}


template<unsigned N>
struct apply_tuple : apply_tuple<N - 1>
{
    template<typename F, typename ...Args>
    apply_tuple(const F & f, const std::tuple<Args...> & tup) : apply_tuple<N - 1>(f, tup)
    {
        enum { index = sizeof...(Args) - N };
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
    print(std::ostream & os) : osp(&os) {}
    
    template<typename T>
    void operator()(const T & t) const
    {
        (*osp) << t;
    }
        
    std::ostream * osp;
};


template<typename ...Tail>
std::ostream& operator<<(std::ostream& os, const std::tuple<Tail...> & tuple)
{
    apply_tuple<sizeof...(Tail)>(print(os), tuple);
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


using Person = std::tuple<PersonId, FirstName, LastName, Address, Birthday, Parents, Children>;



template<typename T>
void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    check<Person>();
    
    Person person(PersonId(), FirstName("John"), LastName("Smith"), Address(), Birthday(), Parents(), Children());
    std::cout << "Person: " << person << std::endl;
    
}