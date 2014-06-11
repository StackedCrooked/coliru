#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   double x = 1;
   double f = (1 - powf(x, 2));
   
   std::cout<< x << " " << f << "\n";
   
   if (f > 0) {
       
       std::cout<<sqrt(f);
       
   } else {
       
      std::cout << "No dice\n";
       
   }
   
   return 0;
}
