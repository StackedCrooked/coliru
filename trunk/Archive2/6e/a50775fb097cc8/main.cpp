#include <iostream>
#include <string>
#include <functional>
#include <map>

using action_t = std::function<void()>;

std::map<std::string, action_t> g_actions;

void process_id(std::string const & str) 
{
   auto it =  g_actions.find(str);
   if ( it != g_actions.end() )  
         (it->second)(); //invoke action
}

#define VAR_NAME(x)       _ ## x
#define DEFINE_VAR(x)  VAR_NAME(x)
#define REGISTER(type) char DEFINE_VAR(__LINE__) = (g_actions[#type] = &foo<type>,true)

template<typename T> void foo() { std::cout << "foo<T>" << std::endl; }

struct A{};
struct B{};
struct C{};
struct D{};

template<> void foo<A>() { std::cout << "foo<A>" << std::endl; }
template<> void foo<B>() { std::cout << "foo<B>" << std::endl; } 
template<> void foo<C>() { std::cout << "foo<C>" << std::endl; } 

REGISTER(A);
REGISTER(B);
REGISTER(C);

int main()
{
    process_id("A");
    process_id("B");
    process_id("C");
    process_id("D"); //will not be invoked!
}