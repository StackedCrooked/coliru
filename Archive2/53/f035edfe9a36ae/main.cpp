#include <utility>
#include <type_traits>

template<typename F>
struct compose_if_nonvoid
{
    F f;
    
    template<typename Arg, typename G>
    auto operator()(Arg& a, G g) -> decltype(g(f(a)))
    {
        return g(f(a));
    }
    
    template<typename Arg, typename G>
    auto operator()(Arg& a, G g) -> std::enable_if_t<std::is_same<decltype(f(a)), void>{}>
    {
        f(a);
        return g();
    }
};

template<typename T> struct future
{
    T get() { return T(); }
};

struct then
{
    template<typename... Args> void operator()(Args&&...) {}
};

int main()
{
    auto f = [](auto& fut){ return fut.get(); };
    auto c = compose_if_nonvoid<decltype(f)>{f};
    
    future<int> fi;
    future<void> fv;
    
    c(fi, then{});
    c(fv, then{});
}