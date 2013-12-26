#include <iostream>
#include <sstream>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace std;

int main(){
    typedef boost::mt19937 rnd_type;
    typedef boost::binomial_distribution<> binom;
    typedef boost::poisson_distribution<> Poi;
    rnd_type gen;
    gen.seed(time(0));
    binom ham(1, (double)1/2);
    Poi eggs(10.5);
    
    cout<<ham(gen)<<endl;
    cout<<eggs(gen)<<endl; /*The code freezes here*/
}
