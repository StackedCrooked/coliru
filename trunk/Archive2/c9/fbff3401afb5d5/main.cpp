#include <functional>
#include <iostream>

class Foo
{
public:
    Foo() : num_(0) {}
    void print_add(int i) { std::cout << num_+i << '\n'; }
    
private:    
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    // store a free function
    std::function<void(int)> f_display = print_num;
    f_display(-9);
 
    // store a lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
 
    // store the result of a call to std::bind
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();
 
    // store a call to a member function
    //std::function<void(const IFoo&, int)> f_add_display = &Foo::print_add;
    Foo foo;
    std::function<void(int)> f_add_display = std::bind(&Foo::print_add, &foo, std::placeholders::_1);
    f_add_display(1);
    f_add_display = nullptr;
    if (f_add_display)
    {
        std::cout << "Should not write thuis." << '\n';
    }
 
    // store a call to a function object
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
}