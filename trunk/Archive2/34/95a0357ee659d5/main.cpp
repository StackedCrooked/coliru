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

#define UniqueID(x)  std::type_index(typeid(decltype(x)))

template <  typename R, typename ...Arg, R(Base::*target)(Arg...) >
struct Generate< R(Base::*)(Arg...), target >
{
    static void call() 
    {
        std::cout << "TARG:" << names_map[ UniqueID(target) ] << std::endl;
    }
};



#define BIND(fp, cxx_target) \
                            fp = &Generate< decltype(&cxx_target), &cxx_target >::call; \
                            names_map[ UniqueID(&cxx_target) ] = std::string(#cxx_target);

int main()
{
    typedef void(*Callfp)();
    
    Callfp u;  BIND( u, Base::f ); 
    Callfp v;  BIND( v, Base::g );
    Callfp w;  BIND( w, Base::h );
    u(); v(); w();
}
