#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

struct pairer
{
    template<class L,class R>
    auto operator()(L&& l, R&& r)->std::pair<L,R>
    {
        return std::make_pair(std::forward<L>(l),std::forward<R>(r));
    }
};

struct zipper
{
    template<class... Args>
    auto operator()(Args&&... args)->std::tuple<Args...>
    {
        return std::make_tuple(std::forward<Args>(args)...);
    }
};
 
 struct serializer
{
    explicit serializer(std::string const& _sep) :sep(_sep) {}
    
    template<class H>
    std::string operator()(H&& h)
    {
        std::stringstream ss;
        ss << h;
        return ss.str();
    }

    template<class H, class... T>
    std::string operator()(H&& h, T&&... args)
    {
        std::stringstream ss;
        ss << h << sep << (*this)(std::forward<T>(args)...);
        return ss.str();
    }
private:
    std::string sep;
};
 


int main()
{
    double a(77.7);
    auto x = serializer("__")(3.1,6,"adsd",7.3f,a);
    std::cout << x << std::endl;
}
