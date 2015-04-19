#include <type_traits>
#include <string>
#include <memory>

// faked concept
// needs `std::string show() const`
template<class T>
struct show : std::false_type {};

struct my_type
{
    std::string show() const { return "boo"; }
};

template<>
struct show<my_type> : std::true_type {};

// automatically generated wrapper interface

struct show_i
{
    struct show_base
    {
        virtual std::string show() const = 0;
    };
    
    template<class T>
    struct show_impl : show_base
    {
        show_impl(T const& v) : _value(v) {}
        
        std::string show() const
        {
            return _value.show();
        }
        
        T const& _value;
    };
    
    template<class T, typename std::enable_if<show<T>::value, int>::type = 0>
    show_i(T const& v)
        : _value(new show_impl<T>(v)) {}
        
    std::string show() const { return _value->show(); }
    
    std::unique_ptr<show_base> _value;
};

#include <iostream>

// should look like: void f(show const& s)
void f(show_i const& s)
{
    std::cout << s.show() << "\n";
}

int main()
{
    my_type blah;
    f(blah);
}