#include <boost/lexical_cast.hpp>
#include <boost/operators.hpp>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <typeinfo>
#include <cxxabi.h>


template<typename To, typename From>
To cast(const std::string & loc, const From & from)
{
    std::cout << "cast: " << loc << ": " << std::flush;
    return boost::lexical_cast<To>(from);
}


#define LOC (std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": ")
#define TRACE std::cout << LOC << std::endl;
std::string demangle(const char * name)
{
    int st;
    std::unique_ptr<char, decltype(&std::free)> p(abi::__cxa_demangle(name, 0, 0, &st), &std::free);
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


std::string join(const std::string & head)
{
    return head;
}

template<typename ...T>
std::string join(const std::string & head, T && ...tail)
{
    return head + ", " + join(std::forward<T>(tail)...);
}


template<unsigned N>
struct Helper;


template<>
struct Helper<0>
{
    template<typename ...T>
    Helper<0>(T && ...)
    {
        std::cout << "Helper<0>: T&&= " << join(demangle(typeid(T).name())...) << std::endl;
    }
};

template<unsigned N>
struct Helper : Helper<N - 1>
{
    enum
    {
        TupleIndex = N - 1
    };
    
    template<typename F, typename ...T>
    Helper(const F & f, std::tuple<T...> & tup) : Helper<N - 1>(f, tup)
    {
        f(std::get<TupleIndex>(tup));
    }
    
    template<typename F, typename ...T>
    Helper(const F & f, const std::tuple<T...> & tup) : Helper<N - 1>(f, tup)
    {
        f(std::get<TupleIndex>(tup));
    }
};


std::string Serialize(const std::string & str)
{
    std::cout << "Serialize string" << std::endl;
    return str;
}


std::string Serialize(int n)
{
    std::cout << "Serialize int:" << std::flush;
    std::string result = std::to_string(n);
    std::cout << result << std::endl;
    return result;
}


struct Serializer
{
    std::string & result;
    
    Serializer(std::string & result) : result(result) {}
    
    template<typename T>
    void operator()(const T & t) const
    {
        result += Serialize(t) + ' ';
    }
};


template<typename ...T>
std::string Serialize(const std::tuple<T...> & tup)
{
    enum { N = sizeof...(T) };
    std::string result;
    Serializer serializer(result);
    Helper<N> helper(serializer, tup);
    return result;
}



struct DeserializeHelper
{
    mutable std::istringstream ss;
    
    DeserializeHelper(std::string s) : ss(s) {}
    
    template<typename U>
    void operator()(U & u) const
    {
        TRACE
        std::string s;
        ss >> s;
        u = cast<U>(LOC, s);
    }
};


void DeserializeImpl(std::string s, std::string & x)
{
    x = s;
}


void DeserializeImpl(std::string s, int & x)
{
    x = cast<int>(LOC, s);
}


template<typename ...T>
void DeserializeImpl(std::string s, std::tuple<T...> & t)
{
    DeserializeHelper d(s);
    Helper<sizeof...(T)>(d, t);
}


template<typename T>
T Deserialize(std::string s)
{
    T t;
    DeserializeImpl(s, t);
    return t;
}


inline void test_serialize()
{
//    std::cout << LOC << Serialize(1) << std::endl << std::endl;
//    std::cout << LOC << Serialize(std::make_tuple(1, 2)) << std::endl << std::endl;    
//    std::cout << LOC << Serialize(std::string("hello")) << std::endl << std::endl;
    
    typedef std::tuple<int, std::string> Tup;
    Tup tup(1, std::string("hello"));
    std::string serialized_tuple = Serialize(tup);
    std::cout << LOC << serialized_tuple << std::endl << std::endl;
    
    Tup copy = Deserialize<Tup>(serialized_tuple);
    assert(tup == copy);
    std::cout << "YAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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
    }


#if 0

//
//
//typedef std::tuple<std::string, std::string> NameAndBody;
//
//
//struct Server
//{
//    std::string accept(const std::string & msg)
//    {
//        std::istringstream iss(msg);
//        NameAndBody nb = Deserialize<NameAndBody>(iss);
//        return dispatch(std::get<0>(nb), std::get<1>(nb));
//    }
//    
//private:
//    std::string dispatch(const std::string & name, const std::string & body)
//    {
//        auto it = mDispatchers.find(name);
//        if (it == mDispatchers.end())
//        {
//            throw std::runtime_error("Dispatcher not found: " + name);
//        }
//        
//        return it->second(body);
//    }
//    
//    typedef std::function<std::string(const std::string&)> Dispatcher;
//    typedef std::map<std::string, Dispatcher> Dispatchers;
//    Dispatchers mDispatchers;
//};
//
//
//struct Client
//{
//    typedef std::function<std::string(const std::string &)> SendFunction;
//    
//    Client(const SendFunction & inSendFunction) : mSendFunction(inSendFunction) {}
//    
//    template<typename F, typename ...Args>
//    typename F::result_type send(Args && ...args)
//    {
//        return do_send<F>(std::make_tuple(std::forward<Args>(args)...));
//    }
//    
//private:
//    template<typename F, typename ...Args>
//    typename F::result_type do_send(const std::tuple<Args...> & arg)
//    {
//        std::string serialized_request = Serialize(arg);
//        std::string serialized_result = mSendFunction(serialized_request);
//        std::istringstream iss(serialized_result);
//        return Deserialize<typename F::result_type>(iss);
//    }
//    
//    SendFunction mSendFunction;
//};
//    
//
//STRONG_TYPEDEF(int, X);
//STRONG_TYPEDEF(int, Y);
//
//
//struct Point : std::tuple<X, Y>
//{
//    Point() {}
//    Point(const X & x, const Y & y) : std::tuple<X, Y>(x, y) {}
//    
//    const X & getX() const { return std::get<0>(*this); }
//    
//    const Y & getY() const { return std::get<1>(*this); }
//};
//
//
//STRONG_TYPEDEF(Point, P1);
//STRONG_TYPEDEF(Point, P2);
//
//
//typedef std::function<int(P1, P2)> Distance;
#endif


int main()
{
    test_serialize();
//    Server server;
    
//    Client client([&server](const std::string & msg) -> std::string {
//        return server.accept(msg);
//    });
//    
//    Point p1 { X{0}, Y{0} };
//    Point p2 { X{1}, Y{1} };
//    std::cout << "Distance is: " << client.send<Distance>(p1, p2) << std::endl;
    std::cout << "End of program." << std::endl;
}
