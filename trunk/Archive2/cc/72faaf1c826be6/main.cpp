#include <functional>

void f(std::function<int(std::size_t, std::size_t)>) {}

struct Zero
{
     template <typename T, typename... Args>
     operator std::function<T(Args...)>() {
         return [] (Args...) { return T();};
     }
};

int main()
{
    f(Zero());   
}
