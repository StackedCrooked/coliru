#include <iostream>
#include <string>
void print_row(unsigned int cnt)
{
     while(cnt --> 0) std::cout << "* "; // or for loop, I just think --> is cute
     std::cout << '\n';
}

namespace impl {
    void triangle_(int maxrow, int row)
    {
         if (row >= maxrow)
         {
             print_row(row);
         }
         else
         {
             std::cout << std::string(maxrow-row, ' ');
             print_row(row);
    
             triangle_(maxrow, row+1);
    
             std::cout << std::string(maxrow-row, ' ');
             print_row(row);
         }
    }
}

void triangle(int maxrow)
{
    impl::triangle_(maxrow, 0);
}

int main()
{
     std::cout << "Enter total lines: ";
     int x = 10;
     //std::cin >> x;
     std::cout << '\n';
     triangle(x);
}