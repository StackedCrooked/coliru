#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <omp.h>
#include <boost/bind.hpp>

typedef std::list<std::string> strlist;

void find(strlist *lst, std::string search);

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

// finding a string - boost way, much less code
void find(strlist *lst, std::string search)
{
   strlist::iterator it = std::find_if(lst->begin(), lst->end(), boost::bind(std::equal_to<std::string>(), _1, search));
   std::cout << "'" << search << (it != lst->end() ? "' found!" : "' not found!") << std::endl;
}