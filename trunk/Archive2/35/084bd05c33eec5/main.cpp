 #include <iostream>
 
 #define swap(a,b) (a)=(a)+(b);b=(a)-(b);(a)=(a)-(b);
 
 void broken_swap(int a, int b)
 {
     std::cout << a << " " << b << "\n";
     a += b;
     b = a - b;
     a = a - b;
     std::cout << a << " " << b << "\n";
 }
 

 int main()
 {
     int a = 5;
     int b = 10;
     swap(a, b);
     std::cout << a << " " << b;
 }