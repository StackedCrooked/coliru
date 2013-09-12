#include <functional>
#include <iostream>
 
using SomeVoidFunc = std::function<void(int)>;
 
class C {
public:
    C(SomeVoidFunc void_func = nullptr) : 
        void_func_(void_func)
    {
        if (void_func_ == nullptr) { // specialized compare with nullptr
            void_func_ = std::bind(&C::default_func, this, std::placeholders::_1);
        }
        void_func_(7);
    }
 
    void default_func(int i) { std::cout << i << '\n'; };
 
private:
    SomeVoidFunc void_func_;
};
 
void user_func(int i)
{
    std::cout << (i + 2) << '\n';
}
 
int main()
{
    C c1;
    C c2(user_func);
}