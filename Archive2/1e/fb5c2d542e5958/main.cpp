#include <functional>

struct Runnable { virtual bool Run() =0;};
struct Base : public Runnable { bool Run() {return true;}};
struct Derived : public Base {};

Derived d;
std::function<bool()> f = std::bind(&Derived::Run,std::ref(d)); //Do not compile
//std::function<bool()> f = boost::bind(&Derived::Run,boost::ref(d)); //compile 