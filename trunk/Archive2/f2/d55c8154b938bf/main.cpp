#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>



using namespace std;

class Polynomial
{ // instances represent polynomials; e.g., 2x^7 - 8x^3 + 5x^2 + 9
    // INVARIANTS: _degree == _terms.begin()._exp;
    //             it1->_exp == it2->_exp  ==>  it1 == it2
    //             *this == ZERO  <==>  _degree == -1
    //                            <==>  _terms.size() == 0;
protected:
    struct Term
    { friend ostream& operator<<(ostream&, const Term&);
        friend Term operator-(const Term&);
        friend Term derivative(const Term&);
        friend Term antiderivative(const Term&);
        friend Term abs(const Term&);
        Term(double=0.0,unsigned=0);
        bool operator==(const Term&) const;
        bool operator!=(const Term&) const;
        bool operator<(const Term&) const;
        double _coef;
        unsigned _exp;
    };
public:
    friend ostream& operator<<(ostream&, const Polynomial&);
    friend Polynomial operator-(const Polynomial&);
    friend Polynomial operator*(const double, const Polynomial&);
    friend Polynomial operator+(const Polynomial&, const Polynomial&);
    friend Polynomial operator-(const Polynomial&, const Polynomial&);
    friend Polynomial operator*(const Polynomial&, const Polynomial&);
    friend Polynomial derivative(const Polynomial&);
    friend Polynomial antiderivative(const Polynomial&);
    Polynomial(double=0,unsigned=0);
    Polynomial& operator+=(const Polynomial&);
    Polynomial& operator-=(const Polynomial&);
    Polynomial& operator*=(const double);
    Polynomial& operator*=(const Polynomial&);
    bool operator==(const Polynomial&) const;
    bool operator!=(const Polynomial&) const;
    double operator()(double) const;  // evaluates the polynomial
    long degree() const;
    unsigned terms() const;  // the number of terms in the polynomial
    static const Polynomial ZERO;  // p(x) = 0
    static const Polynomial ONE;   // p(x) = 1
    static const Polynomial X;     // p(x) = x
protected:
    list<Term> _terms;   // one element for each term
    long _degree;        // maximum exponent
    void reduce();
    typedef list<Term> TermList;
    typedef list<Term>::iterator It;
    typedef list<Term>::const_iterator CIt;
};

ostream& operator<<(ostream& ostr, const Polynomial::Term& term)
{ if (term._exp == 0) return ostr << term._coef;
    if (term._coef == 1.0) ostr << "x";
    else if (term._coef == -1.0) ostr << "-x";
    else ostr << term._coef << "x";
    if (term._exp == 1) return ostr;
    else return ostr << "^" << term._exp;
}

Polynomial::Term operator-(const Polynomial::Term& term)
{ Polynomial::Term t(term);
    t._coef *= -1.0;
    return t;
}

Polynomial::Term derivative(const Polynomial::Term& t)
{ if (t._exp == 0) return Polynomial::Term(0.0,0);
    return Polynomial::Term(t._exp*t._coef,t._exp-1);
}

Polynomial::Term antiderivative(const Polynomial::Term& t)
{ if (t._coef == 0) return Polynomial::Term(1.0,0);
    return Polynomial::Term(t._coef/(t._exp+1),t._exp+1);
}

Polynomial::Term abs(const Polynomial::Term& t)
{ Polynomial::Term term(t);
    if (term._coef < 0) term._coef *= -1.0;
    return term;
}

//////////////////////////////////////////////////////////////////////
//  Term member functions:

Polynomial::Term::Term(double coef, unsigned exp) : _coef(coef), _exp(exp)
{
}

bool Polynomial::Term::operator==(const Term& t) const
{ return _exp == t._exp && _coef == t._coef;
}

bool Polynomial::Term::operator!=(const Term& t) const
{ return _exp != t._exp || _coef != t._coef;
}

bool Polynomial::Term::operator<(const Term& t) const
{ return _exp > t._exp;  // sort terms in decreasing order
}

//////////////////////////////////////////////////////////////////////
//  Polynomial friend functions:

ostream& operator<<(ostream& ostr, const Polynomial& p)
{ if (p == Polynomial::ZERO) return ostr << 0;
    Polynomial::CIt it=p._terms.begin();
    ostr << *it++;
    while (it != p._terms.end())
        if (it->_coef < 0) ostr << " - " << abs(*it++);
        else ostr << " + " << *it++;
    return ostr;
}

