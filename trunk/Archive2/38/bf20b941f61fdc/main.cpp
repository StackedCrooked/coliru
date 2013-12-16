 
#include <iostream>
#include <typeinfo>
#include <vector>
#include <assert.h>


struct doublet {

    doublet(double val1 = 0, double val2 = 0) {
        dob[0] = val1;
        dob[1] = val2;
    }

    template< class Expr >
    doublet& operator=(Expr const& x){
        dob[0] = x[0];
        dob[1] = x[1];
        return *this;
    }

    const double&  operator[](unsigned ix) const  {
      /*
       * BUG HERE
       */
      //assert(ix<2);
      return dob[ix];
    }
    

    void print(){
        std::cout << (*this)[0] << std::endl;
        std::cout << (*this)[1] << std::endl;
    }
private:
      double dob[2];
};

struct plus {

    static double  apply( double a,  double b)  {
        return a + b;
    }
};

struct minus {

      static double  apply(double a, double b){
        return a - b;
    }
};



template <class L, class OpTag, class R>
struct Expression {

    Expression (L const& l, R const& r) :l(l),r(r){}

    L const& l;
    R const& r;

    typedef const double result_type;

    result_type operator[](unsigned ix) const {
        return  OpTag::apply(l[ix],r[ix]);
    }

};

template <class L, class R>
Expression<L,plus,R> operator+(L const& l, R const& r){
    return Expression<L,plus,R>(l,r);
}

template <class L, class R>
Expression<L,minus,R> operator-(L const& l, R const& r){
    return Expression<L,minus,R>(l,r);
}

int main()
{
    doublet a(4.0,1.0), b(5.1,3.3), c(7.4,5.2);

    Expression<Expression<doublet, plus, doublet>, plus, doublet> 
    k = b + a + c;
    std::cout << k[0] << " " << k[1] << std::endl;

}