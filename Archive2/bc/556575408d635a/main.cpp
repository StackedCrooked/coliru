#include <tuple>
#include <iostream>
#include <functional>

namespace helper
{
    template <std::size_t... Ts>
    struct index {};
    
    template <std::size_t N, std::size_t... Ts>
    struct gen_seq : gen_seq<N - 1, N - 1, Ts...> {};
    
    template <std::size_t... Ts>
    struct gen_seq<0, Ts...> : index<Ts...> {};
}

template <typename... Ts>
class Action
{
    private:
        std::function<void (Ts...)> f;
        std::tuple<Ts...> args;
    public:
        Action(std::function<void (Ts...)> func, Ts&&... args) : f(func), args(std::make_tuple(std::forward<Ts>(args)...))
        {}
        
        template <typename... Args, std::size_t... Is>
        void func(std::tuple<Args...>& tup, helper::index<Is...>)
        {
            f(std::get<Is>(tup)...);
        }
        
        template <typename... Args>
        void func(std::tuple<Args...>& tup)
        {
            func(tup, helper::gen_seq<sizeof...(Args)>{});
        }
        
        void act()
        {
            func(args);
        }
};

void output (char **buffer)
{
    printf("%s\n",buffer[0]);
}

int main()
{
   char buffer[100][1024] = {0};
   int len = sprintf(buffer[0],"i am a bastard...");
   buffer[0][len] = '\0';
/*char **ptr = (char **)buffer; 
   这是错的，会导致段错误，事实上你如果不对强转，根本就无法编译通过，
   这样正说明了不能直接将两维数组转成两重指针，你不听编译器的好心劝解，
   非要那么干，杯具那也是活该~~~
*/
   char * aptr = buffer[0];
   char ** ptr = &aptr;
   output(ptr);
}
