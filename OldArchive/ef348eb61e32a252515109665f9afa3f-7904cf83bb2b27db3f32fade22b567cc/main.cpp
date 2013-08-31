#include <iostream>

int main()
{  
   double radius = 11;  /* Centimeters*/
   double pi  = 3.14;
   double sphere_volume = (4 / 3)  * pi *(radius * radius * radius);
   double surface_area = 5 * pi * radius;
   std::cout << "Volume = " << sphere_volume;
   std::cout << "Area = " << surface_area;
   return 0;
}   