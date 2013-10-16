#include <iostream>
#include <typeinfo>

struct unit
{
    virtual ~unit() {}
    // ...

    virtual int getAttack() const { return 5 ; }

    // ...
};

struct soldier : unit
{
    // ...
};

struct hulk_soldier : soldier
{
    // ...

    virtual int getAttack() const override
    { return soldier::getAttack() + 1 ; }
};

struct raging_hulk : hulk_soldier
{
    // ...

    virtual int getAttack() const override
    { return hulk_soldier::getAttack() + 1 ; }
};

struct attack_enhanser : unit // decorator
{
    attack_enhanser( unit* enhance_this ) : decorated_object(enhance_this) {}

    virtual int getAttack() const override
    { return decorated_object->getAttack() * 3 ; }

    private: unit* decorated_object ;
};

struct tracing_proxy : unit // proxy
{
    tracing_proxy( unit* trace_this ) : traced_object(trace_this) {}

    virtual int getAttack() const override
    {
        auto type = typeid(*traced_object).name() ;
        std::cout << "getAttack() called on object of type " << type << '\n' ;
        auto result = traced_object->getAttack() ;
        std::cout << "object of type " << type << " returned: " << result << '\n' ;
        return result ;
    }

    private: unit* traced_object ;
};

int main()
{
    unit* p = new raging_hulk() ;
    int value = p->getAttack() ;
    std::cout << "p->getAttack() => " << value << "\n\n" ;

    p = new tracing_proxy(p) ;
    value = p->getAttack() ;
    std::cout << "p->getAttack() => " << value << "\n\n" ;

    p = new attack_enhanser(p) ;
    value = p->getAttack() ;
    std::cout << "p->getAttack() => " << value << "\n\n" ;

    p = new tracing_proxy(p) ;
    value = p->getAttack() ;
    std::cout << "p->getAttack() => " << value << "\n\n" ;
}
