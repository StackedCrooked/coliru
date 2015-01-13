#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <utility>

#include <map>

static std::map<std::type_index, std::string> names_map;

struct Base {
    void f(int){};
    float g(int,int){return 0.0f;};
    void h(int){};
};

// function generator
template<typename Target, Target target>
struct Generate;

#define UniqueID(G)  std::type_index(typeid(G))

template <  typename R, typename ...Arg, R(Base::*target)(Arg...) >
struct Generate< R(Base::*)(Arg...), target >
{
    static void call() 
    {
        std::cout << "TARG:" << names_map[ UniqueID(Generate) ] << std::endl;
    }
};

#define BIND(fp, cxx_target) \
    { \
        using G = Generate< decltype(&cxx_target), &cxx_target >; \
        fp = &G::call; \
        names_map[ UniqueID(G) ] = std::string(#cxx_target); \
    }

int main()
{
    typedef void(*Callfp)();
    
    Callfp u;  BIND( u, Base::f ); 
    Callfp v;  BIND( v, Base::g );
    Callfp w;  BIND( w, Base::h );
    u(); v(); w();
}
