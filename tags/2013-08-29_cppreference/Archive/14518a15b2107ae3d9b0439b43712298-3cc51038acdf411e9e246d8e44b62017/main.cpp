#include <iostream>

int main()
{
   class Foo
   {
      int x;
      int y;
   };
   Foo o = {1, 2};
   std::cout << o.x << "," << o.y << "\n";
   return 0;
}
