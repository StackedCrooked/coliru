#include <boost/operators.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <typeinfo>
#include <cxxabi.h>

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
    template<typename F, typename ...T>
    Helper(std::ostream & os, F f, const std::tuple<T...> & tup) : Helper<N - 1>(os, f, tup)
    {
        enum
        {
            index = N - 1
        };
        std::cout << "Helper<" << N << "> " << ", Index=" << index << ", F=" << demangle(typeid(f).name()) << ", Tup=" << demangle(typeid(tup).name()) << std::endl;
        os << f(std::get<index>(tup)) << (index ? "" : " ");
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
    template<typename T>
    std::string operator()(const T & t) const
    {
        std::cout << "Serializer::operator()<const " << demangle(typeid(T).name()) << "&>" << std::endl;
        return Serialize(t);
    }
    
    template<typename ...T>
    std::string operator()(T && ...t) const
    {
        std::cout << "Serializer::operator()< " << join(demangle(typeid(T).name())...) << " >" << std::endl;
        return Serialize(std::forward<T>(t)...);
    }
};


template<typename ...T>
std::string Serialize(const std::tuple<T...> & tup)
{
    enum { N = sizeof...(T) };
    std::cout << "ArgCount=" << N << ", Serialize " << demangle(typeid(tup).name()) << std::endl;
    std::stringstream ss;
    Helper<N> helper(ss, Serializer(), tup);
    return ss.str();
}


inline void test_serialize()
{
    std::cout << Serialize(1) << std::endl << std::endl;
    std::cout << Serialize(std::make_tuple(1, 2)) << std::endl << std::endl;
    
    std::cout << Serialize(std::string("hello")) << std::endl << std::endl;
    std::cout << Serialize(std::make_tuple(1, std::string("hello"))) << std::endl << std::endl;
}



#if 0
struct Extract
{
    Extract(std::istream & is) : is(is) {}
    
    void operator()(int & x) { is >> x; }
    void operator()(std::string & x) { is >> x; }
    
    template<typename T>
    void operator()(T & t)
    {
        Extract e(is);
        e(t);
    }
    
    template<typename ...T>
    void operator()(const std::tuple<T...> & tup)
    {
        Extract extract(is);
        Helper<sizeof...(T)> helper(extract, tup);
    }
    
    std::istream & is;
};


template<typename T>
T Deserialize(std::istream & is)
{
    T t;
    Extract extract(is);
    extract(t);
    return t;
}


typedef std::tuple<std::string, std::string> NameAndBody;


struct Server
{
    std::string accept(const std::string & msg)
    {
        std::istringstream iss(msg);
        NameAndBody nb = Deserialize<NameAndBody>(iss);
        return dispatch(std::get<0>(nb), std::get<1>(nb));
    }
    
private:
    std::string dispatch(const std::string & name, const std::string & body)
    {
        auto it = mDispatchers.find(name);
        if (it == mDispatchers.end())
        {
            throw std::runtime_error("Dispatcher not found: " + name);
        }
        
        return it->second(body);
    }
    
    typedef std::function<std::string(const std::string&)> Dispatcher;
    typedef std::map<std::string, Dispatcher> Dispatchers;
    Dispatchers mDispatchers;
};


struct Client
{
    typedef std::function<std::string(const std::string &)> SendFunction;
    
    Client(const SendFunction & inSendFunction) : mSendFunction(inSendFunction) {}
    
    template<typename F, typename ...Args>
    typename F::result_type send(Args && ...args)
    {
        return do_send<F>(std::make_tuple(std::forward<Args>(args)...));
    }
    
private:
    template<typename F, typename ...Args>
    typename F::result_type do_send(const std::tuple<Args...> & arg)
    {
        std::string serialized_request = Serialize(arg);
        std::string serialized_result = mSendFunction(serialized_request);
        std::istringstream iss(serialized_result);
        return Deserialize<typename F::result_type>(iss);
    }
    
    SendFunction mSendFunction;
};


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
    

STRONG_TYPEDEF(int, X);
STRONG_TYPEDEF(int, Y);


struct Point : std::tuple<X, Y>
{
    Point() {}
    Point(const X & x, const Y & y) : std::tuple<X, Y>(x, y) {}
    
    const X & getX() const { return std::get<0>(*this); }
    
    const Y & getY() const { return std::get<1>(*this); }
};


STRONG_TYPEDEF(Point, P1);
STRONG_TYPEDEF(Point, P2);


typedef std::function<int(P1, P2)> Distance;
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
