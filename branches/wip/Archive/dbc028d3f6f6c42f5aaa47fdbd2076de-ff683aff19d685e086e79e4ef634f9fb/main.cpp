#include <type_traits>

struct A
{
    static void foo()
    {
        typeid(this);
        static_assert(std::is_same<decltype(this),A*>(), "");
    }
};
 
int main(){
    
}