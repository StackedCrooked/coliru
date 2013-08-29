#include <cmath>

template<class choice_type>
double computeK(choice_type choice, double R){
   switch (choice){
      case 1: return 1.0/R;
      case 2: return log(R);
      case 3: return exp(-R);
      case 4: return exp(-R*R);
      case 5: return exp(-R);
      default: return 1.0/R/R;
   }
}

#include <functional>
#include <utility>
#include <iostream>

int main ()  { 
    std::cout << computeK(std::integral_constant<int,1>(), 3.5) << ' ' << computeK(1, 3.5);
    return 0;
}    