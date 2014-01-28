#include <iostream>

struct rational
{
    explicit rational( int n = 0, int d = 1 ) : num(n), den(d) {}

    rational& operator+= ( const rational& other )
    {
        num = num * other.den + other.num * den ;
        den *= other.den ;
        return *this ;
    }

    rational& operator+= ( int v )
    {
        num = num + v * den ;
        return *this ;
    }

    int numerator() const { return num ; }
    int denomiator() const { return den ; }

    private:
        int num ;
        int den ;
};

// implemented in terms of +=
rational operator+ ( rational a, const rational& b ) { return a += b ; }
rational operator+ ( rational r, int i ) { return r += i ; }
rational operator+ ( int i, rational r ) { return r += i ; }

std::ostream& operator<< ( std::ostream& stm, const rational& r )
{ return stm << '(' << r.numerator() << '/' << r.denomiator() << ')' ; }

int main()
{
    std::cout << rational{3,2} + rational{1,3} << '\n'
               << rational{3,5} + 2 << '\n'
               << 7 + rational{5,9} << '\n' ;

}
