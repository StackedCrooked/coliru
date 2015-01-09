#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>

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

template<class Function, class ...Args>
auto safe_call(Function fn, Args&&... args) -> return_type<decltype(fn(std::forward<Args>(args)...))>
try
{
    return fn(std::forward<Args>(args)...);
}
catch(...)
{
    return std::current_exception();
}

// this is your function that may throw
std::string throwing(const std::string& s) { if(s != "Life is good") throw std::runtime_error("bad vibes"); return s; }


int main() try
{
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
