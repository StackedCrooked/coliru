    #include <cmath>
    
    struct foo {
      static constexpr double a = std::cos(3.);
      static constexpr double c = std::exp(3.);
      static constexpr double d = std::log(3.);
      static constexpr double e1 = std::asin(1.);
      static constexpr double h = std::sqrt(.1);
      static constexpr double p = std::pow(1.3,-0.75);
      static constexpr double es = std::sinh(1.);
      static constexpr double ec = std::cosh(1.);
      static constexpr double et = std::tanh(1.);
      static constexpr double zs = std::asinh(1.2);
      static constexpr double zc = std::acosh(1.2);
      static constexpr double zt = std::atanh(.5);
      static constexpr double er = std::erfc(0.45f);
    };
    
    int main()
    {
    }