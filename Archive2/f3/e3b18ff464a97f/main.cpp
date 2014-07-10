#include <iostream>
#include <functional>

template<class Operator>
struct SingleFunction{
    
    SingleFunction(std::function<double(double)> f1, Operator op={}) 
    : f1(std::move(f1)), op(std::move(op))
    { }
    
    double operator()(double d) {return op(f1(d));}
private:
    std::function<double(double)> f1;
    Operator op;
};
template<class Operator>
struct CombinedFunction{
    
    CombinedFunction(std::function<double(double)> f1, std::function<double(double)> f2, Operator op={}) 
    : f1(std::move(f1)), f2(std::move(f2)), op(std::move(op))
    { }
    
    double operator()(double d) {return op(f1(d),f2(d));}
private:
    std::function<double(double)> f1, f2;
    Operator op;
};

std::function<double(double)> operator+ (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::plus<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator- (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::minus<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator* (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::multiplies<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator/ (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::divides<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator- (std::function<double(double)> f)
{return SingleFunction<std::negate<double>>(std::move(f));}
std::function<double(double)> operator== (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::equal_to<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator!= (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::not_equal_to<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator> (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::greater<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator< (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::less<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator>= (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::greater_equal<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator<= (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::less_equal<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator&& (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::logical_and<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator|| (std::function<double(double)> f, std::function<double(double)> g)
{return CombinedFunction<std::logical_or<double>>(std::move(f), std::move(g));}
std::function<double(double)> operator! (std::function<double(double)> f)
{return SingleFunction<std::logical_not<double>>(std::move(f));}

double f(double x){
    return 2 * x;
}
double g(double x){
    return 3 * x;
}

int main(){
    auto h = std::function<double(double)>(f) + g;
    std::cout << h(2) << '\n';
    auto h2 = f + h + g;
    std::cout << h2(2);
}