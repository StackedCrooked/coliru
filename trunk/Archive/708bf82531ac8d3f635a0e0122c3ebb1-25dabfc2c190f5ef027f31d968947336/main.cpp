#include <type_traits>
#include <functional>

int add(int a, int b)
{ return a + b; }

struct invoke_with_42
{
    template <typename FunObj>
    auto operator()(FunObj&& fun_obj) const -> decltype((fun_obj(42)))
    { return fun_obj(42); }
};

int main()
{
    //// Compilation error, nested bind expression evaluated
    auto bind_expr =
        std::bind<int>(invoke_with_42{}
          , std::bind(&add, 1, std::placeholders::_1));

    //// Compilation error, cref does not take rvalues
    //auto bind_expr =
    //    std::bind<int>(invoke_with_42{}
    //      , std::cref(std::bind(&add, 1, std::placeholders::_1)));

    //// Ok, inner_bind_expr must be kept alive
    auto inner_bind_expr =
        std::bind(&add, 1, std::placeholders::_1);
    auto outer_bind_expr =
        std::bind<int>(invoke_with_42{}, std::cref(inner_bind_expr));


    //// Ok, with protect
    //auto bind_expr =
    //    std::bind<int>(invoke_with_42{}
    //      , std::protect(std::bind(&add, 1, std::placeholders::_1)));
}
