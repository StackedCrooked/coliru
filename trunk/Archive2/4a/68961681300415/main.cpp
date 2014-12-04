#include <iostream>
#include <stdexcept>

#include <sstream>

// =========================================================
// Implment a variadic function that simply << each argument
// into a stringstream and return the .str() from it

static inline void ToStringImpl(std::stringstream &)
{
}

template<typename T1>
void ToStringImpl(std::stringstream &ss, T1&& arg)
{
    ss << std::forward<T1>(arg);
}

template<typename T1, typename ...T>
void ToStringImpl(std::stringstream &ss, T1&& arg, T&& ...args)
{
    ss << std::forward<T1>(arg);
    ToStringImpl(ss, std::forward<T>(args)...);
}

template<typename ...T>
std::string ToString(T&& ...args)
{
    std::stringstream ss;
    ToStringImpl(ss, std::forward<T>(args)...);
    return ss.str();
}

template<typename ...T>
std::string ToString()
{
    return std::string();
}


class Example
{
public:
    // =======================================================================
    // Exceptions

    template<typename Base>
    class base_exception : public Base
    {
    public:
        base_exception(std::string message) : Base(message) {}
    };

    using file_corrupt = base_exception<std::runtime_error>;
    using invalid_argument = base_exception<std::invalid_argument>;
    using out_of_range = base_exception<std::out_of_range>;
    using out_of_resource = base_exception<std::runtime_error>;
    
    // =======================================================================
    // API
    
    Example() : page(42) {}
    
    bool validateSomething(bool nothrow = false)
    {
        // ... valiation always fails in example
        return returnOrThrow<out_of_range>(nothrow, false, "Something bad happened on page ", page);
    }
    
private:
    template<typename E, typename R, typename ...Args>
    R returnOrThrow(bool nothrow, R value, Args ...args)
    {
        return nothrow
                ? value
                : throw E(ToString(std::forward<Args>(args)...));
    }
    
    int page;
};

int main()
{
    Example e;
    e.validateSomething();
}

