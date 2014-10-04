#include <iostream>

class Class 
{
public:
    Class(int param)
        : m_val(param)
    {}

    void print(int v) 
    {
        std::cout << "Class: " << v + m_val << std::endl;
    }

private:
    int m_val;
};

template <typename R, typename C, typename... Args>
class delegate
{
public:
    template <C* t /*<< here*/, R(C::*F)(Args...)>
    struct adapter 
    {
        static R invoke_no_fwd(Args... args) 
        { 
            return (t->*F)(args...); 
        }
    };
};

Class t{ 123 };

int main()
{
    auto type = (delegate<void, Class, int>::adapter<&t, &Class::print>::invoke_no_fwd);
    
    type(123);
}
