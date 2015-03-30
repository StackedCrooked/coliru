#include <functional>
#include <stdexcept>
#include <iostream>
#include <map>
#include <sstream>

class stream_function
{
public:
    virtual ~stream_function() {}

    virtual void operator()(std::istream& in) const { std::cout << "why?" << std::endl; };
    virtual std::size_t arity() const {};    
};

template<typename T>
inline T get(std::istream& in)
{
    T t{};
    if (!(in >> t))
    {
        in.clear();
        throw std::invalid_argument("Invalid argument");
    }
    return t;
}

template<typename R, typename... As>
class stream_function_impl : public stream_function 
{
public:
    template<typename... Ts>
    stream_function_impl(Ts&&... ts)
      : func_(std::forward<Ts>(ts)...)
    {}

    void operator()(std::istream& in) const override
    {
        func_(get<As>(in)...);        
    }
    
    std::size_t arity() const override
    {
        return sizeof...(As);
    }
    
private:
    std::function<R(As...)> func_;
};

void add(int a, int b)
{
    std::cout << a << " + " << b << " = " << a + b << std::cout;   
}

int main(int argc, char* argv[])
{
    std::map<std::string, stream_function> lookup
    {
        {"add", stream_function_impl<void, int, int>(&add)}
    };
    
    std::stringstream args;
    args << "1" << std::endl;
    args << "2" << std::endl;
    lookup.at("add")(args);
    
}