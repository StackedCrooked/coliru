//Title of this code

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <utility>
#include <map>

struct Value
{
    Value(int i)
    : type(integer_type)
    {
        primitive_value.i = i;
    }
    
    Value(float f)
    : type(float_type)
    {
        primitive_value.f = f;
    }
    
    Value(char* p)
    : type(pointer_type)
    {
        primitive_value.p = p;
    }
    
    enum Type
    {
        integer_type,
        pointer_type,
        float_type,        
    };
    
    Type type;
    
    union
    {
        int i;
        char* p;
        float f;        
    } primitive_value;
};

template <typename T>
struct ValueConversion;
    
template <>
struct ValueConversion<int>
{
    int operator()(const Value& value)
    {
        return value.primitive_value.i;
    }
};

template <>
struct ValueConversion<char*>
{
    char* operator()(const Value& value)
    {
        return value.primitive_value.p;
    }
};

template <>
struct ValueConversion<float>
{
    float operator()(const Value& value)
    {
        return value.primitive_value.f;
    }
};


using Arguments = std::vector<Value>;


template <typename... Args>
struct ArgumentForwarder
{
    using tuple_t = std::tuple<Args...>;
    
    template <std::size_t Index>
    typename std::tuple_element<Index, tuple_t>::type operator()(const Arguments& arguments) const
    {
        using result_type = typename std::tuple_element<Index, tuple_t>::type;
        
        ValueConversion<std::decay_t<result_type>> converter;
        
        return converter(arguments[Index]);
    }
};

struct NativeFunctionBase
{
    virtual void operator()(const Arguments& arguments) const = 0;
};

template <typename Ret, typename... Args>
struct NativeFunction
    : NativeFunctionBase
{    
public:
    template <typename Callable>
    NativeFunction(Callable callable)
        : callable_(std::move(callable))
    {}
            
    
    virtual void operator()(const Arguments& arguments) const override
    {       
        using arg_sequence = std::make_integer_sequence<std::size_t, sizeof...(Args)>;        
        
        InvokeImpl(arguments, arg_sequence());
    }
    
private:
    template <std::size_t... Indices>
    void InvokeImpl(const Arguments& arguments, std::integer_sequence<std::size_t, Indices...>) const
    {
        ArgumentForwarder<Args...> forwarder;
        callable_(forwarder.template operator()<Indices>(arguments)...);
    }
    
    std::function<Ret(Args...)> callable_;
};

struct NativeFunctionDelegate
{    
    template <typename Ret, typename... Args>
    void RegisterNative(std::string name, NativeFunction<Ret, Args...> func)
    {
        functions_[name] = std::make_unique<NativeFunction<Ret, Args...>>(std::move(func));
    }
    
    void Invoke(const std::string& name, const Arguments& arguments)
    {
        auto it = functions_.find(name);
        if (it != functions_.end())
        {
            (*it->second)(arguments);
        }
    }
    
private:
    std::map<std::string, std::unique_ptr<NativeFunctionBase>> functions_;
};

void test(int x, float y)
{
    std::cout << x * y << std::endl;
}

int main()
{
    NativeFunctionDelegate delegate;
    delegate.RegisterNative("test", NativeFunction<void, int, float>(test));
    delegate.Invoke("test", { 3, 5.2f });
    
    std::cout << "Hello, world!\n";
}