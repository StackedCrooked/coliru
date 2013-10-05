#include <iostream>
#include <string>
#include <list>
#include <omp.h>

typedef std::list<std::string> strlist;

// STL find classic way
void find(strlist *lst, std::string search)
{
   bool found = false;
   
   for (strlist::iterator it = lst->begin(); it != lst->end(); it++)
   {
      if (*it == search)
      {
         found = true;
         break;
      }
   }  
   
   std::cout << "'" << search << (found ? "' found!" : "' not found!") << std::endl;
}

int main(int argc, char *argv[])
{
   strlist strings;
   
   strings.push_back("this");
   strings.push_back("is");
   strings.push_back("a list");
   strings.push_back("of strings");
   
   double start = omp_get_wtime();
   find(&strings, "a list");
   find(&strings, "this");
   std::cout << "* benchmark: " << omp_get_wtime() - start << "seconds" << std::endl;
   
   return 0;
}
