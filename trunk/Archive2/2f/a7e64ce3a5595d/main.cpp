#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

template<typename R>
struct invoke_helper
{
    template<typename F, typename... As>
    invoke_helper(F func, As&&... as) 
        : result(func(std::forward<As>(as)...))
    {}
    
    R result;
};

template<>
struct invoke_helper<void>
{
    template<typename F, typename... As>
    invoke_helper(F func, As&&... as)
    {
        func(std::forward<As>(as)...);   
    }
};

class stream_function
{
public:
    template<typename A, typename... B>
    stream_function(std::function<A(B...)> func)
      : impl_(new stream_function_impl<std::function<A(B...)>, A, B...>(func))
    {}
    
    inline void operator()(std::istream& in, std::ostream& out) const
    {
        impl_->invoke(in, out);        
    }
    
    inline std::size_t arity() const
    {
        return impl_->arity();   
    }

private:    
    class stream_function_impl_base
    {
    public:
        virtual ~stream_function_impl_base() {}
        virtual void invoke(std::istream& in, std::ostream& out) const = 0;        
        virtual std::size_t arity() const = 0;
    };
    
    template<typename F, typename R, typename... As>
    class stream_function_impl : stream_function_impl_base
    {
    public:
        stream_function_impl(const F& func) 
          : func_(func) 
        {}
        
        stream_function_impl(F&& func) 
          : func_(std::forward<F>(func)) 
        {}
        
        virtual void invoke(std::istream& in, std::ostream& out) const
        {
            invoke_impl(in, out);            
        }
        
    private:
        template<typename T>
        T arg(std::istream& in) const
        {
            T t{};
            if (!(in >> t))
            {
                in.clear();
                throw std::invalid_argument("Invalid argument");
            }
            return t;
        }

        inline void invoke_impl(std::istream& in, std::ostream& out, std::true_type) const
        {
            invoke_helper<void>{func_, arg<As>(in)...};
        }
    
        inline void invoke_impl(std::istream& in, std::ostream& out, std::false_type) const
        {
            out << invoke_helper<R>{func_, arg<As>(in)...}.result;
        }

        F func_;
    };
    
    std::unique_ptr<stream_function_impl_base> impl_;
};

class any_function
{
public:
    virtual ~any_function() {}

    virtual void operator()(std::istream& in, std::ostream& out) const { std::cout << "srocz" << std::endl; };
    virtual std::size_t arity() const { return 0; };    
};

template<typename R>
struct invoke_impl
{
    template<typename F, typename... As>
    invoke_impl(F func, As&&... as) 
        : result(func(std::forward<As>(as)...))
    {}
    
    R result;
};

template<>
struct invoke_impl<void>
{
    template<typename F, typename... As>
    invoke_impl(F func, As&&... as)
    {
        func(std::forward<As>(as)...);   
    }
};

template<typename F, typename S>
class any_function_impl;

template<typename F, typename R, typename... As>
class any_function_impl<F, R(As...)> : public any_function
{
public:
    explicit any_function_impl(F func) : func_(func) {}

    void operator()(std::istream& in, std::ostream& out) const override
    {
        invoke(in, out, std::is_void<R>());
    }
    
    std::size_t arity() const override
    {
        return sizeof...(As);   
    }
    
private:
    inline void invoke(std::istream& in, std::ostream& out, std::true_type) const
    {
        std::cout << "invoking 1" << std::endl;
        invoke_impl<void>{func_, get_arg<As>(in)...};
    }
    
    inline void invoke(std::istream& in, std::ostream& out, std::false_type) const
    {
        std::cout << "invoking 2" << std::endl;
        out << invoke_impl<R>{func_, get_arg<As>(in)...}.result;
    }
    
    template<typename T>
    T get_arg(std::istream& in) const
    {
        T t{};
        if (!(in >> t))
        {
            in.clear();
            throw std::invalid_argument("Invalid argument");
        }
        return t;
    }

    F func_;
};

template<typename R, typename... As>
any_function make_any_function(std::function<R(As...)> func)
{
    return any_function_impl<std::function<R(As...)>, R(As...)>{func}; 
}

int add(int a, int b)
{
    return a + b;    
}

int sub(int a, int b)
{
    return a - b;    
}

int main(int argc, char* argv[])
{
    std::function<int (int, int)> a = &add;
    std::function<int (int, int)> s = &sub;
    std::unordered_map<std::string, any_function> map
    {
        {"add", make_any_function(a)},
        {"sub", make_any_function(s)}
    };
    
    std::stringstream ss;
    ss << "1" << std::endl;
    ss << "2" << std::endl;
    
    map.at("add")(ss, std::cout);
    
    return 0;   
}
