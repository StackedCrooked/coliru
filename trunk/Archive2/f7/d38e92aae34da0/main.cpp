#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
   try {
      unsigned long nMen = argc > 1 ? std::stoul(std::string(argv[1])) : 1000;
      if (nMen <= 1) {
         std::cout << "You dummy, pick something else..." << std::endl;
         return -1;
      }
      std::vector<unsigned long> men(nMen);
      std::iota(men.begin(), men.end(), 1);
      
      auto printRemaining = [&](){
         std::cout << "Remaining [ ";
         for (int man: men) {
            std::cout << man << " ";
         }
         std::cout << " ] " << std::endl;
      };
      
      printRemaining();
      bool killEven = true;
      unsigned long index = 0;
      auto isPoorAhole = [&](unsigned long) {
        ++index;
        return (index % 2 == 0) ? killEven : !killEven;
      };
      while (men.size() > 1) {
         men.erase(std::remove_if(men.begin(), men.end(), isPoorAhole), men.end());
         killEven = ~killEven;
         printRemaining();
      }
      std::cout << "Last Man standing: " << men.at(0) << std::endl;
      return 0;
   }
   catch(...) {
      std::cout << "what the heck are you doing????" << std::endl;
   }
}