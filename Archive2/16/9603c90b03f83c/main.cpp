#include <string>
#include <iostream>
#include <utility>

template<typename T>
class forward_ref
{
    union
    {
        T const* lvalue;
        T* xvalue;
    };
    bool is_lvalue_;
    
public:
    forward_ref(T&& xvalue) : xvalue(&xvalue), is_lvalue_(false) {}
    forward_ref(T const& lvalue) : lvalue(&lvalue), is_lvalue_(true) {}
    
    forward_ref(forward_ref const&) = delete;
    forward_ref& operator= (forward_ref const&) = delete;
    
    T copy_or_move() const
    {
        if(is_lvalue()) return *lvalue;
        else return std::move(*xvalue);
    }
    
    bool is_lvalue() const noexcept
    { return is_lvalue_; }
    bool is_xvalue() const noexcept
    { return !is_lvalue(); }
    
    T const& get_lvalue() const
    { return *lvalue; }
    T&& get_xvalue() const
    { return std::move(*xvalue); }
    
    template<typename F>
    decltype(auto) call_with_correct_value_category(F f)
    {
        if(is_lvalue()) return f(get_lvalue());
        else return f(get_xvalue());
    }
};

void E(std::string&&) { std::cout << "xvalue\n"; }
void E(std::string const&) { std::cout << "lvalue\n"; }

void f(forward_ref<std::string> arg) {
  auto fun = [](auto&& p){ E(std::forward<decltype(p)>(p)); };
  arg.call_with_correct_value_category(fun);
}

int main()
{
    f({"hello world"});
    auto str = std::string("hello world");
    f({str});
}