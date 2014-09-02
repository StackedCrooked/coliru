#include <iostream>
#include <random>
#include <cmath>

const double pi = 3.1428;

template<class rnd_gen>
class BoxMull
{
    rnd_gen a;
    double range;
public://
    BoxMull(rnd_gen rnd)
    {
        a = rnd;
        range = rnd.max()-rnd.min();
    }
    double operator()()
    {
        static int flag = 0;
        static double n1;
        static double n2;
        if(flag == 0)
        {
            double U1 = a()/range;
            double U2 = a()/range;
            n1 = sqrt(-2*log(U1))*sin(2*pi*U2);
            n2 = sqrt(-2*log(U1))*cos(2*pi*U2);
            flag = 1;
            return n1;
        }
        else
        {
            flag = 0;
            return n2;
        }
    }
};

template<typename norm_gen>
class EulMaru
{
    double s0, mu, sig, T;
    norm_gen N;
public:
    EulMaru(double init_stock, double drift, double vol, double maturity, norm_gen n )
    {
        s0 = init_stock;
        mu = drift;
        sig = vol;
        T = maturity;
        N = n;
    }
    double operator()(double dt)//Returns a final stock price
    {
        double x = s0;
        int num_of_divs = T/dt;
        double sq_dt = sqrt(dt);
        for(int i = 1; i<=num_of_divs; ++i)
        {
            x *= 1 + mu*dt + sig*N()*sq_dt;
        }
        return x;
    }
};

int main ()
{
  std::mt19937 rr;//Object which generates random numbers using Mersenne twister
  BoxMull <decltype(rr)> b(rr);//Object which generates (0,1) normal rvs based on rvs from mt engine
  EulMaru <decltype(b)> e(50, 0.1, 0.3, 1.0, b);
  return 0;
}