#include <iostream>
#include <functional>

template<class Operator, class input> class UnaryFunctionOperator;
template<class Operator, class Ret, class...Args>
class UnaryFunctionOperator<Operator, Ret(Args...)> 
{    
    std::function<Ret(Args...)> f1;
    Operator op;
    
public:
    UnaryFunctionOperator(std::function<Ret(Args...)> f1, Operator op={}) 
    : f1(std::move(f1)), op(std::move(op))
    { }
    
    auto operator()(Args...args) 
    -> decltype(op(f1(std::forward<Args>(args)...)))
    {return op(f1(std::forward<Args>(args)...));}
};

#define DEFINE_UNARY_FUNC_OP(OP, FUNCTIONOID) \
template<class Ret, class...Args, \
    class NewRet=decltype(FUNCTIONOID{}(std::declval<Ret>())) \
    > \
auto operator OP(std::function<Ret(Args...)> f) \
-> std::function<NewRet(Args...)> \
{return UnaryFunctionOperator<FUNCTIONOID, Ret(Args...)>(std::move(f));} \
     \
template<class Ret, class...Args, \
    class NewRet=decltype(FUNCTIONOID{}(std::declval<Ret>())) \
    > \
auto operator OP(Ret(*f)(Args...)) \
-> std::function<NewRet(Args...)> \
{return UnaryFunctionOperator<FUNCTIONOID, Ret(Args...)>(std::move(f));}

DEFINE_UNARY_FUNC_OP(!, std::negate<Ret>)
DEFINE_UNARY_FUNC_OP(~, std::logical_not<Ret>)




template<class Operator, class input1, class input2> class BinaryFunctionOperator;
template<class Operator, class Ret1, class...Args1, class Ret2, class...Args2>
class BinaryFunctionOperator<Operator, Ret1(Args1...), Ret2(Args2...)> 
{    
    std::function<Ret1(Args1...)> f1;
    std::function<Ret2(Args2...)> f2;
    Operator op;
    
public:
    BinaryFunctionOperator(std::function<Ret1(Args1...)> f1, std::function<Ret2(Args2...)> f2, Operator op={}) 
    : f1(std::move(f1)), f2(std::move(f2)), op(std::move(op))
    { }
    
    auto operator()(Args1...args1, Args2...args2) 
    -> decltype(op(f1(std::forward<Args1>(args1)...),f2(std::forward<Args2>(args2)...)))
    {return op(f1(std::forward<Args1>(args1)...),f2(std::forward<Args2>(args2)...));}
};

#define DEFINE_BINARY_FUNC_OP(OP, FUNCTIONOID) \
template<class Ret1, class...Args1, class Ret2, class...Args2, \
    class NewRet=decltype(FUNCTIONOID{}(std::declval<Ret1>(),std::declval<Ret2>())) \
    > \
auto operator OP(std::function<Ret1(Args1...)> f1, std::function<Ret2(Args2...)> f2) \
-> std::function<NewRet(Args1...,Args2...)> \
{return BinaryFunctionOperator<FUNCTIONOID, Ret1(Args1...), Ret2(Args2...)>(std::move(f1), std::move(f2));} \
    \
template<class Ret1, class...Args1, class Ret2, class...Args2, \
    class NewRet=decltype(FUNCTIONOID{}(std::declval<Ret1>(),std::declval<Ret2>())) \
    > \
auto operator OP(std::function<Ret1(Args1...)> f1, Ret2(*f2)(Args2...)) \
-> std::function<NewRet(Args1...,Args2...)> \
{return BinaryFunctionOperator<FUNCTIONOID, Ret1(Args1...), Ret2(Args2...)>(std::move(f1), std::move(f2));} \
    \
template<class Ret1, class...Args1, class Ret2, class...Args2, \
    class NewRet=decltype(FUNCTIONOID{}(std::declval<Ret1>(),std::declval<Ret2>())) \
    > \
auto operator OP(Ret1(*f1)(Args1...), std::function<Ret2(Args2...)> f2) \
-> std::function<NewRet(Args1...,Args2...)> \
{return BinaryFunctionOperator<FUNCTIONOID, Ret1(Args1...), Ret2(Args2...)>(std::move(f1), std::move(f2));} 

DEFINE_BINARY_FUNC_OP(+, std::plus<Ret1>)
DEFINE_BINARY_FUNC_OP(-, std::minus<Ret1>)
DEFINE_BINARY_FUNC_OP(*, std::multiplies<Ret1>)
DEFINE_BINARY_FUNC_OP(/, std::divides<Ret1>)
DEFINE_BINARY_FUNC_OP(%, std::modulus<Ret1>)
DEFINE_BINARY_FUNC_OP(==, std::equal_to<Ret1>)
DEFINE_BINARY_FUNC_OP(!=, std::not_equal_to<Ret1>)
DEFINE_BINARY_FUNC_OP(>, std::greater<Ret1>)
DEFINE_BINARY_FUNC_OP(<, std::less<Ret1>)
DEFINE_BINARY_FUNC_OP(>=, std::greater_equal<Ret1>)
DEFINE_BINARY_FUNC_OP(<=, std::less_equal<Ret1>)
DEFINE_BINARY_FUNC_OP(&&, std::logical_and<Ret1>)
DEFINE_BINARY_FUNC_OP(||, std::logical_or<Ret1>)
DEFINE_BINARY_FUNC_OP(&, std::bit_and<Ret1>)
DEFINE_BINARY_FUNC_OP(|, std::bit_or<Ret1>)
DEFINE_BINARY_FUNC_OP(^, std::bit_xor<Ret1>)




double f(double x){
    return 2 * x;
}
double g(double x){
    return 3 * x;
}

int main(){
    auto h = std::function<double(double)>(f) + g;
    std::cout << h(2, 3) << '\n';
    auto h2 = f + h + g;
    std::cout << h2(2, 4, 5, 6);
}