#include <iostream>
#include <complex>

template <typename T, typename U, typename V>
class X {
    public:
      T in;
      U a;
      V b;
      
      typedef decltype(in * a * b) Y;
      
      Y out;
      
      X(T _in, U _a, V _b) : 
        in(_in), 
        a(_a),
        b(_b)
      {
          out = in * a * b;
      }
};


int main() 
{   
    std::complex<float> a = 1;
    float b = 2;
    
    X<float, std::complex<float>, float > aa(b, a, 3);
        
    std::cout << aa.out << std::endl;
}