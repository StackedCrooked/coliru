
#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <iterator>

template<class Ret>
class return_type
{
    union
    {
        Ret ret_value;
        std::exception_ptr eptr;
    };
    bool value_tag;
public:
    return_type(Ret&& value) : ret_value(std::forward<Ret>(value)), value_tag(true) {}
    return_type(std::exception_ptr e) : eptr(e), value_tag(false) {}
    return_type(const return_type& other) : value_tag(other.value_tag) { if(value_tag) new(&ret_value) Ret(other.ret_value); else eptr = other.eptr; }
    ~return_type() { if(value_tag) ret_value.~Ret(); }
    
    auto get() const -> decltype(ret_value) { if(value_tag) return ret_value; else std::rethrow_exception(eptr); }
    auto get() -> decltype(ret_value) { if(value_tag) return ret_value; else std::rethrow_exception(eptr); }
    
    bool has_value() const { return value_tag; }
};

// specialize for void
template<>
class return_type<void>
{
    std::exception_ptr eptr;
public:
    return_type() = default;
    return_type(std::exception_ptr e) : eptr(e) {}
    
    void get() const { if(eptr) std::rethrow_exception(eptr); }
    bool has_value() const { return !eptr; }
};

template<class Function, class ...Args>
auto safe_call(Function fn, Args&&... args) -> 
typename std::enable_if<!std::is_same<decltype(fn(std::forward<Args>(args)...)), void>::value, return_type<decltype(fn(std::forward<Args>(args)...))>>::type
try
{
    return fn(std::forward<Args>(args)...);
}
catch(...)
{
    return std::current_exception();
}

// specialize for void
template<class Function, class ...Args>
auto safe_call(Function fn, Args&&... args) -> 
typename std::enable_if<std::is_same<decltype(fn(std::forward<Args>(args)...)), void>::value, return_type<void>>::type
try
{
    fn(std::forward<Args>(args)...);
    return return_type<void>{};
}
catch(...)
{
    return std::current_exception();
}

// this is your function that may throw
std::string throwing(const std::string& s) { if(s != "Life is good") throw std::runtime_error("bad vibes"); return s; }


int main() try
{
    std::cerr << __cplusplus << "\n";
    std::cerr << std::uncaught_exception() << "\n";
    
    std::string my{"a"};
    auto it = std::next(my.begin());
    std::cerr << "1: " << ( it == my.end()) << "\n";
    it = std::next(it);
    std::cerr << "2: " << ( it == my.end()) << "\n";
    
    safe_call([&] { std::cerr << "starting\n"; });
    // wrap the possibly throwing function in the safe_call()
    auto result = safe_call(throwing, "Life is good");
    std::cerr << "It didn't throw: " << result.get() << "\n";
    
    auto bad_result = safe_call(throwing, "Puke!\n");
    
    if(!bad_result.has_value())
    {
        std::cerr << "result has no value, and if you try to access it ... \n";
        // It's going to throw now!
        std::cerr << bad_result.get();
    }
}
catch(std::exception& s)
{
    std::cerr << "\nCaught exception: " << s.what() << "\n";
}
