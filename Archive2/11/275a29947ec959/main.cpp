#include <iostream>
#include <string>
#include <vector>

class Bazowa {
    public:
    char b;
};

class D: public Bazowa {
    public: 
    char d;
};

class E: public Bazowa {
    public: 
    char e;
};


class Pochodna: public D, public E {
    
    public:
    Pochodna(){
       D::b='b';
       d='d';
       E::b='B';
       e='e';
       x='x';
       y='y';
    };
    
    void metoda() { std::cout << "Pochodna:" << std::endl <<
            "  D::b=" << D::b << std::endl <<
            "  d=" << d << std::endl <<
            "  E::b=" << E::b << std::endl <<
            "  e=" << e << std::endl; };
    
    char x;
    char y;
};




template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };

    std::cout << words << std::endl;
    
    Bazowa * b1= (D*) new Pochodna();
    Bazowa * b2= (E*) new Pochodna();
    
    void (Bazowa::* wskaznikNaMetode1)();
    void (Bazowa::* wskaznikNaMetode2)();
    
    wskaznikNaMetode1= ( void (Bazowa::*)() ) ( void (D::*)() ) &Pochodna::metoda;
    wskaznikNaMetode2= ( void (Bazowa::*)() ) ( void (E::*)() ) &Pochodna::metoda;
    
    
    (b1->*wskaznikNaMetode1)();
    (b2->*wskaznikNaMetode2)(); 
     std::cout << "show me your x,y! <hacked> ";
    (b2->*wskaznikNaMetode1)();
}
