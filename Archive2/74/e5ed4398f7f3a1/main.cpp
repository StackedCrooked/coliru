#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <cstddef>
#include <complex>

#include <tuple>
#include <type_traits>

using namespace std;

struct Action
{
  const int action_id;
};

struct AddAction : public Action
{
  AddAction(int a) : Action{a}, product(2)
  {
    cout << "hello" << endl;
  }
  int product;
};


// Emplaces a new action of the given type and returns an action ID for it
template<typename ActionT, typename... Args>
int emplace(Args&&... args)
{
std::cout << ActionT(3.0, std::forward<Args>(args)...) << std::endl;
return 0;
}


// Applies type transform to variadic parameter pack
template<template<typename... > class T, 
         template<typename> class Transform, 
         typename... Args>
struct ApplyTypeTransform
{
  using val = T<typename Transform<Args>::type...>;
};

typedef ApplyTypeTransform<std::tuple, std::add_pointer, int, char>::val A;
typedef std::tuple<int*, char*> B;
static_assert(is_same<A, B>::value, ":(");


struct Asdf
{
    int a;
    int b;
};


template<typename... Args>
void make(Args&&... args)
{
    return Asdf(std::forward<Args...>(args...));
}


template<typename T = int>
struct G
{
    T a;
};

struct Ints
{
    int16_t a;
    int16_t b;
    int32_t c;
};


int main()
{
    //emplace<int>(3);
    //emplace<std::string>("asdf");
    emplace<std::complex<double>>(3.2);
    
    Action a{3};
    AddAction b(5);
    std::cout << a.action_id << std::endl;
    std::cout << b.action_id << b.product << std::endl;
    
    Asdf c{3,5};
    std::cout << c.a << std::endl;
//    auto d = make({6, 7});
//    std::cout << d.a << std::endl;

    const std::vector<std::string> stuff = {"a", "b", "c"};
    for (auto& item : stuff)
    {
        for (int i = 0; i < 3; ++i)
        {
            std::cout << item + std::to_string(i) << std::endl;
        }
    }
    G<> g;
    std::cout << g.a << std::endl;
    std::cout << sizeof(Ints) << std::endl;
    
    Ints i{1,2,3};
    const Ints& j = i;
    j.a = 3;
}