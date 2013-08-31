#include <iostream>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

template < typename T, T t >
struct function_object
{
    template < typename... TT >
    auto operator() (TT&&... pp) -> decltype(t(pp...))
    {
        return t(std::forward<TT>(pp)...);
    }
};

struct fs {
    double s;
    fs(double state) : s(state) {}
    double operator()(double x) {
        return x*s;
    }
};

struct ff {
    double operator()(double x, double state) const {
        return x * state;
    }
};

double fb(double x, double state) {
    return x*state;
}

template <typename Function>
void measure(char const* what, Function function)
{
    const auto stp1 = high_resolution_clock::now();
    double sresult(0.0);
    for(double x=0.0; x< 1.0e8; ++x) {
        sresult += function(x);
    }
    const auto stp2 = high_resolution_clock::now();
    const auto sd = duration_cast<milliseconds>(stp2 - stp1);  
    cout << "in " << sd.count() << " ms, "; 
    cout << what << "; result = " << sresult << endl;
}


int main() {
  double state=3.1415926;

  measure("functor as a struct", fs(state));
  measure("function through bind", std::bind(&fb, _1, state));
  measure("function through template binder", std::bind(function_object<decltype(fb)&,fb>(), _1, state));
  measure("function object through bind", std::bind(ff(), _1, state));


  {
      const auto stp1 = high_resolution_clock::now();
      double sresult(0.0);
      auto function = std::bind(fb, _1, state);
      for(double x=0.0; x< 1.0e8; ++x) {
          sresult += function(x);
      }
      const auto stp2 = high_resolution_clock::now();
      const auto sd = duration_cast<milliseconds>(stp2 - stp1);  
      cout << "in " << sd.count() << " ms, "; 
      cout << "embedded bind with function; result = " << sresult << endl;
  }
  {
      const auto stp1 = high_resolution_clock::now();
      double sresult(0.0);
      auto function = std::bind(&fb, _1, state);
      for(double x=0.0; x< 1.0e8; ++x) {
          sresult += function(x);
      }
      const auto stp2 = high_resolution_clock::now();
      const auto sd = duration_cast<milliseconds>(stp2 - stp1);  
      cout << "in " << sd.count() << " ms, "; 
      cout << "embedded bind with function pointer; result = " << sresult << endl;
  }    

  return 0;
}
