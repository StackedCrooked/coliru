#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cassert>
#include <cmath>


struct Verbose
{
    Verbose(){std::cout << "Verbose()" << std::endl;};
    ~Verbose(){std::cout << "~Verbose()" << std::endl;};
    
    Verbose(Verbose const& other){std::cout << "Verbose(Verbose const& other)" << std::endl;};
    Verbose& operator=(Verbose const& other){std::cout << "Verbose& operator=(Verbose const& other)" << std::endl; return *this;}
    
    Verbose(Verbose&& other) noexcept {std::cout << "Verbose(Verbose&& other)" << std::endl;};
    Verbose& operator=(Verbose&& other) noexcept {std::cout << "Verbose& operator=(Verbose&& other)" << std::endl; return *this;}
};


double func1(double val)
{
    assert(val >= 0);
    
    double result = std::sqrt(val);
    assert(result >= 0.);
    return result;    
}

void func2(double val)
{
    assert(val >= 0);
    
    std::cout << val << std::endl;
}

template<typename T>
struct ContractHelper
{
    typedef T ReturnType;
    
    template<typename Body>
    static auto execBody(Body body) -> decltype(body())
    {
        std::cout << typeid(decltype(body())).name() << std::endl;
        return body();
    }
    
    template<typename Result>
    static Result&& getResult(Result&& result)
    {
        return static_cast<Result&&>(result);
    }
    
    template<typename Body, typename Post>
    static auto execBodyAndPostcond(Body body, Post post) -> decltype(post(body()))
    {
        return post(body());
    }
};

template<>
struct ContractHelper<void>
{
    struct NoType{};
    typedef NoType ReturnType;

    template<typename Body>
    static NoType execBody(Body body)
    {
        body();
        return NoType();
    }
    
    template<typename Result>
    static void getResult(NoType result)
    {
    }

    template<typename Body, typename Post>
    static void execBodyAndPostcond(Body body, Post post)
    {
        body();
        post(NoType());
    }
};

double func3(double val)
{
    assert(val >= 0);
    
    auto body = [&]
    {
        return sqrt(val);
    };
    auto postcond = [&](typename ContractHelper<decltype(body())>::ReturnType result)
    {
        assert(result >= 0.);
        return result;
    };
    return ContractHelper<decltype(body())>::execBodyAndPostcond(body, postcond);    
}

void func4(double val)
{
    assert(val >= 0);
    
    auto body = [&]
    {
        std::cout << val << std::endl;
    };
    auto postcond = [&](typename ContractHelper<decltype(body())>::ReturnType result)
    {
        return result;
    };
    return ContractHelper<decltype(body())>::execBodyAndPostcond(body, postcond);    
}

static Verbose toto;

Verbose& func5()
{
    auto body = [&]
    {
        return toto;
    };
    /*
    auto postcond = [&](typename ContractHelper<decltype(body())>::ReturnType result)
    {
        return result;
    };
    return ContractHelper<decltype(body())>::execBodyAndPostcond(body, postcond);    */
    auto result = ContractHelper<decltype(body())>::execBody(body);
    std::cout << typeid(decltype(result)).name() << std::endl;
    return ContractHelper<decltype(body())>::getResult(result);
}

Verbose func5_(Verbose val)
{
    return Verbose();
}

void func6(Verbose val)
{
    auto body = [&]
    {
    };
    auto postcond = [&](typename ContractHelper<decltype(body())>::ReturnType result)
    {
        return result;
    };
    return ContractHelper<decltype(body())>::execBodyAndPostcond(body, postcond);    
}

int main()
{
    Verbose& titi = func5();
    assert(&toto == &titi);
    return 0;
}
