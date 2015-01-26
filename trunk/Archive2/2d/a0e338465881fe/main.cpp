#include <iostream>
using namespace std;

template<int A, typename B, int C = 0> class Pippo {
    B b;
};

template<typename B> class Pippo<-1, B> {
    B b;
};

struct Fava {};

template <typename B, int C> struct Cippa : public B {
};

template<typename B, int C> class Pippo<-2, Cippa<B, C>> {
public:
    Cippa<B, C> b;

    enum { c = C };
    
    void pippo() { cout << c << endl; }
};



int main()
{
    Pippo<-1, int> q;
    Pippo<-2, Cippa<Fava, 3>> p;
    
    p.pippo();
    
   cout << "Questo e' il nostro compilatore online!" << endl;
}
