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
         if ( men.size() > 10) return;
         std::cout << "Remaining [ ";
         for (int man: men) {
            std::cout << man << " ";
         }
         std::cout << " ] " << std::endl;
      };
      
      printRemaining();
      while (men.size() > 1) {
         auto it = men.begin();
         std::cout << "killing man " << *it << std::endl;
         men.erase(it);
         it = men.begin();
         men.push_back(*it);
         men.erase(it);
         printRemaining();
      }

      std::cout << "Last Man standing: " << men.at(0) << std::endl;
      return 0;
   }
   catch(...) {
      std::cout << "what the heck are you doing????" << std::endl;
   }
}