#include <iostream>
#include <functional>

void add(int a, int b){
    std::cout   << "add:" << std::endl
                << a << " + " << b
                << " = " << (a+b) << std::endl;
}

void add3(int a){
    std::cout   << "add3:" << std::endl
                << a << " + 3"
                << " = " << (a+3) << std::endl;
}

void adddouble(int a, double d){
    std::cout   << "adddouble:" << std::endl
                << a << " + " << d
                << " = " << (a+d) << std::endl;
}

class A{
public:
    void setfunctor(void (*f)(int, int)){
        m_functor = f;
        };
    void functor(int a, int b){
        m_functor(a,b);
    }

    template<typename... ARGS> void MakeFunctor(void(*f)(ARGS...)) {
        if(m_Functor)
            delete m_Functor;
        auto functor = new Functor<ARGS...>(f);
        m_Functor = functor;
    }
    template<typename... ARGS> void ExeFunctor(ARGS... args) {
        auto functor = dynamic_cast<Functor<ARGS...>*>(m_Functor);
        if(functor){
            functor->exe(args...);
        }else{
            std::cout << "Error: Wrong Arguments list!\n";
        }
    }
    A() {m_Functor=0;}
private:
    void (*m_functor)(int, int);
    class Base{
    public:
        virtual void print()=0;
        virtual ~Base(){};
    };
    template<typename... ARGS> class Functor: public Base{
        std::function<void(ARGS...)> m_paramfunctor;
    public:
        Functor( std::function<void(ARGS...)> f ) : m_paramfunctor(f) {}
        void exe(ARGS... args) const { m_paramfunctor(args...); }
        void print(){std::cout<<"\t\t\t\t\t\tparamfunctor= "<<&m_paramfunctor<<std::endl;}
    };
    Base* m_Functor;
};

int main()
{
    A test;
    //Old Method: not flexible
    test.setfunctor(add);
    test.functor(1,2);
    
    //New Method, more flexibility
    test.MakeFunctor(add);
    test.ExeFunctor(1,2);
    test.ExeFunctor(2);
    test.MakeFunctor(add3);
    test.ExeFunctor(3);
    test.MakeFunctor(adddouble);
    test.ExeFunctor(3,1.5);
}
