#include <boost/numeric/ublas/vector.hpp>
#include <boost/assign.hpp>
#include <iostream>
using namespace boost::numeric::ublas;

class A{
 protected:
    vector< double > a_;
 public:
    A( vector< double > a ) :
        a_( a ) {};
};

class B : public A{
    _init init_vec()
    {
        using namespace boost::assign;
        std::vector<int> init;
        init += list_of(1)(2)(3);
    }
 public:
    B() : A(init_vec())
    { 
    };
};