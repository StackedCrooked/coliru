#include <iostream>

void g(double& d) {
  d += 10;
  std::cout << d << '\n';
}

template <int n>
class A
    {
        enum {N = n};
        double mVariable;
    
        template <class T, int i>
        struct fImpl {
          static void call(T& t, A& a) {
            g(a.mVariable);
            fImpl<T, i+1>::call(t, a);
          }
        };

        template<class T>
        struct fImpl<T,N> {
          static void call(T&, A&)  {} // stop loop when hit N.
        };

     public:

        template<class T, int i>
        void f(T& t)
        {
            fImpl<T, i+1>::call(t,*this);
        }
   
    };


int main() {
  A<13> a;
  double d = 42.0;
  a.f<double, 2>(d);
}