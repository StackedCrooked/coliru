#include <tuple>

auto tuple = [](auto ...xs) { 
    return [=](auto access) { return access(xs...); }; 
}; 

auto std_tuple = [](auto... args)
{
    return [=](auto f){ return f(std::make_tuple(args...)); };
};

template<typename... ARGS>
void f( const std::tuple<ARGS...>& t ){}

int main()
{
    tuple(1,2,3)(std_tuple)([](auto const& t){ return f(t); });
}