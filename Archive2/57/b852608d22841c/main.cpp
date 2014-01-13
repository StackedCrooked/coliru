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

void output (char buffer[][1024])
{
   printf("%s\n",buffer[0]);
}

int main()
{
   char buffer[100][1024] = {0};
   int len = sprintf(buffer[0],"i am a bastard...");
   buffer[0][len] = '\0';
   output(buffer);
}