Polynomial operator-(const Polynomial& p1)
{ Polynomial p(p1);
    for (Polynomial::It it=p._terms.begin(); it != p._terms.end(); it++)
        it->_coef *= -1;
    return p;
}

Polynomial operator*(const double x, const Polynomial& p1)
{ if (x == 0.0) return Polynomial::ZERO;
    Polynomial p(p1);
    for (Polynomial::It it=p._terms.begin(); it != p._terms.end(); it++)
        it->_coef *= x;
    return p;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{ Polynomial p;
    p._degree = max(p1._degree,p2._degree);
    p._terms = Polynomial::TermList(p1._terms.size()+p2._terms.size());
    merge(p1._terms.begin(),p1._terms.end(),
          p2._terms.begin(),p2._terms.end(),
          p._terms.begin());
    p.reduce();
    return p;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{ return p1 + -p2;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{ Polynomial p;
    p._degree = p1._degree + p2._degree;
    for (Polynomial::CIt it1=p1._terms.begin(); it1 != p1._terms.end(); it1++)
        for (Polynomial::CIt it2=p2._terms.begin(); it2 != p2._terms.end(); it2++)
        { int exp = it1->_exp + it2->_exp;
            double coef = it1->_coef * it2->_coef;
            Polynomial::It it=p._terms.begin();
            for ( ; it != p._terms.end(); it++)
                if (it->_exp <= exp) break;
            if (it->_exp == exp) it->_coef += coef;
            else p._terms.insert(it,Polynomial::Term(coef,exp));
        }
    p.reduce();
    return p;
}

Polynomial derivative(const Polynomial& p1)
{ if (p1._degree < 0) return Polynomial::ZERO;
    Polynomial p;
    p._degree = ( p1._degree>1 ? p1._degree - 1 : 0);
    for (Polynomial::CIt it=p1._terms.begin(); it != p1._terms.end(); it++)
        if (it->_exp>0) p._terms.push_back(derivative(*it));
    return p;
}

Polynomial antiderivative(const Polynomial& p1)
{ Polynomial p;
    p._degree = p1._degree + 1;
    for (Polynomial::CIt it=p1._terms.begin(); it != p1._terms.end(); it++)
        p._terms.push_back(antiderivative(*it));
    return p;
}

//////////////////////////////////////////////////////////////////////
//  Polynomial member functions:

Polynomial::Polynomial(double coef, unsigned exp)
{ if (coef == 0.0)  // the "zero polynomial" has degree -1
{ _terms = TermList(0);
    _degree = -1;
}
else
{ _terms = TermList(1,Term(coef,exp));
    _degree = exp;
}
}

Polynomial& Polynomial::operator+=(const Polynomial& p)
{ *this = *this + p;
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{ *this = *this - p;
    return *this;
}

Polynomial& Polynomial::operator*=(const double x)
{ *this = x * *this;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& p)
{ *this = *this * p;
    return *this;
}

bool Polynomial::operator==(const Polynomial& p) const
{ return _terms == p._terms;
}

bool Polynomial::operator!=(const Polynomial& p) const
{ return _terms != p._terms;
}

double Polynomial::operator()(double x) const
{ CIt it=_terms.begin();
    if (it == _terms.end()) return 0.0;
    double y=it->_coef;
    unsigned e1=it->_exp;
    while (++it != _terms.end())  // Horner's Method
    { int e2=it->_exp;
        y *= pow(x,e1-e2);
        y += it->_coef;
        e1 = e2;
    }
    return y * pow(x,e1);
}

long Polynomial::degree() const
{ return _degree;
}

unsigned Polynomial::terms() const
{ return _terms.size();
}

void Polynomial::reduce()
{ // collects terms and removes those with coefficient equal to 0.0
    if (*this == ZERO) return;
    Polynomial::It it1=_terms.begin(), it2=_terms.begin();
    while (it1 != _terms.end())
    { while (++it2 != _terms.end() && it2->_exp == it1->_exp)
        it1->_coef += it2->_coef;
        if (it1->_coef == 0.0) _terms.erase(it1,it2);
        else _terms.erase(++it1,it2);
        it1 = it2;
    }
    if (_terms.size() == 0) _degree = -1;
    else _degree = _terms.begin()->_exp;
}

//////////////////////////////////////////////////////////////////////
//  static constants:

const Polynomial Polynomial::ZERO(0.0);   // the "zero polynomial"
const Polynomial Polynomial::ONE(1.0,0);  // the monomial p(x) = 1
const Polynomial Polynomial::X(1.0,1);    // the monomial p(x) = x


int main() {
    return 0;
}
