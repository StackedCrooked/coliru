#include <iostream>
 
int main()
{
    // while loop with a single statement
    int i = 0;
    while (i < 10)
         i++;
    std::cout << i << '\n';
 
    // while loop with a compound statement
    int j = 2;
    while (j < 9) {
        std::cout << j << ' ';
        j += 2;
    }
    std::cout << '\n';
 
   // while loop with a declaration condition
   char cstr[] = "Hello";
   int k = 0;
   while(char c = cstr[k++])
       std::cout << c;
   std::cout << '\n';
}