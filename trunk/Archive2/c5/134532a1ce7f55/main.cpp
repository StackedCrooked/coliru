#include <iostream>
#include <typeinfo>
#include <utility>

#include <map>

static std::map<void*, std::string> names_map;

struct Base {
    void f(int){};
    float g(int,int){return 0.0f;};
    void h(int){};
};

// function generator
template<typename Target, Target target>
struct Generate;

template <  typename R, typename ...Arg, R(Base::*target)(Arg...) >
struct Generate< R(Base::*)(Arg...), target >
{
    static void call() 
    {
        std::cout << "TARG:" << map[ UUID( cxx_target ) ] << std::endl;
    }
};

#define BIND(fp, cxx_target) \
                            fp = &Generate< decltype(&cxx_target), &cxx_target >::call;
                            map[ UUID( cxx_target ) ] = std::string(#cxx_target);

int main()
{
    typedef void(*Callfp)();
    
    Callfp u;  BIND( u, Base::f );  u();
    Callfp v;  BIND( v, Base::g );  v();
    Callfp w;  BIND( w, Base::h );  w();
}
