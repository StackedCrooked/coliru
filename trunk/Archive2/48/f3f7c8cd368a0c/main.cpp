#include <iostream>

int main(){
   
   auto l = [](){ int i = 0;
                i++;
                return 5;};
   int h = l();
   std::cout << h;
}

