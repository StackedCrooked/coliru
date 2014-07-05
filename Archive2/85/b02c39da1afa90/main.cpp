#include <iostream>


template <class C> class Fract {

private:
int a_;

friend std::ostream& operator<<(std::ostream& out, Fract f);

};

template <class C>
std::ostream& operator <<(std::ostream& out, const Fract<C>& f)
{
    out << f.a_ ;
    return out ;
}

int main( )
{
    
    
}