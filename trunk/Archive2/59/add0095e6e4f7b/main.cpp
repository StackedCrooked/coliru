#include <utility>
 
#define RETURNS(...) \
  -> decltype(__VA_ARGS__) { \
    return (__VA_ARGS__); \
  }

// Function object type
template<class F, class... Args>
auto eval(F&& f, Args&&... args)
RETURNS(std::forward<F>(f)(std::forward<Args>(args)...))
 
// pointer to member function, object reference
template<class PMF, class C, class... Args>
auto eval(PMF&& pmf, C&& c, Args&&... args)
RETURNS((std::forward<C>(c).*std::forward<PMF>(pmf))(std::forward<Args>(args)...))

// pointer to member function, object pointer
template<class PMF, class P, class... Args>
auto eval(PMF&& pmf, P&& p, Args&&... args)
RETURNS(((*std::forward<P>(p)).*std::forward<PMF>(pmf))(std::forward<Args>(args)...))

// pointer to member object, object reference
template<class PMD, class C>
auto eval(PMD&& pmd, C&& c)
RETURNS(std::forward<C>(c).*std::forward<PMD>(pmd))

// pointer to member object, object pointer
template<class PMD, class P>
auto eval(PMD&& pmd, P&& p)
RETURNS((*std::forward<P>(p)).*std::forward<PMD>(pmd))

#undef RETURNS

#include <iostream>
 
struct Bloop
{
    int a = 10;
    int operator()(){return a;}
    int operator()(int n){return a+n;}
    int triple(){return a*3;}
};
 
int add_one(int n)
{
    return n+1;
}
 
int main()
{
    Bloop bloop;
 
    // free function
    std::cout << eval(add_one,0) << "\n";
 
    // lambda function
    std::cout << eval([](int n){return n+1;},1) << "\n";
 
    // functor
    std::cout << eval(bloop) << "\n";
    std::cout << eval(bloop,4) << "\n";

    // member function
    std::cout << eval(&Bloop::triple,bloop) << "\n";
 
    // member object
    eval(&Bloop::a,&bloop)++; // increment a by reference
    std::cout << eval(&Bloop::a,bloop) << "\n";
}
