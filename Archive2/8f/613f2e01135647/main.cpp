#include <iostream>
#include <vector>
#include <boost/bind.hpp>

struct add{double operator()(double x, double y) const{return x+y;}};  
struct multiply{double operator()(double x, double y) const{return x*y;}};  



template <typename Bind>
struct F  
{  
  Bind func;  
  
  F(const Bind& bind):func(bind){}
  
  double operator()(const std::vector<double>& args) const  
  {  
    return func(args[0],args[1],args[2]); //Skipping boundary check  
  }  
};

template <typename Bind>
F<Bind> make_function(const Bind& bind)
{
    return F<Bind>(bind);
}

int main()
{
    std::vector<double> args{1.,2.,3.};
    auto f_obj=make_function(boost::bind<double>(multiply(), boost::bind<double>(add(), _1, _2), _3));  
    std::cout << f_obj(args) << std::endl;  
}
